cmake_minimum_required(VERSION 3.1)

project(objectSelection VERSION 1.0
                  DESCRIPTION "Building objectSelection using cmake"
                  LANGUAGES CXX)

add_executable(run_objectTSelectorForNanoAOD  run_objectTSelectorForNanoAOD.C objectTSelectorForNanoAOD.C objectTSelectorForNanoAOD.h utilityFuctions.C utilityFunctions.h)