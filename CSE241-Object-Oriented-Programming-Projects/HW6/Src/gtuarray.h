/*
   GEBZE TECHNICAL UNIVERSITY
   Object Orianted Programing - CSE241
   Homework 6
   Writing your own vector, set, array classes with iterators. 
   Yusuf Arslan

   interface of GTUArray
*/

#ifndef GTUARRAY_GUARD
#define GTUARRAY_GUARD

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
   template<typename T, size_t SIZE>
   class GTUArray : public Iterable<T>
   {
      public:
         class GTUIterator;
         class GTUConstIterator;

         GTUArray();
         GTUArray(const GTUArray& new_array);
         GTUArray(GTUArray&& new_array);

         GTUArray& operator=(const GTUArray& new_array);
         GTUArray& operator=(GTUArray&& new_array);
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
         
         T& operator[](int index);
         T& at(int index);
         T& front();
         T& back();
         void fill(T item);

      private:
         shared_ptr<T> Container;
         const unsigned int Size = SIZE;
         bool isempty;
   };
}

#include "gtuarray.cpp"
#endif
