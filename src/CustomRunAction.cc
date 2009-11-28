#ifdef G4ANALYSIS_USE
#include "CustomAnalysisManager.hh"
#endif

#include "CustomRunAction.hh"

CustomRunAction::CustomRunAction(
 CustomAnalysisManager* aAnalysisManager
):fAnalysisManager(aAnalysisManager){}

CustomRunAction::~CustomRunAction(){}

void CustomRunAction::BeginOfRunAction(const G4Run* aRun) {
#ifdef G4ANALYSIS_USE
  if(fAnalysisManager)
  {
	  G4cout << "Started a run action\n";
	  fAnalysisManager->BeginOfRun(aRun);
  }
#endif
}

void CustomRunAction::EndOfRunAction(const G4Run* aRun){
#ifdef G4ANALYSIS_USE
  if(fAnalysisManager)
	  {
	  G4cout << "Stopped a run action\n";
	  fAnalysisManager->EndOfRun(aRun);
	  }
#endif
}
