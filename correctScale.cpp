
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>      //  used for  stringstream

#include <cstdlib>
#include <cmath>
#include <cassert>

#include "Cfg.h"
#include "Poscar.h"
#include "Atom.h"
#include "VectT.h"

using namespace std;

int countLines(string fileNames)
{
   ifstream fin(fileNames.c_str());
   int i = 0;
   string line;
   while (!fin.eof())
   {
      getline(fin, line);
      if ( line != string("") ) // avoids possible blank lines
         i++;
   }
   fin.close();
   return i;
}



void ls2file(string folderName, string fileNames)
{
   //   cout << "we are in " << endl;
   //   system("pwd");
   string run = "ls " + folderName + "/ > " + string("0tem");
   cout << run << endl;
   system(run.c_str());
   
   //cut the first line (has the file name)
   run = string ("sed " ) + string("-i ") + string( " \'1d\' ") + string("/0tem");
   cout << run << endl;
   system(run.c_str());
   
   run = string("mv ") + "0tem  " + fileNames;
   cout << run << endl;
   system(run.c_str());
}



// volumen per atom in a BCC, FCC, HCP crystal type
float vAtomBcc(float a)
{
   float fact = 0.5;
   return fact * pow(a,3.0);
}

float vAtomFcc(float a)
{
   float fact = 0.25;
   return fact * pow(a,3.0);
}

float vAtomHcp(float a)
{
   float fact = pow(2.0, 0.5) / 2.0;
   return fact * pow(a,3.0);
}

float getRequiredVol(int nCo, int nNi, int nTi)
{
   float l_Co_bcc1 = 2.729998;
   float l_Co_fcc1 = 3.46229;
   float l_Co_hcp1 = 2.446759;
   
   float l_Ni_bcc2 = 2.79442;
   float l_Ni_fcc2 = 3.51373;
   float l_Ni_hcp4 = 2.483224;
   
   float l_Ti_bcc3 = 3.21886;
   float l_Ti_fcc3 = 4.100774;
   float l_Ti_hcp6 = 2.914298;
   
   float requiredVol = nCo * vAtomHcp(l_Co_hcp1)
                       + nNi * vAtomFcc(l_Ni_fcc2)
                       + nTi * vAtomHcp(l_Ti_hcp6);
   return requiredVol;
}

float getCorrectScale(Poscar myPoscar)
{
   float latticeVol = myPoscar.vfA( myPoscar.vfB, myPoscar.vfC);
   int nCo = myPoscar.vComposition[0];
   int nNi = myPoscar.vComposition[1];
   int nTi = myPoscar.vComposition[2];
   
   float requiredVol  = getRequiredVol(nCo, nNi, nTi);
   float correctScale = pow( (requiredVol / latticeVol), 1.0/3.0 );
   return correctScale;
}

vector<string> getCfgLinesFromPoscar(string ID, Poscar myPoscar)
{
   float scale = getCorrectScale(myPoscar);
   myPoscar.convertToCartesian(scale);

   // at the end, correctedScale must be 1.0, since everything was converted to
   // cartesian coordinates!
   assert(getCorrectScale(myPoscar) == 1.0);
   
   cout << myPoscar << endl;
   
   Cfg cfg(ID, myPoscar);
   cout << cfg << endl;
   vector<string> vlinesCfg = cfg.getCfgLines();
   
   return vlinesCfg;
}


int main()
{
   string fileNames = "fileNames.txt";
   vector<string> poscarLines;
   vector<string> cfgLines;
   
   int n_ary;
   int nCo = 0;
   int nNi = 0;
   int nTi = 0;
   int nElements;
   string prototypeName;
   string ID;
   VectT<int> vComposition;
   
   int nLines = countLines(fileNames);
   
   ifstream fin(fileNames.c_str());
   for (int i = 0; i < nLines; i++)
   {
      getline(fin, prototypeName);
      
      Poscar myPoscar(prototypeName);
      vComposition = myPoscar.vComposition;
      
      n_ary = vComposition.size();
      nCo   = vComposition[0];
      nNi   = vComposition[1];
      nTi   = vComposition[2];
      nElements = nCo + nNi + nTi;
      
      if (nElements < 11)
      {
         cout << prototypeName << endl;
         ID = prototypeName;
         cfgLines = getCfgLinesFromPoscar(ID, myPoscar);
            
         return 0;
            
//            string newFile = string("fixed_") + prototypeName;
//            ofstream foutNew(newFile.c_str());
//            for (int j = 0; j < poscarLines.size(); j++)
//            {
//               foutNew << poscarLines[j] << endl;
//            }
//            foutNew.close();
//
//            string cfgFile = string("CFG_") + prototypeName + string(".cfg");
//            ofstream foutCFG(cfgFile.c_str());
//            for (int j = 0; j < cfgLines.size(); j++)
//            {
//               foutCFG << cfgLines[j] << endl;
//            }
//            foutCFG.close();


         
      }
      
//         if ( ((nA == 3)&&(nB == 1)) || ((nA == 1)&&(nB == 3)) )
//         {
//            cout << prototypeName << endl;
//            lines = getPoscar(nElements, prototypeName);
//         }
         
      
      
      
      
   }
   fin.close();
   
   
   return 0;
}

