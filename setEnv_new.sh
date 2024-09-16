
#!/bin/bash
# Source the CMSSW environment setup script
source /cvmfs/cms.cern.ch/cmsset_default.sh

# Set the CMSSW version and architecture
export SCRAM_ARCH=slc7_amd64_gcc900
export CMSSW_VERSION=CMSSW_12_2_4

# Set the CMSSW base directory
export CMSSW_BASE=/cvmfs/cms.cern.ch/$SCRAM_ARCH/cms/cmssw/$CMSSW_VERSION

# Update PATH to include the CMSSW Python and pip
export PATH=$CMSSW_BASE/bin/$SCRAM_ARCH:$PATH

# Update LD_LIBRARY_PATH to include CMSSW libraries
export LD_LIBRARY_PATH=$CMSSW_BASE/lib/$SCRAM_ARCH:$LD_LIBRARY_PATH

# Update PYTHONPATH to include CMSSW Python packages
export PYTHONPATH=$CMSSW_BASE/python:$PYTHONPATH