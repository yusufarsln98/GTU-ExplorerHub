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

#include "gtuvector.h"
#include "gtuvectoriterator.h"
#include "gtuconstvectoriterator.h"
#include "gtucontainerexceptions.h"

using std::shared_ptr;
using std::default_delete;
using std::move;
using std::cout;
using std::endl;

namespace YusufArslanGTU_Containers
{
   // --- Default constructor ---
   template<typename T>
   GTUVector<T>::GTUVector() : Container(nullptr), Size(0) {}
   
   // --- int paramater constructor ---
   template<typename T>
   GTUVector<T>::GTUVector(int cap) : Size(cap) 
   {
      shared_ptr<T> temp(new T[Size], default_delete<T[]>());
      Container = temp;
   }

   // --- Copy constructor ---
   template<typename T>
   GTUVector<T>::GTUVector(const GTUVector& new_vector)
   {
      Size = new_vector.size();
      shared_ptr<T> temp(new T[Size], default_delete<T[]>());
      for (auto i = 0; i < Size; i++)
      {
         temp.get()[i] = new_vector.Container.get()[i];
      }
      Container = temp;
   }

   // --- Move constructor ---
   template<typename T>
   GTUVector<T>::GTUVector(GTUVector&& new_vector)
   {
      shared_ptr<T> temp;

      Size = new_vector.size();
      Container = new_vector.Container;

      new_vector.Size = 0;
      new_vector.Container = temp;
   }

   template<typename T>
   bool GTUVector<T>::empty() const 
   {
      return Size == 0 ? true : false;
   }

   template<typename T>
   unsigned int GTUVector<T>::size() const {return Size; }

   template<typename T>
   void GTUVector<T>::clear() 
   {
      shared_ptr<T> temp;
      Container = temp;
      Size = 0;
   }
   
   // Erase an element which position is pointing
   template<typename T>
   typename GTUVector<T>::GTUIterator GTUVector<T>::erase(GTUConstIterator position)
   {
      bool isexist = false;
      
      for (auto i = cbegin(); ; i++)
      {
         if(position == i)
         {
            isexist = true;
            break;
         }
         if (i == cend())
            break;
      }
      
      if (isexist == false)
         return GTUIterator(Container.get());
      else
      {
         shared_ptr<T> temp(new T[Size - 1], default_delete<T[]>());
         for (auto i = cbegin(), j = 0; i != cend(); i++)
         {
            if(position != i)
            {
               temp.get()[j] = *i;
               j++;
            }
         }
         Container = temp;
         Size--;
         return GTUIterator(Container.get());
      }
   }

   template<typename T>
   typename GTUVector<T>::GTUIterator GTUVector<T>::begin()
   {
      return Container.get();
   }

   template<typename T>
   typename GTUVector<T>::GTUIterator GTUVector<T>::end()
   {
      return Container.get() + Size;
   }

   template<typename T>
   typename GTUVector<T>::GTUConstIterator GTUVector<T>::cbegin() const
   {
      return Container.get();
   }

   template<typename T>
   typename GTUVector<T>::GTUConstIterator GTUVector<T>::cend() const
   {
      return Container.get() + Size;
   }

   // --- Copy assigment ---
   template<typename T>
   GTUVector<T>& GTUVector<T>::operator=(const GTUVector& new_vector)
   {
      if (Container == new_vector.Container) return *this;

      Size = new_vector.size();
      shared_ptr<T> temp(new T[Size], default_delete<T[]>());
      for (auto i = 0; i < Size; i++)
      {
         temp.get()[i] = new_vector.Container.get()[i];
      }
      Container = temp;
      return *this;
   }

   // --- Move assigment ---
   template<typename T>
   GTUVector<T>& GTUVector<T>::operator=(GTUVector&& new_vector)
   {
      if (this == &new_vector) return *this;

      shared_ptr<T> temp;

      Size = new_vector.size();
      Container = new_vector.Container;
   
      new_vector.Size = 0;
      new_vector.Container = temp;

      return *this;
   }

   // Insert an element to the back
   template<typename T>
   void GTUVector<T>::push_back(const T& val)
   {
      shared_ptr<T> temp(new T[Size + 1], default_delete<T[]>());
      
      for (auto i = 0; i < Size; i++)
         temp.get()[i] = move(Container.get()[i]);

      temp.get()[Size] = val;
      
      Size++;
      Container = temp;
   }

