#include "G4RunManagerFactory.hh"
#include "G4UImanager.hh"
#include "G4UIExecutive.hh"
#include "G4VisExecutive.hh"
#include "FTFP_BERT.hh"

#include "DetectorConstruction.hh"
#include "ActionInitialization.hh"

int main(int argc,char** argv)
{
  auto* runManager = G4RunManagerFactory::CreateRunManager();

  auto* det = new DetectorConstruction();

  runManager->SetUserInitialization(det);
  runManager->SetUserInitialization(new FTFP_BERT());
  runManager->SetUserInitialization(new ActionInitialization(det));

  auto* visManager = new G4VisExecutive();
  visManager->Initialize();

  auto* UImanager = G4UImanager::GetUIpointer();

  auto* ui = new G4UIExecutive(argc, argv, "Qt");

  UImanager->ApplyCommand("/control/execute ../macros/init_vis.mac");

  ui->SessionStart();

  delete ui;
  delete visManager;
  delete runManager;

  return 0;
}