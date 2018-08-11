/**************************************************************************************
 * Header File:
 *    Atom : Representation of an Atom object.
 * Author:
 *    Carlos Leon. MSG-BYU
 *************************************************************************************/

#ifndef ATOM_h
#define ATOM_h

#include "VectT.h"

class Atom
{
private:
   VectT<float> position;
   int chemType;
   string chemName;
   
public:
   Atom(){}
   
   Atom(const Atom &atom){*this = atom;}
   
   Atom(VectT<float> position, int chemType, string chemName)
   {
      set(position, chemType, chemName);
   }
   
   void set(VectT<float> position, int chemType, string chemName)
   {
      setPosition(position);
      setChemType(chemType);
      setChemName(chemName);
   }
   
   Atom &operator = (const Atom &rhs)
   {
      position = rhs.position;
      chemType = rhs.chemType;
      chemName = rhs.chemName;
      return *this;
   }
   
   // setters
   void setPosition(const VectT<float> &vectT) { position = vectT; }
   void setChemType(int chemType) {this->chemType = chemType;}
   void setChemName(string chemName) {this->chemName = chemName;}
   
   // getters
   int getChemType() {return chemType;}
   string getChemName() {return chemName;}   
   VectT<float> getPosition(){return position;}
   
   //   int factorial(int n)
   //   {
   //      return (n == 1 || n == 0) ? 1 : factorial(n - 1) * n;
   //   }

};


#endif /* VectT_h */
