//
// ********************************************************************
// * DISCLAIMER                                                       *
// *                                                                  *
// * The following disclaimer summarizes all the specific disclaimers *
// * of contributors to this software. The specific disclaimers,which *
// * govern, are listed with their locations in:                      *
// *   http://cern.ch/geant4/license                                  *
// *                                                                  *
// * Neither the authors of this software system, nor their employing *
// * institutes,nor the agencies providing financial support for this *
// * work  make  any representation or  warranty, express or implied, *
// * regarding  this  software system or assume any liability for its *
// * use.                                                             *
// *                                                                  *
// * This  code  implementation is the  intellectual property  of the *
// * GEANT4 collaboration.                                            *
// * By copying,  distributing  or modifying the Program (or any work *
// * based  on  the Program)  you indicate  your  acceptance of  this *
// * statement, and all its terms.                                    *
// ********************************************************************
//
 #include "G4QGSCNeutronBuilder.hh"
 #include "G4ParticleDefinition.hh"
 #include "G4ParticleTable.hh"
 #include "G4ProcessManager.hh"

 G4QGSCNeutronBuilder::
 G4QGSCNeutronBuilder() 
 {
   theMin = 8*GeV;
   theModel = new G4TheoFSGenerator;
   theCascade = new G4StringChipsParticleLevelInterface;
   theModel->SetTransport(theCascade);
   theModel->SetHighEnergyGenerator(&theStringModel);
   theStringDecay = new G4ExcitedStringDecay(&theFragmentation);
   theStringModel.SetFragmentationModel(theStringDecay);
 }

 G4QGSCNeutronBuilder::
 ~G4QGSCNeutronBuilder() 
 {
   delete theStringDecay;
 }

 void G4QGSCNeutronBuilder::
 Build(G4NeutronInelasticProcess & aP)
 {
   theModel->SetMinEnergy(theMin);
   theModel->SetMaxEnergy(100*TeV);
   aP.RegisterMe(theModel);
   aP.AddDataSet(&theXSec);  
 }

 // 2002 by J.P. Wellisch