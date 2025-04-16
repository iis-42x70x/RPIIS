/**************************************************
Название: Нахождение булеана
Разработчик: Кравцова Вероника Кирилловна
Дата: 07.04.2025
Описание: программа получает через консольные
параметры имя файла, читает из него множество,
после чего составляет и выводит все подмножества
считанного множества.
**************************************************/
#pragma warning(disable : 4996)

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
#include <locale>

#define MAX_ELEMENTS 32
#define MAX_NAME_LEN 50
#define MAX_FILENAME_LEN 256
#define MAX_NESTING_LEVEL 5

//объявление структуры для представления переменной
typedef struct Element {
    char name[MAX_NAME_LEN];
    bool is_set;
    struct Element* elements;
    int element_count;
} Element;

//объявление структуры для представления множества
typedef struct {
    char name[MAX_NAME_LEN];
    Element elements[MAX_ELEMENTS];
    int size;
} Set;

//функция пропуска пробелов. передвигает указатель
//в файле, пока символ является пробелом. в качестве
//аргумента получает указатель на файл.
void skip_whitespace(FILE* file) {
    int c;
    while ((c = fgetc(file)) != EOF && isspace(c));
    if (c != EOF) ungetc(c, file);
}

//функция считывания имени элемента. в качестве аргументов получает
//указатель на файл и указатель на массив, хранящий имя элемента.
void read_element_name(FILE* file, char* name) {
    int i = 0;
    int c;
    while ((c = fgetc(file)) != EOF && !isspace(c) && c != ',' && c != '}' && i < MAX_NAME_LEN - 1) {
        name[i++] = c;
    }
    name[i] = '\0';
    if (c != EOF) ungetc(c, file);
}

bool parse_set(FILE*, Element*, int);
//функция разделения элементов. в качестве аргументов получает
//указатель на файл, указатель на элемент, уровень вложенности
bool parse_element(FILE* file, Element* element, int nesting_level) {
    if (nesting_level >= MAX_NESTING_LEVEL) return false;

    skip_whitespace(file);
    int c = fgetc(file);

    if (c == '{') {
        return parse_set(file, element, nesting_level);
    }
    else {
        ungetc(c, file);
        element->is_set = false;
        read_element_name(file, element->name);
        return strlen(element->name) > 0;
    }
}

//функция разделения множеств. в качестве аргументов получает
//указатель на файл, указатель на элемент, уровень вложенности
bool parse_set(FILE* file, Element* set_element, int nesting_level) {
    set_element->is_set = true;
    set_element->element_count = 0;
    set_element->elements = (Element*)malloc(MAX_ELEMENTS * sizeof(Element));
    if (!set_element->elements) return false;

    while (true) {
        skip_whitespace(file);
        int c = fgetc(file);
        if (c == '}') break;
        if (c == EOF) {
            free(set_element->elements);
            return false;
        }
        ungetc(c, file);

        if (set_element->element_count >= MAX_ELEMENTS) {
            free(set_element->elements);
            return false;
        }

        if (!parse_element(file, &set_element->elements[set_element->element_count], nesting_level + 1)) {
            free(set_element->elements);
            return false;
        }
        set_element->element_count++;

        skip_whitespace(file);
        c = fgetc(file);
        if (c == '}') break;
        if (c != ',') {
            free(set_element->elements);
            return false;
        }
    }
    return true;
}

//функция чтения имени множества. в качестве аргументов
//получает указатель на файл, указатель на множество
bool read_set(FILE* file, Set* set) {
    int i = 0;
    int c;
    while ((c = fgetc(file)) != EOF && c != '=' && i < MAX_NAME_LEN - 1) {
        if (!isspace(c)) set->name[i++] = c;
    }
    set->name[i] = '\0';

    while (i > 0 && isspace(set->name[i - 1])) set->name[--i] = '\0';

    if (c != '=') return false;

    skip_whitespace(file);
    c = fgetc(file);
    if (c != '{') return false;

    set->size = 0;
    while (set->size < MAX_ELEMENTS) {
        if (!parse_element(file, &set->elements[set->size], 0)) break;
        set->size++;

        skip_whitespace(file);
        c = fgetc(file);
        if (c == '}') break;
        if (c != ',') return false;
    }

    return true;
}

//функция
void print_element(const Element* element) {
    if (element->is_set) {
        printf("{");
        for (int i = 0; i < element->element_count; i++) {
            if (i > 0) printf(", ");
            print_element(&element->elements[i]);
        }
        printf("}");
    }
    else {
        printf("%s", element->name);
    }
}

/**
 * Генерирует все подмножества множества с использованием битовой маски
 * @param set Указатель на исходное множество
 */
void generate_subsets(const Set* set) {
    unsigned int total_subsets = 1 << set->size; // 2^n подмножеств

    for (unsigned int mask = 0; mask < total_subsets; mask++) {
        printf("{");
        bool first = true;

        // Проверяем каждый бит маски
        for (int i = 0; i < set->size; i++) {
            if (mask & (1 << i)) {  // Если i-й бит установлен
                if (!first) printf(", ");
                print_element(&set->elements[i]);
                first = false;
            }
        }
        printf("}\n");
    }
}

void free_element(Element* element) {
    if (element->is_set) {
        for (int i = 0; i < element->element_count; i++) {
            free_element(&element->elements[i]);
        }
        free(element->elements);
    }
}

int main() {
    setlocale(LC_ALL, "ru");
    char filename[MAX_FILENAME_LEN];
    FILE* input;
    Set set;
    bool flag;
    do {
        do {
            flag = false;
            printf("Введите имя файла с множеством: ");
            if (!fgets(filename, sizeof(filename), stdin)) {
                printf("Ошибка чтения имени файла\n");
                flag = true;
            }
            filename[strcspn(filename, "\n")] = '\0';

            input = fopen(filename, "r");
            if (!input) {
                printf("Не удалось открыть файл '%s'\n", filename);
                flag = true;
            }
        } while (flag);


        flag = false;
        if (!read_set(input, &set)) {
            printf("Ошибка чтения множества. Проверьте формат файла.\n");
            printf("Ожидаемый формат: имя_множества = {элемент1, элемент2, {вложенный1, вложенный2}}\n");
            fclose(input);
            flag = true;
        }
    } while (flag);
        
    
    fclose(input);
    printf("\nИсходное множество '%s':\n", set.name);
    printf("{");
    for (int i = 0; i < set.size; i++) {
        if (i > 0) printf(", ");
        print_element(&set.elements[i]);
    }
    printf("}\n\nВсе подмножества:\n");

    generate_subsets(&set);

    for (int i = 0; i < set.size; i++) {
        free_element(&set.elements[i]);
    }

    return 0;
}
