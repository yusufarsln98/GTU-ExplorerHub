/*
   GEBZE TECHNICAL UNIVERSITY
   Object Orianted Programing - CSE241
   Homework 6
   Writing your own vector, set, array classes with iterators. 
   Yusuf Arslan
*/


#include <iostream>
#include <memory>
#include <cstddef>
#include <iterator> 

#include "gtuarray.h"
#include "gtuarrayiterator.h"
#include "gtuconstarrayiterator.h"
#include "gtucontainerexceptions.h"

using std::shared_ptr;
using std::default_delete;
using std::move;
using std::cout;
using std::endl;

namespace YusufArslanGTU_Containers
{
   // --- Default constructor ---
   template<typename T, size_t SIZE>
   GTUArray<T, SIZE>::GTUArray() 
   {
      shared_ptr<T> temp(new T[Size], default_delete<T[]>());
      Container = temp;
      isempty = true;
   }

   // --- Copy constructor ---
   template<typename T, size_t SIZE>
   GTUArray<T, SIZE>::GTUArray(const GTUArray& new_array)
   {
      Size = new_array.size();
      shared_ptr<T> temp(new T[Size], default_delete<T[]>());
      for (auto i = 0; i < Size; i++)
      {
         temp.get()[i] = new_array.Container.get()[i];
      }
      Container = temp;
      isempty = new_array.isempty;
   }

   // --- Move constructor ---
   template<typename T, size_t SIZE>
   GTUArray<T, SIZE>::GTUArray(GTUArray&& new_array) : Size(new_array.size()), Container(new_array.Container), isempty(new_array.isempty)
   {
      shared_ptr<T> temp(new T[new_array.size()], default_delete<T[]>());
      new_array.Container = temp;
      new_array.isempty = true;
   }


   template<typename T, size_t SIZE>
   bool GTUArray<T, SIZE>::empty() const 
   {
      return isempty;
   }

   template<typename T, size_t SIZE>
   unsigned int GTUArray<T, SIZE>::size() const {return Size; }

   template<typename T, size_t SIZE>
   void GTUArray<T, SIZE>::clear() 
   {
      shared_ptr<T> temp(new T[Size], default_delete<T[]>());
      Container = temp;
      isempty = true;
   }
   
   // Erase an element which position is pointing
   template<typename T, size_t SIZE>
   typename GTUArray<T, SIZE>::GTUIterator GTUArray<T, SIZE>::erase(GTUConstIterator position)
   {
      bool isexist = false;

      for (auto i = cbegin(); ; i++)
      {
         if(position == i)
         {
            isexist = true;
            break;
         }
         if (i == cend()) break;
      }
      
      if (isexist == false)
         return GTUIterator(Container.get());
      else
      {
         for (auto i = begin(), j = 0; i != end(); i++)
         {
            if(position == i)
            {
               (*i) = *(Container.get() + Size);
            }
         }
         return GTUIterator(Container.get());
      }
   }

   template<typename T, size_t SIZE>
   typename GTUArray<T, SIZE>::GTUIterator GTUArray<T, SIZE>::begin()
   {
      return Container.get();
   }

   template<typename T, size_t SIZE>
   typename GTUArray<T, SIZE>::GTUIterator GTUArray<T, SIZE>::end()
   {
      return Container.get() + Size;
   }

   template<typename T, size_t SIZE>
   typename GTUArray<T, SIZE>::GTUConstIterator GTUArray<T, SIZE>::cbegin() const
   {
      return Container.get();
   }

   template<typename T, size_t SIZE>
   typename GTUArray<T, SIZE>::GTUConstIterator GTUArray<T, SIZE>::cend() const
   {
      return Container.get() + Size;
   }

   // --- Copy assigment ---
   template<typename T, size_t SIZE>
   GTUArray<T, SIZE>& GTUArray<T, SIZE>::operator=(const GTUArray& new_array)
   {
      if (Container == new_array.Container) return *this;

      Size = new_array.size();
      isempty = new_array.isempty;

      shared_ptr<T> temp(new T[Size], default_delete<T[]>());
      for (auto i = 0; i < Size; i++)
      {
         temp.get()[i] = new_array.Container.get()[i];
      }
      Container = temp;
      return *this;
   }

   // --- Move assigment ---
   template<typename T, size_t SIZE>
   GTUArray<T, SIZE>& GTUArray<T, SIZE>::operator=(GTUArray&& new_array)
   {
      if (this == &new_array) return *this;

      shared_ptr<T> temp;

      Size = new_array.size();
      Container = new_array.Container;
      isempty = new_array.isempty;

      new_array.Container = temp;
      new_array.isempty = true;

      return *this;
   }

   // Accessing functions
   template<typename T, size_t SIZE>
   T& GTUArray<T, SIZE>::operator[] (int index)
   {
      if (!(index >= 0 && index < Size))
         throw(out_of_array_range());
      
      isempty = false;
      return Container.get()[index];
   }

   template<typename T, size_t SIZE>
   T& GTUArray<T, SIZE>::at(int index)
   {
      if (!(index >= 0 && index < Size))
         throw(out_of_array_range());

      isempty = false;
      return Container.get()[index];
   }

