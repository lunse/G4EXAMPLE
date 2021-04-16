
#include "EventAction.hh"
#include "Analysis.hh"
#include "G4Event.hh"
#include "G4UnitsTable.hh"
#include "G4SystemOfUnits.hh"
#include "RunAction.hh"


EventAction::EventAction(RunAction* runAction)
:G4UserEventAction(),
 fTotalEnergyDeposit(0.),
 fRunAction(runAction)
{ }


EventAction::~EventAction()
{ }


void EventAction::BeginOfEventAction( const G4Event*)
{  
 fTotalEnergyDeposit = 0.;
}


void EventAction::EndOfEventAction( const G4Event*)
{ 
  if (fTotalEnergyDeposit>0.)   
  {                      
  G4AnalysisManager* analysisManager = G4AnalysisManager::Instance();
  analysisManager->FillH1(1, fTotalEnergyDeposit/MeV);
  fRunAction->AddEdep(fTotalEnergyDeposit/MeV);
  }
}

