/**************************************************************************************
 * Header File:
 *    Cfg : Content of a *.cfg file.
 * Author:
*    Carlos Leon. MSG-BYU
 *************************************************************************************/

#ifndef CFG_h
#define CFG_h

#include <iostream>
#include <fstream>
#include <stdio.h>
#include <string>
#include <vector>
#include <sstream>      //  used for  stringstream

#include "Poscar.h"
#include "Atom.h"
#include "VectT.h"

using namespace std;

/**************************************************************************************
 * CFG
 * Contents of a *.cfg file
 *************************************************************************************/
class Cfg
{
private:
   string head1;
   string head2;
   string head3;
   string head4;
   string featureID;
   string tail;
   
   string getAtomLine(int cont, Atom* pAtom);
   
public:
   string ID;
   VectT<float> vfA;
   VectT<float> vfB;
   VectT<float> vfC;
   VectT<int> vComposition;
   vector<Atom*> pAtoms;

   // non-default constructor
   Cfg(string ID, Poscar poscar);
   
   // setters
   void setA(VectT<float> vfA) {this->vfA = vfA;}
   void setB(VectT<float> vfB) {this->vfA = vfB;}
   void setC(VectT<float> vfC) {this->vfA = vfC;}
   
   void push_atom(char chemType, VectT<float> position);
   vector<string> getCfgLines();
   void getCfgFromPoscarClass(string ID, Poscar poscar);
   
   friend ostream &operator << (ostream &out, Cfg &cfg)
   {
      vector<string> cfgLines = cfg.getCfgLines();
      for (int i = 0; i < cfgLines.size(); i++)
         out << cfgLines[i] << endl;
      return out;
   }

   void display();

};

#endif /* CFG_h */

