

#ifndef RunAction_h
#define RunAction_h 1

#include "Analysis.hh"

#include "G4UserRunAction.hh"
#include "globals.hh"
#include "G4Accumulable.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

class G4Run;

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

class RunAction : public G4UserRunAction
{
  public:
    RunAction();
   ~RunAction();

  public:
    virtual void BeginOfRunAction(const G4Run*);
    virtual void   EndOfRunAction(const G4Run*);

    void AddEdep (G4double edep);

  private:
        G4Accumulable<G4double> fEdep;
        G4Accumulable<G4double> fEdep2;
};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif

