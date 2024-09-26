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
//
/// \file ShieldModelDetectorConstruction.cc
/// \brief Implementation of the ShieldModelDetectorConstruction class

#include "ShieldModelDetectorConstruction.hh"

#include "G4RunManager.hh"
#include "G4NistManager.hh"
#include "G4Box.hh"
#include "G4Cons.hh"
#include "G4Orb.hh"
#include "G4Sphere.hh"
#include "G4Trd.hh"
#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"
#include "G4VisAttributes.hh"
#include "G4SystemOfUnits.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

ShieldModelDetectorConstruction::ShieldModelDetectorConstruction()
: G4VUserDetectorConstruction(),
  fScoringVolume(0)
{ }

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

ShieldModelDetectorConstruction::~ShieldModelDetectorConstruction()
{ }

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

G4VPhysicalVolume* ShieldModelDetectorConstruction::Construct()
{  
  // Get nist material manager
  G4NistManager* nist = G4NistManager::Instance();
  
  // Fridge parameters simplified
  //
  G4double frg_sizeXY   = 100*mm,
           frgAl0_sizeZ = 3.2*mm,
           frgAl1_sizeZ = 4*mm,
           frgAl2_sizeZ = 3*mm,
           frgBr0_sizeZ = 3*mm,
           frgBr1_sizeZ = 2*mm,
           frgCu0_sizeZ = 5*mm;

  G4Material* al_mat = nist->FindOrBuildMaterial("G4_Al");
  G4Material* br_mat = nist->FindOrBuildMaterial("G4_BRASS");
  G4Material* cu_mat = nist->FindOrBuildMaterial("G4_Cu");

  // Dector Vol
  //
  G4double csi_sizeXY   = 14*mm,
           csi_sizeZ    = 25.4*mm;

  G4Material* csi_mat = nist->FindOrBuildMaterial("G4_CESIUM_IODIDE"); //G4_CESIUM_IODIDE
 
  // Option to switch on/off checking of volumes overlaps
  //
  G4bool checkOverlaps = true;

  //     
  // World
  //
  G4double world_sizeXY = frg_sizeXY;
  G4double world_sizeZ  = 250*mm;
  G4Material* world_mat = nist->FindOrBuildMaterial("G4_AIR");
  G4double localZero = -170*mm;

  G4Box* solidWorld =    
    new G4Box("World",                       //its name
              world_sizeXY, 
              world_sizeXY, 
              world_sizeZ);                  //its size
      
  G4LogicalVolume* logicWorld =                         
    new G4LogicalVolume(solidWorld,          //its solid
                        world_mat,           //its material
                        "World");            //its name
                                   
  G4VPhysicalVolume* physWorld = 
    new G4PVPlacement(0,                     //no rotation
                      G4ThreeVector(),       //at (0,0,0) REQUIRED
                      logicWorld,            //its logical volume
                      "World",               //its name
                      0,                     //its mother  volume
                      false,                 //no boolean operation
                      0,                     //copy number
                      checkOverlaps);        //overlaps checking
  //     
  // Fridge
  //  
  
  // AL 0
  G4ThreeVector pos0 = G4ThreeVector(0, 0, (0+localZero)*mm);
  
  G4Box* solidShape0 =    
    new G4Box("Al0", 
              frg_sizeXY,
              frg_sizeXY,
              frgAl0_sizeZ);
                      
  G4LogicalVolume* logicShape0 =                         
    new G4LogicalVolume(solidShape0,         //its solid
                        al_mat,              //its material
                        "Al0");              //its name
               
  new G4PVPlacement(0,                       //no rotation
                    pos0,                    //at position
                    logicShape0,             //its logical volume
                    "Al0",                   //its name
                    logicWorld,                       //its mother  volume
                    false,                   //no boolean operation
                    0,                       //copy number
                    checkOverlaps);          //overlaps checking

  // AL 1
  G4ThreeVector pos1 = G4ThreeVector(0, 0, (20.2+localZero)*mm);
  
  G4Box* solidShape1 =    
    new G4Box("Al1", 
              frg_sizeXY,
              frg_sizeXY,
              frgAl1_sizeZ);
                      
  G4LogicalVolume* logicShape1 =                         
    new G4LogicalVolume(solidShape1,         //its solid
                        al_mat,              //its material
                        "Al1");              //its name
               
  new G4PVPlacement(0,                       //no rotation
                    pos1,                    //at position
                    logicShape1,             //its logical volume
                    "Al1",                   //its name
                    logicWorld,                       //its mother  volume
                    false,                   //no boolean operation
                    0,                       //copy number
                    checkOverlaps);          //overlaps checking


  // AL 2
  G4ThreeVector pos2 = G4ThreeVector(0, 0, (46.2+localZero)*mm);
  
  G4Box* solidShape2 =    
    new G4Box("Al2", 
              frg_sizeXY,
              frg_sizeXY,
              frgAl2_sizeZ);
                      
  G4LogicalVolume* logicShape2 =                         
    new G4LogicalVolume(solidShape2,         //its solid
                        al_mat,              //its material
                        "Al2");              //its name
               
  new G4PVPlacement(0,                       //no rotation
                    pos2,                    //at position
                    logicShape2,             //its logical volume
                    "Al2",                   //its name
                    logicWorld,                       //its mother  volume
                    false,                   //no boolean operation
                    0,                       //copy number
                    checkOverlaps);          //overlaps checking

  // BRASS 0
  if (0){
     G4ThreeVector pos3 = G4ThreeVector(0, 0, (61.2+localZero)*mm);
     
     G4Box* solidShape3 =    
       new G4Box("Br0", 
                 frg_sizeXY,
                 frg_sizeXY,
                 frgBr0_sizeZ);
                         
     G4LogicalVolume* logicShape3 =                         
       new G4LogicalVolume(solidShape3,         //its solid
                           br_mat,              //its material
                           "Br0");              //its name
                  
     new G4PVPlacement(0,                       //no rotation
                       pos3,                    //at position
                       logicShape3,             //its logical volume
                       "Br0",                   //its name
                       logicWorld,                       //its mother  volume
                       false,                   //no boolean operation
                       0,                       //copy number
                       checkOverlaps);          //overlaps checking
  }

  // BRASS 1
  if (0){
     G4ThreeVector pos4 = G4ThreeVector(0, 0, (77.7+localZero)*mm);
     
     G4Box* solidShape4 =    
       new G4Box("Br1", 
                 frg_sizeXY,
                 frg_sizeXY,
                 frgBr1_sizeZ);
                         
     G4LogicalVolume* logicShape4 =                         
       new G4LogicalVolume(solidShape4,         //its solid
                           br_mat,              //its material
                           "Br1");              //its name
                  
     new G4PVPlacement(0,                       //no rotation
                       pos4,                    //at position
                       logicShape4,             //its logical volume
                       "Br1",                   //its name
                       logicWorld,                       //its mother  volume
                       false,                   //no boolean operation
                       0,                       //copy number
                       checkOverlaps);          //overlaps checking
  }
 
  // Cu 0
  if (1){
     G4ThreeVector pos5 = G4ThreeVector(0, 0, (77.7+2.0+localZero)*mm);
     
     G4Box* solidShape5 =    
       new G4Box("Cu0", 
                 frg_sizeXY,
                 frg_sizeXY,
                 frgCu0_sizeZ);
                         
     G4LogicalVolume* logicShape5 =                         
       new G4LogicalVolume(solidShape5,         //its solid
                           cu_mat,              //its material
                           "Cu0");              //its name
                  
     new G4PVPlacement(0,                       //no rotation
                       pos5,                    //at position
                       logicShape5,             //its logical volume
                       "Cu0",                   //its name
                       logicWorld,                       //its mother  volume
                       false,                   //no boolean operation
                       0,                       //copy number
                       checkOverlaps);          //overlaps checking
  }
  
  // CsI Det
  G4ThreeVector pos6 = G4ThreeVector(0, 0, (218.9+localZero)*mm);
  
  G4Box* solidShape6 =    
    new G4Box("Csi", 
              csi_sizeXY,
              csi_sizeXY,
              csi_sizeZ);
                      
  G4LogicalVolume* logicShape6 =                         
    new G4LogicalVolume(solidShape6,         //its solid
                        csi_mat,              //its material
                        "Csi");              //its name
               
  new G4PVPlacement(0,                       //no rotation
                    pos6,                    //at position
                    logicShape6,             //its logical volume
                    "Csi",                   //its name
                    logicWorld,                       //its mother  volume
                    false,                   //no boolean operation
                    0,                       //copy number
                    checkOverlaps);          //overlaps checking


            
  // Set Shape4 as scoring volume
  //
  fScoringVolume = logicShape6;

  //
  //always return the physical World
  //
  return physWorld;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
