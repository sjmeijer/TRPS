//
// ********************************************************************
// * License and Disclaimer                                           *
// *                                                                  *
// * The  Geant4 software  is  copyright of the Copyright Holders  of *
// * the Geant4 Collaboration.  It is provided  under  the terms  and *
// * conditions of the Geant4 Software License,  included in the file *
// * LICENSE and available at  http://cern.ch/geant4/license .  These *
// * include a list of copyright holders.                             *
// *                                                                  *
// * Neither the authors of this software system, nor their employing *
// * institutes,nor the agencies providing financial support for this *
// * work  make  any representation or  warranty, express or implied, *
// * regarding  this  software system or assume any liability for its *
// * use.  Please see the license in the file  LICENSE  and URL above *
// * for the full disclaimer and the limitation of liability.         *
// *                                                                  *
// * This  code  implementation is the result of  the  scientific and *
// * technical work of the GEANT4 collaboration.                      *
// * By using,  copying,  modifying or  distributing the software (or *
// * any work based  on the software)  you  agree  to acknowledge its *
// * use  in  resulting  scientific  publications,  and indicate your *
// * acceptance of all terms of the Geant4 Software license.          *
// ********************************************************************
//
/// \file exoticphysics/phonon/XGeBox.cc
/// \brief Main program of the exoticphysics/phonon example
//
// $Id: XGeBox.cc 76246 2013-11-08 11:17:29Z gcosmo $
//
 
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
 //

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
   G4String fileName = argv[1];
   UImanager->ApplyCommand(command+fileName);
 }

#ifdef G4VIS_USE
 delete visManager;
#endif
 delete runManager;

 return 0;
}


