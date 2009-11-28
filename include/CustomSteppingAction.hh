#ifndef CustomSteppingAction_h
#define CustomSteppingAction_h 1

#include "G4UserSteppingAction.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
class CustomEventAction;
class G4SteppingVerbose2;


class CustomSteppingAction : public G4UserSteppingAction
{
  public:
    CustomSteppingAction(CustomEventAction*);
   ~CustomSteppingAction(){};

    void UserSteppingAction(const G4Step*);

  private:
      CustomEventAction* eventAction;
      G4SteppingVerbose2* myVerbose;
};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif
