#include "CustomEventAction.hh"
#include "CustomRunAction.hh"

#include "G4Event.hh"
#include "G4EventManager.hh"
#include "G4TrajectoryContainer.hh"
#include "G4Trajectory.hh"
#include "G4ios.hh"
#include "G4VVisManager.hh"
#include "G4UnitsTable.hh"

#ifdef G4ANALYSIS_USE
  #include "AIDA/IHistogram1D.h"
#endif

 
CustomEventAction::CustomEventAction(CustomRunAction* run):
Run(run),drawFlag("all"),printModulo(1000)
{
	// eventMessenger = new EventActionMessenger(this);

}
CustomEventAction::~CustomEventAction()
{

}
 
void CustomEventAction::BeginOfEventAction(const G4Event* evt)
{
/*	//G4cout << "Begin of event action \n";
#ifdef G4ANALYSIS_USE
	//G4cout << "Analysis loop \n";
	if(fAnalysisManager){
		//G4cout << "Executing an event" << G4endl;
		fAnalysisManager->BeginOfEvent(aEvent);
	}
#endif //*/
	G4int eventID = evt->GetEventID();

	if(!(eventID % printModulo))
		{
		G4cout << "\n---> Begin of Event: " << eventID << G4endl;
		}

	for(int i = 0; i<100; i++) // 100 detectors have to be enough for anyone
	{
		TotalEnergyDeposit[i] = 0;
	}

}

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
	if(eventID != 0)
	{

	if(!(eventID % printModulo))
	{
		G4cout << "-------->Event ID - " << eventID << G4endl;
		for(int i = 0; i < Run->nDetectors; i++)
		{

		G4cout << "Detector no. " << i << "  |  Energy deposit: "
		           << TotalEnergyDeposit[i] << "KeV" << G4endl;
		}
	}

	#ifdef G4ANALYSIS_USE
	for(int i = 0; i < Run->nDetectors; i ++)
	{
		// G4cout << "Filling energy of hist " << i << " with " << TotalEnergyDeposit[i] << endl;
		G4double energyThreshold = 0.0;
		if(TotalEnergyDeposit[i] > energyThreshold)
		{
			Run->GetHisto(i)->fill(TotalEnergyDeposit[i]/MeV);
		}
	}
	#endif

#ifndef G4VIS_NONE
		if(G4VVisManager::GetConcreteInstance())
		  {
			G4cout <<"Drawing a trajectory now!" << G4endl;
		   G4TrajectoryContainer* trajectoryContainer = evt->GetTrajectoryContainer();
		   G4int n_trajectories = 0;
		   if (trajectoryContainer) n_trajectories = trajectoryContainer->entries();
		   for(G4int i=0; i<n_trajectories; i++)
		      { G4Trajectory* trj = (G4Trajectory *)
		                                      ((*(evt->GetTrajectoryContainer()))[i]);
		        if (drawFlag == "all") trj->DrawTrajectory(1000);
		        else if ((drawFlag == "charged")&&(trj->GetCharge() != 0.))
		                               trj->DrawTrajectory(1000);
		      }
		  }
#endif
	}

}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
