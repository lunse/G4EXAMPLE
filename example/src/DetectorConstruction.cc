#include "DetectorConstruction.hh"
#include "G4Material.hh"
#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"
#include "G4SystemOfUnits.hh"
#include "G4NistManager.hh"
#include "G4Box.hh"

DetectorConstruction::DetectorConstruction()
:G4VUserDetectorConstruction()
{}

DetectorConstruction::~DetectorConstruction()
{}

G4VPhysicalVolume* DetectorConstruction::Construct()
{

  G4double a, z;
  G4double density;  
  G4int ncomponents;
 
  G4Element* C = new G4Element("Carbon"  ,"C" , z= 6., a= 12.01*g/mole);
  G4Element* B = new G4Element("B"  ,"B" , z= 5.,  a= 10.81*g/mole);
  G4Element* Si = new G4Element("Si","Si", z= 14., a= 28.0855*g/mole);

  G4NistManager* nist = G4NistManager::Instance();

  G4Material* env_mat = nist->FindOrBuildMaterial("G4_AIR");
 
  G4Material* M_B4C = new G4Material("B4C", density= 2.52*g/cm3, ncomponents=2);
  M_B4C->AddElement(B, 4);
  M_B4C->AddElement(C, 1);

  G4Material* M_SiC = new G4Material("SiC", density= 3.2*g/cm3, ncomponents=2);
  M_SiC->AddElement(Si, 1);
  M_SiC->AddElement(C, 1);


  G4Box*  solidWorld = new G4Box("World",50*cm,50*cm,50*cm);
  G4LogicalVolume* logicWorld = new G4LogicalVolume(solidWorld, env_mat, "World");
  G4VPhysicalVolume*  physiWorld = new G4PVPlacement(0, G4ThreeVector(), logicWorld, "World", 0,  false, 0);

  G4Box*  box_B4C = new G4Box("box_B4C",5*mm,5*mm,10*um);
  G4LogicalVolume* logicB4C = new G4LogicalVolume(box_B4C, M_B4C, "B4C");
  new G4PVPlacement(0, G4ThreeVector(0,0,10*um), logicB4C, "B4C", logicWorld,  false, 0);

  G4Box*  box_SiC = new G4Box("box_SiC",5*mm,5*mm,50*um);
  G4LogicalVolume* logicSiC = new G4LogicalVolume(box_SiC, M_SiC, "SiC");
  new G4PVPlacement(0, G4ThreeVector(0,0,70*um), logicSiC, "SiC", logicWorld,  false, 0);

  return physiWorld;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
