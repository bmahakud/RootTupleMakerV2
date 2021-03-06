#ifndef RootTupleMakerV2Electrons
#define RootTupleMakerV2Electrons

#include "FWCore/Framework/interface/EDProducer.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "FWCore/Utilities/interface/InputTag.h"
#include "DataFormats/Common/interface/ValueMap.h"
#include "DataFormats/Common/interface/EDCollection.h"
#include "DataFormats/PatCandidates/interface/VIDCutFlowResult.h"
#include "DataFormats/PatCandidates/interface/Electron.h"
#include "DataFormats/EcalRecHit/interface/EcalRecHitCollections.h"

class RootTupleMakerV2_Electrons : public edm::EDProducer {
 public:
  explicit RootTupleMakerV2_Electrons(const edm::ParameterSet&);

 private:
  void produce( edm::Event &, const edm::EventSetup & );
  const edm::InputTag trkInputTag;
  edm::EDGetTokenT<std::vector<pat::Electron> >electronInputToken_;
  edm::EDGetTokenT<reco::VertexCollection> vtxInputToken_;
  edm::EDGetTokenT<double> rhoInputToken_;
  edm::EDGetTokenT<edm::ValueMap<bool> > electronVetoIdMapToken_;
  edm::EDGetTokenT<edm::ValueMap<bool> > electronLooseIdMapToken_;
  edm::EDGetTokenT<edm::ValueMap<bool> > electronMediumIdMapToken_;
  edm::EDGetTokenT<edm::ValueMap<bool> > electronTightIdMapToken_;
  edm::EDGetTokenT<edm::ValueMap<bool> > electronHEEPIdMapToken_;
  edm::EDGetTokenT<edm::ValueMap<vid::CutFlowResult> > eleVetoIdCutFlowResultMapToken_;
  edm::EDGetTokenT<edm::ValueMap<vid::CutFlowResult> > eleLooseIdCutFlowResultMapToken_;
  edm::EDGetTokenT<edm::ValueMap<vid::CutFlowResult> > eleMediumIdCutFlowResultMapToken_;
  edm::EDGetTokenT<edm::ValueMap<vid::CutFlowResult> > eleTightIdCutFlowResultMapToken_;
  edm::EDGetTokenT<edm::ValueMap<vid::CutFlowResult> > eleHEEPIdCutFlowResultMapToken_;
  edm::EDGetTokenT<edm::ValueMap<float> > heep70trkIsolMapToken_;
  edm::EDGetTokenT<reco::BeamSpot> beamSpotInputToken_;
  edm::EDGetTokenT<EcalRecHitCollection> ebReducedRecHitsInputToken_;
  edm::EDGetTokenT<EcalRecHitCollection> eeReducedRecHitsInputToken_;
  // for 03Feb2017 re-miniaod
  edm::EDGetTokenT<bool> dupEcalClustersToken_;
  edm::EDGetTokenT<edm::EDCollection<DetId> > ecalMultiAndGSGlobalRecHitEBHitsNotReplacedToken_;
  const double          electronIso, muonPt, muonIso;
  const std::string     muonID;
  const edm::InputTag   singleEleTriggerMatchTag, singleEleTriggerMatchWP80Tag, doubleEleTriggerMatchTag;
  const std::string     prefix, suffix;
  const unsigned int    maxSize;

  typedef std::vector< edm::Handle< edm::ValueMap<double> > > IsoDepositVals;
};

#endif
