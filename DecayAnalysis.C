/////////////////////////////////////
//Probability distribution Analysis//
//of a hypothetical decay////////////
/////////////////////////////////////
#include<iostream>
//#include"rndm.C"
using namespace std;



int DecayAnalysis(int numEvents){

//arrays to store the data
int H0_arr[numEvents];
int H1_arr[numEvents];


	//open the data files
ifstream File_H0("H0_data.txt");
if(!File_H0.is_open()){
cout<< "Error opening the  H0data file"<<endl;
}

ifstream File_H1("H1_data.txt");
if(!File_H1.is_open()){
cout<< "Error opening the  H1data file"<<endl;
}
//store the data into arrays	
for(int r=0; r<numEvents; r++ )
{
 File_H0 >> H0_arr[r];
 File_H1 >> H1_arr[r];
}
	

File_H0.close(); //close the files
File_H1.close();
//plotting the histo for random data 

auto *h0 = new TH1D("h0", "Histo for H0_data", 10000, 0.5, 3.5);
auto *h1 = new TH1D("h1", "Histo for H1_data", 10000, 0.5, 3.5);

for(int i=0; i<numEvents; i++){

h0->Fill(H0_arr[i]);
h1->Fill(H1_arr[i]);

 }

cout<< H0_arr[9]<< " : "<<H1_arr[9]<<endl;	
//couting the particles 
int numAlpha_H0=0, numBeta_H0=0, numGamma_H0=0;
int numAlpha_H1=0, numBeta_H1=0, numGamma_H1=0;
for(int j=0; j<numEvents; j++){

	//numb of i-particles appeared in the event based on H0 
	//cout<<H0_arr[j]<<endl;
	if(H0_arr[j]==1){

		numAlpha_H0 = numAlpha_H0+1;
	}
	else if(H0_arr[j]==2){
	numBeta_H0 = numBeta_H0 +1;
	}
	else {
	numGamma_H0 = numGamma_H0 +1;
	}

 //numb of j-particles appeared in the event based on H1 
        //cout<<H1_arr[j]<<endl;
        if(H1_arr[j]==1){

                numAlpha_H1 = numAlpha_H1+1;
        }
        else if(H1_arr[j]==2){
        numBeta_H1 = numBeta_H1 +1;
        }
        else {
        numGamma_H1 = numGamma_H1 +1;
        }

}

cout<<"num alpha, beta ana gamma appeard in data are: "<< numAlpha_H0<< "   "<<numBeta_H0<<"  "<<numGamma_H0<<endl;
cout<<"num alpha, beta ana gamma appeard in data are: "<< numAlpha_H1<< "   "<<numBeta_H1<<"  "<<numGamma_H1<<endl;

double Pa_H0= 0.333333, Pb_H0=0.333333, Pg_H0=0.666667; //Hypo H0
double Pa_H1= 0.666666, Pb_H1=0.166667, Pg_H1=0.166667; //Hypo H1

//to get the LLR
double LLR_Pa, LLR_Pb, LLR_Pg, LLR;

auto *hs = new THStack("hs","Log Likelyhood Ratios; LLR; Entries");// to plot the multi histo in one canvas
auto *h0_LLR = new TH1D("h0_LLR", "DecayAnalysis LLR plots", 10000, -0.06,0.06 );
//calculating the likelyhood ratios based on H0

for(int a=1, b=1, g=1; a<numAlpha_H0, b<numBeta_H0, g<numGamma_H0; a++, b++, g++){

LLR_Pa = a*TMath::Log10(Pa_H0/Pa_H1);
LLR_Pb = b*TMath::Log10(Pb_H0/Pb_H1);
LLR_Pg = g*TMath::Log10(Pg_H0/Pg_H1);
//cout<<"LLR Values for each  "<<LLR_Pa<<" :  "<<LLR_Pb<<"  : "<<LLR_Pg<<endl;
LLR = (LLR_Pa/numAlpha_H0)*(LLR_Pb/numBeta_H0)*(LLR_Pg/numGamma_H0);
//cout<<"LLR val: " <<LLR<<endl;
h0_LLR->Fill(LLR);
}

//calculating the likelyhood ratios based on H0
double LLR_PaH1, LLR_PbH1, LLR_PgH1, LLR_H1;
auto *h1_LLR = new TH1D("h1_LLR", "LLR histo for H1", 10000, 0.06, 0.06);

for(int i=1, j=1, k=1; i<numAlpha_H1, j<numBeta_H1, k<numGamma_H1; i++, j++, k++){

	LLR_PaH1 =  i*TMath::Log10(Pa_H0/Pa_H1);
	LLR_PbH1 =  j*TMath::Log10(Pb_H0/Pb_H1);
	LLR_PgH1 =  k*TMath::Log10(Pg_H0/Pg_H1);

	LLR_H1 = (LLR_PaH1/numAlpha_H1)*(LLR_PbH1/numBeta_H1)*(LLR_PgH1/numGamma_H1);

        //cout<<"LLR val: " <<LLR_H1<<endl;
	h1_LLR->Fill(LLR_H1);

}



//creat canvas 
auto *c = new TCanvas(); 
c->Divide(1, 2);

c->cd(1) ;
h0->SetLineColor(3);
h0->SetFillColor(5);
h0->GetXaxis()->SetTitle("particle-name (1=alpha, 2=beta, 3=gamma)"); //giving titles to axis
h0->GetYaxis()->SetTitle("Number of events");
h0->Draw();

c->cd(2) ;
h1->SetLineColor(2);
h1->SetFillColor(7);
h1->GetXaxis()->SetTitle("particle-name(1=alpha, 2=beta, 3=gamma)"); //giving titles to axis
h1->GetYaxis()->SetTitle("Number of events");
h1->Draw();

/*
h0_LLR->SetLineColor(6);
h0_LLR->SetFillColor(3);
h1_LLR->SetLineColor(4);
h1_LLR->SetFillColor(2);

hs->Add(h0_LLR);
hs->Add(h1_LLR);
hs->SetTitle("Histogram for Log Likelyhood Ratios;LLR;Entries");
hs->Draw();

auto *l = new TLegend(0.1,0.7,0.48,0.9);

l->AddEntry("h0_LLR", "H0 Hypothesis");
l->AddEntry("h1_LLR", "H1 Hypothesis");
l->Draw();

*/

c->SaveAs("Histo_Prob.pdf");

return 0;

}
