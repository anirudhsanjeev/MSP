/*
 * CustomCalorimeterDetector.hh
 *
 *  Created on: 28-Nov-2009
 *      Author: Anirudh Sanjeev
 */

#ifndef CUSTOMCALORIMETERDETECTOR_HH_
#define CUSTOMCALORIMETERDETECTOR_HH_

#include "G4VSensitiveDetector.hh"
#include "globals.hh"

class CustomDetectorConstruction;
class G4HCofThisEvent;
class G4Step;
#include "CustomCalorHit.hh"


class CustomCalorimeterDetector : public G4VSensitiveDetector
{
  public:

      CustomCalorimeterDetector(G4String, CustomDetectorConstruction* );
     ~CustomCalorimeterDetector();

      void Initialize(G4HCofThisEvent*);
      G4bool ProcessHits(G4Step*,G4TouchableHistory*);
      void EndOfEvent(G4HCofThisEvent*);
      void clear();
      void DrawAll();
      void PrintAll();

  private:

      CustomCalorHitsCollection*  CalCollection;
      CustomDetectorConstruction* Detector;
      G4int*                   HitID;
};


#endif /* CUSTOMCALORIMETERDETECTOR_HH_ */
