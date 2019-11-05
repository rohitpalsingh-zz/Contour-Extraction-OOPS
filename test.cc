#include <iostream>
#include "contour.h"
#include <time.h>
using namespace std;


int main () {

 char inputfilename[200];
 char outputfilename[200];
 clock_t t1,t2;
 contour *c = new contour();
 cout<<"Enter the input filename::";
 cin>>inputfilename;
 cout<<"Enter the Output filename ::";
 cin>>outputfilename;
 cout<<"Reading a EsriFile format"<<endl;
 t1=clock();
 c->readfile(inputfilename);
 cout<<"Extracting Boundary"<<endl;
 c->boundaryextraction(); 
 c->writetofile(outputfilename);
 t2=clock();
 float diff ((float)t2-(float)t1);
 cout<<"Total time :: "<<diff/CLOCKS_PER_SEC<<endl;
}
 
 
