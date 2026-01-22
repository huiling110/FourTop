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

from fourtop.stage4.datacards import (
    getSysDic,
    getProSysDic,
    addLumi,
    addProcessNormalization,
    remove0Process,
    write_shape_datacard,
    DatacardWriter,
)

from fourtop.stage4.systematics import (
    getMCSubPro,
    add_histograms_to_rootfile,
    addUpDownToFile,
    addTESToFile,
    addJERToFile,
    addMETToFile,
    addEESToFile,
    addJESToFile,
    getJESHistForDir,
)

from fourtop.stage4.combine import (
    ensure_dir,
    ensure_dir_with_fallback,
    ensure_writable_carddir,
    get_workspace_file,
    runCommand,
    cardToWorkspaces,
)
