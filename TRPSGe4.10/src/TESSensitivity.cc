
#include "TESSensitivity.hh"

#include "TESHit.hh"
#include "G4HCofThisEvent.hh"
#include "G4TouchableHistory.hh"
#include "G4Track.hh"
#include "G4Step.hh"
#include "G4SDManager.hh"
#include "G4Navigator.hh"
#include "G4SystemOfUnits.hh"
#include "G4ios.hh"


using namespace std;

TESHitsCollection* 
TESSensitivity::fHitsCollection = NULL;

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

TESSensitivity::TESSensitivity(G4String name)
:G4VSensitiveDetector(name)
{
  G4String HCname;
  collectionName.insert(HCname="TESHit");
  fHCID = -1;
  fWriter.open("caustic.ssv", fstream::out | fstream::ate);
  fWriter2.open("timing.ssv", fstream::out | fstream::ate);

  if(!fWriter.is_open()){
    G4cout<<"\nTESSensitivity::Constructor:";
    G4cout<<"\n\tFailed to open caustic.ssv for appending data.";
    G4cout<<"\n\tCreating caustic.ssv" << G4endl;
    fWriter.open("caustic.ssv");
  }

  if(!fWriter2.is_open()){
    G4cout<<"\nTESSensitivity::Constructor: ";
    G4cout<<"\n\tFailed to open timing.ssv for appending data.";
    G4cout<<"\n\tCreating timing.ssv." << G4endl;
    fWriter2.open("timing.ssv");
  }

  if(!(fWriter.is_open() && fWriter2.is_open())){
    G4cout<<"\nTESSensitivity::Constructor: "
          <<"\nERROR: COULD NOT CREATE OUTPUT FILES FOR WRITING" << G4endl;
  }
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

TESSensitivity::~TESSensitivity(){
  fWriter.close();
  fWriter2.close();
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

TESHitsCollection* 
TESSensitivity::GetHitsCollection(){
  return fHitsCollection;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

void TESSensitivity::Initialize(G4HCofThisEvent*HCE)
{
  fHitsCollection = new TESHitsCollection
                   (SensitiveDetectorName,collectionName[0]);
  if(fHCID<0)
  { fHCID = G4SDManager::GetSDMpointer()->GetCollectionID(fHitsCollection); }
  HCE->AddHitsCollection(fHCID,fHitsCollection);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

G4bool TESSensitivity::ProcessHits(G4Step* aStep,
                                                  G4TouchableHistory* /*ROhist*/)
{
  //if(aStep->GetTrack()->GetDefinition()!=Phonon::PhononDefinition()) return true;
  G4double edp = aStep->GetNonIonizingEnergyDeposit();
  if(edp==0.) return true;

  G4StepPoint* preStepPoint = aStep->GetPreStepPoint();
  G4StepPoint* postStepPoint = aStep->GetPostStepPoint();
  G4TouchableHistory* theTouchable
    = (G4TouchableHistory*)(preStepPoint->GetTouchable());
  G4ThreeVector fWorldPos = postStepPoint->GetPosition();
  G4ThreeVector fLocalPos
    = theTouchable->GetHistory()->GetTopTransform().TransformPoint(fWorldPos);

  TESHit* aHit = new TESHit();
  aHit->SetTime(postStepPoint->GetGlobalTime());
  aHit->SetEDep(edp);
  aHit->SetWorldPos(fWorldPos);
  aHit->SetLocalPos(fLocalPos);

  fHitsCollection->insert(aHit);

  fWriter<<"\n"<<fWorldPos.getX()/mm
         <<","<<fWorldPos.getY()/mm
         <<","<<fWorldPos.getZ()/mm;

  fWriter2<<"\n"<<postStepPoint->GetGlobalTime()/ns<<" "
          <<aHit->GetEDep()/eV;

  return true;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

void TESSensitivity::EndOfEvent(G4HCofThisEvent* /*HCE*/)
{;}

