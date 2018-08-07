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
   
public:
   Atom(){}
   
   // setters
   void setPosition(const VectT<float> &vectT) { position = vectT; }
   void setChem(int chemType) {this->chemType = chemType;}
   
   // getters
   char getChem() {return chemType;}
   VectT<float> getPosition(){return position;}
   
};


#endif /* VectT_h */
