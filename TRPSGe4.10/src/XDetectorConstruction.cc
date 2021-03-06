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
/// \file exoticphysics/phonon/src/XDetectorConstruction.cc
/// \brief Implementation of the XDetectorConstruction class
//
// $Id: XDetectorConstruction.cc 76938 2013-11-19 09:51:36Z gcosmo $
//

#include "XDetectorConstruction.hh"

#include "G4Material.hh"
#include "G4NistManager.hh"

#include "G4Box.hh"
#include "G4Tubs.hh"
#include "G4Sphere.hh"
#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"
#include "G4UniformMagField.hh"
#include "G4TransportationManager.hh"
#include "G4FieldManager.hh"
#include "G4VisAttributes.hh"
#include "G4Colour.hh"
#include "G4SDManager.hh"

#include "TESSensitivity.hh"
#include "G4LatticePhysical.hh"
#include "G4LatticeLogical.hh"
#include "G4LatticeManager.hh"

#include "G4UserLimits.hh"
#include "G4SystemOfUnits.hh"
#include "G4ios.hh"


//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

XDetectorConstruction::XDetectorConstruction()
 : fConstructed(false), fIfField(true) {
  fLiquidHelium = NULL;
  fGermanium = NULL;
  fAluminum = NULL;
  fTungsten = NULL;
  fWorldPhys = NULL;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

XDetectorConstruction::~XDetectorConstruction() {;}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

G4VPhysicalVolume* XDetectorConstruction::Construct()
{
  if(!fConstructed)
  { 
    fConstructed = true;
    DefineMaterials();
    SetupGeometry();
  }
  return fWorldPhys;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

void XDetectorConstruction::DefineMaterials()
{ 
  G4NistManager* nistManager = G4NistManager::Instance();

  fLiquidHelium = nistManager->FindOrBuildMaterial("G4_AIR"); // to be corrected
  fGermanium = nistManager->FindOrBuildMaterial("G4_Ge");
  fAluminum = nistManager->FindOrBuildMaterial("G4_Al");
  fTungsten = nistManager->FindOrBuildMaterial("G4_W");
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

void XDetectorConstruction::SetupGeometry()
{
  //     
  // World
  //
  G4VSolid* worldSolid = new G4Box("World",16.*cm,16.*cm,16.*cm);
  G4LogicalVolume* worldLogical =
    new G4LogicalVolume(worldSolid,fLiquidHelium,"World");
  worldLogical->SetUserLimits(new G4UserLimits(10*mm, DBL_MAX, DBL_MAX, 0, 0));
  fWorldPhys = new G4PVPlacement(0,G4ThreeVector(),worldLogical,"World",0,
                                 false,0);
  
  //                               
  // Germanium cylinder - this is the volume in which we will propagate phonons
  //  
  G4VSolid* fGermaniumSolid = new G4Box("fGermaniumSolid",2.5*cm,2.5*cm,2.5*cm);
  G4LogicalVolume* fGermaniumLogical = new G4LogicalVolume(fGermaniumSolid,fGermanium,"fGermaniumLogical");
  G4VPhysicalVolume* GePhys = new G4PVPlacement(0,G4ThreeVector(),fGermaniumLogical,"fGermaniumPhysical",worldLogical,false,0);

  //
  //Germanium lattice information
  //

  // G4LatticeManager gives physics processes access to lattices by volume
  G4LatticeManager* LM = G4LatticeManager::GetLatticeManager();
  G4LatticeLogical* GeLogical = LM->LoadLattice(fGermanium, "Ge");

  // G4LatticePhysical assigns G4LatticeLogical a physical orientation
  G4LatticePhysical* GePhysical =
    new G4LatticePhysical(GeLogical, GePhys->GetFrameRotation());
  LM->RegisterLattice(GePhys, GePhysical);

  // NOTE:  Above registration can also be done in single step:
  // G4LatticlePhysical* GePhysical = LM->LoadLattice(GePhys, "Ge");

  //
  // Aluminum - crystal end caps. This is where phonon hits are registered
  //
  G4VSolid* fAlSolid = new G4Box("fAluminumSolid",2.0*cm,2.0*cm,0.025*cm);

  G4LogicalVolume* fAlLogical = new G4LogicalVolume(fAlSolid,fAluminum,"fAlLogical");
  new G4PVPlacement(0,G4ThreeVector(0.,0.,2.5*cm+0.025*cm),fAlLogical,"fAlPhysical",worldLogical,true,0);
  new G4PVPlacement(0,G4ThreeVector(0.,0.,-2.5*cm-0.025*cm),fAlLogical,"fAlPhysical",worldLogical,true,1);
  G4RotationMatrix* rotm23 = new G4RotationMatrix();
  rotm23->rotateY(90*deg);
  new G4PVPlacement(rotm23,G4ThreeVector(2.5*cm+0.025*cm,0.,0.),fAlLogical,"fAlPhysical",worldLogical,true,2);
  new G4PVPlacement(rotm23,G4ThreeVector(-2.5*cm-0.025*cm,0.,0.),fAlLogical,"fAlPhysical",worldLogical,true,3);
  G4RotationMatrix* rotm45 = new G4RotationMatrix();
  rotm45->rotateX(90*deg);
  new G4PVPlacement(rotm45,G4ThreeVector(0.,2.5*cm+0.025*cm,0.),fAlLogical,"fAlPhysical",worldLogical,true,4);
  new G4PVPlacement(rotm45,G4ThreeVector(0.,-2.5*cm-0.025*cm,0.),fAlLogical,"fAlPhysical",worldLogical,true,5);

  //
  // detector -- Note : Aluminum electrode sensitivity is attached to Germanium because phonons don't step into the Al. 
  //
  G4SDManager* SDman = G4SDManager::GetSDMpointer();
  TESSensitivity* electrodeSensitivity = new TESSensitivity("TES");
  SDman->AddNewDetector(electrodeSensitivity);
  fGermaniumLogical->SetSensitiveDetector(electrodeSensitivity);

  //                                        
  // Visualization attributes
  //
  worldLogical->SetVisAttributes(G4VisAttributes::Invisible);
  G4VisAttributes* GeVisAtt= new G4VisAttributes(G4Colour(1.0,1.0,1.0));
  G4VisAttributes* AlVisAtt= new G4VisAttributes(G4Colour(0.0,1.0,0.0));
  GeVisAtt->SetVisibility(true);
  AlVisAtt->SetVisibility(true);
  fGermaniumLogical->SetVisAttributes(GeVisAtt);
  fAlLogical->SetVisAttributes(AlVisAtt);
}
