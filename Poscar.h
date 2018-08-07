/**************************************************************************************
 * Header File:
 *    Poscar : Content of a POSCAR file.
 * Author:
*    Carlos Leon. MSG-BYU
 *************************************************************************************/

#ifndef POSCAR_h
#define POSCAR_h

#include <iostream>
#include <fstream>
#include <stdio.h>
#include <string>
#include <vector>
#include <sstream>      //  used for  stringstream

#include "VectT.h"
#include "Atom.h"
using namespace std;

class Poscar
{
private:
   int chemType;
   void latticeVectorsToCartesian(float scale);
   
   // change to cartesian coordiantes ( using vfA, vfC, vfC in CARTESIANS !! )
   VectT<float> getCartesianFromFractional(VectT<float> fractional);
   
   int getTypeChem(int cont, VectT<int> vComposition);
   
public:
   string head;
   float scale;
   VectT<float> vfA;
   VectT<float> vfB;
   VectT<float> vfC;
   VectT<int> vComposition;
   char coordinatesType;
   vector<Atom*> pAtoms;
   
   Poscar(string fileName) {getPoscarFromFile(fileName);}
   void getPoscarFromFile(string fileName);
   vector<string> getPoscarLines();
   void convertToCartesian(float scale);
   
   friend ostream &operator << (ostream &out, Poscar &poscar)
   {
      vector<string> poscarLines = poscar.getPoscarLines();
      for (int i = 0; i < poscarLines.size(); i++)
         out << poscarLines[i] << endl;
      return out;
   }
};

#endif /* POSCAR_h */

