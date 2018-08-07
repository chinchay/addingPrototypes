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
               chemType = getTypeChem(j, vComposition);
               
               Atom* pAtom = new Atom;
               pAtom->setPosition(position);
               pAtom->setChem(chemType);
               pAtoms.push_back(pAtom);
               j++;
               break;
         }
         i++;
      }
   }
   
   fin.close();
}
   
/**************************************************************************************
 * POSCAR : GETPOSCALINES
 * This function convert a Poscar object into strings lines, so that the lines can then
 * be pasted into into a POSCAR file.
 *************************************************************************************/
vector<string> Poscar::getPoscarLines()
{
   string s;
   if (coordinatesType == 'c')
      s = "C";
   else if (coordinatesType == 'd')
      s = "D";
   
   vector<string> poscarLines;
   poscarLines.push_back(head);
   poscarLines.push_back(to_string(scale));
   poscarLines.push_back(vfA.getStringFromVectT());
   poscarLines.push_back(vfB.getStringFromVectT());
   poscarLines.push_back(vfC.getStringFromVectT());
   poscarLines.push_back(vComposition.getStringFromVectT());
   poscarLines.push_back(s);
   
   int nAtoms = pAtoms.size();
   VectT<float> position;
   for (int i = 0; i < nAtoms; i++)
   {
      position = pAtoms[i]->getPosition();
      poscarLines.push_back(position.getStringFromVectT());
   }
   
   return poscarLines;
}

/**************************************************************************************
 * POSCAR : CONVERTTOCARTESIAN
 * This function scales the lattice vectors by the parameter `scale`, and then gets
 * the position of each atom in cartesian coordinates by taking the fractional
 * coordinates saved in pAtoms[i], for i = 1,2,..., numberOfAtoms.
 *************************************************************************************/
void Poscar::convertToCartesian(float scale = 1.0)
{
   // scale the lattice coordinates, and get them in cartesian coordinates:
   latticeVectorsToCartesian(scale);
   
   if ( tolower(this->coordinatesType) == 'd')
   {
      VectT<float> position;
      for (int i = 0; i < pAtoms.size(); i++)
      {
         position = pAtoms[i]->getPosition();
         position = getCartesianFromFractional(position);
         pAtoms[i]->setPosition(position); // update into pAtoms.
      }
   }
   else if ( tolower(this->coordinatesType) == 'c')
   {
      // position = position
   }
   else
   {
      cout << "PROBLEM. WHAT TYPE OF COORDINATES IS THIS? " << coordinatesType;
      cout << endl;
   }
   // we have moved everything to cartesian system, so:
   this->coordinatesType = 'c';
   this->scale = 1.0;
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
 * POSCAR : GETCARTESIANFROMFRACTIONAL
 * Just convert fractional to cartesian coordinates, using the lattice vectors.
 *************************************************************************************/
VectT<float> Poscar::getCartesianFromFractional(VectT<float> fractional)
{
   return fractional[0] * vfA  +  fractional[1] * vfB  +  fractional[2] * vfC;
}

/**************************************************************************************
 * POSCAR : GETTYPECHEM
 * This functions assign an integer to a chemical element.
 *************************************************************************************/
int Poscar::getTypeChem(int cont, VectT<int> vComposition)
{
   int nChems = vComposition.size();
   int nAtomsOfTheSameChemType;
   
   int k = 0;
   int chemType = 0;
   // I put char chemType = 'A' previously, but '0' is more convenient
   // when working with *.cfg format later.
   for (int i = 0; i < nChems; i++)
   {
      nAtomsOfTheSameChemType = vComposition[i];
      for (int j = 0; j < nAtomsOfTheSameChemType; j++)
      {
         if (cont == k)
            return chemType;
         k++;
      }
      chemType++; // this will take values 0, 1, 2, ...
   }
   
   // something must be wrong if reaching here! cont > sum(vCompostion)!!
   chemType = -1;
   return chemType;
}


