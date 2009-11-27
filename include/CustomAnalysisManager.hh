/*
 * CustomAnalysisManager.hh
 *
 *  Created on: 28-Nov-2009
 *      Author: anirudhs
 */

#ifndef CUSTOMANALYSISMANAGER_HH_
#define CUSTOMANALYSISMANAGER_HH_

#ifdef G4ANALYSIS_USE

class G4Run;
class G4Event;
class G4Step;

namespace AIDA {
  class IAnalysisFactory;
  class ITree;
  class IHistogram1D;
  class ITuple;
}

class CustomAnalysisManager {
public:
  CustomAnalysisManager(AIDA::IAnalysisFactory*);
  virtual ~CustomAnalysisManager();
public:
  virtual void BeginOfRun(const G4Run*);
  virtual void EndOfRun(const G4Run*);
  virtual void BeginOfEvent(const G4Event*);
  virtual void EndOfEvent(const G4Event*);
  virtual void Step(const G4Step*);
private:
  int fCalorimeterCollID;
  AIDA::IAnalysisFactory* fAIDA;
  AIDA::ITree* fTree;
  AIDA::IHistogram1D* fEAbs;
  AIDA::IHistogram1D* fLAbs;
  AIDA::IHistogram1D* fEGap;
  AIDA::IHistogram1D* fLGap;
  AIDA::ITuple* fTuple;
};

#else

class CustomAnalysisManager;

#endif


#endif /* CUSTOMANALYSISMANAGER_HH_ */
