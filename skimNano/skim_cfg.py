
import FWCore.ParameterSet.Config as cms

process = cms.Process("SKIM")

# Load standard configurations
process.load("FWCore.MessageService.MessageLogger_cfi")
process.load("Configuration.StandardSequences.MagneticField_cff")
process.load("Configuration.StandardSequences.GeometryRecoDB_cff")
process.load("Configuration.StandardSequences.FrontierConditions_GlobalTag_cff")

# Set the global tag (adjust this according to your dataset)
process.GlobalTag.globaltag = '106X_dataRun2_v32'

# Input source
process.source = cms.Source("PoolSource",
    fileNames = cms.untracked.vstring(
        # 'file:input_nanoaod.root'  # Replace with your input NanoAOD file
        # 'root://cms-xrd-global.cern.ch//store/data/Run2017F/BTagCSV/NANOAOD/UL2017_MiniAODv2_NanoAODv9-v1/1210000/1586633B-9F9B-804A-8030-48685D834D98.root',
        'root://xrootd-cms.infn.it//store/data/Run2017B/BTagCSV/NANOAOD/UL2017_MiniAODv2_NanoAODv9-v1/270000/CC6BC2DE-CA64-BB41-B3D0-F47EB7C67FC9.root',
    )
)

# process.maxEvents = cms.untracked.PSet(input = cms.untracked.int32(-1))
process.maxEvents = cms.untracked.PSet(input = cms.untracked.int32(1000))

# Define the skim filter (select events with at least 6 jets)
process.selectedJets = cms.EDFilter("PATJetSelector",
    src = cms.InputTag("slimmedJets"),
    cut = cms.string("pt > 30 && abs(eta) < 2.4")
)

process.jetFilter = cms.EDFilter("CandViewCountFilter",
    src = cms.InputTag("selectedJets"),
    minNumber = cms.uint32(6)
)

# Output module
process.out = cms.OutputModule("PoolOutputModule",
    fileName = cms.untracked.string('skimmed_nanoaod.root'),
    SelectEvents = cms.untracked.PSet(
        SelectEvents = cms.vstring('p')
    ),
    outputCommands = cms.untracked.vstring(
        'keep *'  # Keep all branches from the input file
    )
)

# Define the path
process.p = cms.Path(process.selectedJets + process.jetFilter)
# End path
process.e = cms.EndPath(process.out)

# Schedule definition
process.schedule = cms.Schedule(process.p, process.e)
