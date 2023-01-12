/*
   GEBZE TECHNICAL UNIVERSITY
   Object Orianted Programing - CSE241
   Homework 6
   Writing your own vector, set, array classes with iterators. 
   Yusuf Arslan
*/
#ifndef GTUCONSTVECTORITERATOR_GUARD
#define GTUCONSTVECTORITERATOR_GUARD

#include <iostream>
#include <cstddef>
#include <iterator> 

#include "iterator.h"
#include "gtuvector.h"
#include "gtuvectoriterator.h"


namespace YusufArslanGTU_Containers
{
   template<typename T>
   class GTUVector<T>::GTUConstIterator : public Iterator
   {
      public:
         using iterator_category = std::random_access_iterator_tag;
         using difference_type   = std::ptrdiff_t;
         using value_type        = T;
         using pointer           = value_type*; 
         using reference         = value_type&; 
         
         friend class GTUIterator;
         
         GTUConstIterator();
         GTUConstIterator(const T* newIt);
         GTUConstIterator(const GTUIterator& rval);
         GTUConstIterator(const GTUConstIterator& rval);
         GTUConstIterator(GTUConstIterator&& rval);
         ~GTUConstIterator();
         GTUConstIterator& operator=(const GTUConstIterator& rval);
         GTUConstIterator& operator=(GTUConstIterator&& rval);
         const T& operator*();
         const T* operator->();
         GTUConstIterator& operator++();
         GTUConstIterator operator++(int discard);
         GTUConstIterator& operator--();
         GTUConstIterator operator--(int discard);
         bool operator==(const GTUConstIterator& rval) const;
         bool operator!=(const GTUConstIterator& rval) const;
         GTUConstIterator operator+(int addint);
         GTUConstIterator operator+(const difference_type& addptrdiff);
         GTUConstIterator operator-(int subtint);
         GTUConstIterator operator-(const difference_type& subtptrdiff);
         operator bool() const;

      private:
         const T* itr;
   };
}


#endif