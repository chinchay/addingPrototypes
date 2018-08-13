/**************************************************************************************
 * Header File:
 *    Poscar : Content of a POSCAR file.
 * Author:
*    Carlos Leon. MSG-BYU
 *************************************************************************************/

#ifndef POSCAR_h
#define POSCAR_h

#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <iomanip>

#include "VectT.h"
#include "Atom.h"
using namespace std;

class Poscar
{
private:
   int chemType;
   void latticeVectorsToCartesian(float scale);
   string getCoordType();
   void getPoscarFromFile(string fileName);
   int getChemTypeForAnAtom(int i);
   VectT<float> getCartFromFract(VectT<float> fractional); // To Cartesian coords.
   
   template <class T>
   VectT<T> getChemPerAtom(VectT<T> vecOfChems);
   
public:
   string head;
   float scale;
   VectT<float> vfA;
   VectT<float> vfB;
   VectT<float> vfC;
   VectT<int> chemTypes;   // chemTypes       = [0, 1, 2], for example
   VectT<string> chemNames;   // chemNames   = [Co Ni Ti], for example
   VectT<int> vComposition; // vComposition  = [ 4,  2,  2], for example
   VectT<int> chemTypesPerAtom; // = [0 0 0 0 1 1 2 2] for example
   VectT<string> chemNamesPerAtom; // = [Co Co Co Co Ni Ni Ti Ti ] for example
   char coordinatesType;
   vector<Atom> atoms;
   
   Poscar(){} // default constructor
   Poscar(const Poscar &poscar) {*this = poscar;} // copyConstructor uses =Operator
   Poscar(string fileName) {getPoscarFromFile(fileName);}
   Poscar &operator = (const Poscar &rhs); // Asignment (=) operator
   
   void convertToCartesian(float scale);
   void setChemicals(VectT<int> chemTypes, VectT<string> chemNames);
   
   friend ostream &operator << (ostream &out, Poscar &poscar);
   friend ofstream &operator << (ofstream &fout, Poscar &poscar);

};

#endif /* POSCAR_h */

