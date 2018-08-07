///**************************************************************************************
// * Source File:
// *    VECTTH : Child class of std::vector
// * Author:
// *    Carlos Leon. MSG-BYU
// *************************************************************************************/
//
//#include <stdio.h>
//#include <string>
//#include <vector>
//#include <iostream>
//#include <sstream>      //  used for  stringstream
//
//#include "VectT.h"
//using namespace std;
//
///**************************************************************************************
// * POSCAR : NON-DEFAULT CONSTRUCTOR WITH VECTT
// * Initialize VectT.
// *************************************************************************************/
//template <class T>
//VectT<T>::VectT(const VectT &vectT)
//{
//   // We can use the assignment operator to avoid duplicating code
//   *this = vectT;
//}
//
///**************************************************************************************
// * POSCAR : OVERLOADING OPERATOR *=
// * Allows multiplication unto a VectT by a float factor number.
// *************************************************************************************/
//template <class T>
//VectT<T> &VectT<T>::operator *= (const T &factor)
//{
//   typename vector<T>::iterator it;
//
//   //     typename vector<T>::iterator itBegin  = vector<T>::iterator.begin();
//   //     typename vector<T>::iterator itEnd  = vector<T>::iterator.end();
//   typename vector<T>::iterator itBegin  = vector<T>::begin();
//   typename vector<T>::iterator itEnd  = vector<T>::end();
//
//   for (it = itBegin; it != itEnd; it++)
//      *it = factor * (*it);
//
//   return *this;
//}
//
///**************************************************************************************
// * POSCAR : OVERLOADING OPERATOR (b)
// * This function implements vectorial product with another VectT object.
// *************************************************************************************/
//// vectorial product:
//template <class T>
//VectT<T> VectT<T>::operator () (const VectT &b)
//{
//   VectT<T> a = *this;
//   VectT<T> vectProduct;
//   float x = -a[2] * b[1]  +  a[1] * b[2];
//   float y =  a[2] * b[0]  -  a[0] * b[2];
//   float z = -a[1] * b[0]  +  a[0] * b[1];
//   vectProduct.push_back(x);
//   vectProduct.push_back(y);
//   vectProduct.push_back(z);
//   return vectProduct;
//}
//
///**************************************************************************************
// * POSCAR : OVERLOADING OPERATOR (b,c)
// * This function implements vectorial product with VectT object, and then a inner
// * product with another VectT object: (*this x b) . c
// * Remember: volume = DotProduct( CrossProduct(*this,b), c  )
// *************************************************************************************/
//template <class T>
//float VectT<T>::operator () (const VectT &b, const VectT &c)
//{
//   VectT<T> a = *this;
//   //      VectT<T> vectProd = a * b;
//   VectT<T> vectProd = a(b);
//   return dot(vectProd, c);
//}
//
/////**************************************************************************************
//// * POSCAR : GETSTRINGFROMVECTT
//// * This function convert the components of a vectT into a line string.
//// *************************************************************************************/
////template <class T>
////string VectT<T>::getStringFromVectT()
////{
////   VectT v = *this;
////   string line;
////   for (int i = 0; i < v.size(); i++)
////   {
////      line += string("   ");
////      line += to_string(v[i]);
////   }
////   return line;
////}
//
