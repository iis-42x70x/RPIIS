#ifndef SET_HPP
#define SET_HPP

#include <iostream>
#include <vector>
#include <algorithm>
#include <variant>
#include <string>

#include "Tuple.hpp"
template<typename T>
struct Tuple;

template<typename T>
struct Set
{
        using Element = std::variant<T, Tuple<T>, Set<T> >;
        std::vector<Element> elements;
        //adding elements to Set
        void add(const Element& elem) {
            elements.push_back(elem);
        }
		// getting size of Set
        const int getsize()
        {
            return this->elements.size();
        }

		// operator to assign 
        Set &operator=(const Set &s)
        {
            if (this != &s)
            {
				this->elements.resize(s.elements.size());
                for (size_t i = 0; i < this->getsize(); i++)
                {
                    this->elements[i] = s.elements[i];
                }
            }
            return *this;
        }

		// operator to display set
        template<typename T1>
        friend std::ostream & operator<<(std::ostream &, const Set<T1> &);  

		// operator to compare elements of Set or Tuple
		template<typename T1>
		friend bool operator== (const std::variant <T1, Set <T1>, Tuple <T1> > &,
								const std::variant <T1, Set <T1>, Tuple <T1> > &);
		
		// operator to compare Sets
		template<typename T1>
		friend bool operator== (const Set<T1>& , const Set<T1>& );

		
};

//operator to display Set
template<typename T>
std::ostream & operator<<(std::ostream &out,const Set<T> &set)
{
	out << "{ ";
	for (int i = 0; i <set.elements.size(); i++)
	{
			try
			{
				T currentElement = std::get<T>(set.elements[i]);
				out << currentElement;
			}
			catch (const std::bad_variant_access &)
			{
				try
				{
					Set<T> currentElementSet = std::get< Set<T> >(set.elements[i]);
					out << currentElementSet;
				}
				catch (const std::bad_variant_access &)
				{
					Tuple<T> currentElementTuple = std::get< Tuple<T> >(set.elements[i]);
					out << currentElementTuple;
				}
			}
			if(i != set.elements.size()-1)
				out << ", ";
	}
	out << " }";
	
	return out;
}

//operator to compare elements of Set or Tuple 
template<typename T1>
bool operator==(const std::variant <T1, Set <T1>, Tuple <T1> > &s1, 
				const std::variant <T1, Set <T1>, Tuple <T1> > &s2)
{
	if(s1.index() != s2.index())
		return false;
	else
		return (s1==s2);
}

// operator to compare Sets 
template<typename T>
bool operator==(const Set<T>& a, const Set<T>& b) {

    if (a.elements.size() != b.elements.size()) return false;

	for(size_t i = 0; i < a.elements.size(); i++){
		bool isFound = false;
		for(size_t j = 0; j< b.elements.size(); j++){
			if(a.elements[i] == b.elements[j]){
				isFound = true;
				break;
			}
		}
		if(!isFound)
			return false;
	}
    return true;
}

#endif
