#ifndef EventR_h
#define EventR_h
#include "TESHit.hh"


class EventR
{

	public:
		static EventR* Instance();
		~EventR();
		void clear();
		

	private:

		EventR();
		static EventR* instance;
		TESHit* hit;

		
		int n;
		int TESid;
 		vector<int> TESid;
 		vector<double> time;
		vector<double> Edep;
		vector<int> Pol;
		vector<double> positionsX;
		vector<double> positionsY;
		vector<double> positionsZ;

		void PushTESid(G4int);
		void PushTEStime(G4double);
		void PushTESEdep(G4double);
		void PushTESX(G4double);
		void PushTESY(G4double);
		void PushTESZ(G4double);
		void PushPol(G4int);
  		

		friend class EventAction;
		friend class PrimaryGeneratorAction;
		friend class TESSensitivity;
		friend class TRPSTree;

};

#endif
