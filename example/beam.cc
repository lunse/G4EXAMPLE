#include "G4Types.hh"

#ifdef G4MULTITHREADED
#include "G4MTRunManager.hh"
#else
#include "G4RunManager.hh"
#endif

#include "G4UImanager.hh"
#include "Randomize.hh"

#include "DetectorConstruction.hh"
#include "QGSP_BIC_HP.hh"
#include "ActionInitialization.hh"
#include "G4UIExecutive.hh"
#include "G4VisExecutive.hh"
#include "FTFP_BERT_HP.hh"

int main(int argc,char** argv) {

  G4UIExecutive* ui = nullptr;
  if (argc == 1) ui = new G4UIExecutive(argc,argv);

  G4Random::setTheEngine(new CLHEP::RanecuEngine);

  #ifdef G4MULTITHREADED
    G4MTRunManager* runManager = new G4MTRunManager;
    G4int nThreads = G4Threading::G4GetNumberOfCores();
    if (argc==3) nThreads = G4UIcommand::ConvertToInt(argv[2]);
    runManager->SetNumberOfThreads(nThreads);
  #else
    G4RunManager* runManager = new G4RunManager;
  #endif

  runManager->SetUserInitialization(new DetectorConstruction);
  runManager->SetUserInitialization(new FTFP_BERT_HP);
  runManager->SetUserInitialization(new ActionInitialization());
  runManager->Initialize();


  G4VisManager* visManager = nullptr;

  G4UImanager* UImanager = G4UImanager::GetUIpointer();

  if (ui)  {
   visManager = new G4VisExecutive;
   visManager->Initialize();
   UImanager->ApplyCommand("/control/execute vis.mac");
   ui->SessionStart();
   delete ui;
  }
  else  {

   G4String command = "/control/execute ";
   G4String fileName = argv[1];
   UImanager->ApplyCommand(command+fileName);
  }

  delete visManager;
  delete runManager;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

