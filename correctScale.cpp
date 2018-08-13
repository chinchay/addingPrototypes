/**************************************************************************************
 * Source File:
 *    correctScale
 * Author:
 *    Carlos Leon. MSG-BYU
 *************************************************************************************/

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
#include "ChemicalTypes.h"

using namespace std;

/**************************************************************************************
 * countLines
 *************************************************************************************/
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

/**************************************************************************************
 * ls2file
 *************************************************************************************/
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
/**************************************************************************************
 * vAtomBcc:
 *************************************************************************************/
float vAtomBcc(float a)
{
   float fact = 0.5;
   return fact * pow(a,3.0);
}

/**************************************************************************************
 * vAtomFcc
 *************************************************************************************/
float vAtomFcc(float a)
{
   float fact = 0.25;
   return fact * pow(a,3.0);
}

/**************************************************************************************
 * vAtomHcp
 *************************************************************************************/
float vAtomHcp(float a)
{
   float fact = pow(2.0, 0.5) / 2.0;
   return fact * pow(a,3.0);
}

/**************************************************************************************
 * getRequiredVol
 *************************************************************************************/
float getRequiredVol(Poscar poscar)
//float getRequiredVol(int nCo, int nNi, int nTi)
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
   
   int nAtoms = poscar.atoms.size();
   int chemType;
   float requiredVol = 0;
   float temp;

//   int nAllElements = chemTypes.size();
//   assert(nAtoms <= nAllElements);

   
   for (int i = 0; i < nAtoms; i++)
   {
      chemType = poscar.atoms[i].getChemType();
      switch (chemType)
      {
         case 0:
            temp = vAtomHcp(l_Co_hcp1);
            break;
         case 1:
            temp = vAtomFcc(l_Ni_fcc2);
            break;
         case 2:
            temp = vAtomHcp(l_Ti_hcp6);
            break;
         default:
            cout << "INTRODUCE MORE DATA!" << endl;
            break;
      }
      
      requiredVol += temp;
   }
   
//   float requiredVol = nCo * vAtomHcp(l_Co_hcp1)
//                       + nNi * vAtomFcc(l_Ni_fcc2)
//                       + nTi * vAtomHcp(l_Ti_hcp6);
   
   return requiredVol;
}

/**************************************************************************************
 * getCorrectScale
 *************************************************************************************/
float getCorrectScale(Poscar poscar)
{
   float latticeVol = poscar.vfA( poscar.vfB, poscar.vfC);
   float requiredVol  = getRequiredVol(poscar);
   float correctScale = pow( (requiredVol / latticeVol), 1.0/3.0 );
   return correctScale;
}

/**************************************************************************************
 * areEqual: compares to floats.
 *************************************************************************************/
bool areEqual(float lhs, float rhs)
{
   float eps = 0.00001;
   return ( (lhs - eps <= rhs) || (rhs <= lhs + eps) );
}

/**************************************************************************************
 * getCfgFromPoscar:
 *************************************************************************************/
Cfg getCfgFromPoscar(string ID, Poscar poscar)
{
   float scale = getCorrectScale(poscar);
   poscar.convertToCartesian(scale);

   // at the end, correctedScale must be 1.0, since everything was converted to
   // cartesian coordinates!
   assert( areEqual(getCorrectScale(poscar), 1.0) );
   
   Cfg cfg(ID, poscar);
   
//   cout << poscar << endl;
//   cout << cfg << endl;
   
   return cfg;
}

string remove_extension(const string& filename)
{
   // from
   // stackoverflow.com/questions/6417817/easy-way-to-remove-extension-from-a-filename
   size_t lastdot = filename.find_last_of(".");
   if (lastdot == string::npos) return filename;
   return filename.substr(0, lastdot);
}

/**************************************************************************************
 * Main:
 *************************************************************************************/
int main()
{
   string fileNames = "fileNames.txt";
   vector<string> poscarLines;
   vector<string> cfgLines;
   
   VectT<string> allElementNames;
   allElementNames.push_back(string("Co"));
   allElementNames.push_back(string("Ni"));
   allElementNames.push_back(string("Ti"));
   
   int n_ary;

   int nAtoms;
   string prototypeName;
   string ID;
   VectT<int> vComposition;
   
   int nLines = countLines(fileNames);
   
   ifstream fin(fileNames.c_str());
   
   int m = 0;
   for (int i = 0; i < nLines; i++)
   {
      getline(fin, prototypeName);
      
      Poscar prototypePoscar(prototypeName);
      VectT<float> pos = prototypePoscar.atoms[0].getPosition();
//      cout << i << endl;
//      cout << "position = " <<pos << endl;
      
      
      vComposition = prototypePoscar.vComposition;
      
      n_ary = vComposition.size();
      nAtoms = vComposition.getSumComponents();
      
      if (nAtoms < 11)
      {
         cout << prototypeName << endl;
//         ID = prototypeName;
         
//         cout << "COMIENZO..." << endl;
//         cout << prototypePoscar << endl;
         
//         n_ary = 3;
         VectT<ChemicalTypes> listChemTypes = getVectMixChemTypes(allElementNames, n_ary);
//         cout << "________________________________________________________" << endl;

         for (int k = 0; k < listChemTypes.size(); k++)
         {
//            cout << listChemTypes[k].types << " >>>> " << listChemTypes[k].head << endl << endl;
            
            // here COPY CONSTRUCTOR is used!!! but not uses directly the =operator !!
            // equivalent to: mixPoscar(prototypePoscar)
            Poscar mixPoscar = prototypePoscar;
            
            mixPoscar.head = listChemTypes[k].head + string(" # # # # # # # ") + mixPoscar.head;
            mixPoscar.setChemicals(listChemTypes[k].types, allElementNames);
            
            ID = to_string(k) + string("___") + remove_extension(prototypeName);
            
            Cfg cfg;
            cfg = getCfgFromPoscar(ID, mixPoscar);
            
            string newNamePoscar = string("POSCAR_") + ID;
            string nameCfgFile = ID + (".cfg");
            
            ofstream fout(newNamePoscar.c_str());
            fout << mixPoscar;
            fout.close();
            
            string fileNameCfg = ID + string(".cfg");
            ofstream foutCfg(fileNameCfg.c_str());
            foutCfg << cfg << endl;
            foutCfg.close();
            
            
         }
                  
//         if (m == 2)
//            return 0;
         
         m++;
         
      }
   }
   fin.close();

   return 0;
}

