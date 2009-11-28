#ifndef CustomRunAction_h
#define CustomRunAction_h 1

#include "G4UserRunAction.hh"
#include "globals.hh"
#include "CustomAnalysisManager.hh"
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

class G4Run;

namespace AIDA {
  class IAnalysisFactory;
  class ITree;
  class IHistogram1D;
}

class CustomRunAction : public G4UserRunAction
{
  public:
    //CustomRunAction(CustomAnalysisManager* = 0);
	CustomRunAction();
   ~CustomRunAction();

  public:
    void BeginOfRunAction(const G4Run*);
    void EndOfRunAction(const G4Run*);

    AIDA::IHistogram1D* GetHisto(G4int id) {return histo[id];}
  private:
    CustomAnalysisManager* fAnalysisManager;
  private:
    AIDA::IAnalysisFactory* af;
    AIDA::ITree*            tree;
    AIDA::IHistogram1D*     histo[4];
};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif





