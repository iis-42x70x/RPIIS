#include <iostream>
#include <string>
#include <fstream>
#include <set>
#include "kkkk.h"
int poisknachala(std::string stroka) {//ищет элемент строки с которого начинается множество(пропускает пробелы)
	int i;
	for (i = 0; stroka[i] != NULL && stroka[i] == ' '; ++i) {
		if (stroka[i] != NULL && (stroka[i] == '{' || stroka[i] == '<'))
			++i;
		return i;
	}
}
void pereborSET(std::string stroka/*,bool skobka*/, int& kolvo) {//ишет ошибку в количестве скобок для множеств
	for (int i = 0; stroka[i] != NULL; i++) {
		if (stroka[i] == '{' || stroka[i] == '<') {
			++kolvo;
		}
		if (stroka[i] == '}' || stroka[i] == '>') {
			--kolvo;
		}
	}
	if (kolvo != 0) {
		std::cout << "nevrny vvod mnojestva(oshibka s '{', '}', '<', '>' ";
		exit(10705);
	}
}
std::string convertsettostring(const superset& sett) {//преобразует структуру superset в одну строку std::string
	std::string result;
	result += sett.posled ? '<' : '{';

	bool first = true;

	// Сначала выводим элементы
	for (const auto& el : sett.elem) {
		if (!first) result += ',';
		result += el;
		first = false;
	}
	// Затем подмножества
	for (const auto& subset : sett.mnoj) {
		if (!first) result += ',';
		result += convertsettostring(subset);
		first = false;
	}

	result += sett.posled ? '>' : '}';
	return result;
}
// Аналог std::set_difference для std::set<string>
void custom_set_difference(const std::set<std::string>& a,
	const std::set<std::string>& b,
	std::set<std::string>& result) {
	auto it_a = a.begin();
	auto it_b = b.begin();

	while (it_a != a.end() && it_b != b.end()) {
		if (*it_a < *it_b) {
			result.insert(*it_a);
			++it_a;
		}
		else if (*it_b < *it_a) {
			++it_b;
		}
		else { // Элементы равны
			++it_a;
			++it_b;
		}
	}

	// Добавляем оставшиеся элементы из a
	while (it_a != a.end()) {
		result.insert(*it_a);
		++it_a;
	}
}
void insertmnoj(superset& sett, const std::string& stroka, int& pos) {//вставка множества в виде строки std::string в структуру superset
	while (pos < stroka.length()) {
		if (stroka[pos] == ' ' || stroka[pos] == ',') {
			pos++;
			continue;
		}
		if (stroka[pos] == '{' || stroka[pos] == '<') {//найдено множество
			bool is_ordered = (stroka[pos] == '<');
			pos++;

			if (stroka[pos] == (is_ordered ? '>'  : '}')) {
				// Пустое множество
				sett.elem.insert( "{}");
				pos++;
				continue;
			}

			superset new_set;
			new_set.posled = is_ordered;
			auto result = sett.mnoj.insert(new_set);
			insertmnoj(const_cast<superset&>(*result.first), stroka, pos);
		}
		else if (stroka[pos] == '>' || stroka[pos] == '}') {
			pos++;
			return;
		}
		else {
			// Обработка обычного элемента
			std::string element;
			while (pos < stroka.length() && stroka[pos] != ' ' &&
				stroka[pos] != ',' && stroka[pos] != '>' &&
				stroka[pos] != '}' ) {
				element += stroka[pos++];
			}
			if (!element.empty()) {
				sett.elem.insert(element);
			}
		}
	}
}
//	if (stroka[k] == NULL) return;
//	for (int i = k + 1; stroka[i] != '}' && stroka[i] != '>'; ++i) {
//		if (stroka[i] == ' ' || stroka[i] == ',') {
//			continue;
//		}
//		else if (stroka[i] == '{' && stroka[i + 1] == '}') {
//			std::string strochka;
//			strochka.push_back('{');
//			strochka.push_back('}');
//			sett.elem.insert(strochka);
//			l++;
//			i++;
//			continue;
//		}
//		else if (stroka[i] == '{') {
//			/*drevo[l].poryadok = 0;*/
//			k = i;
//			superset mnojestvo;
//			mnojestvo.posled = 0;
//			sett.mnoj.insert(mnojestvo);
//			auto it = sett.mnoj.find(mnojestvo);
//			insertmnoj(*it, stroka, k, l);
//			/*Insert(tree, drevo[l].root->key, drevo[l].root->info);*/
//			/*insertmnoj(drevo[l], drevo, stroka, i, l);*/
//			/*drevo[l].root->parent = leaf;*/
//			++l;
//		}
//		else if (stroka[i] == '<') {
//			/*drevo[l].poryadok = 1;*/
//			k = i;
//			superset mnojestvo;
//			mnojestvo.posled = 1;
//			sett.mnoj.insert(mnojestvo);
//			auto it = sett.mnoj.find(mnojestvo);
//			insertmnoj(*it, stroka, k, l);
//			++l;
//		}
//		else {
//			std::string strochka;
//			for (int j = 0; stroka[i] != ' ' && stroka[i] != ',' && stroka[i] != NULL; i++, j++) {
//				if (stroka[i] == '>' || stroka[i] == '}') {
//					--i; break;
//				}
//				strochka.push_back(stroka[i]);
//			}
//			sett.elem.insert(strochka);
//		}
//	}
//	return;
//}
//
superset raznost2(const superset& a, const superset& b) {//разность элементов множества + подмножества с их разностью
	superset result;
	result.posled = a.posled;

	// 1. Вычитаем простые элементы
	for (const auto& el : a.elem) {
		if (b.elem.find(el) == b.elem.end()) {
			result.elem.insert(el);
		}
	}

	// 2. Вычитаем вложенные множества
	for (const auto& subset_a : a.mnoj) {
		bool exact_match_found = false;
		superset recursive_diff;
		recursive_diff.posled = subset_a.posled;

		// Ищем точное совпадение или максимально похожее подмножество
		for (const auto& subset_b : b.mnoj) {
			if (subset_a == subset_b) {
				exact_match_found = true;
				break;
			}

			// Если не полное совпадение, но есть общие элементы
			if (subset_a.posled == subset_b.posled) {
				recursive_diff = raznost(subset_a, subset_b);
			}
		}

		if (!exact_match_found) {
			if (recursive_diff.elem.empty() && recursive_diff.mnoj.empty()) {
				result.mnoj.insert(subset_a);
			}
			else if (!recursive_diff.elem.empty() || !recursive_diff.mnoj.empty()) {
				result.mnoj.insert(recursive_diff);
			}
		}
	}

	return result;
}
superset raznost(const superset& a, const superset& b) {//разность элементов и подмножеств(стандарт) не работает по неизвестной причине
	superset result;
	result.posled = a.posled;

	// 1. Вычитаем простые элементы
	for (const auto& el : a.elem) {
		if (b.elem.find(el) == b.elem.end()) {
			result.elem.insert(el);
		}
	}

	// 2. Обрабатываем вложенные множества
	for (const auto& subset_a : a.mnoj) {
		bool is_subset_found = false;

		// Ищем ПОДОБНОЕ подмножество в b (не обязательно точное совпадение)
		for (const auto& subset_b : b.mnoj) {
			// Если типы разные - пропускаем сравнение
			if (subset_a.posled != subset_b.posled) continue;

			// Если нашли похожее подмножество - отмечаем
			if (subset_a.elem == subset_b.elem && subset_a.mnoj == subset_b.mnoj) {
				is_subset_found = true;
				break;
			}
		}

		// Если не нашли похожего подмножества - добавляем целиком
		if (!is_subset_found) {
			result.mnoj.insert(subset_a);
		}
	}

	return result;
}
//std::string raznost(superset mnoj1, superset mnoj2,superset &raznost) {
//	if (mnoj1.elem == mnoj2.elem && mnoj1.mnoj == mnoj2.mnoj)
//		return "{}";
//	for (auto it2 = mnoj2.elem.begin(); it2 != mnoj2.elem.end(); ++it2)
//		for (auto it1 = mnoj1.elem.begin(); it1 != mnoj1.elem.end(); ++it1) {
//			if (*it2 != *it1)
//				raznost.elem.insert(*it1);
//		}
//	for (auto it2 = mnoj2.mnoj.begin(); it2 != mnoj2.mnoj.end(); ++it2)
//		for (auto it1 = mnoj1.mnoj.begin(); it1 != mnoj1.mnoj.end(); ++it1) {
//			if (*it2 != *it1)
//				raznost.mnoj.insert(*it1);
//		}
//	return convertsettostring( raznost);
//}
int main() {
	int kolvo = 0, kolvo2 = 0;
	int l=0,l2=0;
	std::string stroka,stroka2;
	std::ifstream inputfile("C:\\Users\\boyarskiu\\source\\repos\\mnojestva\\filetext.txt"/*, std::ios::binary*/);
	if (inputfile.is_open()){
		/*inputfile.open();*/
		std::getline(inputfile, stroka);
		std::getline(inputfile, stroka2);
		inputfile.close();
	}
	pereborSET(stroka,  kolvo);
	pereborSET(stroka2, kolvo2);
	superset sett1, sett2;
	int k = poisknachala(stroka);
	int K = poisknachala(stroka2);
	insertmnoj(sett1,stroka,k );
	insertmnoj(sett2,stroka2, K);
	std::cout <<'\n'<<stroka;
	std::cout << '\n' << stroka2;
	/*if (sett1 == sett2)
		std::cout << "\nreal";*/
	superset raznost1= raznost2(sett1, sett2);
	std::string itog = convertsettostring(raznost1);
	superset raznost2 = raznost(sett1, sett2);
	std::string itog2 = convertsettostring(raznost2);
	std::ofstream outputfile("C:\\Users\\boyarskiu\\source\\repos\\mnojestva\\itog.txt"/*, std::ios::binary*/);
	outputfile << itog<<' '<<itog2;
	/*std::string itog1; int p1 = 0, p2 = 0;
	std::string itog2;*/
	/*std::cout << '\n' << convertsettostring( sett1);
	std::cout << '\n' << convertsettostring(sett2);*/
	std::cout << '\n' << itog;
	std::cout << '\n' << itog2;
	outputfile.close();
	return -105;
}