"""
FourTop Constants Package
=========================

Physics constants, systematic definitions, and era mappings.

Modules:
    physics - Cross sections, luminosity, branching ratios
    samples - Process mappings, sample definitions
    systematics - MCSys dictionary for CMS Combine
    jes - JES variation sources, skip subprocesses
    era - Era mappings, VFP handling
"""

from fourtop.constants.era import (
    ERAS,
    VFP_ERAS,
    ERA_TO_UL,
    ERA_TO_NANOAOD,
    map_vfp_era,
)

from fourtop.constants.physics import (
    lumiMap,
    crossSectionMap,
    get_cross_section,
    get_luminosity,
)

from fourtop.constants.samples import (
    histoGramPerSample,
    proChannelDic,
    proChannelDic_forCombine,
    ttX_newMap,
    subSumProDic,
    Run3Samples,
    dataDict,
    genSumDic,
    summedProcessList,
    get_process,
    get_process_list,
    is_data_sample,
    is_mc_sample,
)

from fourtop.constants.jes import (
    JESVariationList,
    SKIP_SUBPROCESSES,
    validate_jes_list,
    get_jes_source_name,
    should_skip_subprocess,
)

from fourtop.constants.systematics import (
    MCSYS,
    PROCESS_MC,
    PROCESS_FAKE_TAU,
    PROCESS_FAKE_LEPTON,
    PROCESS_FAKE_TAU_MC,
    CHANNEL_1TAU1L,
    CHANNEL_1TAU0L,
    CHANNEL_1TAU2L,
    CHANNEL_ALL,
    get_systematics_for_channel,
    get_correlated_systematics,
    get_era_dependent_systematics,
    is_process_uncorrelated,
)
