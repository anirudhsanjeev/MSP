#include "CustomEventAction.hh"

#include "G4Event.hh"
#include "G4EventManager.hh"
#include "G4TrajectoryContainer.hh"
#include "G4Trajectory.hh"
#include "G4ios.hh"


//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
 
CustomEventAction::CustomEventAction(CustomAnalysisManager* aAnalysisManager) : fAnalysisManager(aAnalysisManager)
{

}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
 
CustomEventAction::~CustomEventAction()
{}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
 
void CustomEventAction::BeginOfEventAction(const G4Event* aEvent)
{
	//G4cout << "Begin of event action \n";
#ifdef G4ANALYSIS_USE
	//G4cout << "Analysis loop \n";
	if(fAnalysisManager){
		//G4cout << "Executing an event" << G4endl;
		fAnalysisManager->BeginOfEvent(aEvent);
	}
#endif

}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
 
void CustomEventAction::EndOfEventAction(const G4Event* aEvent)
{

#ifdef G4ANALYSIS_USE
  if(fAnalysisManager) fAnalysisManager->EndOfEvent(aEvent);
#endif
  G4int event_id = aEvent->GetEventID();
  
  // get number of stored trajectories
  //
  /*G4TrajectoryContainer* trajectoryContainer = evt->GetTrajectoryContainer();
  G4int n_trajectories = 0;
  if (trajectoryContainer) n_trajectories = trajectoryContainer->entries();*/
  
  // periodic printing
  //
  if (event_id < 100 || event_id%100 == 0) {
    G4cout << ">>> Event " << aEvent->GetEventID() << G4endl;
    //G4cout << "    " << n_trajectories
	//   << " trajectories stored in this event." << G4endl;
  }
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
