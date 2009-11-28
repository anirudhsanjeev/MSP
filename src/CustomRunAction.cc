#ifdef G4ANALYSIS_USE
#include "CustomAnalysisManager.hh"
#endif

#include "CustomRunAction.hh"

#include "G4Run.hh"
#include "G4RunManager.hh"

#include "Randomize.hh"

#ifdef G4ANALYSIS_USE
#include "AIDA/AIDA.h"
#endif

#include "CustomRunAction.hh"

/*CustomRunAction::CustomRunAction(
 CustomAnalysisManager* aAnalysisManager
):fAnalysisManager(aAnalysisManager){}*/

CustomRunAction::CustomRunAction():af(0), tree(0)
{
	histo[0] = 0;
	histo[1] = 0;
	histo[3] = 0;
	histo[4] = 0;

#ifdef G4ANALYSIS_USE
	af = AIDA_createAnalysisFactory();

	if (af)  {
		AIDA::ITreeFactory* tf = af->createTreeFactory();

		G4bool readOnly = false;
		G4bool createNew = true;
		G4cout << "creating tree and structure now!\n";
		   G4String options =  "--noErrors export=XML uncompress";
		   //tree = tf->create("custom.hbook","hbook",readOnly,createNew, options);
		   tree = tf->create("testem4.XML","XML",readOnly,createNew, options);
		   //tree = tf->create("testem4.XML" ,"XML" ,readOnly,createNew, options);
		   delete tf;

		   if (tree) {
		     // Creating a histogram factory
		     AIDA::IHistogramFactory* hf = af->createHistogramFactory(*tree);

		     // Creating the histogram
		     histo[0]=hf->createHistogram1D
		                         ("1","total energy deposit in D1",100,0.,10.);
		     histo[1]=hf->createHistogram1D
		     		                        ("2","total energy deposit in D2",100,0.,10.);
		     histo[2]=hf->createHistogram1D
		     		                         ("3","total energy deposit in D3",100,0.,10.);
		     histo[3]=hf->createHistogram1D
		     		                         ("4","total energy deposit in D4",100,0.,10.);

		     delete hf;
		     G4cout << "\n----> Histogram tree is opened" << G4endl;
		}
	}
#endif
}

CustomRunAction::~CustomRunAction(){
#ifdef G4ANALYSIS_USE
	G4cout << "Writing tree file now...";

	tree->commit();
	tree->close();

	delete tree;
	delete af;
#endif
}

void CustomRunAction::BeginOfRunAction(const G4Run* aRun) {
	G4cout << "### Run " << aRun->GetRunID() << " start." << G4endl;

	  // save Rndm status
	  G4RunManager::GetRunManager()->SetRandomNumberStore(true);
	  CLHEP::HepRandom::showEngineStatus();
/*#ifdef G4ANALYSIS_USE
  if(fAnalysisManager)
  {
	  G4cout << "Started a run action\n";
	  fAnalysisManager->BeginOfRun(aRun);
  }
#endif*/
}

void CustomRunAction::EndOfRunAction(const G4Run* aRun){
	CLHEP::HepRandom::showEngineStatus();
/*#ifdef G4ANALYSIS_USE
  if(fAnalysisManager)
	  {
	  G4cout << "Stopped a run action\n";
	  fAnalysisManager->EndOfRun(aRun);
	  }
#endif*/
}
