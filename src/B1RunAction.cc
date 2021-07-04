#include "B1RunAction.hh"
#include "B1PrimaryGeneratorAction.hh"
#include "B1DetectorConstruction.hh"

#include "G4RunManager.hh"
#include "G4Run.hh"
#include "G4AccumulableManager.hh"
#include "G4LogicalVolumeStore.hh"
#include "G4LogicalVolume.hh"
#include "G4UnitsTable.hh"
#include "G4SystemOfUnits.hh"

B1RunAction::B1RunAction()
: G4UserRunAction(),
  fEdep(0.),
  fEdep2(0.)
{ 
}

B1RunAction::~B1RunAction()
{}

void B1RunAction::BeginOfRunAction(const G4Run*)
{
}

void B1RunAction::EndOfRunAction(const G4Run* run)
{
}

void B1RunAction::AddEdep(G4double edep)
{
}
