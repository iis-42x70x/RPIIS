#ifndef DIFFERENCE_HPP
#define DIFFERENCE_HPP

#include "Set.hpp"
#include "Tuple.hpp"

template<typename T>
Set<T> Difference(Set<T> a, Set<T> b)
{
	Set<T> s;
	
    for(size_t i = 0; i < a.getsize(); i++){
        bool foundInB = false;
        for(size_t j = 0; j < b.getsize(); j++){
            if(a.elements[i] == b.elements[j]){
                foundInB = true;
                break;
            }
        }
        if(!foundInB)
            s.add(a.elements[i]);
    }
	
	return s;
}

#endif


