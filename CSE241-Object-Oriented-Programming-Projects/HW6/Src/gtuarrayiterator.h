/*
   GEBZE TECHNICAL UNIVERSITY
   Object Orianted Programing - CSE241
   Homework 6
   Writing your own vector, set, array classes with iterators. 
   Yusuf Arslan
*/
#ifndef GTUARRAYITERATOR_GUARD
#define GTUARRAYITERATOR_GUARD

#include <iostream>
#include <cstddef>
#include <iterator> 

#include "iterator.h"
#include "gtuarray.h"
#include "gtuconstarrayiterator.h"


namespace YusufArslanGTU_Containers
{
   template<typename T, size_t SIZE>
   class GTUArray<T, SIZE>::GTUIterator : public Iterator
   {
      public:
         using iterator_category = std::random_access_iterator_tag;
         using difference_type   = std::ptrdiff_t;
         using value_type        = T;
         using pointer           = value_type*;  
         using reference         = value_type&; 

         friend class GTUConstIterator;

         GTUIterator();
         GTUIterator(T* newIt);
         GTUIterator(const GTUConstIterator& rval);
         GTUIterator(const GTUIterator& rval);
         GTUIterator(GTUIterator&& rval);
         ~GTUIterator();
         GTUIterator& operator=(const GTUIterator& rval);
         GTUIterator& operator=(GTUIterator&& rval);
         T& operator*();
         T* operator->();
         GTUIterator& operator++();
         GTUIterator operator++(int discard);
         GTUIterator& operator--();
         GTUIterator operator--(int discard);
         bool operator==(const GTUIterator& rval) const;
         bool operator!=(const GTUIterator& rval) const;
         GTUIterator operator+(int addint);
         GTUIterator operator+(const difference_type &other);
         GTUIterator operator-(int subtint);
         GTUIterator operator-(const difference_type &other);
         operator bool() const;

      private:
         T* itr;
   };
}


#endif