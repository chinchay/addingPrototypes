/**************************************************************************************
 * Header File:
 *    ChemicalTypes : 
 * Author:
 *    Carlos Leon. MSG-BYU
 *************************************************************************************/

#ifndef CHEMICALTYPES_h
#define CHEMICALTYPES_h

#include <iostream>
#include <fstream>
#include <stdio.h>
#include <string>
#include <vector>
#include <sstream>      //  used for  stringstream
#include "assert.h"
//#include <cmath>

#include "VectT.h"
using namespace std;

class ChemicalTypes
{
public:
   VectT<int> types;
   string head; // head for POSCAR file
   
   ChemicalTypes(){head = "";}
   
   ChemicalTypes(const ChemicalTypes &chemicalTypes) {*this = chemicalTypes;}
   
   ChemicalTypes &operator = (const ChemicalTypes &rhs)
   {
      this->types = rhs.types;
      this->head = rhs.head;
      return *this;
   }
   
   ChemicalTypes(VectT<int> types, VectT<string> allElementNames)
   {
      this->types = types;
      this->head = getHead(types, allElementNames);
   }
   
   string getHead(VectT<int> types, VectT<string> allElementNames)
   {
      string head = string("");
      if ( types.size() <= allElementNames.size() )
      {
         for (int i = 0; i < types.size(); i++)
         {
            head += allElementNames[ types[i] ] + string(" ");
         }
      }
      else
      {
         cout << "Wrong size of ChemicalTypes" << endl;
      }
      return head;
   }
   
};

/**************************************************************************************
 * GETMIXEDCHEMTYPES
 *
 *************************************************************************************/
void getMixedChemTypes(int i, int n_ary, VectT<int> vHead,
                       VectT<ChemicalTypes> &listIntHeads, VectT<string> allElementNames )
{
   // In the last step, vHead was vHeadTemp. Now we instance another vHeadTemp:
   VectT<int> vHeadTemp;
   for (int j = i + 1; j < allElementNames.size(); j++)
   {
      vHeadTemp = vHead; // vHead is not a copy, but a new instance!
      vHeadTemp.push_back(j);
      
      if (vHeadTemp.size() == n_ary)
      {
         ChemicalTypes chemicalTypes(vHeadTemp, allElementNames);
         vHeadTemp.clear(); // remove all elements once we collected the n_ary into head
         vHeadTemp = vHead;
         listIntHeads.push_back(chemicalTypes);
         
      }
      else
         getMixedChemTypes(j, n_ary, vHeadTemp, listIntHeads, allElementNames);
      
   }
}

/**************************************************************************************
 * GETVECTMIXCHEMTYPES
 *
 *************************************************************************************/
VectT<ChemicalTypes> getVectMixChemTypes(VectT<string> allElementNames, int n_ary)
{
   VectT<int> vHead;
   VectT<ChemicalTypes> listIntHeads;
   
   if (allElementNames.size() >= n_ary)
      getMixedChemTypes(-1, n_ary, vHead, listIntHeads, allElementNames);
   else
      cout << "ERROR allElementNamesSize < n_ary!!!" << endl;
   
   return listIntHeads;
   
}


#endif /* CHEMICALTYPES_h */
