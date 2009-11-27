/*
 * CustomCalorimeterDetector.cc
 *
 *  Created on: 28-Nov-2009
 *      Author: Anirudh Sanjeev
 */

#include "CustomCalorimeterDetector.hh"
#include "CustomCalorHit.hh"
#include "CustomDetectorConstruction.hh"

#include "G4VPhysicalVolume.hh"
#include "G4Step.hh"
#include "G4VTouchable.hh"
#include "G4TouchableHistory.hh"
#include "G4SDManager.hh"

#include "G4ios.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

CustomCalorimeterDetector::CustomCalorimeterDetector(G4String name,
                                   CustomDetectorConstruction* det)
:G4VSensitiveDetector(name),Detector(det)
{
  collectionName.insert("CalCollection");
  HitID = new G4int[500];
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

CustomCalorimeterDetector::~CustomCalorimeterDetector()
{
  delete [] HitID;
}

void CustomCalorimeterDetector::Initialize(G4HCofThisEvent*)
{
  /*CalCollection = new CustomHitsDetection
                      (SensitiveDetectorName,collectionName[0]);
  for (G4int j=0;j<Detector->GetNbOfLayers();j++) {HitID[j] = -1;};*/
}

G4bool CustomCalorimeterDetector::ProcessHits(G4Step* aStep,G4TouchableHistory*)
{
  G4double edep = aStep->GetTotalEnergyDeposit();

  G4double stepl = 0.;
  if (aStep->GetTrack()->GetDefinition()->GetPDGCharge() != 0.)
      stepl = aStep->GetStepLength();

  if ((edep==0.)&&(stepl==0.)) return false;

  G4TouchableHistory* theTouchable
    = (G4TouchableHistory*)(aStep->GetPreStepPoint()->GetTouchable());

  G4VPhysicalVolume* physVol = theTouchable->GetVolume();
  //theTouchable->MoveUpHistory();
  //G4int LayerNumber = 0;
  //if (Detector->GetNbOfLayers()>1) LayerNumber = theTouchable->GetReplicaNumber(1);

  /*if (HitID[LayerNumber]==-1)
    {
      CustomCalorHit* calHit = new CustomCalorHit();
      if (physVol == Detector->GetAbsorber()) calHit->AddAbs(edep,stepl);
      if (physVol == Detector->GetGap     ()) calHit->AddGap(edep,stepl);
      HitID[LayerNumber] = CalCollection->insert(calHit) - 1;
      if (verboseLevel>0)
        G4cout << " New Calorimeter Hit on layer: " << LayerNumber << G4endl;
    }
  else
    {
      if (physVol == Detector->GetAbsorber())
         (*CalCollection)[HitID[LayerNumber]]->AddAbs(edep,stepl);
      if (physVol == Detector->GetGap())
         (*CalCollection)[HitID[LayerNumber]]->AddGap(edep,stepl);
      if (verboseLevel>0)
        G4cout << " Energy added to Layer: " << LayerNumber << G4endl;
    }*/
  CustomCalorHit* calHit = new CustomCalorHit();



  return true;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

void CustomCalorimeterDetector::EndOfEvent(G4HCofThisEvent* HCE)
{
  static G4int HCID = -1;
  if(HCID<0)
  { HCID = G4SDManager::GetSDMpointer()->GetCollectionID(collectionName[0]); }
  HCE->AddHitsCollection(HCID,CalCollection);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

void CustomCalorimeterDetector::clear()
{}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

void CustomCalorimeterDetector::DrawAll()
{}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

void CustomCalorimeterDetector::PrintAll()
{}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

