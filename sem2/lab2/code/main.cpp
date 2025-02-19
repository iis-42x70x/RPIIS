/******************************************************************************
    Название:    SymmetricalDifference.cpp
    Разработчик: Вашкевич Максим Викторович
    Дата:        18.02.2024
    Описание:    программа получает через консольные параметры имя файла, чита-
                 ет  из него  все множества,  после чего  программа выводит  на
                 стандартный вывод результат выполнения операции симметрической
                 разности для всех этих множеств
******************************************************************************/

#include <iostream> // std::cout
#include <fstream>  // std::ifstream
#include <cstdlib>  // size_t
#include <string>   // std::string
#include <cmath>    // std::abs

#include "Set.hpp"

/**
 * @brief Выдаёт количество множеств во входном файле.
 *
 * @param filePath - путь до входного файла.
 * @return size_t - количество множеств.
 */
size_t getSetsCount(std::ifstream &fin)
{	
	size_t setsCount;
	fin >> setsCount;
	
	return setsCount;
}

/**
 * @brief Выдаёт следующее множество, находящееся во входном файле.
 *
 * @param filePath - путь до входного файла.
 * @return Set<int> - следующее множество.
 */
Set<int> getNextSet(std::ifstream &fin)
{
	size_t setSize;
	fin >> setSize;
	
	Set<int> s;
	for (size_t i = 0; i < setSize; i++)
	{
		int currentElement;
		fin >> currentElement;
		
		s.insert(currentElement, 1);
	}
	
	return s;
}

/**
 * @brief Симметрическая разность двух множеств.
 *
 * @param a - первое множество.
 * @param b - второе множество.
 * @return Set<int> - симметрическая разность.
 */
Set<int> symmetricalDifference(Set<int> a, Set<int> b)
{
	Set<int> s;
	
	int *aElements = nullptr;
	a.getElements(aElements);
	for (size_t i = 0; i < a.getSize(); i++)
	{
		s.insert(aElements[i],
		         std::abs((int)a.getMultiplicity(aElements[i]) -
		                  (int)b.getMultiplicity(aElements[i])));
	}
	
	int *bElements = nullptr;
	b.getElements(bElements);
	for (size_t i = 0; i < b.getSize(); i++)
	{
		if (!s.isFound(bElements[i]))
		{
			s.insert(bElements[i],
			         std::abs((int)a.getMultiplicity(bElements[i]) -
			                  (int)b.getMultiplicity(bElements[i])));
		}
	}
	
	delete[] aElements;
	delete[] bElements;
	
	return s;
}

int main(/* [[maybe_unused]] */int argc, const char *argv[])
{
	const std::string FILE_PATH = argv[1];
	
	Set<int> result;
	
        std::ifstream fin(FILE_PATH);
	size_t setsCount = getSetsCount(fin);
	for (size_t i = 0; i < setsCount; i++)
	{
		Set<int> currentSet = getNextSet(fin);
		
		result = symmetricalDifference(result, currentSet);
	}
        fin.close();
	
	int *resultElements = nullptr;
	result.getElements(resultElements);
	for (size_t i = 0; i < result.getSize(); i++)
	{
		for     (size_t j = 0;
		         j < result.getMultiplicity(resultElements[i]);
		         j++)
		{
			std::cout << resultElements[i] << ' ';
		}
	}
	
	delete[] resultElements;
	
	return EXIT_SUCCESS;
}