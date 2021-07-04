#include "B1SteppingAction.hh"
#include "B1EventAction.hh"
#include "B1DetectorConstruction.hh"

#include "G4Step.hh"
#include "G4Event.hh"
#include "G4RunManager.hh"
#include "G4LogicalVolume.hh"

#include <stdlib.h>

B1SteppingAction::B1SteppingAction(B1EventAction* eventAction)
: G4UserSteppingAction(),
  fEventAction(eventAction),
  fScoringVolume(0)
{}

B1SteppingAction::~B1SteppingAction()
{}

void B1SteppingAction::UserSteppingAction(const G4Step* step)
{
    G4double z = (step->GetTrack()->GetPosition()).z();
    
    G4int trackID  = step->GetTrack()->GetTrackID();
    G4String name = step->GetTrack()->GetDefinition()->GetParticleName();

  // get volume of the current step
  G4LogicalVolume* volume
    = step->GetPreStepPoint()->GetTouchableHandle()
      ->GetVolume()->GetLogicalVolume();
    
  //  G4String volumeName = step -> GetPreStepPoint() -> GetPhysicalVolume()-> GetName();
    
    G4StepPoint* prePoint = step->GetPreStepPoint();
    G4double kinEnergyPreStep = prePoint->GetKineticEnergy();
    
    CLHEP::Hep3Vector deltaMomentum = step -> GetDeltaMomentum();
    G4double deltaEnergy = step -> GetDeltaEnergy();
    G4ThreeVector deltaPosition = step -> GetDeltaPosition();
    
    
    G4StepPoint* preStepPoint = step -> GetPreStepPoint();
    G4StepPoint* postStepPoint = step -> GetPostStepPoint();
    
    G4double t = step -> GetTrack() -> GetGlobalTime();
    
    
    if((postStepPoint -> GetStepStatus() ==  fGeomBoundary ) /* || ( preStepPoint -> GetStepStatus() ==  fGeomBoundary) */ && name == "gamma") {
    
   // G4Material* nextMaterial = step -> GetPostStepPoint() -> GetMaterial();
    G4String volumeNamePre = step -> GetPreStepPoint() -> GetPhysicalVolume()-> GetName();
    G4String volumeNamePost = step -> GetPostStepPoint() -> GetPhysicalVolume()-> GetName();
    
   
    
    if( (volumeNamePre == "Shape2_1" && volumeNamePost == "Shape3_1") ||(volumeNamePre == "Shape3_1" && volumeNamePost == "Shape2_1")){
        
     //   std::ofstream outf("file_1.csv", std::ios::app);
        
       /* if(volumeNamePre == "Shape2" && volumeNamePost == "Shape3"){
            std::cout << " 1 " << t << std::endl;
            outf << 1 << std::endl;
        }*/
      //  std::cout << "time " << t <<" z "<< z/CLHEP::km << " trackID: " << trackID <<  " Energy " <<  kinEnergyPreStep/CLHEP::keV << " volumeNamePre  " << volumeNamePre  <<  " volumeNamePost " <<  volumeNamePost  << std::endl;
      
        
       // outf << "time " << t <<" z "<< z/CLHEP::km << " trackID: " << trackID <<  " Energy " <<  kinEnergyPreStep/CLHEP::keV  << " volumeNamePre  " << volumeNamePre  <<  " volumeNamePost " <<  volumeNamePost  << std::endl;
        /*if(volumeNamePre == "Shape3" && volumeNamePost == "Shape2"){
            std::cout << " -1 " << t << std::endl;
            outf << -1 << std::endl;
        }*/
   }

    
    
    /*
    
    std::ofstream outf("d2.csv", std::ios::app);
    outf << "time " << t <<" postStepPoint" << postStepPoint << " z "<< z/CLHEP::km << " trackID: " << trackID <<  " Energy " <<  kinEnergyPreStep/CLHEP::keV << " volumeName " <<  volumeName << " deltaMomentum " <<  deltaMomentum << " deltaEnergy " << deltaEnergy << " deltaPosition " << deltaPosition << std::endl;
     */
    }
}
