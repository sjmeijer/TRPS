#include "TRPSTree.hh"
#include "EventR.hh"

TRPSTree* TRPSTree::instance = NULL;

TRPSTree* TRPSTree::Instance(const char* name, const char* title){
	if (!instance){
		instance = new TRPSTree(name, title );
	//	SetMaxTreeSize(100000000);
	}
	return instance;
}

TRPSTree::TRPSTree( const char* name, const char* title ) : TTree(name, title){
	EventR* eventR = EventR::Instance();

	//Branch("n_primaries",&truth->n,"n_primaries/I");
	Branch("n",&eventR->n,"n/I");
	Branch("TESid",&eventR->TESid);
	Branch("t",&eventR->time);
	Branch("Edep",&eventR->Edep);
	Branch("Pol",&eventR->Pol);
	Branch("x",&eventR->positionsX);
	Branch("y",&eventR->positionsY);
	Branch("z",&eventR->positionsZ);
	
}

TRPSTree::~TRPSTree(){

}
