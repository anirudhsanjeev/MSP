/*
 * CustomCalorHit.hh
 *
 *  Created on: 28-Nov-2009
 *      Author: anirudh sanjeev
 */

#ifndef CUSTOMCALORHIT_HH_
#define CUSTOMCALORHIT_HH_

#include "G4VHit.hh"
#include "G4THitsCollection.hh"
#include "G4Allocator.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

class CustomCalorHit : public G4VHit
{
  public:

      CustomCalorHit();
     ~CustomCalorHit();
      CustomCalorHit(const CustomCalorHit&);
      const CustomCalorHit& operator=(const CustomCalorHit&);
      int operator==(const CustomCalorHit&) const;

      inline void* operator new(size_t);
      inline void  operator delete(void*);

      void Draw();
      void Print();

  public:

      void AddAbs(G4double de, G4double dl) {EdepAbs += de; TrackLengthAbs += dl;};
      void AddGap(G4double de, G4double dl) {EdepGap += de; TrackLengthGap += dl;};

      G4double GetEdepAbs()     { return EdepAbs; };
      G4double GetTrakAbs()     { return TrackLengthAbs; };
      G4double GetEdepGap()     { return EdepGap; };
      G4double GetTrakGap()     { return TrackLengthGap; };

  private:

      G4double EdepAbs, TrackLengthAbs;
      G4double EdepGap, TrackLengthGap;

};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

typedef G4THitsCollection<CustomCalorHit> CustomCalorHitsCollection;

extern G4Allocator<CustomCalorHit> CustomCalorHitAllocator;

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

inline void* CustomCalorHit::operator new(size_t)
{
  void* aHit;
  aHit = (void*) CustomCalorHitAllocator.MallocSingle();
  return aHit;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

inline void CustomCalorHit::operator delete(void* aHit)
{
  CustomCalorHitAllocator.FreeSingle((CustomCalorHit*) aHit);
}


#endif /* CUSTOMCALORHIT_HH_ */
