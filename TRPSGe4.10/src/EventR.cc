#include "EventR.hh"
#include "TrackerHit.hh"
#include "EvStep.hh"
#include "EvTrack.hh"

EventR* EventR::instance = NULL;

EventR* EventR::Instance(){
if (!instance)
	instance = new EventR();
return instance;
}

EventR::EventR(){
	truth = new EvTruth();
	hits = new EvHit();
	steps = new EvStep();
	tracks = new EvTrack();
}

EventR::~EventR(){
	if (instance) {
		delete n;
		delete TESid;
		delete time;
		delete Edep;
		delete Pol;
		delete positionsX;
		delete positionsY;
		delete positionsZ;
	}
}

void EventR::clear(){
	TESid.clear();
	time.clear();
	Edep.clear();
	Pol.clear();
	positionsX.clear();
	positionsY.clear();
	positionsZ.clear();
}

void PushTESid(G4int id){
	TESid.push_back(id);
}
void PushTEStime(G4double t){
	time.push_back(t);
}
void PushTESEdep(G4double e){
	Edep.push_back(e);
}
void PushTESX(G4double){
	positionsX.push_back(y);
}
void PushTESY(G4double y){
	positionsY.push_back(y);
}
void PushTESZ(G4double z){
	positionsZ.push_back(z);
}
void PushPol(G4int a){
	Pol.push_back(a);
}

