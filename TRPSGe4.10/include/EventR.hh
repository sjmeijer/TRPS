#ifndef EventR_h
#define EventR_h
#include "TESHit.hh"

class EventR
{

	public:
		static EventR* Instance();
		~EventR();
		void clear();
		
		void PushTESid(G4int);
		void PushTEStime(G4double);
		void PushTESEdep(G4double);
		void PushTESX(G4double);
		void PushTESY(G4double);
		void PushTESZ(G4double);
		void PushPol(G4int);
  		
		

	private:

		EventR();
		static EventR* instance;
		TESHit* hit;
		
		int n;
 		std::vector<int> TESid;
 		std::vector<double> time;
		std::vector<double> Edep;
		std::vector<int> Pol;
		std::vector<double> positionsX;
		std::vector<double> positionsY;
		std::vector<double> positionsZ;


		friend class EventAction;
		friend class PrimaryGeneratorAction;
		friend class TESSensitivity;
		friend class TRPSTree;

};

#endif
