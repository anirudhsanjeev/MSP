#include "CustomDetectorMessenger.hh"

#include "CustomDetectorConstruction.hh"
#include "G4UIdirectory.hh"
#include "G4UIcmdWithAString.hh"
#include "G4UIcmdWithADoubleAndUnit.hh"
#include "globals.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

CustomDetectorMessenger::CustomDetectorMessenger(CustomDetectorConstruction* myDet)
:myDetector(myDet)
{ 
  customDir = new G4UIdirectory("/custom/");
  customDir->SetGuidance("UI commands specific to this application.");
  
  detDir = new G4UIdirectory("/custom/det/");
  detDir->SetGuidance("detector control.");
  
  /*TargMatCmd = new G4UIcmdWithAString("/N02/det/setTargetMate",this);
  TargMatCmd->SetGuidance("Select Material of the Target.");
  TargMatCmd->SetParameterName("choice",false);
  TargMatCmd->AvailableForStates(G4State_PreInit,G4State_Idle);
  
  ChamMatCmd = new G4UIcmdWithAString("/N02/det/setChamberMate",this);
  ChamMatCmd->SetGuidance("Select Material of the Target.");
  ChamMatCmd->SetParameterName("choice",false);
  ChamMatCmd->AvailableForStates(G4State_PreInit,G4State_Idle);  
  
  FieldCmd = new G4UIcmdWithADoubleAndUnit("/N02/det/setField",this);  
  FieldCmd->SetGuidance("Define magnetic field.");
  FieldCmd->SetGuidance("Magnetic field will be in X direction.");
  FieldCmd->SetParameterName("Bx",false);
  FieldCmd->SetUnitCategory("Magnetic flux density");
  FieldCmd->AvailableForStates(G4State_PreInit,G4State_Idle);
        
  StepMaxCmd = new G4UIcmdWithADoubleAndUnit("/N02/det/stepMax",this);  
  StepMaxCmd->SetGuidance("Define a step max");
  StepMaxCmd->SetParameterName("stepMax",false);
  StepMaxCmd->SetUnitCategory("Length");
  StepMaxCmd->AvailableForStates(G4State_Idle);*/

  CubeSizeCmd = new G4UIcmdWithADoubleAndUnit("/custom/det/cubeSize", this);
  CubeSizeCmd->SetGuidance("Specify the size of the cube");
  CubeSizeCmd->SetParameterName("CubeSize", false);
  CubeSizeCmd->SetUnitCategory("Length");
  CubeSizeCmd->SetDefaultUnit("cm");
  CubeSizeCmd->AvailableForStates(G4State_PreInit, G4State_Idle);

  CubeAtCmd = new G4UIcmdWith3VectorAndUnit("/custom/det/cubeAt", this);
  CubeAtCmd->SetGuidance("Specify the position of a cube");
  CubeAtCmd->SetParameterName("CubeAtX", "CubeAtY", "CubeAtZ", false);
  CubeAtCmd->SetUnitCategory("Length");
  CubeAtCmd->SetDefaultUnit("cm");
  CubeAtCmd->AvailableForStates(G4State_PreInit, G4State_Idle);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

CustomDetectorMessenger::~CustomDetectorMessenger()
{
  /*delete TargMatCmd;
  delete ChamMatCmd;
  delete FieldCmd;
  delete StepMaxCmd;  
  delete detDir;
  delete N02Dir;*/
  delete customDir;
  delete detDir;
  delete CubeSizeCmd;
  delete CubeAtCmd;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void CustomDetectorMessenger::SetNewValue(G4UIcommand* command,G4String newValue)
{ 
  /*if( command == TargMatCmd )
   { myDetector->setTargetMaterial(newValue);}
   
  if( command == ChamMatCmd )
   { myDetector->setChamberMaterial(newValue);}  
  
  if( command == FieldCmd )
   { myDetector->SetMagField(FieldCmd->GetNewDoubleValue(newValue));}
      
  if( command == StepMaxCmd )
   { myDetector->SetMaxStep(StepMaxCmd->GetNewDoubleValue(newValue));}*/

	if(command == CubeSizeCmd)
	{
		myDetector->SetCubeSize(CubeSizeCmd->GetNewDoubleValue(newValue));
	}
	if(command == CubeAtCmd)
	{
		myDetector->AddCubeAt(CubeAtCmd->GetNew3VectorValue(newValue));
	}

}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
