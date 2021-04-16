
#include "SteppingAction.hh"
#include "EventAction.hh"
#include "G4SteppingManager.hh"
#include "G4RunManager.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

SteppingAction::SteppingAction(EventAction* EvAct)
:G4UserSteppingAction(),fEventAction(EvAct)
{ }

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

SteppingAction::~SteppingAction()
{ }

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void SteppingAction::UserSteppingAction(const G4Step* aStep)
{

 G4double EdepStep = aStep->GetTotalEnergyDeposit();
 G4String volume =aStep->GetPreStepPoint()->GetTouchableHandle()->GetVolume()->GetName();
 if (volume=="SiC")
 {
     fEventAction->AddEdep(EdepStep);
     //G4cout<<volume<<G4endl;
 }
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

