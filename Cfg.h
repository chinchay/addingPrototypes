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
   
public:
   string ID;
   VectT<float> vfA;
   VectT<float> vfB;
   VectT<float> vfC;
   VectT<int> vComposition;
   vector<Atom> atoms;

   Cfg(){} // default constructor
   Cfg(const Cfg &cfg) {*this = cfg;} // copy constructor uses the = operator.
   Cfg &operator = (const Cfg &rhs); // Asignment (=) operator
   
   // non-default constructor
   Cfg(string ID, Poscar poscar);
   
   // setters
   void setA(VectT<float> vfA) {this->vfA = vfA;}
   void setB(VectT<float> vfB) {this->vfA = vfB;}
   void setC(VectT<float> vfC) {this->vfA = vfC;}
   
//   void push_atom(char chemType, VectT<float> position);
   void getCfgFromPoscarClass(string ID, Poscar poscar);
   
   friend ostream &operator << (ostream &out, Cfg &cfg);
   friend ofstream &operator << (ofstream &fout, Cfg &cfg);

};

#endif /* CFG_h */

