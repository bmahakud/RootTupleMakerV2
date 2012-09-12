#include "Leptoquarks/RootTupleMakerV2/interface/RootTupleMakerV2_GenParticles.h"
#include "FWCore/Framework/interface/Event.h"
#include "FWCore/MessageLogger/interface/MessageLogger.h"
#include "DataFormats/HepMCCandidate/interface/GenParticle.h"
#include "TMath.h"

RootTupleMakerV2_GenParticles::RootTupleMakerV2_GenParticles(const edm::ParameterSet& iConfig) :
    inputTag(iConfig.getParameter<edm::InputTag>("InputTag")),
    prefix  (iConfig.getParameter<std::string>  ("Prefix")),
    suffix  (iConfig.getParameter<std::string>  ("Suffix")),
    maxSize (iConfig.getParameter<unsigned int> ("MaxSize"))
{
  produces <std::vector<double> > ( prefix + "Eta"          + suffix );
  produces <std::vector<double> > ( prefix + "Phi"          + suffix );
  produces <std::vector<double> > ( prefix + "P"            + suffix );
  produces <std::vector<double> > ( prefix + "Px"           + suffix );
  produces <std::vector<double> > ( prefix + "Py"           + suffix );
  produces <std::vector<double> > ( prefix + "Pz"           + suffix );
  produces <std::vector<double> > ( prefix + "Pt"           + suffix );
  produces <std::vector<double> > ( prefix + "Energy"       + suffix );
  produces <std::vector<int> >    ( prefix + "PdgId"        + suffix );
  produces <std::vector<double> > ( prefix + "VX"           + suffix );
  produces <std::vector<double> > ( prefix + "VY"           + suffix );
  produces <std::vector<double> > ( prefix + "VZ"           + suffix );
  produces <std::vector<int> >    ( prefix + "NumDaught"    + suffix );
  produces <std::vector<int> >    ( prefix + "Status"       + suffix );
  produces <std::vector<int> >    ( prefix + "MotherIndex"  + suffix );
  produces <std::vector<int> >    ( prefix + "TauDecayMode" + suffix );
}

void RootTupleMakerV2_GenParticles::
produce(edm::Event& iEvent, const edm::EventSetup& iSetup) {

  std::auto_ptr<std::vector<double> >  eta  ( new std::vector<double>()  );
  std::auto_ptr<std::vector<double> >  phi  ( new std::vector<double>()  );
  std::auto_ptr<std::vector<double> >  p  ( new std::vector<double>()  );
  std::auto_ptr<std::vector<double> >  px  ( new std::vector<double>()  );
  std::auto_ptr<std::vector<double> >  py  ( new std::vector<double>()  );
  std::auto_ptr<std::vector<double> >  pz  ( new std::vector<double>()  );
  std::auto_ptr<std::vector<double> >  pt  ( new std::vector<double>()  );
  std::auto_ptr<std::vector<double> >  energy  ( new std::vector<double>()  );
  std::auto_ptr<std::vector<int> >     pdgId ( new std::vector<int>()  );
  std::auto_ptr<std::vector<double> >  vx  ( new std::vector<double>()  );
  std::auto_ptr<std::vector<double> >  vy  ( new std::vector<double>()  );
  std::auto_ptr<std::vector<double> >  vz  ( new std::vector<double>()  );
  std::auto_ptr<std::vector<int> >     numDaught  ( new std::vector<int>()  );
  std::auto_ptr<std::vector<int> >     status  ( new std::vector<int>()  );
  std::auto_ptr<std::vector<int> >     motherIndex  ( new std::vector<int>()  );
  std::auto_ptr<std::vector<int> >     taudecaymode ( new std::vector<int>()  );
  
  //-----------------------------------------------------------------
  if( !iEvent.isRealData() ) {
    edm::Handle<reco::GenParticleCollection> genParticles;
    iEvent.getByLabel(inputTag, genParticles);

    if( genParticles.isValid() ) {
      edm::LogInfo("RootTupleMakerV2_GenParticlesInfo") << "Total # GenParticles: " << genParticles->size();

      for( reco::GenParticleCollection::const_iterator it = genParticles->begin(); it != genParticles->end(); ++it ) {
        // exit from loop when you reach the required number of GenParticles
        if(eta->size() >= maxSize)
          break;

        // fill in all the vectors
        eta->push_back( it->eta() );
        phi->push_back( it->phi() );
        p->push_back( it->p() );
        px->push_back( it->px() );
        py->push_back( it->py() );
        pz->push_back( it->pz() );
        pt->push_back( it->pt() );
        energy->push_back( it->energy() );
        pdgId->push_back( it->pdgId() );
        vx->push_back( it->vx() );
        vy->push_back( it->vy() );
        vz->push_back( it->vz() );
        numDaught->push_back( it->numberOfDaughters() );
        status->push_back( it->status() );
	//---------
	//if gen-particle is a tau, check decay mode:
	int getGenTauDecayMode_ = 0;
	if( abs(it->pdgId()) == 15 ) getGenTauDecayMode_ =  getGenTauDecayMode( & (*it) );
	taudecaymode->push_back( (int)(getGenTauDecayMode_) );
	//---------

	int idx = -1;
        for( reco::GenParticleCollection::const_iterator mit = genParticles->begin(); mit != genParticles->end(); ++mit ) {
          if( it->mother()==&(*mit) ) {
	    idx = std::distance(genParticles->begin(),mit);
	    break;
          }
        }
        motherIndex->push_back( idx );
      }
    } else {
      edm::LogError("RootTupleMakerV2_GenParticlesError") << "Error! Can't get the product " << inputTag;
    }
  }
  //-----------------------------------------------------------------
  // put vectors in the event
  iEvent.put( eta,         prefix + "Eta"         + suffix );
  iEvent.put( phi,         prefix + "Phi"         + suffix );
  iEvent.put( p,           prefix + "P"           + suffix );
  iEvent.put( px,          prefix + "Px"          + suffix );
  iEvent.put( py,          prefix + "Py"          + suffix );
  iEvent.put( pz,          prefix + "Pz"          + suffix );
  iEvent.put( pt,          prefix + "Pt"          + suffix );
  iEvent.put( energy,      prefix + "Energy"      + suffix );
  iEvent.put( pdgId,       prefix + "PdgId"       + suffix );
  iEvent.put( vx,          prefix + "VX"          + suffix );
  iEvent.put( vy,          prefix + "VY"          + suffix );
  iEvent.put( vz,          prefix + "VZ"          + suffix );
  iEvent.put( numDaught,   prefix + "NumDaught"   + suffix );
  iEvent.put( status,      prefix + "Status"      + suffix );
  iEvent.put( motherIndex, prefix + "MotherIndex" + suffix );
  iEvent.put( taudecaymode,prefix + "TauDecayMode"+ suffix );
}

