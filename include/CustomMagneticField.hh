#ifndef CustomMagneticField_H
#define CustomMagneticField_H

#include "G4UniformMagField.hh"

class G4FieldManager;

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......


class CustomMagneticField: public G4UniformMagField
{
  public:
  
   CustomMagneticField(G4ThreeVector);  //  The value of the field
   CustomMagneticField();               //  A zero field
  ~CustomMagneticField();  
      
   //Set the field (fieldValue,0,0)
   void SetMagFieldValue(G4double fieldValue);
   void SetMagFieldValue(G4ThreeVector fieldVector);
      
   G4ThreeVector GetConstantFieldValue();

  protected:

      // Find the global Field Manager
      G4FieldManager* GetGlobalFieldManager();   // static 
};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif
