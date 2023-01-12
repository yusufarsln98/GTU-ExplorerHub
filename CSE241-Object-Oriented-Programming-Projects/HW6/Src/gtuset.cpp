/*
   GEBZE TECHNICAL UNIVERSITY
   Object Orianted Programing - CSE241
   Homework 6
   Writing your own set, set, array classes with iterators. 
   Yusuf Arslan
*/


#include <iostream>
#include <memory>
#include <cstddef>
#include <iterator> 

#include "gtuset.h"
#include "gtusetiterator.h"
#include "gtuconstsetiterator.h"
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
   GTUSet<T>::GTUSet() : Container(nullptr), Size(0) {}
   
   // --- Copy constructor ---
   template<typename T>
   GTUSet<T>::GTUSet(const GTUSet& new_set)
   {
      Size = new_set.size();
      shared_ptr<T> temp(new T[Size], default_delete<T[]>());
      for (auto i = 0; i < Size; i++)
      {
         temp.get()[i] = new_set.Container.get()[i];
      }
      Container = temp;
   }

   // --- Move constructor ---
   template<typename T>
   GTUSet<T>::GTUSet(GTUSet&& new_set)
   {
      shared_ptr<T> temp;

      Size = new_set.size();
      Container = new_set.Container;

      new_set.Size = 0;
      new_set.Container = temp;
   }

   template<typename T>
   bool GTUSet<T>::empty() const 
   {
      return Size == 0 ? true : false;
   }

   template<typename T>
   unsigned int GTUSet<T>::size() const {return Size; }

   template<typename T>
   void GTUSet<T>::clear() 
   {
      shared_ptr<T> temp;
      Container = temp;
      Size = 0;
   }
   
   // Erase an element which position is pointing
   template<typename T>
   typename GTUSet<T>::GTUIterator GTUSet<T>::erase(GTUConstIterator position)
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
   typename GTUSet<T>::GTUIterator GTUSet<T>::begin()
   {
      return Container.get();
   }

   template<typename T>
   typename GTUSet<T>::GTUIterator GTUSet<T>::end()
   {
      return Container.get() + Size;
   }

   template<typename T>
   typename GTUSet<T>::GTUConstIterator GTUSet<T>::cbegin() const
   {
      return Container.get();
   }

   template<typename T>
   typename GTUSet<T>::GTUConstIterator GTUSet<T>::cend() const
   {
      return Container.get() + Size;
   }

   // --- Copy assigment ---
   template<typename T>
   GTUSet<T>& GTUSet<T>::operator=(const GTUSet& new_set)
   {
      if (Container == new_set.Container) return *this;

      Size = new_set.size();
      shared_ptr<T> temp(new T[Size], default_delete<T[]>());
      for (auto i = 0; i < Size; i++)
      {
         temp.get()[i] = new_set.Container.get()[i];
      }
      Container = temp;
      return *this;
   }

   // --- Move assigment ---
   template<typename T>
   GTUSet<T>& GTUSet<T>::operator=(GTUSet&& new_set)
   {
      if (this == &new_set) return *this;

      shared_ptr<T> temp;

      Size = new_set.size();
      Container = new_set.Container;
   
      new_set.Size = 0;
      new_set.Container = temp;

      return *this;
   }

   // Insert an element to set. Do not add if the element is already exist
   template<typename T>
   void GTUSet<T>::insert(const T& val)
   {
      if(isexist(val)) return;

      shared_ptr<T> temp(new T[Size + 1], default_delete<T[]>());
      
      for (auto i = 0; i < Size; i++)
         temp.get()[i] = Container.get()[i];
      
      temp.get()[Size] = val;
      Container = temp;
      Size++;
   }

   template<typename T>
   bool GTUSet<T>::isexist(const T& val) const
   {
      if (Size == 0) return false;
      for (auto i = cbegin(); ; i++)
      {
         if (val == *i)       return true;
         else if (i == cend()) break;
      }
      return false;
   }

   // Find position of an element
   template<typename T>
   typename GTUSet<T>::GTUIterator GTUSet<T>::find(const T& val)
   {
      if(!isexist(val)) return GTUIterator(nullptr);

      for (auto i = begin(); ; i++)
         if (val == *i) return GTUIterator(i);
   }

   // Erase an item from set
   template<typename T>
   typename GTUSet<T>::GTUIterator GTUSet<T>::erase(const T& val)
   {
      GTUConstIterator temp;
      temp = find(val);
      return erase(temp);
   }

   // Union of 2 set 
   template<typename T>
   GTUSet<T> GTUSet<T>::Union(const GTUSet<T>& new_set) const
   {
      GTUSet<T> temp(*this);
      for (auto i = 0; i < new_set.size(); i++)
      {
         temp.insert(new_set.Container.get()[i]);
      }
      return move(temp);
   }

   // Union of 2 set 
   template<typename T>
   GTUSet<T> GTUSet<T>::operator+(const GTUSet<T>& new_set) const
   {
      return move(Union(new_set));
   }

   // Intersection of 2 set
   template<typename T>
   GTUSet<T> GTUSet<T>::Intersect(const GTUSet<T>& new_set) const
   {
      GTUSet<T> temp;
      for (auto i = 0; i < new_set.size(); i++)
      {
         if(isexist(new_set.Container.get()[i]))
            temp.insert(new_set.Container.get()[i]);
      }
      return move(temp);
   }

   // Intersection of 2 set
   template<typename T>
   GTUSet<T> GTUSet<T>::operator^(const GTUSet<T>& new_set) const
   {
      return move(Intersect(new_set));
   }

   // Complement of 2 set
   template<typename T>
   GTUSet<T> GTUSet<T>::Complement(const GTUSet<T>& new_set) const
   {
      GTUSet<T> temp(*this);
      for (auto i = 0; i < new_set.size(); i++)
      {
         if(isexist(new_set.Container.get()[i]))
            temp.erase(new_set.Container.get()[i]);
      }
      return move(temp);
   }

   // Complement of 2 set
   template<typename T>
   GTUSet<T> GTUSet<T>::operator-(const GTUSet<T>& new_set) const
   {
      return move(Complement(new_set));
   }

   // ------------------ Inner Classes ------------------
   // --------- GTUITerator Inner Class ---------
   template<typename T>
   GTUSet<T>::GTUIterator::GTUIterator() : itr(nullptr) {}

   template<typename T>
   GTUSet<T>::GTUIterator::GTUIterator(T* newItr) : itr(newItr) {}

   template<typename T>
   GTUSet<T>::GTUIterator::GTUIterator(const GTUConstIterator& rval) : itr(rval.itr) {}

   template<typename T>
   GTUSet<T>::GTUIterator::GTUIterator(const GTUIterator& rval) : itr(rval.itr) {}

   template<typename T>
   GTUSet<T>::GTUIterator::GTUIterator(GTUIterator&& rval) : itr(rval.itr) {rval.itr = nullptr; }

   template<typename T>
   GTUSet<T>::GTUIterator::~GTUIterator() {}

   template<typename T>
   typename GTUSet<T>::GTUIterator& GTUSet<T>::GTUIterator::operator=(const GTUIterator& rval)
   {
      itr = rval.itr;
      return *this;
   }

   template<typename T>
   typename GTUSet<T>::GTUIterator& GTUSet<T>::GTUIterator::operator=(GTUIterator&& rval)
   {
      itr = rval.itr;
      rval.itr = nullptr;
      return *this;
   }

   template<typename T>
   T& GTUSet<T>::GTUIterator::operator*()
   {
      return *itr;
   }
   
   template<typename T>
   T* GTUSet<T>::GTUIterator::operator->()
   {
      return itr;
   }

   // prefix
   template<typename T>
   typename GTUSet<T>::GTUIterator& GTUSet<T>::GTUIterator::operator++()
   {
      itr++;
      return *this;
   }

   // postfix
   template<typename T>
   typename GTUSet<T>::GTUIterator GTUSet<T>::GTUIterator::operator++(int discard)
   {
      GTUIterator temp(itr);
      itr++;
      return temp;
   }
   
   // prefix
   template<typename T>
   typename GTUSet<T>::GTUIterator& GTUSet<T>::GTUIterator::operator--()
   {
      itr--;
      return *this;
   }

   // postfix
   template<typename T>
   typename GTUSet<T>::GTUIterator GTUSet<T>::GTUIterator::operator--(int discard)
   {
      GTUIterator temp(itr);
      itr--;
      return temp;
   }

   template<typename T>
   bool GTUSet<T>::GTUIterator::operator==(const GTUIterator& rval) const
   {
      return itr == rval.itr ? true : false;
   }

   template<typename T>
   bool GTUSet<T>::GTUIterator::operator!=(const GTUIterator& rval) const
   {
      return itr != rval.itr ? true : false;
   }

   template<typename T>
   typename GTUSet<T>::GTUIterator GTUSet<T>::GTUIterator::operator+(int addint)
   {
      GTUIterator temp(itr);
      temp.itr += addint;
      return temp;
   }

   template<typename T>
   typename GTUSet<T>::GTUIterator GTUSet<T>::GTUIterator::operator+(const difference_type& addptrdiff)
   {
      GTUIterator temp(itr);
      temp.itr += addptrdiff;
      return temp;
   }

   template<typename T>
   typename GTUSet<T>::GTUIterator GTUSet<T>::GTUIterator::operator-(int subtint)
   {
      GTUIterator temp(itr);
      temp.itr -= subtint;
      return temp;
   }
   
   template<typename T>
   typename GTUSet<T>::GTUIterator GTUSet<T>::GTUIterator::operator-(const difference_type& subtptrdiff)
   {
      GTUIterator temp(itr);
      temp.itr -= subtptrdiff;
      return temp;
   }

   template<typename T>
   GTUSet<T>::GTUIterator::operator bool() const
   {
      if (itr) return true;
      else return false;
   }

   // --------- GTUConstITerator Inner Class ---------
   template<typename T>
   GTUSet<T>::GTUConstIterator::GTUConstIterator() : itr(nullptr) {}

   template<typename T>
   GTUSet<T>::GTUConstIterator::GTUConstIterator(const T* newItr) : itr(newItr) {}
   
   template<typename T>
   GTUSet<T>::GTUConstIterator::GTUConstIterator(const GTUIterator& rval) : itr(rval.itr) {}
   
   template<typename T>
   GTUSet<T>::GTUConstIterator::GTUConstIterator(const GTUConstIterator& rval) : itr(rval.itr) {}

   template<typename T>
   GTUSet<T>::GTUConstIterator::GTUConstIterator(GTUConstIterator&& rval) : itr(rval.itr) {rval.itr = nullptr; }

   template<typename T>
   GTUSet<T>::GTUConstIterator::~GTUConstIterator() {}

   template<typename T>
   typename GTUSet<T>::GTUConstIterator& GTUSet<T>::GTUConstIterator::operator=(const GTUConstIterator& rval)
   {
      itr = rval.itr;
      return *this;
   }

   template<typename T>
   typename GTUSet<T>::GTUConstIterator& GTUSet<T>::GTUConstIterator::operator=(GTUConstIterator&& rval)
   {
      itr = rval.itr;
      rval.itr = nullptr;
      return *this;
   }

   template<typename T>
   const T& GTUSet<T>::GTUConstIterator::operator*()
   {
      return *itr;
   }
   
   template<typename T>
   const T* GTUSet<T>::GTUConstIterator::operator->()
   {
      return itr;
   }

   // prefix
   template<typename T>
   typename GTUSet<T>::GTUConstIterator& GTUSet<T>::GTUConstIterator::operator++()
   {
      itr++;
      return *this;
   }

   // postfix
   template<typename T>
   typename GTUSet<T>::GTUConstIterator GTUSet<T>::GTUConstIterator::operator++(int discard)
   {
      GTUConstIterator temp(itr);
      itr++;
      return temp;
   }
   
   // prefix
   template<typename T>
   typename GTUSet<T>::GTUConstIterator& GTUSet<T>::GTUConstIterator::operator--()
   {
      itr--;
      return *this;
   }

   // postfix
   template<typename T>
   typename GTUSet<T>::GTUConstIterator GTUSet<T>::GTUConstIterator::operator--(int discard)
   {
      GTUConstIterator temp(itr);
      itr--;
      return temp;
   }

   template<typename T>
   bool GTUSet<T>::GTUConstIterator::operator==(const GTUConstIterator& rval) const
   {
      return itr == rval.itr ? true : false;
   }

   template<typename T>
   bool GTUSet<T>::GTUConstIterator::operator!=(const GTUConstIterator& rval) const
   {
      return itr != rval.itr ? true : false;
   }

   template<typename T>
   typename GTUSet<T>::GTUConstIterator GTUSet<T>::GTUConstIterator::operator+(int addint)
   {
      GTUConstIterator temp(itr);
      temp.itr += addint;
      return temp;
   }

   template<typename T>
   typename GTUSet<T>::GTUConstIterator GTUSet<T>::GTUConstIterator::operator+(const difference_type& addptrdiff)
   {
      GTUConstIterator temp(itr);
      temp.itr += addptrdiff;
      return temp;
   }

   template<typename T>
   typename GTUSet<T>::GTUConstIterator GTUSet<T>::GTUConstIterator::operator-(int subtint)
   {
      GTUConstIterator temp(itr);
      temp.itr -= subtint;
      return temp;
   }

   template<typename T>
   typename GTUSet<T>::GTUConstIterator GTUSet<T>::GTUConstIterator::operator-(const difference_type& subtptrdiff)
   {
      GTUConstIterator temp(itr);
      temp.itr -= subtptrdiff;
      return temp;
   }

   template<typename T>
   GTUSet<T>::GTUConstIterator::operator bool() const
   {
      if (itr) return true;
      else     return false;
   }
}
