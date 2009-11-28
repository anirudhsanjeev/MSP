#ifndef CustomPrimaryGeneratorAction_h
#define CustomPrimaryGeneratorAction_h 1

#include "G4VUserPrimaryGeneratorAction.hh"

class CustomDetectorConstruction;
class G4ParticleGun;
class G4Event;
#include "G4GeneralParticleSource.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
 
class CustomPrimaryGeneratorAction : public G4VUserPrimaryGeneratorAction
{
  public:
    CustomPrimaryGeneratorAction(CustomDetectorConstruction*);    
   ~CustomPrimaryGeneratorAction();

  public:
    void GeneratePrimaries(G4Event*);

  private:
    G4GeneralParticleSource* particleGun;
    CustomDetectorConstruction* myDetector;
};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif


