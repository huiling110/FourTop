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
