cmake_minimum_required(VERSION 3.18)

project(
    run_objectSelection
    VERSION 0.0
    LANGUAGES CXX
)

set(CMAKE_CXX_COMPILER "/cvmfs/cms.cern.ch/slc7_amd64_gcc900/external/gcc/9.3.0/bin/gcc")

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CXXFLAGS -O3 -Wall -fPIC -g -std=c++17)

include_directories(include
    /cvmfs/cms.cern.ch/slc7_amd64_gcc900/cms/cmssw/CMSSW_12_2_4/external/slc7_amd64_gcc900/bin/../../../../../../../slc7_amd64_gcc900/lcg/root/6.22.08-8d9ab2b279c3f35e6100d909611c3c2f/include
    /cvmfs/cms.cern.ch/slc7_amd64_gcc900/external/py3-correctionlib/2.0.0-0c4f44c8dd5561d8c0660135feeb81f4/lib/python3.9/site-packages/correctionlib/include
)

# Set the ROOTCFLAGS, ROOTLIBS, and ROOTGLIBS variables
# execute_process(
#     COMMAND root-config --cflags
#     OUTPUT_VARIABLE ROOTCFLAGS
#     OUTPUT_STRIP_TRAILING_WHITESPACE
# )
# execute_process(
#     COMMAND root-config --libs
#     OUTPUT_VARIABLE ROOTLIBS
#     OUTPUT_STRIP_TRAILING_WHITESPACE
# )
# execute_process(
#     COMMAND root-config --glibs
#     OUTPUT_VARIABLE ROOTGLIBS
#     OUTPUT_STRIP_TRAILING_WHITESPACE
# )
# Print the variables (optional)
set(ROOTCFLAGS -pthread -std=c++17 -m64 -I/cvmfs/cms.cern.ch/slc7_amd64_gcc900/cms/cmssw/CMSSW_12_2_4/external/slc7_amd64_gcc900/bin/../../../../../../../slc7_amd64_gcc900/lcg/root/6.22.08-8d9ab2b279c3f35e6100d909611c3c2f/include)
set(ROOTLIBS -L/cvmfs/cms.cern.ch/slc7_amd64_gcc900/cms/cmssw/CMSSW_12_2_4/external/slc7_amd64_gcc900/bin/../../../../../../../slc7_amd64_gcc900/lcg/root/6.22.08-8d9ab2b279c3f35e6100d909611c3c2f/lib -lCore -lImt -lRIO -lNet -lHist -lGraf -lGraf3d -lGpad -lROOTVecOps -lTree -lTreePlayer -lRint -lPostscript -lMatrix -lPhysics -lMathCore -lThread -lMultiProc -lROOTDataFrame -pthread -lm -ldl -rdynamic)
set(ROOTGLIBS -L/cvmfs/cms.cern.ch/slc7_amd64_gcc900/cms/cmssw/CMSSW_12_2_4/external/slc7_amd64_gcc900/bin/../../../../../../../slc7_amd64_gcc900/lcg/root/6.22.08-8d9ab2b279c3f35e6100d909611c3c2f/lib -lGui -lCore -lImt -lRIO -lNet -lHist -lGraf -lGraf3d -lGpad -lROOTVecOps -lTree -lTreePlayer -lRint -lPostscript -lMatrix -lPhysics -lMathCore -lThread -lMultiProc -lROOTDataFrame -pthread -lm -ldl -rdynamic)
message("ROOTCFLAGS: ${ROOTCFLAGS}")
message("ROOTLIBS: ${ROOTLIBS}")
message("ROOTGLIBS: ${ROOTGLIBS}")

# Run the correction config command to get the flags and libraries
# execute_process(
#     COMMAND correction config --cflags
#     OUTPUT_VARIABLE CORRECTIONLIB_FLAGS
#     OUTPUT_STRIP_TRAILING_WHITESPACE
# )
# execute_process(
#     COMMAND correction config --ldflags --rpath
#     OUTPUT_VARIABLE CORRECTIONLIB_LIB
#     OUTPUT_STRIP_TRAILING_WHITESPACE
# )
# Set the flags and libraries as variables
#???can not set in this way???
# set(CORRECTIONLIB_FLAGS ${CORRECTIONLIB_FLAGS})
# set(CORRECTIONLIB_LIB ${CORRECTIONLIB_LIB})
# Print the variables (optional)
message("CORRECTIONLIB_FLAGS: ${CORRECTIONLIB_FLAGS}")
message("CORRECTIONLIB_LIB: ${CORRECTIONLIB_LIB}")
set(CORRECTIONLIB_FLAGS -std=c++17 -I/cvmfs/cms.cern.ch/slc7_amd64_gcc900/external/py3-correctionlib/2.0.0-0c4f44c8dd5561d8c0660135feeb81f4/lib/python3.9/site-packages/correctionlib/include)
set(CORRECTIONLIB_LIB -L/cvmfs/cms.cern.ch/slc7_amd64_gcc900/external/py3-correctionlib/2.0.0-0c4f44c8dd5561d8c0660135feeb81f4/lib/python3.9/site-packages/correctionlib/lib -lcorrectionlib -Wl,-rpath,/cvmfs/cms.cern.ch/slc7_amd64_gcc900/external/py3-correctionlib/2.0.0-0c4f44c8dd5561d8c0660135feeb81f4/lib/python3.9/site-packages/correctionlib/lib)


# Set the XGBOOST_LIB and XGBOOST_FLAGS variables
set(XGBOOST_LIB -L/cvmfs/cms.cern.ch/slc7_amd64_gcc700/external/py2-xgboost/0.80-ikaegh/lib/python2.7/site-packages/xgboost/lib/ -lxgboost)
set(XGBOOST_FLAGS -I/cvmfs/cms.cern.ch/slc7_amd64_gcc700/external/py2-xgboost/0.80-ikaegh/lib/python2.7/site-packages/xgboost/rabit/include/)
# Print the variables (optional)
message("XGBOOST_LIB: ${XGBOOST_LIB}")
message("XGBOOST_FLAGS: ${XGBOOST_FLAGS}")

#TMVA
set(TMVALIBS -lTMVA)

# Gather all the source files in src/
file(GLOB SOURCES "src/*.C")

# Create a library from the source files
add_library(objecSelection ${SOURCES})
# target_link_libraries(objecSelection PUBLIC ROOT::Physics ${XGBOOST_LIB} ${CORRECTIONLIB_LIB} ${TMVALIBS})
target_compile_options(objecSelection PRIVATE ${CXXFLAGS}  ${ROOTCFLAGS} ${XGBOOST_FLAGS} ${CORRECTIONLIB_FLAGS})
target_link_libraries(objecSelection PUBLIC ${ROOTLIBS} ${ROOTGLIBS} ${XGBOOST_LIB} ${CORRECTIONLIB_LIB} ${TMVALIBS})

add_compile_options(-O3 -Wall -fPIC -g -std=c++17)
add_compile_options(-pthread -m64)

# Specify the executable for the test code
add_executable(run_objectSelection apps/run_objectSelection.C)
# target_compile_options(run_objectSelection PRIVATE ${ROOTCFLAGS})
target_compile_options(run_objectSelection PRIVATE ${CXXFLAGS} ${ROOTCFLAGS} ${XGBOOST_FLAGS})
target_link_libraries(run_objectSelection PRIVATE objecSelection ${ROOTLIBS} ${ROOTGLIBS} ${XGBOOST_LIB} ${CORRECTIONLIB_LIB} ${TMVALIBS})
