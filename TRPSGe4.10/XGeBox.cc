 
#include "G4RunManager.hh"
#include "G4UImanager.hh"
#include "G4UserSteppingAction.hh"

#ifdef G4VIS_USE
#include "G4VisExecutive.hh"
#endif

#ifdef G4UI_USE
#include "G4UIExecutive.hh"
#endif

#include "XDetectorConstruction.hh"
#include "XPhysicsList.hh"
#include "XPrimaryGeneratorAction.hh"
#include "RunAction.hh"
#include "EventAction.hh"
#include "XPhononStackingAction.hh"

int main(int argc,char** argv)
{
  

 // Construct the run manager
 //
 G4RunManager * runManager = new G4RunManager;

 // Set mandatory initialization classes
 //
 XDetectorConstruction* detector = new XDetectorConstruction();
 runManager->SetUserInitialization(detector);
 //
 G4VUserPhysicsList* physics = new XPhysicsList();
 physics->SetCuts();
 runManager->SetUserInitialization(physics);
    
 // Set user action classes
 //

 runManager->SetUserAction(new XPhononStackingAction);
 // runManager->SetUserAction(new DriftingElectronStackingAction);
 // runManager->SetUserAction(new XPhononTrackingAction);
 // runManager->SetUserAction(new PhononSteppingAction);

 G4VUserPrimaryGeneratorAction* gen_action = new XPrimaryGeneratorAction();
 runManager->SetUserAction(gen_action);
 
 RunAction* run_action = new RunAction;
 runManager->SetUserAction(run_action);
 
 EventAction* evt_action = new EventAction(run_action);
 runManager->SetUserAction(evt_action);
 
 G4String fileName;
 if(argc > 2){
	fileName=argv[2];
	run_action->SetOutputFileName(fileName);
 }
 else{
	run_action->SetOutputFileName("TRPS");
 }

#ifdef G4VIS_USE
 // Visualization manager
 //
 G4VisManager* visManager = new G4VisExecutive;
 visManager->Initialize();
#endif
    
 // Initialize G4 kernel
 //
 runManager->Initialize();
  
 // Get the pointer to the User Interface manager
 //
 G4UImanager* UImanager = G4UImanager::GetUIpointer();  

 if (argc==1)   // Define UI session for interactive mode
 {
#ifdef G4UI_USE
      G4UIExecutive * ui = new G4UIExecutive(argc,argv);
#ifdef G4VIS_USE
      UImanager->ApplyCommand("/control/execute vis.mac");
#endif
      ui->SessionStart();
      delete ui;
#endif
 }
 else           // Batch mode
 {
   G4String command = "/control/execute ";
   G4String scriptName = argv[1];
   UImanager->ApplyCommand(command+scriptName);
 }

#ifdef G4VIS_USE
 delete visManager;
#endif
 delete runManager;

 return 0;
}


