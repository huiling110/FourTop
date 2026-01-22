"""
FourTop Utilities Package
=========================

Common utility functions for file I/O, histogram operations, and process filtering.

Modules:
    io - File and directory operations
    histogram - ROOT histogram utilities
    process - Process classification and filtering
    logging - Centralized logging setup
"""

from fourtop.utils.logging import setup_logger, get_logger, set_log_level

from fourtop.utils.io import (
    checkMakeDir,
    runCommand,
    submitJobs,
    getInputDic,
    getInputDicNew,
    getDirDic,
)

from fourtop.utils.process import (
    isData,
    isBG,
    getAllSubPro,
    getSubProDic,
    getSubProScale,
    checkIfOtherYear,
    checkIfInputDic,
    getSumList,
    getSumListFull,
    getSameValues,
    getEraFromDir,
    getChannelFromDir,
    isRun3,
    isRun3Era,
)

from fourtop.utils.histogram import (
    getHistFromFile,
    handle_negative_bins,
    addBGHist,
    addDataHist,
    getYmax,
    getSysList,
    getHistName,
    merge_dicts,
    print_dict_structure,
    getEff,
    getHistFromFileDic,
    sumProDic,
    getSumHist,
)
