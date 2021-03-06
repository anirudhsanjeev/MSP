#ifndef CustomDetectorMessenger_h
#define CustomDetectorMessenger_h 1

#include "globals.hh"
#include "G4UImessenger.hh"
#include "G4UIcmdWith3VectorAndUnit.hh"
class CustomDetectorConstruction;
class G4UIdirectory;
class G4UIcmdWithAString;
class G4UIcmdWithADoubleAndUnit;

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

class CustomDetectorMessenger: public G4UImessenger
{
  public:
    CustomDetectorMessenger(CustomDetectorConstruction*);
   ~CustomDetectorMessenger();
    
    void SetNewValue(G4UIcommand*, G4String);
    
  private:
    CustomDetectorConstruction* myDetector;
    
    /*G4UIdirectory*             N02Dir;
    G4UIdirectory*             detDir;
    G4UIcmdWithAString*        TargMatCmd;
    G4UIcmdWithAString*        ChamMatCmd;    
    G4UIcmdWithADoubleAndUnit* FieldCmd;
    G4UIcmdWithADoubleAndUnit* StepMaxCmd;*/
    G4UIdirectory* customDir;
    G4UIdirectory* detDir;
    G4UIcmdWithADoubleAndUnit* CubeSizeCmd;
    G4UIcmdWith3VectorAndUnit* CubeAtCmd;
};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif

