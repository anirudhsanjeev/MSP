#include "CustomSteppingAction.hh"
#include "CustomEventAction.hh"
#include "G4SteppingManager.hh"
#include "CustomDetectorConstruction.hh"
#include "G4TouchableHistory.hh"
#include "G4VPhysicalVolume.hh"
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

CustomSteppingAction::CustomSteppingAction(CustomEventAction* evAct, CustomDetectorConstruction* detCon) : eventAction(evAct),myVerbose(NULL),detector(detCon)
{ }


//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void CustomSteppingAction::UserSteppingAction(const G4Step* aStep)
{ 
	G4double EdepStep = aStep->GetTotalEnergyDeposit();

	// get the physical volume it's in now
	G4TouchableHistory* theTouchable = (G4TouchableHistory*)(aStep->GetPreStepPoint()->GetTouchable());
	G4VPhysicalVolume* physVol = theTouchable->GetVolume();
	G4int cubeID = detector->GetDetectorCubeID(physVol);

	if(cubeID > 0 && EdepStep == 0.)
	{
		G4cout <<"Something's wrong. cubeID>0 but EdepStep is zero\n";
	}
	if(cubeID == 0 && EdepStep > 0.)
	{
		G4cout <<"Something's wrong. cubeID==0 but EdepStep is >0\n";
	}
	if(cubeID > 0 && EdepStep > 0)
	{
		eventAction->addEdep(EdepStep, cubeID - 1);
	}

	//if (EdepStep > 0.)
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

