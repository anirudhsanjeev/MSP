#include "CustomDetectorConstruction.hh"
#include "CustomDetectorMessenger.hh"
#include "CustomChamberParameterisation.hh"
#include "CustomMagneticField.hh"
#include "CustomTrackerSD.hh"
#include "CustomCalorimeterDetector.hh"


#include "G4Material.hh"
#include "G4Box.hh"
#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"
#include "G4PVParameterised.hh"
#include "G4SDManager.hh"
#include "G4GeometryTolerance.hh"
#include "G4GeometryManager.hh"

#include "G4UserLimits.hh"

#include "G4VisAttributes.hh"
#include "G4Colour.hh"

#include "G4ios.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
 
CustomDetectorConstruction::CustomDetectorConstruction()
:solidWorld(0),  logicWorld(0),  physiWorld(0),
 solidTarget(0), logicTarget(0), physiTarget(0), 
 solidTracker(0),logicTracker(0),physiTracker(0), 
 solidChamber(0),logicChamber(0),physiChamber(0), 
 TargetMater(0), ChamberMater(0),chamberParam(0),
 stepLimit(0), fpMagField(0),
 fWorldLength(0.),  fTargetLength(0.), fTrackerLength(0.),
 NbOfChambers(0) ,  ChamberWidth(0.),  ChamberSpacing(0.)
{
  fpMagField = new CustomMagneticField();
  detectorMessenger = new CustomDetectorMessenger(this);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
 
CustomDetectorConstruction::~CustomDetectorConstruction()
{
  delete fpMagField;
  delete stepLimit;
  delete chamberParam;
  delete detectorMessenger;             
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

G4VPhysicalVolume* CustomDetectorConstruction::Construct()
{
    G4double a, z;
    G4double density, temperature, pressure;
    G4int nel;

    //Lead
    G4Material* Pb = 
    new G4Material("Lead", z=82., a= 207.19*g/mole, density= 11.35*g/cm3);
    //Air
    G4Element* N = new G4Element("Nitrogen", "N", z=7., a= 14.01*g/mole);
    G4Element* O = new G4Element("Oxygen"  , "O", z=8., a= 16.00*g/mole);

    G4Material* Air = new G4Material("Air", density= 1.29*mg/cm3, nel=2);
    Air->AddElement(N, 70*perCent);
    Air->AddElement(O, 30*perCent);
    // Print all the materials defined.
    //
    G4cout << G4endl << "The materials defined are : " << G4endl << G4endl;
    G4cout << *(G4Material::GetMaterialTable()) << G4endl;


    // Define the world
    G4Box* experiment_Box = new G4Box ("experiment_Box", 30.0*cm, 30.0*cm, 30.0*cm);
    G4LogicalVolume* experiment_Log = new G4LogicalVolume(experiment_Box, Air, "experiment_Log");
    G4VPhysicalVolume* experiment_Phys = new G4PVPlacement(0,
            G4ThreeVector(0, 0, 0), experiment_Log, "experiment_Physical", 0,
            false, // no boolean operations
            0); // copy number


    G4Box* detector_Box = new G4Box ("detector_Box", 3.0*cm, 3.0*cm, 3.0*cm);
    G4LogicalVolume *detector_Log = new G4LogicalVolume(detector_Box, Pb, "detector_Log");
    G4LogicalVolume *emitter_Log = new G4LogicalVolume(detector_Box, Pb, "emitter_Log");

    // Make an array of 4 detectors

    detector_Phys[0] = new G4PVPlacement(0,
            G4ThreeVector(4.5*cm, 4.5*cm, 0), // Placed at the appropriate location
            emitter_Log, // 3cm cube
            "emitter_Phys_0", // Name
            experiment_Log, // The mother volume.
            false, // no boolean operations
            0); // Copy number
    detector_Phys[0] = new G4PVPlacement(0,
            G4ThreeVector(4.5*cm, 4.5*cm, 0), // Placed at the appropriate location
            detector_Log, // 3cm cube
            "detector_Phys_0", // Name
            experiment_Log, // The mother volume.
            false, // no boolean operations
            0); // Copy number
    detector_Phys[1] = new G4PVPlacement(0,
            G4ThreeVector(-4.5*cm, 4.5*cm, 0), // Placed at the appropriate location
            detector_Log, // 3cm cube
            "detector_Phys_1", // Name
            experiment_Log, // The mother volume.
            false, // no boolean operations
            0); // Copy number
    detector_Phys[2] = new G4PVPlacement(0,
            G4ThreeVector(-4.5*cm, -4.5*cm, 0), // Placed at the appropriate location
            detector_Log, // 3cm cube
            "detector_Phys_2", // Name
            experiment_Log, // The mother volume.
            false, // no boolean operations
            0); // Copy number
    detector_Phys[3] = new G4PVPlacement(0,
            G4ThreeVector(4.5*cm, -4.5*cm, 0), // Placed at the appropriate location
            detector_Log, // 3cm cube
            "detector_Phys_3", // Name
            experiment_Log, // The mother volume.
            false, // no boolean operations
            0); // Copy number

    // Set up sensitive detectors: 3 detectors
    G4SDManager* SDman = G4SDManager::GetSDMpointer();
    if(!calorimeterSD)
    {
    	calorimeterSD = new CustomCalorimeterDetector("CalorSD", this);
    	SDman->AddNewDetector ( calorimeterSD );
    }

    detector_Log->SetSensitiveDetector(calorimeterSD);
    //detector_Phys[2]->SetSensitiveDetector(calorimeterSD);
    //detector_Phys[3]->SetSensitiveDetector(calorimeterSD);


    // Set the viusalization colors for all the wireframes!
    G4VisAttributes* experiment_VisAtt = new G4VisAttributes(G4Colour(1.0,0.2,0.6));
    experiment_Log->SetVisAttributes(experiment_VisAtt);

    G4VisAttributes* detector_VisAtt = new G4VisAttributes(G4Colour(1.0,1.0,0.0));
    detector_Log->SetVisAttributes(detector_VisAtt);

    PrintCalorimeters();

    return experiment_Phys;
}


 
void CustomDetectorConstruction::setTargetMaterial(G4String materialName)
{
  // search the material by its name 
  G4Material* pttoMaterial = G4Material::GetMaterial(materialName);  
  if (pttoMaterial)
     {TargetMater = pttoMaterial;
      logicTarget->SetMaterial(pttoMaterial); 
      G4cout << "\n----> The target is " << fTargetLength/cm << " cm of "
             << materialName << G4endl;
     }             
}
 
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void CustomDetectorConstruction::setChamberMaterial(G4String materialName)
{
  // search the material by its name 
  G4Material* pttoMaterial = G4Material::GetMaterial(materialName);  
  if (pttoMaterial)
     {ChamberMater = pttoMaterial;
      logicChamber->SetMaterial(pttoMaterial); 
      G4cout << "\n----> The chambers are " << ChamberWidth/cm << " cm of "
             << materialName << G4endl;
     }             
}
 
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
 
void CustomDetectorConstruction::SetMagField(G4double fieldValue)
{
  fpMagField->SetFieldValue(fieldValue);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void CustomDetectorConstruction::SetMaxStep(G4double maxStep)
{
  if ((stepLimit)&&(maxStep>0.)) stepLimit->SetMaxAllowedStep(maxStep);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
void CustomDetectorConstruction::PrintCalorimeters()
{

}

G4int CustomDetectorConstruction::GetDetectorCubeID(G4VPhysicalVolume *target)
{
	// Get the cube id from the physical volume

	for(int i = 0; i < 4; i++) //TODO: make more flexible
	{
		if(detector_Phys[i] == target)
		{
			G4cout << "Registered a positive impact in "<< i << "\n";
			return i+1;
		}
	}

	// failure
	return 0;
}
