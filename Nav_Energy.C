/*
Rat6.4.1, Updated 9 Feb 2018
*/
#include <RAT/DU/DSReader.hh>
#include <RAT/DU/Utility.hh>
#include <RAT/DS/Entry.hh>
#include <RAT/DS/MC.hh>
#include <RAT/DS/EV.hh>
#include <RAT/DS/PMT.hh>
#include <RAT/DU/PMTInfo.hh>
#include <RAT/TrackNode.hh>
#include <RAT/TrackCursor.hh>
#include <RAT/TrackNav.hh>
#include <iostream>
#include <vector>
#include "TH2D.h"
#include "TH1D.h"
#include "TH3D.h"
#include <TVector3.h>
#include <TMath.h>
#include <TROOT.h>
#include "TFile.h"
void Nav_Energy()
{
    using namespace RAT;
    //using namespace std;
    RAT::DU::DSReader dsReader("trackOn_SNOP_N16Source_center_1e4eventsV641.root");
//  RAT::DU::DSReader dsReader("/media/vphys/seagate/N16/RatSimuData/trackOn_D2O_N16Source_center_10000evts.root");
    TH1F *hSx = new TH1F("hSx","Sx",1200,-6000,6000);
    TH1F *hSy = new TH1F("hSy","Sy",1200,-6000,6000);
    TH1F *hSz = new TH1F("hSz","Sz",1200,-6000,6000);
    TH1F *hTimeElectron = new TH1F("hTimeElectron","child e- global time",100,0,50);
    TH1F *hE_Compton = new TH1F("hE_Compton","compton energy",100,0,10); 
    TH1F *hE_PairProduct = new TH1F("hE_PairProduct","pair production",100,0,10);
    TH1F *hE_PEabsorb = new TH1F("hE_PEabsorb","PEabsorb",100,0,10);
    
    TVector3 pos0; pos0.SetXYZ(0,0,0);
    
    int countBetaOnly =0,countNone=0, count2gamma=0, count1gamma=0, countGammaInside = 0;
    int countCompt = 0, countProd = 0, countPhot = 0;
    for (size_t iEntry = 0; iEntry<dsReader.GetEntryCount();iEntry++)//dsReader.GetEntryCount();iEntry++)
    {
       const RAT::DS::Entry& ds = dsReader.GetEntry(iEntry);
       const RAT::DS::MC& rmc= ds.GetMC();
       int particleNum = rmc.GetMCParticleCount();
       std::cout<<"event "<<iEntry<<"  "<<particleNum<<std::endl;
       //check for e- caused gammas
       //RAT::TrackNav nav(&ds);
       //RAT::TrackCursor c0 = nav.Cursor(false);   
       //c0.GoChild(0);//e- track
       //RAT::TrackNode *n0 = c0.Here();
       //bool flag= 1;bool checkLeak = 0;
       //while(flag)
       //{
         //TString volume = n0->GetStartVolume();
         //TString process = n0->GetProcess();
         //if(process=="Cerenkov")
         //{flag = 0;cout<<"found!"<<endl;}
         //else {
			 //if(c0.IsTrackEnd()) {checkLeak = 1 ; break;} //if hit the bottom, break in case of overflow
			 //else {c0.GoNext(); *n0 = c0.Here();}
			 //}
		//}

       //for the 1st initial gamma
       TVector3 PosFirstGamma;
       if (particleNum>1 )//some events only have electron
       {
          RAT::TrackNav nav1(&ds);
	  RAT::TrackCursor c = nav1.Cursor(false);   
	  c.GoChild(1);//1st gamma
	  RAT::TrackNode *n = c.Here();
	  bool flag= 1;bool checkLeak = 0;
	  while(flag)
	  {
	     TString volume = n->GetStartVolume();
             TString process = n->GetProcess();
		     
             if(volume=="inner_av" && (process =="compt" || process =="conv" ||process =="phot" ))
             {flag = 0;}
             else {
        		 if(c.IsTrackEnd()) {checkLeak = 1 ;  countGammaInside++; break;} //if hit the bottom, break in case of overflow
        		 else {c.GoNext(); RAT::TrackNode *n = c.Here();}
                  }
              //std::cout<<n->GetProcess()<<" "<<n->GetStartVolume()<<std::endl;		      
          }	   
          //  std::cout<<n->GetPosition().X()<<", "<<std::endl;
          if(!checkLeak)
          {
           int childTrack =  n->fChild.size();
           for(int iChild=0;iChild<childTrack;iChild++)
           {
               if((n->fChild[iChild])->GetParticleName()=="e-")
               { 
                //posFirstGamma.SetXYZ(n->GetPosition().X(),n->GetPosition().Y(),n->GetPosition().Z());
                hSx->Fill(n->GetPosition().X());hSy->Fill(n->GetPosition().Y());hSz->Fill(n->GetPosition().Z());
                hTimeElectron->Fill(n->GetGlobalTime());
                if(n->GetProcess()=="compt") {hE_Compton->Fill( (n->fChild[iChild])->GetDepositedEnergy());countCompt++;}
                else if(n->GetProcess()=="conv") {hE_PairProduct->Fill((n->fChild[iChild])->GetDepositedEnergy());countProd++;}
                else if(n->GetProcess()=="phot") {hE_PEabsorb->Fill((n->fChild[iChild])->GetDepositedEnergy());countPhot++;}       
               }   
           }
           count1gamma++;
           delete n;    
          }
       }
      ////for the 2nd initial gamma
      if(particleNum>2)
      {
           RAT::TrackNav nav2(&ds);
           RAT::TrackCursor c2 = nav2.Cursor(false);   
           c2.GoChild(2);//2nd gamma
           RAT::TrackNode *n2 = c2.Here();
           bool flag2= 1;bool checkLeak2 = 0;
           while(flag2)
           {
                TString volume2 = n2->GetStartVolume();
                TString process2 = n2->GetProcess();
                 
                 if(volume2 =="inner_av" && (process2 =="compt" || process2 =="conv" ||process2 =="phot" ))
                 {flag2 = 0;}
                 else {
                   	if(c2.IsTrackEnd()) {checkLeak2 = 1;  countGammaInside++; break;} //if hit the bottom, break in case of overflow
            	else {c2.GoNext(); RAT::TrackNode *n2 = c2.Here();}
                 }
                  //std::cout<<n->GetProcess()<<" "<<n->GetStartVolume()<<std::endl;
                  
           }   
             //  std::cout<<n2->GetPosition().X()<<", "<<std::endl;
              if(!checkLeak2)
              {
               int childTrack2 =  n2->fChild.size();
               for(int iChild=0;iChild<childTrack2;iChild++)
               {
                  if((n2->fChild[iChild])->GetParticleName()=="e-")
                  {   
                    hSx->Fill(n2->GetPosition().X());hSy->Fill(n2->GetPosition().Y());hSz->Fill(n2->GetPosition().Z());
                    hTimeElectron->Fill(n2->GetGlobalTime());
                    if(n2->GetProcess()=="compt") {hE_Compton->Fill((n2->fChild[iChild])->GetDepositedEnergy());}
                     else if(n2->GetProcess()=="conv") {hE_PairProduct->Fill((n2->fChild[iChild])->GetDepositedEnergy());}
                     else if(n2->GetProcess()=="phot") {hE_PEabsorb->Fill((n2->fChild[iChild])->GetDepositedEnergy()); }    
               }
           }   
          }
           delete n2; 
           count2gamma++;
      }
      
      if(particleNum==1) countBetaOnly++;
      if(particleNum==0) countNone++;
    }//for entries     
    std::cout<<"BetaOnly  "<<countBetaOnly<<" 1 gamma "<<count1gamma<<" 2 gamma "<<count2gamma<<" gamma inside events "<<countGammaInside<<std::endl;
    std::cout<<"compt "<<countCompt<<" pair prod "<<countProd<<" pe absorb "<<countPhot<<std::endl;
    
    TFile *ff=new TFile("fSpatial_NewRat.root","RECREATE");
    ff->cd(); hSx->Write();  hSy->Write();hSz->Write();hE_Compton->Write();hE_PairProduct->Write();hE_PEabsorb->Write();
    hTimeElectron->Write();
    //hSx->Draw();

}
