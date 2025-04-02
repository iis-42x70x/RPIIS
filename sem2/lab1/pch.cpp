//pch.cpp
#include "pch.h"
#include <algorithm>
#include <iostream>
#include <fstream>
#include <sstream>

std::vector<std::vector<int>> YoungTableau::getTable() const {
	return table; // Предполагается, что table — это член класса
}

void YoungTableau::initialize(int row_number)
{
	if (hasDuplicates()) {
		std::cout << "Ошибка: Таблица содержит дубликаты элементов.\n";
		return;  // Прекращаем инициализацию
	}
	if (!table.empty())
	{
		for (auto& row : table)
			row.clear();
		table.clear();
	}
	this->row_number = row_number; // Инициализация поля row_number
	for (int i = 0; i < row_number; i++)
	{
		table.push_back({});
	}
}
size_t YoungTableau::width()
{
	return table.size();
}

void YoungTableau::initialize(const std::vector<std::vector<int>>& inputTable) {
	table = inputTable;

	// 1. Сортируем каждую строку по возрастанию
	for (auto& row : table) {
		std::sort(row.begin(), row.end());
	}

	// 2. Обеспечиваем порядок в столбцах (просеивание вниз)
	for (int col = 0; col < table[0].size(); ++col) {
		for (int row = 1; row < table.size(); ++row) {
			if (table[row].size() > col && table[row - 1][col] > table[row][col]) {
				std::swap(table[row - 1][col], table[row][col]);

				// Просеивание вниз
				int r = row;
				while (r + 1 < table.size() && table[r + 1].size() > col && table[r + 1][col] < table[r][col]) {
					std::swap(table[r][col], table[r + 1][col]);
					r++;
				}
			}
		}
	}
}

bool YoungTableau::hasDuplicates() const {
	for (size_t i = 0; i < table.size(); ++i) {
		for (size_t j = 0; j < table[i].size(); ++j) {
			// Сравниваем текущий элемент с последующими
			for (size_t k = i; k < table.size(); ++k) {
				for (size_t l = (k == i ? j + 1 : 0); l < table[k].size(); ++l) {
					if (table[i][j] == table[k][l]) {
						return true;  // Дубликат найден
					}
				}
			}
		}
	}
	return false;  // Дубликатов нет
}


void YoungTableau::add(int line_number, int element)
{
	if (line_number > table.size())
	{
		std::cout << "Ошибка: Недопустимый номер строки.\n";
		return;
	}

	auto& row = table[line_number - 1];
	row.push_back(element);

	// Просеивание вверх (bubble-up)
	int rowIndex = line_number - 1;
	int colIndex = row.size() - 1;

	while (rowIndex > 0 || colIndex > 0)
	{
		int parentRow = rowIndex > 0 ? rowIndex - 1 : rowIndex;
		int parentCol = colIndex > 0 ? colIndex - 1 : colIndex;

		if (table[parentRow][parentCol] > table[rowIndex][colIndex])
		{
			std::swap(table[parentRow][parentCol], table[rowIndex][colIndex]);
			rowIndex = parentRow;
			colIndex = parentCol;
		}
		else
		{
			break;
		}
	}
}

void YoungTableau::removeAll(int element)
{
	bool in_table = false;
	for (auto& row : table)
	{
		while (true)
		{
			auto it = std::find(row.begin(), row.end(), element);

			if (it != row.end())
			{
				row.erase(it);
				in_table = true;
			}
			else
				break;
		}
	}
	if (!in_table)
		std::cout << "Данного элемента нет в таблице.\n";
	else
		std::cout << "Из таблицы были удалены все элементы " << element << ".\n";
}

void YoungTableau::print()
{
	if (table.size() == 0)
		std::cout << "\nТаблица пуста.\n";
	bool nonempty_row = false;
	for (auto& row : table)
	{
		if (!row.empty())
		{
			nonempty_row = true;
			break;
		}
	}
	if (!nonempty_row)
	{
		std::cout << "\nТаблица пуста.\n";
		return;
	}
	std::cout << "\nТаблица Юнга:\n";
	for (auto& row : table)
	{
		for (int element : row)
		{
			std::cout << element << " ";
		}
		std::cout << "\n";
	}
}

void YoungTableau::printToFile(std::string filename)
{
	std::ofstream fout(filename);
	if (table.size() == 0)
		fout << "Таблица пуста.";
	fout << "Таблица Юнга:";
	for (auto& row : table)
	{
		fout << "\n";
		for (int element : row)
		{
			fout << element << " ";
		}
	}
	std::cout << "Таблица была выведена в " << filename << "\n";
}

void YoungTableau::add1(int element, int line_number = 1)
{

	// Проверка допустимости номера строки
	if (line_number <= table.size())
	{
		auto& row = table[line_number - 1];

		// Проверка наличия элемента в строке
		if (std::find(row.begin(), row.end(), element) != row.end())
		{
			std::cout << "Ошибка: Элемент уже присутствует в таблице.\n";
			return;
		}

		// Поиск позиции для вставки элемента
		auto insert_pos = std::upper_bound(row.begin(), row.end(), element);

		// Если элемент больше всех элементов строки, вставляем его в конец
		if (insert_pos == row.end())
		{
			row.push_back(element);
			std::cout << "Элемент " << element << " добавлен в конец строки.\n";
		}
		else
		{
			// Замена элемента в строке
			int replaced_element = *insert_pos;
			*insert_pos = element;
			std::cout << "Элемент " << element << " заменяет элемент " << replaced_element << " в строке.\n";

			// Вставка вытесненного элемента в следующую строку
			if (line_number < table.size())
			{
				add1(replaced_element, line_number + 1);
			}
			else
			{
				std::vector<int> new_row = { replaced_element };
				table.push_back(new_row);
				std::cout << "Элемент " << replaced_element << " добавлен в новую строку.\n";
			}
		}
	}
	else
	{
		std::cout << "Ошибка: Недопустимый номер строки.\n";
	}
}
void YoungTableau::remove(int position, int line_number)
{
	if (line_number > table.size() || position > table[line_number - 1].size())
	{
		std::cout << "Ошибка: Недопустимый номер строки или позиции.\n";
		return;
	}

	auto& row = table[line_number - 1];

	// Удаляем элемент
	row.erase(row.begin() + position - 1);

	// Просеивание вниз (sink-down)
	int rowIndex = line_number - 1;
	int colIndex = position - 1;

	while (rowIndex < table.size() - 1 || colIndex < row.size() - 1)
	{
		int childRow = rowIndex < table.size() - 1 ? rowIndex + 1 : rowIndex;
		int childCol = colIndex < row.size() - 1 ? colIndex + 1 : colIndex;

		if (table[childRow][childCol] < table[rowIndex][colIndex])
		{
			std::swap(table[childRow][childCol], table[rowIndex][colIndex]);
			rowIndex = childRow;
			colIndex = childCol;
		}
		else
		{
			break;
		}
	}
}