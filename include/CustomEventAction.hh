#ifndef CustomEventAction_h
#define CustomEventAction_h 1

#include "G4UserEventAction.hh"

class G4Event;

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
//class CustomAnalysisManager;
#include "CustomAnalysisManager.hh"


// Forward declare AIDA classes
namespace AIDA  {
	class IAnalysisFactory;
	class ITree;
	class IHistogram1D;
}

class CustomEventAction : public G4UserEventAction
{
  public:
    //CustomEventAction(CustomAnalysisManager* = 0);

	CustomEventAction(RunAction*)
   ~CustomEventAction();

  public:
    void BeginOfEventAction(const G4Event*);
    void EndOfEventAction(const G4Event*);

    void addEdep(G4double Edep, G4int index)     {TotalEnergyDeposit[index] += Edep;};
    G4double GetEnergyDeposit(G4int index)     {return TotalEnergyDeposit[index];};
    void SetDrawFlag(G4String val)  {drawFlag = val;};
    void SetPrintModulo(G4int val)  {printModulo = val;};

  private:
    CustomAnalysisManager* fAnalysisManager;
    CustomRunAction* Run;
    G4double TotalEnergyDeposit[100];   // Energy deposited in c6f6
    G4String drawFlag;             // control the drawing of event
    G4int                     printModulo;
    //EventActionMessenger*  eventMessenger;

};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif

    
