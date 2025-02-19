/******************************************************************************
    Название:    SymmetricalDifference.cpp
    Разработчик: Вашкевич Максим Викторович
    Дата:        18.02.2024
    Описание:    программа получает через консольные параметры имя файла, чита-
                 ет  из него  все множества,  после чего  программа выводит  на
                 стандартный вывод результат выполнения операции симметрической
                 разности для всех этих множеств
******************************************************************************/

#include <iostream>  // std::cout
#include <fstream>   // std::ifstream
#include <cstdlib>   // size_t
#include <string>    // std::string
#include <exception> // std::exception
#include <clocale>   // setlocale

#include "Set.hpp"

/**
 * @brief Выдаёт количество множеств во входном файле.
 *
 * @param filePath - путь до входного файла.
 * @return size_t - количество множеств.
 */
size_t getSetsCount(std::ifstream &fin)
{
	std::string setsCountStr;
	fin >> setsCountStr;
	
	long long setsCount = 0;
	try
	{
		setsCount = std::stoll(setsCountStr);

                if (setsCount <= 0)
		{
			throw std::exception();
		}
	}
	catch (const std::exception &ex)
	{
		std::cout << "The sets count value is invalid! Please, fix "
		"the file.\n";
		exit(EXIT_FAILURE);
	}
	
	return (size_t)setsCount;
}

/**
 * @brief Выдаёт следующее множество, находящееся во входном файле.
 *
 * @param filePath - путь до входного файла.
 * @return Set<int> - следующее множество.
 */
Set<int> getNextSet(std::ifstream &fin)
{
	std::string setSizeStr;
	fin >> setSizeStr;
	
	long long setSize = 0;
	try
	{
		setSize = std::stoul(setSizeStr);

                if (setSize <= 0)
		{
			throw std::exception();
		}
	}
	catch (const std::exception &ex)
	{
		std::cout << "The set size is invalid! Please, fix the file."
			"\n";
		exit(EXIT_FAILURE);
	}
	
	Set<int> s;
	for (size_t i = 0; i < (size_t)setSize; i++)
	{
		std::string currentElementStr;
		fin >> currentElementStr;
		
		int currentElement = 0;
		try
		{
			currentElement = std::stoi(currentElementStr);
		}
		catch (const std::exception &ex)
		{
			std::cout << "The set element value is invalid! "
				"Please, fix the file.\n";
			exit(EXIT_FAILURE);
		}
		
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

int main(/*[[maybe_unused]]*/int argc, const char *argv[])
{
	setlocale(LC_ALL, "rus");

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
	
        std::cout << "Симметрическая разность всех перечисленных в файле "
        	"множеств равна множеству:\n{ ";

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
	std::cout << "}\n";

	delete[] resultElements;
	
	return EXIT_SUCCESS;
}