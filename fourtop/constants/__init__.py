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
