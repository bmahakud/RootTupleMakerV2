import FWCore.ParameterSet.Config as cms

rootTupleTriggerObjects= cms.EDProducer("RootTupleMakerV2_TriggerObjects",
    TriggerBitsTag = cms.InputTag("TriggerResults","","HLT"),
    TriggerObjectsTag = cms.InputTag("selectedPatTrigger"),
    Prefix = cms.string("HLT"),
    Suffix = cms.string('')
)