   // Remove an element from back
   template<typename T>
   void GTUVector<T>::pop_back()
   {
      shared_ptr<T> temp(new T[Size - 1], default_delete<T[]>());
      
      for (auto i = 0; i < Size - 1; i++)
         temp.get()[i] = move(Container.get()[i]);
      
      Size--;
      Container = temp;
   }

   // Access the data
   template<typename T>
   T& GTUVector<T>::operator[] (int index)
   {
      if (!(index >= 0 && index < Size))
         throw(out_of_vector_range());
         
      return Container.get()[index];
   }

   // Access the data
   template<typename T>
   T& GTUVector<T>::at(int index)
   {
      if (!(index >= 0 && index < Size))
         throw(out_of_vector_range());

      return Container.get()[index];
   }

   // ------------------ Inner Classes ------------------
   // --------- GTUITerator Inner Class ---------
   template<typename T>
   GTUVector<T>::GTUIterator::GTUIterator() : itr(nullptr) {}

   template<typename T>
   GTUVector<T>::GTUIterator::GTUIterator(T* newItr) : itr(newItr) {}

   template<typename T>
   GTUVector<T>::GTUIterator::GTUIterator(const GTUConstIterator& rval) : itr(rval.itr) {}

   template<typename T>
   GTUVector<T>::GTUIterator::GTUIterator(const GTUIterator& rval) : itr(rval.itr) {}

   template<typename T>
   GTUVector<T>::GTUIterator::GTUIterator(GTUIterator&& rval) : itr(rval.itr) {rval.itr = nullptr; }

   template<typename T>
   GTUVector<T>::GTUIterator::~GTUIterator() {}

   template<typename T>
   typename GTUVector<T>::GTUIterator& GTUVector<T>::GTUIterator::operator=(const GTUIterator& rval)
   {
      itr = rval.itr;
      return *this;
   }

   template<typename T>
   typename GTUVector<T>::GTUIterator& GTUVector<T>::GTUIterator::operator=(GTUIterator&& rval)
   {
      itr = rval.itr;
      rval.itr = nullptr;
      return *this;
   }

   template<typename T>
   T& GTUVector<T>::GTUIterator::operator*()
   {
      return *itr;
   }
   
   template<typename T>
   T* GTUVector<T>::GTUIterator::operator->()
   {
      return itr;
   }

   // prefix
   template<typename T>
   typename GTUVector<T>::GTUIterator& GTUVector<T>::GTUIterator::operator++()
   {
      itr++;
      return *this;
   }

   // postfix
   template<typename T>
   typename GTUVector<T>::GTUIterator GTUVector<T>::GTUIterator::operator++(int discard)
   {
      GTUIterator temp(itr);
      itr++;
      return temp;
   }
   
   // prefix
   template<typename T>
   typename GTUVector<T>::GTUIterator& GTUVector<T>::GTUIterator::operator--()
   {
      itr--;
      return *this;
   }

   // postfix
   template<typename T>
   typename GTUVector<T>::GTUIterator GTUVector<T>::GTUIterator::operator--(int discard)
   {
      GTUIterator temp(itr);
      itr--;
      return temp;
   }

   template<typename T>
   bool GTUVector<T>::GTUIterator::operator==(const GTUIterator& rval) const
   {
      return itr == rval.itr ? true : false;
   }

   template<typename T>
   bool GTUVector<T>::GTUIterator::operator!=(const GTUIterator& rval) const
   {
      return itr != rval.itr ? true : false;
   }

   template<typename T>
   typename GTUVector<T>::GTUIterator GTUVector<T>::GTUIterator::operator+(int addint)
   {
      GTUIterator temp(itr);
      temp.itr += addint;
      return temp;
   }
   
   template<typename T>
   typename GTUVector<T>::GTUIterator GTUVector<T>::GTUIterator::operator+(const difference_type& addptrdiff)
   {
      GTUIterator temp(itr);
      temp.itr += addptrdiff;
      return temp;
   }

   template<typename T>
   typename GTUVector<T>::GTUIterator GTUVector<T>::GTUIterator::operator-(int subtint)
   {
      GTUIterator temp(itr);
      temp.itr -= subtint;
      return temp;
   }

