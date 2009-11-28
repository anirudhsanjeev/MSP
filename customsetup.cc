#include "CustomDetectorConstruction.hh"
#include "CustomPhysicsList.hh"
#include "CustomPrimaryGeneratorAction.hh"
#include "CustomRunAction.hh"
#include "CustomEventAction.hh"
#include "CustomSteppingAction.hh"
#include "CustomSteppingVerbose.hh"
#include "CustomAnalysisManager.hh"

// AIDA :
#ifdef G4ANALYSIS_USE
#include <AIDA/IAnalysisFactory.h>
#endif

#include "G4RunManager.hh"
#include "G4UImanager.hh"

#ifdef G4VIS_USE
#include "G4VisExecutive.hh"
#include "G4UIterminal.hh"
#include "G4UItcsh.hh"
#endif

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

int main(int argc,char** argv)
{
  // User Verbose output class
  //
  G4VSteppingVerbose* verbosity = new CustomSteppingVerbose;
  G4VSteppingVerbose::SetInstance(verbosity);
  
  //choose the Random engine
  CLHEP::HepRandom::setTheEngine(new CLHEP::RanecuEngine);

  // Run manager
  //
  G4RunManager * runManager = new G4RunManager;

  // User Initialization classes (mandatory)
  //
  CustomDetectorConstruction* detector = new CustomDetectorConstruction;
  runManager->SetUserInitialization(detector);
  //
  G4VUserPhysicsList* physics = new CustomPhysicsList;
  runManager->SetUserInitialization(physics);
   
  // User Action classes
  //
  G4VUserPrimaryGeneratorAction* gen_action = new CustomPrimaryGeneratorAction(detector);
  runManager->SetUserAction(gen_action);
  //

  //
  CustomAnalysisManager * analysisManager = 0;
  /*#ifdef G4ANALYSIS_USE
    AIDA::IAnalysisFactory* aida = AIDA_createAnalysisFactory();
    analysisManager = new CustomAnalysisManager(aida);
  #endif*/
  G4UserRunAction* run_action = new CustomRunAction;
  runManager->SetUserAction(run_action);
  G4UserEventAction* event_action = new CustomEventAction((CustomRunAction*)run_action);
  runManager->SetUserAction(event_action);

  //
  G4UserSteppingAction* stepping_action = new CustomSteppingAction((CustomEventAction*)event_action);
  runManager->SetUserAction(stepping_action);





  // Initialize G4 kernel
  //
  runManager->Initialize();
      
  // Get the pointer to the User Interface manager
  //
  G4UImanager * UI = G4UImanager::GetUIpointer();

  if (argc!=1)   // batch mode  
    {
     G4String command = "/control/execute ";
     G4String fileName = argv[1];

     UI->ApplyCommand(command+fileName);
    }
    
  else           // interactive mode : define visualization and UI terminal
    {
#ifdef G4VIS_USE
      G4VisManager* visManager = new G4VisExecutive;
      visManager->Initialize();
      G4UIsession * session = 0;
#endif
     

#ifdef G4VIS_USE
      //session = new G4UIterminal(new G4UItcsh);
      session = new G4UIterminal();
      UI->ApplyCommand("/control/execute vis.mac");
      session->SessionStart();
      delete session;
#endif
     
#ifdef G4VIS_USE
      delete visManager;
#endif     
    }

  // Free the store: user actions, physics_list and detector_description are
  //                 owned and deleted by the run manager, so they should not
  //                 be deleted in the main() program !

  delete runManager;
  delete verbosity;
  //delete run_action;
  return 0;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

