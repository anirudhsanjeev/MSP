#ifndef CustomRunAction_h
#define CustomRunAction_h 1

#include "G4UserRunAction.hh"
#include "globals.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

class G4Run;

class CustomRunAction : public G4UserRunAction
{
  public:
    CustomRunAction(CustomAnalysisManager* = 0);
   ~CustomRunAction();

  public:
    void BeginOfRunAction(const G4Run*);
    void EndOfRunAction(const G4Run*);
  private:
    AnaEx01AnalysisManager* fAnalysisManager;
};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif





