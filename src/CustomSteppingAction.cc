#include "CustomSteppingAction.hh"
#include "CustomEventAction.hh"
#include "G4SteppingManager.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

CustomSteppingAction::CustomSteppingAction(CustomEventAction* evAct) : eventAction(evAct),myVerbose(NULL)
{ }


//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void CustomSteppingAction::UserSteppingAction(const G4Step* aStep)
{ 
	G4double EdepStep = aStep->GetTotalEnergyDeposit();

	if (EdepStep > 0.) eventAction->addEdep(EdepStep, 1);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

