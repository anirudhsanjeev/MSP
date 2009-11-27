class CustomSteppingVerbose;

#ifndef CustomSteppingVerbose_h
#define CustomSteppingVerbose_h 1

#include "G4SteppingVerbose.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

class CustomSteppingVerbose : public G4SteppingVerbose 
{
 public:
   
  CustomSteppingVerbose();
 ~CustomSteppingVerbose();

  void StepInfo();
  void TrackingStarted();

};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif
