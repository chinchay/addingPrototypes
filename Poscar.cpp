/**************************************************************************************
 * Source File:
 *    Poscar : Content of a POSCAR file.
 * Author:
*    Carlos Leon. MSG-BYU
 *************************************************************************************/

#include <iostream>
#include <fstream>
#include <stdio.h>
#include <string>
#include <vector>
#include <sstream>      //  used for  stringstream

#include "Poscar.h"
#include "VectT.h"
#include "Atom.h"
using namespace std;

/**************************************************************************************
 * POSCAR : OPERATOR OVERLOADING = (ASSIGNMENT)
 *************************************************************************************/
Poscar &Poscar::operator = (const Poscar &rhs)
{
   head = rhs.head;
   scale = rhs.scale;
   vfA = rhs.vfA;
   vfB = rhs.vfB;
   vfC = rhs.vfC;
   vComposition = rhs.vComposition;
   coordinatesType = rhs.coordinatesType;
   
   atoms.clear(); // delete all elements if they were defined previously!
   for (int i = 0; i < rhs.atoms.size(); i++)
      atoms.push_back(rhs.atoms[i]);

   return *this;
}

/**************************************************************************************
 * POSCAR : GETPOSCARFROMFILE
 * This functions reads a POSCAR file and saves it into a Poscar class.
 *************************************************************************************/
void Poscar::getPoscarFromFile(string fileName)
{
   ifstream fin(fileName.c_str());
   string line;
   
   int i = 0;
   int j = 0;
   while( !fin.eof() )
   {
      getline(fin, line);
      
      if ( line != string("") )
      {
         stringstream buffer(line);
         
         switch (i)
         {
            case 0:
               head = line;
               break;
               
            case 1:
               buffer >> scale;
               break;
               
               // getting the lattice vectors
            case 2:
               buffer >> vfA;
               break;
            case 3:
               buffer >> vfB;
               break;
            case 4:
               buffer >> vfC;
               break;
               
               // getting composition
            case 5:
               buffer >> vComposition;
               break;
               
            case 6:
               buffer >> coordinatesType;
               break;
               
            default:
               VectT<float> position;
               buffer >> position;
               chemType = getChemTypeForAnAtom(j); // to initialize
               atoms.push_back( Atom( position, chemType, to_string(chemType) ) );
               j++;
               break;
         }
         i++;
      }
   }
   
   fin.close();
}
   
/**************************************************************************************
 * POSCAR : CONVERTTOCARTESIAN
 * This function scales the lattice vectors by the parameter `scale`, and then gets
 * the position of each atom in cartesian coordinates by taking the fractional
 * coordinates saved in atoms[i], for i = 1,2,..., numberOfAtoms.
 *************************************************************************************/
void Poscar::convertToCartesian(float scale = 1.0)
{
   // scale the lattice coordinates, and get them in cartesian coordinates:
   latticeVectorsToCartesian(scale);
   if ( getCoordType() == string("Direct") )
   {
      for (int i = 0; i < atoms.size(); i++)
         atoms[i].setPosition( getCartFromFract( atoms[i].getPosition() ) );
      
      // we have moved everything to cartesian system, so:
      this->coordinatesType = 'c';
      this->scale = 1.0;
   }
   else if ( getCoordType() == string("Cartesian") )
   {
      // position = position
   }
   else
   {
      cout << "PROBLEM. WHAT TYPE OF COORDINATES IS THIS? " << coordinatesType;
      cout << endl;
   }
}

/**************************************************************************************
 * POSCAR : LATTICEVECTORSTOCARTESIAN
 * Just scales the lattice vectors (updating them into cartesian coordinates).
 *************************************************************************************/
void Poscar::latticeVectorsToCartesian(float scale)
{
   this->vfA *= scale;
   this->vfB *= scale;
   this->vfC *= scale;
}

/**************************************************************************************
 * POSCAR : GETCARTFROMFRACT
 * Just convert fractional to cartesian coordinates, using the lattice vectors.
 *************************************************************************************/
VectT<float> Poscar::getCartFromFract(VectT<float> fractional)
{
   return fractional[0] * vfA  +  fractional[1] * vfB  +  fractional[2] * vfC;
}

/**************************************************************************************
 * POSCAR : GETCOORDTYPE
 *
 *************************************************************************************/
string Poscar::getCoordType()
{
   if (tolower(coordinatesType) == 'c')
      return string("Cartesian");
   else if (tolower(coordinatesType) == 'd')
      return string("Direct");
   else
      return string("ERROR_COORDINATES????");
}

/**************************************************************************************
 * POSCAR : GETCHEMTYPEFORANATOM
 *
 *************************************************************************************/
int Poscar::getChemTypeForAnAtom(int i)
{
   if (chemTypesPerAtom.size() == 0)
   {
      VectT<int> chemTypes;
      for (int i = 0; i < vComposition.size(); i++)
         chemTypes.push_back(i);
      this->chemTypesPerAtom = getChemPerAtom(chemTypes);
   }
   return this->chemTypesPerAtom[i];
   
}

/**************************************************************************************
 * POSCAR : SETCHEMICALS
 *
 *************************************************************************************/
void Poscar::setChemicals(VectT<int> chemTypes, VectT<string> chemNames)
{
   this->chemTypes = chemTypes;
   this->chemNames = chemNames;
   
   // Erase here because they were defined previously by default.
   chemTypesPerAtom.clear();
   chemNamesPerAtom.clear();
   
   this->chemTypesPerAtom = getChemPerAtom(chemTypes);
   this->chemNamesPerAtom = getChemPerAtom(chemNames);

   for (int i = 0; i < atoms.size(); i++)
   {
      atoms[i].setChemType( chemTypesPerAtom[i] );
      atoms[i].setChemName( chemNamesPerAtom[i] );
   }
}

/**************************************************************************************
 * POSCAR : GETCHEMPERATOM
 *
 *************************************************************************************/
template <class T>
VectT<T> Poscar::getChemPerAtom(VectT<T> vecOfChems)
{
   int n_ary = vComposition.size();
   int nAtomsOfTheSameChemType;
   VectT<T> chemPerAtom;
   
   // I put char chemType = 'A' previously, but '0' is more convenient
   // when working with *.cfg format later.
   for (int i = 0; i < n_ary; i++)
   {
      nAtomsOfTheSameChemType = vComposition[i];
      for (int j = 0; j < nAtomsOfTheSameChemType; j++)
         chemPerAtom.push_back(vecOfChems[i]);
   }
   return chemPerAtom;
}

/**************************************************************************************
 * FRIEND OPERATOR OVERLOADING <<
 * Have access to private members of poscar !!
 *************************************************************************************/
ostream &operator << (ostream &out, Poscar &poscar)
{
   cout.setf(ios::fixed);
   cout.setf(ios::showpoint);
   cout.precision(8);
   
   out << poscar.head << endl;
   out << poscar.scale << endl;
   out << poscar.vfA << endl;
   out << poscar.vfB << endl;
   out << poscar.vfC << endl;
   for (int i = 0; i < poscar.vComposition.size(); i++)
      out << poscar.vComposition[i] << " ";
   out << endl;
   out << poscar.getCoordType() << endl; //getCoordType is private, but << is friend!

   for (int i = 0; i < poscar.atoms.size(); i++)
      out << poscar.atoms[i].getPosition() << endl; // works with const !!! overload
   return out;
}

/**************************************************************************************
 * FRIEND OPERATOR OVERLOADING << FOR SAVING INTO FILES
 * Have access to private members of poscar !!
 *************************************************************************************/
ofstream &operator << (ofstream &fout, Poscar &poscar)
{
   fout.setf(ios::fixed);
   fout.setf(ios::showpoint);
   fout.precision(8);
   
   fout << poscar.head << endl;
   fout << poscar.scale << endl;
   fout << poscar.vfA << endl;
   fout << poscar.vfB << endl;
   fout << poscar.vfC << endl;
   for (int i = 0; i < poscar.vComposition.size(); i++)
      fout << poscar.vComposition[i] << " ";
   fout << endl;
   fout << poscar.getCoordType() << endl; //getCoordType is private, but << is friend!
   
   for (int i = 0; i < poscar.atoms.size(); i++)
      fout << poscar.atoms[i].getPosition() << endl; // works with const !!! overload
   return fout;
}
