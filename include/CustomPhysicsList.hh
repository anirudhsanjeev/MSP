#ifndef CustomPhysicsList_h
#define CustomPhysicsList_h 1

#include "G4VUserPhysicsList.hh"
#include "globals.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

class CustomPhysicsList: public G4VUserPhysicsList
{
public:
  CustomPhysicsList();
 ~CustomPhysicsList();

protected:
  // Construct particle and physics
  void ConstructParticle();
  void ConstructProcess();

  void SetCuts();

public:
  // Set/Get cut values
  void      SetCutForGamma(G4double);
  void      SetCutForElectron(G4double);
  void      SetCutForProton(G4double);
  G4double  GetCutForGamma() const;
  G4double  GetCutForElectron() const;
  G4double  GetCutForProton() const;

protected:
  // these methods Construct particles
  void ConstructBosons();
  void ConstructLeptons();
  void ConstructMesons();
  void ConstructBaryons();

protected:
// these methods Construct physics processes and register them
  void ConstructGeneral();
  void ConstructEM();

private:
  G4double cutForGamma;
  G4double cutForElectron;
  G4double cutForProton;
  G4double currentDefaultCut;
};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif

 