//-------------------------------------------------------------------------------------------------------------------------------------//
// See: https://hypernews.cern.ch/HyperNews/CMS/get/tauid/301/1/1/1.html                                                               //
// countDecayProducts()  and  getGenTauDecayMode()  are reproduced from:                                                               //
// http://cmssw.cvs.cern.ch/cgi-bin/cmssw.cgi/CMSSW/TauAnalysis/CandidateTools/src/candidateAuxFunctions.cc?revision=1.26&view=markup  //
//-------------------------------------------------------------------------------------------------------------------------------------//
void RootTupleMakerV2_GenParticles::countDecayProducts(const reco::GenParticle* genParticle,
						       int& numElectrons, int& numElecNeutrinos, int& numMuons, int& numMuNeutrinos, 
						       int& numChargedHadrons, int& numPi0s, int& numOtherNeutralHadrons, int& numPhotons)
{
  int absPdgId = TMath::Abs(genParticle->pdgId());
  int status   = genParticle->status();
  int charge   = genParticle->charge();
  
  if      ( absPdgId == 111 ) ++numPi0s;
  else if ( status   ==   1 ) {
    if      ( absPdgId == 11 ) ++numElectrons;
    else if ( absPdgId == 12 ) ++numElecNeutrinos;
    else if ( absPdgId == 13 ) ++numMuons;
    else if ( absPdgId == 14 ) ++numMuNeutrinos;
    else if ( absPdgId == 15 ) { 
      edm::LogError ("countDecayProducts")
        << "Found tau lepton with status code 1 !!";
      return; 
    }
    else if ( absPdgId == 16 ) return; // no need to count tau neutrinos
    else if ( absPdgId == 22 ) ++numPhotons;
    else if ( charge   !=  0 ) ++numChargedHadrons;
    else                       ++numOtherNeutralHadrons;
  } else {
    unsigned numDaughters = genParticle->numberOfDaughters();
    for ( unsigned iDaughter = 0; iDaughter < numDaughters; ++iDaughter ) {
      const reco::GenParticle* daughter = genParticle->daughterRef(iDaughter).get();
      
      countDecayProducts(daughter, 
			 numElectrons, numElecNeutrinos, numMuons, numMuNeutrinos,
			 numChargedHadrons, numPi0s, numOtherNeutralHadrons, numPhotons);
    }
  }
}

int RootTupleMakerV2_GenParticles::getGenTauDecayMode(const reco::GenParticle* genParticle) 
{
  //--- determine generator level tau decay mode
  //    NOTE: 
  //        (1) function implements logic defined in PhysicsTools/JetMCUtils/src/JetMCTag::genTauDecayMode
  //            for different type of argument 
  //        (2) this implementation should be more robust to handle cases of tau --> tau + gamma radiation

  int numElectrons           = 0;
  int numElecNeutrinos       = 0;
  int numMuons               = 0;
  int numMuNeutrinos         = 0; 
  int numChargedHadrons      = 0;
  int numPi0s                = 0; 
  int numOtherNeutralHadrons = 0;
  int numPhotons             = 0;
  
  countDecayProducts(genParticle,
		     numElectrons, numElecNeutrinos, numMuons, numMuNeutrinos,
		     numChargedHadrons, numPi0s, numOtherNeutralHadrons, numPhotons);
  
  if      ( numElectrons == 1 && numElecNeutrinos == 1 ) return 1;//std::string("electron");
  else if ( numMuons     == 1 && numMuNeutrinos   == 1 ) return 2;//std::string("muon");
  
  switch ( numChargedHadrons ) {
  case 1 : 
    if ( numOtherNeutralHadrons != 0 ) return 11;//std::string("oneProngOther");
    switch ( numPi0s ) {
    case 0:
      return 3;//std::string("oneProng0Pi0");
    case 1:
      return 4;//std::string("oneProng1Pi0");
    case 2:
      return 5;//std::string("oneProng2Pi0");
    default:
      return 6;//std::string("oneProngOther");
    }
  case 3 : 
    if ( numOtherNeutralHadrons != 0 ) return 12;//std::string("threeProngOther");
    switch ( numPi0s ) {
    case 0:
      return 7;//std::string("threeProng0Pi0");
    case 1:
      return 8;//std::string("threeProng1Pi0");
    default:
      return 9;//std::string("threeProngOther");
    }
  default:
    return 13;//std::string("rare");
  }
}

