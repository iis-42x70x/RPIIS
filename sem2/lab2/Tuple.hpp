#ifndef TUPLE_HPP
#define TUPLE_HPP

#include "Set.hpp"
template<typename T>
struct Set;

template <typename T>
struct Tuple{
        using Element = std::variant<T, Tuple<T>, Set<T> >;
        std::vector<Element> elements; // all the elements in a tuple

        // adding method
        void add(const Element& elem) {
            elements.push_back(elem);
        }

		// getting size of tuple method
        const int getsize()
        {
            return this->elements.size();
        }

		//operator to copy tuples
		Tuple &operator=(const Tuple &t)
        {
            if (this != &t)
            {
				this->elements.resize(t.elements.size());
                for (size_t i = 0; i < this->getsize(); i++)
                {
                    this->elements[i] = t.elements[i];
                }
            }
            return *this;
        }

		// operator to display a tuple
		template<typename T1>
		friend std::ostream & operator<<(std::ostream &,const Tuple<T1> &);

		// operator to compare tuples
		template<typename T1>
		friend bool operator==(const Tuple<T>& , const Tuple<T>& );
};

//operator to display tuples
template<typename T>
std::ostream & operator<<(std::ostream &out, const Tuple<T> &tuple)
{
	out << "< ";
	for (int i = 0; i < tuple.elements.size(); i++)
	{
		try
		{
			T currentElement = std::get<T>(tuple.elements[i]);
			out << currentElement;
		}
		catch (const std::bad_variant_access &)
		{
			try
			{
				Set<T> currentElementSet = std::get< Set<T> >(tuple.elements[i]);
				out << currentElementSet;
			}
			catch (const std::bad_variant_access &)
			{
				Tuple<T> currentElementTuple = std::get< Tuple<T> >(tuple.elements[i]);
				out << currentElementTuple;
			}
		}
		if(i != tuple.elements.size()-1)
			out << ", ";
	}
	out << " >";
	
	return out;
}

// operator to compare tuples
template<typename T>
bool operator==(const Tuple<T>& a, const Tuple<T>& b) {
    if (a.elements.size() != b.elements.size()) return false;

	for(size_t i = 0; i<a.elements.size(); i++){
		if(!(a.elements[i] == b.elements[i]))
			return false;
	}
	return true;
}

#endif


