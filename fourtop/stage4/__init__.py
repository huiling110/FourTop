"""
FourTop Stage 4 Package
=======================

Template generation, datacard writing, and CMS Combine operations.

Modules:
    templates - Template ROOT file generation
    datacards - CMS Combine datacard writing
    systematics - JES/TES/MET systematic consolidation
    combine - Combine fit orchestration
    combination - Multi-era combination
"""

from fourtop.stage4.templates import (
    resetNegativeBins,
    addDataHist,
    renameProcessUncorrelatedSys,
    writeTemplateFile,
    buildTemplatePath,
    TemplateBuilder,
)
