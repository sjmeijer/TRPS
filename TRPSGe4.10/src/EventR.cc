#include "EventR.hh"

EventR* EventR::instance = NULL;

EventR* EventR::Instance(){
if (!instance)
	instance = new EventR();
return instance;
}

EventR::EventR(){
}

EventR::~EventR(){
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

void EventR::PushTESid(G4int id){
	TESid.push_back(id);
}
void EventR::PushTEStime(G4double t){
	time.push_back(t);
}
void EventR::PushTESEdep(G4double e){
	Edep.push_back(e);
}
void EventR::PushTESX(G4double x){
	positionsX.push_back(x);
}
void EventR::PushTESY(G4double y){
	positionsY.push_back(y);
}
void EventR::PushTESZ(G4double z){
	positionsZ.push_back(z);
}
void EventR::PushPol(G4int a){
	Pol.push_back(a);
}