   template<typename T, size_t SIZE>
   T& GTUArray<T, SIZE>::front()
   {
      return Container.get()[0];
   }

   template<typename T, size_t SIZE>
   T& GTUArray<T, SIZE>::back()
   {
      return Container.get()[Size - 1];
   }

   // Fill array with any item.
   template<typename T, size_t SIZE>
   void GTUArray<T, SIZE>::fill(T item)
   {
      for (auto i = 0; i < Size; i++)
      {
         Container.get()[i] = item;
      }
      isempty = false;

   }
   

   // ------------------ Inner Classes ------------------
   // --------- GTUITerator Inner Class ---------
   template<typename T, size_t SIZE>
   GTUArray<T, SIZE>::GTUIterator::GTUIterator() : itr(nullptr) {}

   template<typename T, size_t SIZE>
   GTUArray<T, SIZE>::GTUIterator::GTUIterator(T* newItr) : itr(newItr) {}

   template<typename T, size_t SIZE>
   GTUArray<T, SIZE>::GTUIterator::GTUIterator(const GTUConstIterator& rval) : itr(rval.itr) {}

   template<typename T, size_t SIZE>
   GTUArray<T, SIZE>::GTUIterator::GTUIterator(const GTUIterator& rval) : itr(rval.itr) {}

   template<typename T, size_t SIZE>
   GTUArray<T, SIZE>::GTUIterator::GTUIterator(GTUIterator&& rval) : itr(rval.itr) {rval.itr = nullptr; }

   template<typename T, size_t SIZE>
   GTUArray<T, SIZE>::GTUIterator::~GTUIterator() {}

   template<typename T, size_t SIZE>
   typename GTUArray<T, SIZE>::GTUIterator& GTUArray<T, SIZE>::GTUIterator::operator=(const GTUIterator& rval)
   {
      itr = rval.itr;
      return *this;
   }

   template<typename T, size_t SIZE>
   typename GTUArray<T, SIZE>::GTUIterator& GTUArray<T, SIZE>::GTUIterator::operator=(GTUIterator&& rval)
   {
      itr = rval.itr;
      rval.itr = nullptr;
      return *this;
   }

   template<typename T, size_t SIZE>
   T& GTUArray<T, SIZE>::GTUIterator::operator*()
   {
      return *itr;
   }
   
   template<typename T, size_t SIZE>
   T* GTUArray<T, SIZE>::GTUIterator::operator->()
   {
      return itr;
   }

   // prefix
   template<typename T, size_t SIZE>
   typename GTUArray<T, SIZE>::GTUIterator& GTUArray<T, SIZE>::GTUIterator::operator++()
   {
      itr++;
      return *this;
   }

   // postfix
   template<typename T, size_t SIZE>
   typename GTUArray<T, SIZE>::GTUIterator GTUArray<T, SIZE>::GTUIterator::operator++(int discard)
   {
      GTUIterator temp(itr);
      itr++;
      return temp;
   }
   
   // prefix
   template<typename T, size_t SIZE>
   typename GTUArray<T, SIZE>::GTUIterator& GTUArray<T, SIZE>::GTUIterator::operator--()
   {
      itr--;
      return *this;
   }

   // postfix
   template<typename T, size_t SIZE>
   typename GTUArray<T, SIZE>::GTUIterator GTUArray<T, SIZE>::GTUIterator::operator--(int discard)
   {
      GTUIterator temp(itr);
      itr--;
      return temp;
   }

   template<typename T, size_t SIZE>
   bool GTUArray<T, SIZE>::GTUIterator::operator==(const GTUIterator& rval) const
   {
      return itr == rval.itr ? true : false;
   }

   template<typename T, size_t SIZE>
   bool GTUArray<T, SIZE>::GTUIterator::operator!=(const GTUIterator& rval) const
   {
      return itr != rval.itr ? true : false;
   }

   template<typename T, size_t SIZE>
   typename GTUArray<T, SIZE>::GTUIterator GTUArray<T, SIZE>::GTUIterator::operator+(int addint)
   {
      GTUIterator temp(itr);
      temp.itr += addint;
      return temp.itr;
   }
   
   template<typename T, size_t SIZE>
   typename GTUArray<T, SIZE>::GTUIterator GTUArray<T, SIZE>::GTUIterator::operator+(const difference_type& addptrdiff)
   {
      GTUIterator temp(itr);
      temp.itr += addptrdiff;
      return temp;
   }

   template<typename T, size_t SIZE>
   typename GTUArray<T, SIZE>::GTUIterator GTUArray<T, SIZE>::GTUIterator::operator-(int subtint)
   {
      GTUIterator temp(itr);
      temp.itr -= subtint;
      return temp;
   }

   template<typename T, size_t SIZE>
   typename GTUArray<T, SIZE>::GTUIterator GTUArray<T, SIZE>::GTUIterator::operator-(const difference_type& subtptrdiff)
   {
      GTUIterator temp(itr);
      temp.itr -= subtptrdiff;
      return temp;
   }

