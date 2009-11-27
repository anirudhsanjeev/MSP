#ifndef CustomEventAction_h
#define CustomEventAction_h 1

#include "G4UserEventAction.hh"

class G4Event;

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
//class CustomAnalysisManager;
#include "CustomAnalysisManager.hh"

class CustomEventAction : public G4UserEventAction
{
  public:
    CustomEventAction(CustomAnalysisManager* = 0);
   ~CustomEventAction();

  public:
    void BeginOfEventAction(const G4Event*);
    void EndOfEventAction(const G4Event*);
  private:
    CustomAnalysisManager* fAnalysisManager;
};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif

    
