#include<iostream>
using namespace std;


//function to generate random numbers based on H0
double Get_H0Rand(double num){
int y;
if ( num>0 && num<0.333333)
{
	y= 1;
}
else if (0.333333<num && num<0.666666)
{
       y=2;
}
else if (0.666666<num && num<1)
{
 y= 3;
}
return y;
}

//function to generate random numbers based on H1
double Get_H1Rand(double numb){

int x;

if ( numb>0 && numb<0.666666) //more channes to get 1(alpha)
{
    	x=1 ;
}
else if (0.666666<numb && numb<0.833333)
{
    	x= 2;
}
else if (0.833333<numb && numb<1)
{
x= 3;
}

return x;
}


//main function
int rndm(int Num_events){
//files to store the data

ofstream outFileH0;
outFileH0.open("H0_data.txt");
ofstream outFileH1;
outFileH1.open("H1_data.txt");


int H0_r;
int H1_r;	
TRandom3 *rnd = new TRandom3();

for (int i=1; i<=Num_events; i++){

double r = rnd->Rndm();
H0_r = Get_H0Rand(r);
H1_r = Get_H1Rand(r);

outFileH0 << H0_r<<endl;
outFileH1 << H1_r<<endl;
cout<<H0_r<<"    "<<H1_r<<endl;

}

outFileH0.close(); //close files
outFileH1.close();

return 0;
}