   template<typename T, size_t SIZE>
   GTUArray<T, SIZE>::GTUIterator::operator bool() const
   {
      if (itr) return true;
      else return false;
   }

   // --------- GTUConstITerator Inner Class ---------
   template<typename T, size_t SIZE>
   GTUArray<T, SIZE>::GTUConstIterator::GTUConstIterator() : itr(nullptr) {}

   template<typename T, size_t SIZE>
   GTUArray<T, SIZE>::GTUConstIterator::GTUConstIterator(const T* newItr) : itr(newItr) {}
   
   template<typename T, size_t SIZE>
   GTUArray<T, SIZE>::GTUConstIterator::GTUConstIterator(const GTUIterator& rval) : itr(rval.itr) {}
   
   template<typename T, size_t SIZE>
   GTUArray<T, SIZE>::GTUConstIterator::GTUConstIterator(const GTUConstIterator& rval) : itr(rval.itr) {}

   template<typename T, size_t SIZE>
   GTUArray<T, SIZE>::GTUConstIterator::GTUConstIterator(GTUConstIterator&& rval) : itr(rval.itr) {rval.itr = nullptr; }

   template<typename T, size_t SIZE>
   GTUArray<T, SIZE>::GTUConstIterator::~GTUConstIterator() {}

   template<typename T, size_t SIZE>
   typename GTUArray<T, SIZE>::GTUConstIterator& GTUArray<T, SIZE>::GTUConstIterator::operator=(const GTUConstIterator& rval)
   {
      itr = rval.itr;
      return *this;
   }

   template<typename T, size_t SIZE>
   typename GTUArray<T, SIZE>::GTUConstIterator& GTUArray<T, SIZE>::GTUConstIterator::operator=(GTUConstIterator&& rval)
   {
      itr = rval.itr;
      rval.itr = nullptr;
      return *this;
   }

   template<typename T, size_t SIZE>
   const T& GTUArray<T, SIZE>::GTUConstIterator::operator*()
   {
      return *itr;
   }
   
   template<typename T, size_t SIZE>
   const T* GTUArray<T, SIZE>::GTUConstIterator::operator->()
   {
      return itr;
   }

   // prefix
   template<typename T, size_t SIZE>
   typename GTUArray<T, SIZE>::GTUConstIterator& GTUArray<T, SIZE>::GTUConstIterator::operator++()
   {
      itr++;
      return *this;
   }

   // postfix
   template<typename T, size_t SIZE>
   typename GTUArray<T, SIZE>::GTUConstIterator GTUArray<T, SIZE>::GTUConstIterator::operator++(int discard)
   {
      GTUConstIterator temp(itr);
      itr++;
      return temp;
   }
   
   // prefix
   template<typename T, size_t SIZE>
   typename GTUArray<T, SIZE>::GTUConstIterator& GTUArray<T, SIZE>::GTUConstIterator::operator--()
   {
      itr--;
      return *this;
   }

   // postfix
   template<typename T, size_t SIZE>
   typename GTUArray<T, SIZE>::GTUConstIterator GTUArray<T, SIZE>::GTUConstIterator::operator--(int discard)
   {
      GTUConstIterator temp(itr);
      itr--;
      return temp;
   }

   template<typename T, size_t SIZE>
   bool GTUArray<T, SIZE>::GTUConstIterator::operator==(const GTUConstIterator& rval) const
   {
      return itr == rval.itr ? true : false;
   }

   template<typename T, size_t SIZE>
   bool GTUArray<T, SIZE>::GTUConstIterator::operator!=(const GTUConstIterator& rval) const
   {
      return itr != rval.itr ? true : false;
   }

   template<typename T, size_t SIZE>
   typename GTUArray<T, SIZE>::GTUConstIterator GTUArray<T, SIZE>::GTUConstIterator::operator+(int addint)
   {
      GTUConstIterator temp(itr);
      temp.itr += addint;
      return temp;
   }

   template<typename T, size_t SIZE>
   typename GTUArray<T, SIZE>::GTUConstIterator GTUArray<T, SIZE>::GTUConstIterator::operator+(const difference_type& addptrdiff)
   {
      GTUConstIterator temp(itr);
      temp.itr += addptrdiff;
      return temp;
   }

   template<typename T, size_t SIZE>
   typename GTUArray<T, SIZE>::GTUConstIterator GTUArray<T, SIZE>::GTUConstIterator::operator-(int subtint)
   {
      GTUConstIterator temp(itr);
      temp.itr -= subtint;
      return temp;
   }

   template<typename T, size_t SIZE>
   typename GTUArray<T, SIZE>::GTUConstIterator GTUArray<T, SIZE>::GTUConstIterator::operator-(const difference_type& subtptrdiff)
   {
      GTUConstIterator temp(itr);
      temp.itr -= subtptrdiff;
      return temp;
   }

   template<typename T, size_t SIZE>
   GTUArray<T, SIZE>::GTUConstIterator::operator bool() const
   {
      if (itr) return true;
      else     return false;
   }
}
