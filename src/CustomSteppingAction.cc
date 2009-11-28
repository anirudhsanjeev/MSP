#include "CustomSteppingAction.hh"
#include "EventAction.hh"
#include "G4SteppingManager.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

CustomSteppingAction::CustomSteppingAction()
{ }

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void CustomSteppingAction::UserSteppingAction(const G4Step*)
{ 
	G4double EdepStep = aStep->GetTotalEnergyDeposit();

	if (EdepStep > 0.) eventAction->addEdep(EdepStep, 1);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

