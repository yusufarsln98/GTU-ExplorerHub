/*
   GEBZE TECHNICAL UNIVERSITY
   Object Orianted Programing - CSE241
   Homework 6
   Writing your own vector, set, array classes with iterators. 
   Yusuf Arslan

   interface of GTUVector
*/

#ifndef GTUVECTOR_GUARD
#define GTUVECTOR_GUARD

#include <iostream>
#include <memory>

#include "iterable.h"

using std::shared_ptr;
using std::make_shared;
using std::default_delete;
using std::move;
using std::cout;
using std::endl;

namespace YusufArslanGTU_Containers
{
   template<typename T>
   class GTUVector : public Iterable<T>
   {
      public:
         class GTUIterator;
         class GTUConstIterator;

         GTUVector();
         GTUVector(int cap);
         GTUVector(const GTUVector& new_vector);
         GTUVector(GTUVector&& new_vector);

         GTUVector& operator=(const GTUVector& new_vector);
         GTUVector& operator=(GTUVector&& new_vector);
         // -------------------------------
         virtual bool empty() const;
         virtual unsigned int size() const;
         virtual void clear();
         GTUIterator erase(GTUConstIterator position);
         GTUIterator begin();
         GTUIterator end();
         GTUConstIterator cbegin() const;
         GTUConstIterator cend() const;
         // -------------------------------
         void push_back(const T& val);
         void pop_back();
         T& operator[](int index);
         T& at(int index);

      private:
         shared_ptr<T> Container;
         unsigned int Size;
   };
}

#include "gtuvector.cpp"
#endif
