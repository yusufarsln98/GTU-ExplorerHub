/*
   GEBZE TECHNICAL UNIVERSITY
   Object Orianted Programing - CSE241
   Homework 6
   Writing your own vector, set, array classes with iterators. 
   Yusuf Arslan
*/

#ifndef GTUCONTAINEREXCEPTION_GUARD
#define GTUCONTAINEREXCEPTION_GUARD

#include <iostream>
#include "gtuexceptions.h"

namespace YusufArslanGTU_Containers
{
    class out_of_vector_range : public YusufArslanGTUExceptions
    {
        const char * what () const throw () {return "Vector: either n '< 0' or 'n >= SIZE'"; }
    };

    class out_of_array_range : public YusufArslanGTUExceptions
    {
        const char * what () const throw () {return "Array: either n '< 0' or 'n >= SIZE'"; }
    };
}

#endif

