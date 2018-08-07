/**************************************************************************************
 * Source File:
 *    Cfg : Content of a *.cfg file.
 * Author:
*    Carlos Leon. MSG-BYU
 *************************************************************************************/

#include <iostream>
#include <fstream>
#include <stdio.h>
#include <string>
#include <vector>
#include <sstream>      //  used for  stringstream

#include "Cfg.h"
#include "Poscar.h"
#include "Atom.h"
#include "VectT.h"
using namespace std;

/**************************************************************************************
 * CFG : NON-DEFAULT CONSTRUCTOR WITH ID, POSCAR
 * Initialize Cfg with ID and Poscar objects
 *************************************************************************************/
Cfg::Cfg(string ID, Poscar poscar)
{
   // fixed line strings in a *.cfg file:
   head1 = string("BEGIN_CFG");
   head2 = string(" Size");
   head3 = string(" SuperCell");
   head4 = string("   AtomData:  id type       ") +
           string("cartes_x      cartes_y      cartes_z");
   featureID = string(" Feature   conf_id  ");
   tail = string("END_CFG");
   
   // Collect data from an object of Poscar class.
   // The ID is no identify the configuration in the *.cfg file
   getCfgFromPoscarClass(ID, poscar);
}

/**************************************************************************************
 * CFG : PUSH_ATOM
 * Creates an object of Atom class using chemType and position. Push it into pAtoms.
 *************************************************************************************/
void Cfg::push_atom(char chemType, VectT<float> position)
{
   Atom* pAtom = new Atom;
   pAtom->setPosition(position);
   pAtom->setChem(chemType);
   
   this->pAtoms.push_back(pAtom);
}

/**************************************************************************************
 * CFG : GETCFGLINES
 * Creates a vector of strings to be the content of a *.cfg file.
 *************************************************************************************/
vector<string> Cfg::getCfgLines() //vector<string>
{
   vector<string> cfgLines;
   
   cfgLines.push_back(head1);
   
   cfgLines.push_back(head2);
   int nAtoms = pAtoms.size();
   cfgLines.push_back(string("    ") + to_string(nAtoms));
   
   cfgLines.push_back(head3);
   cfgLines.push_back( vfA.getStringFromVectT() );
   cfgLines.push_back( vfB.getStringFromVectT() );
   cfgLines.push_back( vfC.getStringFromVectT() );
   
   cfgLines.push_back(head4);
   for (int i = 0; i < nAtoms; i++)
   {
      Atom* pAtom = pAtoms[i];
      string atomLine = getAtomLine(i, pAtom);
      cfgLines.push_back(atomLine);
   }
   
   string lineID = featureID + ID;
   cfgLines.push_back(lineID);
   cfgLines.push_back(tail);
   
   return cfgLines;
}

/**************************************************************************************
 * CFG : GETCFGFROMPOSCARCLASS
 *
 *************************************************************************************/
void Cfg::getCfgFromPoscarClass(string ID, Poscar poscar)
{
   this->ID = ID;
   this->vfA = poscar.vfA;
   this->vfB = poscar.vfB;
   this->vfC = poscar.vfC;
   this->vComposition = poscar.vComposition;
   this->pAtoms = poscar.pAtoms;
}

/**************************************************************************************
 * CFG : GETATOMLINE
 *
 *************************************************************************************/
string Cfg::getAtomLine(int cont, Atom* pAtom)
{
   string atomLine;
   atomLine = string("             ");
   atomLine += to_string(cont);
   atomLine += string("    ");
   
   int chemType = pAtom->getChem(); // it could be 0, 1, 2, ...
   atomLine += to_string(chemType);
   atomLine += string("     ");
   
   VectT<float> position = pAtom->getPosition();
   atomLine += position.getStringFromVectT();
   
   return atomLine;
}

void Cfg::display()
{
   cout << "hello" << endl;
}
