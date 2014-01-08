
#ifndef TESSensitivity_h
#define TESSensitivity_h 1

#include "G4VSensitiveDetector.hh"
#include "TESHit.hh"

#include <iostream>
#include <fstream>

class G4Step;
class G4HCofThisEvent;
class G4TouchableHistory;

using namespace std;


class TESSensitivity : public G4VSensitiveDetector
{

  public:
      TESSensitivity(G4String);
      virtual ~TESSensitivity();

      virtual void Initialize(G4HCofThisEvent*);
      virtual G4bool ProcessHits(G4Step*,G4TouchableHistory*);
      virtual void EndOfEvent(G4HCofThisEvent*);

  TESHitsCollection* GetHitsCollection();
  static TESHitsCollection* fHitsCollection;

  private:
  //TESHitsCollection * hitsCollection;
  ofstream fWriter; //writing hit posn to file. Temporary fix.
  ofstream fWriter2; //writing timing information to file. Temporary fix.

      G4int fHCID;
};




#endif

