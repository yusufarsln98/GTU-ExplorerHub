/*
   GEBZE TECHNICAL UNIVERSITY
   Object Orianted Programing - CSE241
   Homework 6
   Writing your own vector, set, array classes with iterators. 
   Yusuf Arslan
*/

#ifndef ITERABLE_GUARD
#define ITERABLE_GUARD

#include <iostream>

#include "iterator.h"


namespace YusufArslanGTU_Containers
{
   template <class T>
   class Iterable
   { 
   public:
      virtual bool empty() const = 0;
      virtual unsigned int size() const = 0;
      virtual void clear() = 0;
   };
}

#endif

