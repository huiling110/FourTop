"""
JES (Jet Energy Scale) Configuration
=====================================

JES variation sources and subprocess skip lists for the FourTop analysis.

IMPORTANT: JESVariationList MUST match MV::JES_uncer in
makeVariables_goodCode/include/inputMap_MV.h. Use validate_jes_list()
to verify synchronization before running JES jobs.

Usage:
    from fourtop.constants.jes import JESVariationList, SKIP_SUBPROCESSES

    for source in JESVariationList:
        process_jes_variation(source)
"""

import os
import re
from typing import Dict, List

# =============================================================================
# JES Variation Sources
# =============================================================================

#: JES variation sources (MUST match C++ MV::JES_uncer array)
#: Format: {JES_source_name}_AK4PFchs
JESVariationList: List[str] = [
    "AbsoluteMPFBias_AK4PFchs",
    "AbsoluteScale_AK4PFchs",
    "AbsoluteStat_AK4PFchs",
    # "FlavorQCD_AK4PFchs",  # Replaced by FlavorPure* decomposition
    "Fragmentation_AK4PFchs",
    "PileUpDataMC_AK4PFchs",
    "PileUpPtBB_AK4PFchs",
    "PileUpPtEC1_AK4PFchs",
    "PileUpPtEC2_AK4PFchs",
    "PileUpPtHF_AK4PFchs",
    "PileUpPtRef_AK4PFchs",
    "RelativeFSR_AK4PFchs",
    "RelativeJEREC1_AK4PFchs",
    "RelativeJEREC2_AK4PFchs",
    "RelativeJERHF_AK4PFchs",
    "RelativePtBB_AK4PFchs",
    "RelativePtEC1_AK4PFchs",
    "RelativePtEC2_AK4PFchs",
    "RelativePtHF_AK4PFchs",
    "RelativeBal_AK4PFchs",
    "RelativeSample_AK4PFchs",
    "RelativeStatEC_AK4PFchs",
    "RelativeStatFSR_AK4PFchs",
    "RelativeStatHF_AK4PFchs",
    "SinglePionECAL_AK4PFchs",
    "SinglePionHCAL_AK4PFchs",
    "TimePtEta_AK4PFchs",
    "FlavorPureGluon_AK4PFchs",   # FlavorQCD decomposition
    "FlavorPureQuark_AK4PFchs",   # FlavorQCD decomposition (uds)
    "FlavorPureCharm_AK4PFchs",   # FlavorQCD decomposition
    "FlavorPureBottom_AK4PFchs",  # FlavorQCD decomposition
]

# =============================================================================
# Subprocess Skip Lists
# =============================================================================

#: Subprocesses to SKIP per channel - negligible contribution, add noise to systematics
#: Skip criteria: < 1% of parent process AND < 1 event in region
SKIP_SUBPROCESSES: Dict[str, List[str]] = {
    '1tau1l': [
        'TTBB_4f_TTToSemiLeptonic',  # 0.3% of ttbb, ~0.1-0.3 events
        'ttbar_1l',                   # 0.7% of tt in SR, ~0.1 events (but 1 in CR12)
    ],
    '1tau0l': [
        # Add 1tau0l specific skips here after analysis
    ],
    '1tau2l': [
        # TTBB samples don't exist in 1tau2l MV output (no entries pass selection)
        'TTBB_4f_TTTo2L2Nu',
        'TTBB_4f_TTToHadronic',
        'TTBB_4f_TTToSemiLeptonic',
    ],
}

# =============================================================================
# Validation Functions
# =============================================================================

def validate_jes_list(cpp_header_path: str = None) -> bool:
    """
    Validate that Python JESVariationList matches C++ MV::JES_uncer array.

    Parses the C++ header file and compares with Python list to catch
    synchronization errors that would cause wrong JES variations to be applied.

    Args:
        cpp_header_path: Path to inputMap_MV.h. If None, uses default relative path.

    Returns:
        True if lists match, raises ValueError if mismatch found.

    Raises:
        ValueError: If JES lists don't match between Python and C++.

    Usage:
        from fourtop.constants.jes import validate_jes_list
        validate_jes_list()  # Call before submitting JES jobs
    """
    if cpp_header_path is None:
        # Default path relative to fourtop package
        this_dir = os.path.dirname(os.path.abspath(__file__))
        cpp_header_path = os.path.join(
            this_dir, '..', '..', 'makeVariables_goodCode', 'include', 'inputMap_MV.h'
        )

    if not os.path.exists(cpp_header_path):
        print(f"WARNING: Cannot validate JES list - C++ header not found: {cpp_header_path}")
        return True

    # Parse C++ header to extract JES_uncer array
    with open(cpp_header_path, 'r') as f:
        content = f.read()

    # Find the JES_uncer array definition
    match = re.search(r'JES_uncer\s*=\s*\{([^}]+)\}', content, re.DOTALL)
    if not match:
        print("WARNING: Cannot find JES_uncer array in C++ header")
        return True

    # Extract source names from C++ array
    array_content = match.group(1)
    cpp_sources = []
    for line in array_content.split('\n'):
        # Skip commented lines
        line = line.strip()
        if line.startswith('//'):
            continue
        # Extract quoted string
        string_match = re.search(r'"([^"]+)"', line)
        if string_match:
            cpp_sources.append(string_match.group(1))

    # Compare with Python list
    if len(cpp_sources) != len(JESVariationList):
        raise ValueError(
            f"JES list length mismatch!\n"
            f"  C++ MV::JES_uncer has {len(cpp_sources)} sources\n"
            f"  Python JESVariationList has {len(JESVariationList)} sources\n"
            f"  Fix: Synchronize lists in inputMap_MV.h and fourtop/constants/jes.py"
        )

    for i, (cpp_src, py_src) in enumerate(zip(cpp_sources, JESVariationList)):
        if cpp_src != py_src:
            raise ValueError(
                f"JES list mismatch at index {i}!\n"
                f"  C++ MV::JES_uncer[{i}] = '{cpp_src}'\n"
                f"  Python JESVariationList[{i}] = '{py_src}'\n"
                f"  Fix: Synchronize lists in inputMap_MV.h and fourtop/constants/jes.py"
            )

    return True


def get_jes_source_name(source: str) -> str:
    """
    Extract JES source name without _AK4PFchs suffix.

    Args:
        source: Full JES source name (e.g., 'AbsoluteMPFBias_AK4PFchs')

    Returns:
        Source name without suffix (e.g., 'AbsoluteMPFBias')
    """
    return source.replace('_AK4PFchs', '')


def should_skip_subprocess(subprocess: str, channel: str) -> bool:
    """
    Check if a subprocess should be skipped for JES processing.

    Args:
        subprocess: Subprocess name (e.g., 'TTBB_4f_TTToSemiLeptonic')
        channel: Channel name ('1tau0l', '1tau1l', '1tau2l')

    Returns:
        True if subprocess should be skipped.
    """
    skip_list = SKIP_SUBPROCESSES.get(channel, [])
    return subprocess in skip_list
