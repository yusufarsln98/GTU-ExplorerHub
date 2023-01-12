/*
   GEBZE TECHNICAL UNIVERSITY
   Object Orianted Programing - CSE241
   Homework 6
   Writing your own set, set, array classes with iterators. 
   Yusuf Arslan

   interface of GTUSet
*/

#ifndef GTUSET_GUARD
#define GTUSET_GUARD

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
   class GTUSet : public Iterable<T>
   {
      public:
         class GTUIterator;
         class GTUConstIterator;

         GTUSet();
         GTUSet(const GTUSet& new_set);
         GTUSet(GTUSet&& new_set);
         GTUSet& operator=(const GTUSet& new_set);
         GTUSet& operator=(GTUSet&& new_set);
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
         void insert(const T& val);
         bool isexist(const T& val) const;
         GTUIterator find(const T& val);
         GTUIterator erase(const T& val);

         
         GTUSet<T> Union(const GTUSet<T>& new_set) const;
         GTUSet<T> operator+(const GTUSet<T>& new_set) const;
         GTUSet<T> Intersect(const GTUSet<T>& new_set) const;
         GTUSet<T> operator^(const GTUSet<T>& new_set) const;
         GTUSet<T> Complement(const GTUSet<T>& new_set) const;
         GTUSet<T> operator-(const GTUSet<T>& new_set) const;
 
   
      private:
         shared_ptr<T> Container;
         unsigned int Size;
   };
}

#include "gtuset.cpp"
#endif
