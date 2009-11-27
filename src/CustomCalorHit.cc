/*
 * CustomCalorHit.cc
 *
 *  Created on: 28-Nov-2009
 *      Author: anirudhs
 */

#include "CustomCalorHit.hh"

G4Allocator<CustomCalorHit> CustomCalorHitAllocator;

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

CustomCalorHit::CustomCalorHit()
{
   EdepAbs = 0.; TrackLengthAbs = 0.;
   EdepGap = 0.; TrackLengthGap = 0.;
}



CustomCalorHit::~CustomCalorHit()
{;}


CustomCalorHit::CustomCalorHit(const CustomCalorHit& right)
  : G4VHit(right)
{
  EdepAbs = right.EdepAbs; TrackLengthAbs = right.TrackLengthAbs;
  EdepGap = right.EdepGap; TrackLengthGap = right.TrackLengthGap;
}

const CustomCalorHit& CustomCalorHit::operator=(const CustomCalorHit& right)
{
  EdepAbs = right.EdepAbs; TrackLengthAbs = right.TrackLengthAbs;
  EdepGap = right.EdepGap; TrackLengthGap = right.TrackLengthGap;
  return *this;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

int CustomCalorHit::operator==(const CustomCalorHit& right) const
{
  return (this==&right) ? 1 : 0;
}

void CustomCalorHit::Draw()
{;}

void CustomCalorHit::Print()
{;}
