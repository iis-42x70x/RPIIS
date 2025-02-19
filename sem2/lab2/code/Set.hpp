/******************************************************************************
    Название:    Set.hpp
    Разработчик: Вашкевич Максим Викторович
    Дата:        18.02.2024
    Описание:    файл содержит определение класса Set, который представляет со-
                 бой множество (всё определение находится в заголовочном файле,
                 поскольку определяемый здесь класс является шаблонным).
******************************************************************************/

#include <cstdlib>

/**
 * @brief Класс-множество.
 * 
 * @tparam T - тип элементов множества.
 */
template<typename T>
class Set
{
private:
	T *m_data;
	size_t *m_multiplicity;
	size_t m_size;
	size_t m_capacity;
public:
        /**
         * @brief Конструктор для класса-множества.
         */
	Set()
	{
		this->m_size = 0;
		this->m_capacity = 1;
		this->m_data = new T[this->m_capacity];
		this->m_multiplicity = new size_t[m_capacity];
	}
	
        /**
         * @brief Оператор присваивания для Set.
         * 
         * @param s присваиваемый объект Set.
         * @return Set& присвоенный Set.
         */
	Set &operator=(const Set &s)
	{
		if (this != &s)
		{
			this->m_size = 0;
			this->m_capacity = 0;
			
			delete[] m_data;
			delete[] m_multiplicity;
			
			this->m_data = nullptr;
			this->m_multiplicity = nullptr;
			
			this->m_size = s.m_size;
			this->m_capacity = s.m_capacity;
			
			this->m_data = new T[this->m_capacity];
			this->m_multiplicity = new size_t[this->m_capacity];
			
			for (size_t i = 0; i < this->m_size; i++)
			{
				this->m_data[i] = s.m_data[i];
				this->m_multiplicity[i] = s.m_multiplicity[i];
			}
		}
		return *this;
	}
	
        /**
         * @brief Вставка элемента множества с определённой кратностью.
         * 
         * @param value - элемент.
         * @param count - кратность элемента.
         */
	void insert(const T &value, size_t count)
	{
		for (size_t i = 0; i < this->m_size; i++)
		{
			if (this->m_data[i] == value)
			{
				this->m_multiplicity[i] += count;
				return;
			}
		}
		
		if (this->m_size == this->m_capacity)
		{
			this->m_capacity = this->m_capacity * 3 / 2 + 1;
			
			T *dataAux = new T[this->m_capacity];
			auto *multiplicityAux = new size_t[this->m_capacity];
			for (size_t i = 0; i < this->m_size; i++)
			{
				dataAux[i] = this->m_data[i];
				multiplicityAux[i] = this->m_multiplicity[i];
			}
			
			delete[] this->m_data;
			delete[] this->m_multiplicity;
			
			this->m_data = dataAux;
			this->m_multiplicity = multiplicityAux;
		}
		
		this->m_data[this->m_size++] = value;
		this->m_multiplicity[this->m_size - 1] = count;
	}
	
        /**
         * @brief Кратность определённого элемента множества.
         * 
         * @param value - элемент.
         * @return size_t - кратность.
         */
	size_t getMultiplicity(const T &value)
	{
		for (size_t i = 0; i < this->m_size; i++)
		{
			if (this->m_data[i] == value)
			{
				return this->m_multiplicity[i];
			}
		}
		
		return 0;
	}
	
        /**
         * @brief Размер множества.
         * 
         * @return size_t размер.
         */
	size_t getSize()
	{
		return this->m_size;
	}
	
        /**
         * @brief Все элементы множества в динамическом массиве.
         * 
         * @param destination - динамический массив, куда надо записать множес-
         *                      тво.
         */
	void getElements(T *&destination) {
		if (destination != nullptr) {
			delete[] destination;
			destination = nullptr;
		}
		
		destination = new T[this->m_size];
		for (size_t i = 0; i < this->m_size; i++) {
			destination[i] = this->m_data[i];
		}
	}
	
        /**
         * @brief Существует ли элемент в множестве.
         * 
         * @param value - элемент.
         * @return true - если элемент найден.
         * @return false - если нет.
         */
	bool isFound(const T &value)
	{
		return this->getMultiplicity(value) != 0;
	}
};