#include "CustomEventAction.hh"
#include "CustomRunAction.hh"

#include "G4Event.hh"
#include "G4EventManager.hh"
#include "G4TrajectoryContainer.hh"
#include "G4Trajectory.hh"
#include "G4ios.hh"


//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
 
/*CustomEventAction::CustomEventAction(CustomAnalysisManager* aAnalysisManager) : fAnalysisManager(aAnalysisManager)
{

}//*/



//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
 
CustomEventAction::CustomEventAction(CustomRunAction* run)
Run(run),drawFlag("none"),printModulo(10),eventMessenger(NULL)
{
	// eventMessenger = new EventActionMessenger(this);

}
CustomEventACtion::~CustomEventAction()
{

}
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
 
void CustomEventAction::BeginOfEventAction(const G4Event* aEvent)
{
/*	//G4cout << "Begin of event action \n";
#ifdef G4ANALYSIS_USE
	//G4cout << "Analysis loop \n";
	if(fAnalysisManager){
		//G4cout << "Executing an event" << G4endl;
		fAnalysisManager->BeginOfEvent(aEvent);
	}
#endif //*/



}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
 
void CustomEventAction::EndOfEventAction(const G4Event* evt)
{

/*#ifdef G4ANALYSIS_USE
  if(fAnalysisManager) fAnalysisManager->EndOfEvent(aEvent);
#endif
  G4int event_id = aEvent->GetEventID();
  
  // get number of stored trajectories
  //
  /*G4TrajectoryContainer* trajectoryContainer = evt->GetTrajectoryContainer();
  G4int n_trajectories = 0;
  if (trajectoryContainer) n_trajectories = trajectoryContainer->entries();
  
  // periodic printing
  //
  if (event_id < 100 || event_id%100 == 0) {
    G4cout << ">>> Event " << aEvent->GetEventID() << G4endl;
    //G4cout << "    " << n_trajectories
	//   << " trajectories stored in this event." << G4endl;
  }//*/

	G4int eventID = evt->GetEventID();

	if(!(eventID % printModulo))
	{

		G4cout << "Event ID - " << eventID << "   Energy deposit: "
		           << G4BestUnit(TotalEnergyDeposit[1],"Energy") << G4endl;
	}

	#ifdef G4ANALYSIS_USE
		Run->GetHisto(1)->fill(TotalEnergyDeposit[1]/MeV);
	#endif

}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
