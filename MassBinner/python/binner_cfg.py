import FWCore.ParameterSet.Config as cms
import FWCore.ParameterSet.VarParsing as VarParsing

process = cms.Process("Demo")

process.load("FWCore.MessageService.MessageLogger_cfi")

process.load("Configuration.StandardSequences.GeometryRecoDB_cff")
process.load("Configuration.StandardSequences.FrontierConditions_GlobalTag_cff")

process.maxEvents = cms.untracked.PSet(input=cms.untracked.int32(-1))

process.MessageLogger.cerr.FwkReport.reportEvery = cms.untracked.int32(1)

options = VarParsing.VarParsing('standard')
# options = VarParsing.VarParsing("analysis")

options.register('inputFile',
       "file:name1.root",
       VarParsing.VarParsing.multiplicity.singleton,
       VarParsing.VarParsing.varType.string,
       "File containing a list of the EXACT location of the input file"
       )

options.parseArguments()
infilename = str(options.inputFile).split('/')[-1]
print(infilename)
options.inputFile = "file:"+options.inputFile
process.source = cms.Source(
    "PoolSource",
    # replace 'myfile.root' with the source file you want to use
    fileNames=cms.untracked.vstring(
	options.inputFile
    ),
)


process.massfilter = cms.EDFilter(
    #"Photon_Skimmer",
    "MassBinner",
    #"GenEventDump",
    genParticles=cms.InputTag("genParticles"),
    minMass = cms.double(0.56),
    maxMass = cms.double(0.64),
    #minMass = cms.double(0),
    #maxMass = cms.double(2),
    partId = cms.int32(36)
)
# Define the sequence
process.filterSequence = cms.Sequence(process.massfilter)

# Path for the filtering
process.p = cms.Path(process.filterSequence)
process.out = cms.OutputModule("PoolOutputModule",
    fileName = cms.untracked.string('output.root'),
    SelectEvents = cms.untracked.PSet(SelectEvents = cms.vstring('p')),   
)
process.outpath = cms.EndPath(process.out)
