"""
FourTop Plotting Package
========================

ROOT plotting utilities for validation and publication plots.

Modules:
    style - TDR style setup, CMS text
    stack - Stacked histogram building
    validation - Data/MC validation plots
    postfit - Post-fit distribution plots
"""

from fourtop.plotting.stack import (
    COLOUR_PER_SAMPLE,
    getHists,
    getSystVariation,
    addStatisticUncer,
    getErrorPlot,
    getHistToData,
    getIntegral,
    setUpStack,
)

from fourtop.plotting.style import (
    setTDRStyle,
    setMyStyle,
    addCMSTextToPad,
    addCMSTextToCan,
    getMyLegend,
    addRegionLabel,
    addFitTypeLabel,
)

from fourtop.plotting.labels import (
    PROCESS_LABELS_PAPER,
    REGION_LABELS,
    get_process_label,
    get_signal_label,
    get_region_label,
    get_fit_type_label,
)
