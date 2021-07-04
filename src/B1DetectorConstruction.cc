
#include "B1DetectorConstruction.hh"

#include "G4RunManager.hh"
#include "G4NistManager.hh"
#include "G4Box.hh"
#include "G4Cons.hh"
#include "G4Sphere.hh"
#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"
#include "G4SystemOfUnits.hh"

#include <G4UniformMagField.hh>
#include <G4ClassicalRK4.hh>
#include <G4TransportationManager.hh>
#include <G4EqMagElectricField.hh>
#include "G4EquationOfMotion.hh"

#include "G4ChargeState.hh"
#include "G4EquationOfMotion.hh"
#include "G4ElectroMagneticField.hh"
#include "G4MonopoleEq.hh"

#include "globals.hh"
#include "G4PhysicalConstants.hh"
#include "G4SystemOfUnits.hh"

#include "G4EqEMFieldWithSpin.hh"
#include "G4PropagatorInField.hh"

B1DetectorConstruction::B1DetectorConstruction()
: G4VUserDetectorConstruction(),
  fScoringVolume(0)
{ }

B1DetectorConstruction::~B1DetectorConstruction()
{ }

G4VPhysicalVolume* B1DetectorConstruction::Construct()
{  
  // Get nist material manager
    
    G4String name, symbol;
    G4double density, fractionmass;
    G4int nel, ncomponents;
    
    G4NistManager* nist = G4NistManager::Instance();
    G4int nvar = 8;
    fMinStep = 0.001*mm ;
    G4bool isotopes = true;
    
    G4bool checkOverlaps = true;
    auto nistManager = G4NistManager::Instance();
      
    density = 0.4113*kg/m3;
    auto AirDensity = nistManager ->BuildMaterialWithNewDensity("AirDensity", "G4_AIR", density);

  // World
  //
  G4double world_sizeXY = 250*m;
  G4double world_sizeZ  = 250*m;

    G4Box* solidWorld =
    new G4Box("World",
              1.0*world_sizeXY, 1.0*world_sizeXY, 1.0*world_sizeZ);
      
  G4LogicalVolume* logicWorld =                         
    new G4LogicalVolume(solidWorld,
                        AirDensity,
                        "World");
                                   
  G4VPhysicalVolume* physWorld = 
    new G4PVPlacement(0,
                      G4ThreeVector(0, 0, 0),
                      logicWorld,
                      "World",
                      0,
                      false,
                      0,
                      checkOverlaps);

    
    
    //first part
        G4double a = 100;
        G4Box* solidShape2_1 =
          new G4Box("Shape2_1",                      //its name
                    a*m, a*m, a*m); //its size
                      
        G4LogicalVolume* logicShape2_1 =
          new G4LogicalVolume(solidShape2_1,         //its solid
                              AirDensity,          //its material
                              "Shape2_1");           //its name
                     
        new G4PVPlacement(0,                       //no rotation
                          G4ThreeVector(0*cm, 0, -a*m),                    //at position
                          logicShape2_1,             //its logical volume
                          "Shape2_1",                //its name
                          logicWorld,                //its mother  volume
                          false,                   //no boolean operation
                          0,                       //copy number
                          checkOverlaps);          //overlaps
      
    //two part
    
    G4Box* solidShape3_1 =
      new G4Box("Shape3_1",                      //its name
                a*m, a*m, a*m); //its size
                  
    G4LogicalVolume* logicShape3_1 =
      new G4LogicalVolume(solidShape3_1,         //its solid
                          AirDensity,          //its material
                          "Shape3_1");           //its name
                 
    new G4PVPlacement(0,                       //no rotation
                      G4ThreeVector(0*cm, 0, a*m),                    //at position
                      logicShape3_1,             //its logical volume
                      "Shape3_1",                //its name
                      logicWorld,                //its mother  volume
                      false,                   //no boolean operation
                      0,                       //copy number
                      checkOverlaps);          //overlaps
   

    //uniform field
    G4ElectricField* magField_5 = new G4UniformElectricField( G4ThreeVector(0.0,0.0,
                                                                          -228*kilovolt/m));
    G4EqMagElectricField* fEquation1_5 = new G4EqMagElectricField(magField_5);
    G4MagIntegratorStepper* fStepper1_5 = new G4ClassicalRK4( fEquation1_5, nvar );
    G4FieldManager* localFieldMgr1_5
            = new G4FieldManager(magField_5);
    logicShape2_1->SetFieldManager(localFieldMgr1_5, true);
    G4MagInt_Driver* fIntgrDriver1_5 = new G4MagInt_Driver(fMinStep,
                                     fStepper1_5,
                                     fStepper1_5->GetNumberOfVariables() );
    G4ChordFinder* fChordFinder1_5 = new G4ChordFinder(fIntgrDriver1_5);
       localFieldMgr1_5->SetChordFinder( fChordFinder1_5 );
    
    
    
    G4ElectricField* magField3_5 = new G4UniformElectricField( G4ThreeVector(0.0,0.0,
                                                                          228*kilovolt/m));
    G4EqMagElectricField* fEquation2_5 = new G4EqMagElectricField(magField3_5);
    G4MagIntegratorStepper* fStepper2_5 = new G4ClassicalRK4( fEquation2_5, nvar );
    G4FieldManager* localFieldMgr2_5
            = new G4FieldManager(magField3_5);
    logicShape3_1->SetFieldManager(localFieldMgr2_5, true);
    G4MagInt_Driver* fIntgrDriver2_5 = new G4MagInt_Driver(fMinStep,
                                     fStepper2_5,
                                     fStepper2_5->GetNumberOfVariables() );
    G4ChordFinder* fChordFinder2_5 = new G4ChordFinder(fIntgrDriver2_5);
       localFieldMgr2_5->SetChordFinder( fChordFinder2_5 );
    
    
    
    
  fScoringVolume = logicWorld;

  return physWorld;
}
