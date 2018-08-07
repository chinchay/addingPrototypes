/**************************************************************************************
 * Header File:
 *    VECTTH : Child class of std::vector
 * Author:
 *    Carlos Leon. MSG-BYU
 *************************************************************************************/

#ifndef VectT_h
#define VectT_h

#include <stdio.h>
#include <string>
#include <vector>
#include <iostream>
#include <sstream>      //  used for  stringstream
using namespace std;

template <class T>
class VectT : public vector<T>
{
public:
   VectT(){}
   
   /***********************************************************************************
    * VECTTH : NON-DEFAULT CONSTRUCTOR WITH VECTT
    * Initialize VectT.
    **********************************************************************************/
   //   template <class T>
   VectT(const VectT &vectT)
   {
      // We can use the assignment operator to avoid duplicating code
      *this = vectT;
   }
   
   /***********************************************************************************
    * VECTTH : OPERATOR OVERLOADING *=
    * Allows multiplication unto a VectT by a float factor number.
    **********************************************************************************/
   //   template <class T>
   VectT<T> &operator *= (const T &factor)
   {
      //   typename vector<T>::iterator it;
      typename VectT::iterator it;
      
      //     typename vector<T>::iterator itBegin  = vector<T>::iterator.begin();
      //     typename vector<T>::iterator itEnd  = vector<T>::iterator.end();
      typename vector<T>::iterator itBegin  = vector<T>::begin();
      typename vector<T>::iterator itEnd  = vector<T>::end();
      
      for (it = itBegin; it != itEnd; it++)
         *it = factor * (*it);
      
      return *this;
   }
   
   /***********************************************************************************
    * VECTTH : OPERATOR OVERLOADING (b)
    * This function implements vectorial product with another VectT object.
    **********************************************************************************/
   //   template <class T>
   VectT<T> operator () (const VectT &b)
   {
      VectT<T> a = *this;
      VectT<T> vectProduct;
      float x = -a[2] * b[1]  +  a[1] * b[2];
      float y =  a[2] * b[0]  -  a[0] * b[2];
      float z = -a[1] * b[0]  +  a[0] * b[1];
      vectProduct.push_back(x);
      vectProduct.push_back(y);
      vectProduct.push_back(z);
      return vectProduct;
   }
   
   /***********************************************************************************
    * VECTTH : OPERATOR OVERLOADING (b,c)
    * This function implements vectorial product with VectT object, and then a inner
    * product with another VectT object: (*this x b) . c
    * Remember: volume = DotProduct( CrossProduct(*this,b), c  )
    **********************************************************************************/
   //   template <class T>
   float operator () (const VectT &b, const VectT &c)
   {
      VectT<T> a = *this;
      //      VectT<T> vectProd = a * b;
      VectT<T> vectProd = a(b);
      return dot(vectProd, c);
   }
   
   /***********************************************************************************
    * VECTTH : GETSTRINGFROMVECTT
    * This function convert the components of a vectT into a line string.
    **********************************************************************************/
   //   template <class T>
   string getStringFromVectT()
   {
      VectT v = *this;
      string line;
      for (int i = 0; i < v.size(); i++)
      {
         line += string("   ");
         line += to_string(v[i]);
      }
      return line;
   }
   
   /***********************************************************************************
    * VECTTH : OPERATOR OVERLOADING +
    * Allow the addition of two VectT objects.
    **********************************************************************************/
   friend VectT operator + (const VectT &lhs, const VectT &rhs)
   {
      //      typename vector<T>::iterator itBegin = lhs.begin();
      //      typename vector<T>::iterator itEnd   = lhs.end();
      
      VectT<T> sum;
      if (lhs.size() == rhs.size())
      {
         for (int i = 0; i < lhs.size(); i++)
         {
            sum.push_back(lhs[i] + rhs[i]);
         }
      }
      else
      {
         cout << "DIFFERENT SIZES!!!" << endl;
      }
      return sum;
   }
   
   /***********************************************************************************
    * VECTTH : OPERATOR OVERLOADING >>
    **********************************************************************************/
   friend istream &operator >> (istream &in, VectT &vectT)
   {
      T t;
      while (in >> t)
      {
         vectT.push_back(t);
      }
      return in;
   }
   
   /***********************************************************************************
    * VECTTH : OPERATOR OVERLOADING *
    * Multiplies a float and a VectT object.
    **********************************************************************************/
   friend VectT operator * (const float &factor, const VectT &rhs)
   {
      VectT<T> product;
      for (int i = 0; i < rhs.size(); i++)
         product.push_back(factor * rhs[i]);
      return product;
   }
   
   /***********************************************************************************
    * VECTTH : OPERATOR OVERLOADING *
    * Multiplies a VectT object and a float.
    **********************************************************************************/
   friend VectT operator * (const VectT &lhs, const float &factor)
   {
      VectT<T> product;
      for (int i = 0; i < lhs.size(); i++)
         product.push_back(lhs[i] * factor);
      return product;
   }
   
   /***********************************************************************************
    * VECTTH : DOT
    * Calculates the inner product of two VectT objects.
    **********************************************************************************/
   friend float dot(const VectT &lhs, const VectT &rhs)
   {
      float dotProduct = 0;
      for (int i = 0; i < lhs.size(); i++) { dotProduct += lhs[i] * rhs[i]; }
      return dotProduct;
   }
   
};

#endif /* VectT_h */