   template<typename T>
   typename GTUVector<T>::GTUIterator GTUVector<T>::GTUIterator::operator-(const difference_type& subtptrdiff)
   {
      GTUIterator temp(itr);
      temp.itr -= subtptrdiff;
      return temp;
   }

   template<typename T>
   GTUVector<T>::GTUIterator::operator bool() const
   {
      if (itr) return true;
      else return false;
   }

   // --------- GTUConstITerator Inner Class ---------
   template<typename T>
   GTUVector<T>::GTUConstIterator::GTUConstIterator() : itr(nullptr) {}

   template<typename T>
   GTUVector<T>::GTUConstIterator::GTUConstIterator(const T* newItr) : itr(newItr) {}
   
   template<typename T>
   GTUVector<T>::GTUConstIterator::GTUConstIterator(const GTUIterator& rval) : itr(rval.itr) {}
   
   template<typename T>
   GTUVector<T>::GTUConstIterator::GTUConstIterator(const GTUConstIterator& rval) : itr(rval.itr) {}

   template<typename T>
   GTUVector<T>::GTUConstIterator::GTUConstIterator(GTUConstIterator&& rval) : itr(rval.itr) {rval.itr = nullptr; }

   template<typename T>
   GTUVector<T>::GTUConstIterator::~GTUConstIterator() {}

   template<typename T>
   typename GTUVector<T>::GTUConstIterator& GTUVector<T>::GTUConstIterator::operator=(const GTUConstIterator& rval)
   {
      itr = rval.itr;
      return *this;
   }

   template<typename T>
   typename GTUVector<T>::GTUConstIterator& GTUVector<T>::GTUConstIterator::operator=(GTUConstIterator&& rval)
   {
      itr = rval.itr;
      rval.itr = nullptr;
      return *this;
   }

   template<typename T>
   const T& GTUVector<T>::GTUConstIterator::operator*()
   {
      return *itr;
   }
   
   template<typename T>
   const T* GTUVector<T>::GTUConstIterator::operator->()
   {
      return itr;
   }

   // prefix
   template<typename T>
   typename GTUVector<T>::GTUConstIterator& GTUVector<T>::GTUConstIterator::operator++()
   {
      itr++;
      return *this;
   }

   // postfix
   template<typename T>
   typename GTUVector<T>::GTUConstIterator GTUVector<T>::GTUConstIterator::operator++(int discard)
   {
      GTUConstIterator temp(itr);
      itr++;
      return temp;
   }
   
   // prefix
   template<typename T>
   typename GTUVector<T>::GTUConstIterator& GTUVector<T>::GTUConstIterator::operator--()
   {
      itr--;
      return *this;
   }

   // postfix
   template<typename T>
   typename GTUVector<T>::GTUConstIterator GTUVector<T>::GTUConstIterator::operator--(int discard)
   {
      GTUConstIterator temp(itr);
      itr--;
      return temp;
   }

   template<typename T>
   bool GTUVector<T>::GTUConstIterator::operator==(const GTUConstIterator& rval) const
   {
      return itr == rval.itr ? true : false;
   }

   template<typename T>
   bool GTUVector<T>::GTUConstIterator::operator!=(const GTUConstIterator& rval) const
   {
      return itr != rval.itr ? true : false;
   }

   template<typename T>
   typename GTUVector<T>::GTUConstIterator GTUVector<T>::GTUConstIterator::operator+(int addint)
   {
      GTUConstIterator temp(itr);
      temp.itr += addint;
      return temp;
   }

   template<typename T>
   typename GTUVector<T>::GTUConstIterator GTUVector<T>::GTUConstIterator::operator+(const difference_type& addptrdiff)
   {
      GTUConstIterator temp(itr);
      temp.itr += addptrdiff;
      return temp;
   }

   template<typename T>
   typename GTUVector<T>::GTUConstIterator GTUVector<T>::GTUConstIterator::operator-(int subtint)
   {
      GTUConstIterator temp(itr);
      temp.itr -= subtint;
      return temp;
   }

   template<typename T>
   typename GTUVector<T>::GTUConstIterator GTUVector<T>::GTUConstIterator::operator-(const difference_type& subtptrdiff)
   {
      GTUConstIterator temp(itr);
      temp.itr -= subtptrdiff;
      return temp;
   }

   template<typename T>
   GTUVector<T>::GTUConstIterator::operator bool() const
   {
      if (itr) return true;
      else     return false;
   }
}
