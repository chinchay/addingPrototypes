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
 * CFG : OPERATOR OVERLOADING = (ASSIGNMENT)
 *************************************************************************************/
Cfg &Cfg::operator = (const Cfg &rhs)
{
   head1 = rhs.head1;
   head2 = rhs.head2;
   head3 = rhs.head3;
   head4 = rhs.head4;
   featureID = rhs.featureID;
   tail = rhs.tail;
   ID = rhs.ID;
   vfA = rhs.vfA;
   vfB = rhs.vfB;
   vfC = rhs.vfC;
   vComposition = rhs.vComposition;

   for (int i = 0; i < rhs.atoms.size(); i++)
      atoms.push_back( Atom(rhs.atoms[i]) );

   return *this;
}

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
   this->atoms = poscar.atoms; // it is not necessary to make atoms.clear() it's empty?
}

/**************************************************************************************
 * CFG : OPERATOR OVERLOADING <<
 *
 *************************************************************************************/
ostream &operator << (ostream &out, Cfg &cfg)
{
   cout.setf(ios::fixed);
   cout.setf(ios::showpoint);
   cout.precision(8);
   
   out << cfg.head1 << endl;
   out << cfg.head2 << endl;
   out << "    " << cfg.atoms.size() << endl;
   out << cfg.head3 << endl;
   out << cfg.vfA << endl;
   out << cfg.vfB << endl;
   out << cfg.vfC << endl;
   out << cfg.head4 << endl;
   
   for (int i = 0; i < cfg.atoms.size(); i++)
   {
      out << setw(16) << i << setw(5) << cfg.atoms[i].getChemType() << " ";
      out << cfg.atoms[i].getPosition() << endl;      
   }
   
   out << cfg.featureID << cfg.ID << endl;
   out << cfg.tail << endl;
   
   return out;
}

/**************************************************************************************
 * CFG : OPERATOR OVERLOADING << FOR SAVING INTO A FILE
 *
 *************************************************************************************/
ofstream &operator << (ofstream &fout, Cfg &cfg)
{
   fout.setf(ios::fixed);
   fout.setf(ios::showpoint);
   fout.precision(8);
   
   fout << cfg.head1 << endl;
   fout << cfg.head2 << endl;
   fout << "    " << cfg.atoms.size() << endl;
   fout << cfg.head3 << endl;
   fout << cfg.vfA << endl;
   fout << cfg.vfB << endl;
   fout << cfg.vfC << endl;
   fout << cfg.head4 << endl;
   
   for (int i = 0; i < cfg.atoms.size(); i++)
   {
      fout << setw(16) << i << setw(5) << cfg.atoms[i].getChemType() << " ";
      fout << cfg.atoms[i].getPosition() << endl;
   }
   
   fout << cfg.featureID << cfg.ID << endl;
   fout << cfg.tail << endl;
   
   return fout;
}



