

#include "RunAction.hh"

#include "G4Run.hh"
#include "G4RunManager.hh"

#include "G4SystemOfUnits.hh"
#include "Randomize.hh"
#include "G4AccumulableManager.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

RunAction::RunAction()
 : G4UserRunAction(),
   fEdep(0.),
   fEdep2(0.)
{
  G4AnalysisManager* analysisManager = G4AnalysisManager::Instance();
  analysisManager->SetFirstHistoId(1);
  analysisManager->SetNtupleMerging(true);
  analysisManager->CreateH1("1","energy spectrum",100,0.,10.);

  G4AccumulableManager* accumulableManager = G4AccumulableManager::Instance();
   accumulableManager->RegisterAccumulable(fEdep);
   accumulableManager->RegisterAccumulable(fEdep2);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

RunAction::~RunAction()
{
   delete G4AnalysisManager::Instance();
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void RunAction::BeginOfRunAction(const G4Run*)
{
  G4AnalysisManager* analysisManager = G4AnalysisManager::Instance();
  G4String fileName = "beam";
  analysisManager->OpenFile(fileName);
  G4AccumulableManager* accumulableManager = G4AccumulableManager::Instance();
  accumulableManager->Reset();
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void RunAction::EndOfRunAction(const G4Run* Run)
{  
    G4int Num=Run->GetNumberOfEvent();
  G4AnalysisManager* analysisManager = G4AnalysisManager::Instance();
  analysisManager->Write();
  analysisManager->CloseFile();

  // Merge accumulables
    G4AccumulableManager* accumulableManager = G4AccumulableManager::Instance();
    accumulableManager->Merge();

    // Compute dose = total energy deposit in a run and its variance
    //
    G4double edep  = fEdep.GetValue();
    G4double edep2 = fEdep2.GetValue();


    if (IsMaster())
    {
      G4double rms = std::sqrt(std::abs(edep2 - edep*edep)/Num);
      //G4cout<<"Enengy: "<<edep<<" MeV error: "<<rms<<   G4endl;
       G4String OutEName="detector.txt";

        std::fstream dataEfile;
        dataEfile.open(OutEName,std::ios::out|std::ios::app);
           dataEfile<<"Enengy: "<<edep<<" MeV error: "<<rms<<   G4endl;
        dataEfile.close();
    }
}

void RunAction::AddEdep(G4double edep)
{
  fEdep  += edep;
  fEdep2 += edep*edep;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
