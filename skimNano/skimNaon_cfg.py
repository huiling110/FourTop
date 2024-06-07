import FWCore.ParameterSet.Config as cms

process = cms.Process("ReadNanoAOD")

# Set the maximum number of events to process (-1 means all events)
process.maxEvents = cms.untracked.PSet(input = cms.untracked.int32(-1))

# Define the source with the specified input files
process.source = cms.Source("PoolSource",
    fileNames = cms.untracked.vstring(
        'root://xrootd-cms.infn.it//store/data/Run2017B/BTagCSV/NANOAOD/UL2017_MiniAODv2_NanoAODv9-v1/270000/CC6BC2DE-CA64-BB41-B3D0-F47EB7C67FC9.root',
        # 'root://xrootd-cms.infn.it//store/data/Run2017B/BTagCSV/NANOAOD/UL2017_MiniAODv2_NanoAODv9-v1/270000/D60B9531-0D37-AD40-BA18-EA194D7B2059.root'
        # Add more files as needed
    )
)

# Load the NanoAOD tools and modules
process.load("PhysicsTools.NanoAOD.nano_cff")

# Define a simple EDAnalyzer to print some information
class SimpleAnalyzer(cms.EDAnalyzer):
    def __init__(self, config):
        super(SimpleAnalyzer, self).__init__(config)
    
    def analyze(self, event, context):
        print("Successfully read an event.")

process.simpleAnalyzer = SimpleAnalyzer(cms.PSet())

# Define the path
process.p = cms.Path(process.simpleAnalyzer)

# Schedule the path
process.schedule = cms.Schedule(process.p)
