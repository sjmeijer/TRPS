#include "EventAction.hh"

#include "RunAction.hh"
#include "EventActionMessenger.hh"

#include "G4Event.hh"
#include "G4UnitsTable.hh"
#include "Randomize.hh"
#include <iomanip>
#include "TRPSTree.hh"

EventAction::EventAction(RunAction* run)
:runAct(run),printModulo(1),eventMessenger(0)
{
  eventMessenger = new EventActionMessenger(this);
}

EventAction::~EventAction()
{
  delete eventMessenger;
}

void EventAction::BeginOfEventAction(const G4Event* evt)
{  
  G4int evtNb = evt->GetEventID();
  if (evtNb%printModulo == 0) { 
    G4cout << "\n---> Begin of event: " << evtNb << G4endl;
    //CLHEP::HepRandom::showEngineStatus();
  }
 
 // initialisation per event
 // ....nothing to do here
}

void EventAction::EndOfEventAction(const G4Event* evt)
{
  G4int evtNb = evt->GetEventID();
  TRPSTree* mytree = TRPSTree::Instance("tree","tree"); 
  EventR* eventR = EventR::Instance();
  mytree->Fill();
  G4cout << "\n---> HC of event: " << evtNb << G4endl;
  eventR->Print();
  G4cout << "\n---> End of event: " << evtNb << G4endl;

  eventR->clear();
}  
