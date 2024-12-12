# Отчет по расчетной работе по дисциплине ПиОИвИС

### Цель:
Ознакомиться с  основами теории графов, способами представления графов, базовыми алгоритмами для работы с разными видами графов.
### Условие задания
Определить, является ли граф планарным(1.21).
Граф задается матрицей инцидентности данные который читаются из файла.
Вывод работы программы выводиться в консоль.
### Базовые понятия 
- **Граф** - совокупность двух множеств множества самих объектов, называемого множеством вершин, и множества их парных связей, называемого множеством рёбер.
- Граф называется *планарным* если все его вершины можно поместить  на одной плоскости.
- Граф называется *непланарным*,если граф содержит графы гомеоморфные графам K<sub>5</sub> и K<sub>3,3</sub>
- **Планарный граф** — это граф, который можно нарисовать на плоскости без пересечения ребер. Другими словами, граф является плоским, если его можно вложить в плоскость так, чтобы никакие ребра не пересекались
- **Неориентированный граф - это граф, рёбра которого не имеют направления.
- **Матрица инцидентности** - это способ представления графа в виде матрицы. В этой матрице каждая строка соответствует одной вершине графа, а каждый столбец соответствует ребру графа. Элемент матрицы на пересечении строки i и столбца j равен 1, если ребро j либо выходит либо входит в точку i, и 0, в противном случае.
### Алгоритм работы программы:
1. Считываем примеры из файлов(1-4) или заполняем матрицу инцидентности вручную(5).
2. Выполним проверу на планарность. Если выполняется хотя бы одно условия снизу, то граф не является планарным.
   2.1. При количестве вершин в графе  `p>= 3`, а количество ребёр `q>= 3(p-2)`(p - вершины, q - рёбра).
   2.2. Граф не содержит треугольники и `p> 3` `q=>2*(p-2)`(p - вершины, q - рёбра).
   2.3. В графе больше 3 вершин со степенью  более 4.
   2.4. В графе больше 2 вершин со степенью более 5.
   2.5. Граф содержит  K<sub>5</sub> и K<sub>3,3</sub>.
Вот пример кода:
~~~c++
//r=q-p+2, p-вершина, q - рёбра - формула Эйлера
//p>3 => q<=3(p-2)

#include <iostream>
#include <fstream>
#include <string>

void wrong_message(short int x) {
    switch (x)
    {
    case 1: {
        system("cls");
        std::cout << "Invalid input..." << std::endl;
        system("pause");
        system("cls");
        break;
    }
    case 2: {
        system("cls");
        std::cout << "Error when opening file...";
        break;
    }
    case 3: {
        system("cls");
        std::cout << "Something happened:(";
        break;
    }
    default:
        break;
    }
}

bool cheking_choose(short int choose) {
    return choose >= 1 && choose <= 5;
}

void vivod(short int** matrix, short int m, short int n) {
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            std::cout << matrix[i][j] << " ";
            if (j == 4) {
                std::cout << std::endl;
            }
        }
    }
}

bool contains_triangle(short int** matrix, short int p, short int q) {
    // Перебираем все возможные тройки вершин
    for (int v1 = 0; v1 < p; v1++) {
        for (int v2 = v1 + 1; v2 < p; v2++) {
            for (int v3 = v2 + 1; v3 < p; v3++) {
                bool edge1 = false, edge2 = false, edge3 = false;

                // Проверяем наличие рёбер между вершинами v1, v2, v3
                for (int e = 0; e < q; e++) {
                    if (matrix[v1][e] && matrix[v2][e]) edge1 = true;
                    if (matrix[v2][e] && matrix[v3][e]) edge2 = true;
                    if (matrix[v3][e] && matrix[v1][e]) edge3 = true;
                }

                // Если все три ребра существуют, то найден треугольник
                if (edge1 && edge2 && edge3) {
                    return true;
                }
            }
        }
    }
    return false; // Треугольников нет
}

bool is_planar(short int** matrix, short int p, short int q) {
    // Проверяем 1 следствие теоремы Эйлера: q <= 3(p - 2), если p > 3
    if (p > 3 && q > 3 * (p - 2)) {
        std::cout << "!!1!!" << std::endl;
        return false;
    }

    // Проверяем 2 следствие теоремы Эйлера: для графов без треугольников q < 2(p - 2)
    if (p > 3 && !contains_triangle(matrix, p, q) && q >= 2 * (p - 2)) {
        std::cout << "!!2!!" << std::endl;
        return false;
    }

    // Вычисляем степени вершин
    short int* degrees = new short int[p] {};
    for (int i = 0; i < p; i++) {
        for (int j = 0; j < q; j++) {
            if (matrix[i][j] == 1) {
                degrees[i]++;
            }
        }
    }

    // Считаем количество вершин с высокой степенью
    int count_degree_gt_3 = 0;
    int count_degree_gt_2 = 0;

    for (int i = 0; i < p; i++) {
        if (degrees[i] > 3) count_degree_gt_3++;
        if (degrees[i] > 2) count_degree_gt_2++;
    }

    delete[] degrees;

    // Проверяем дополнительные условия планарности
    if (count_degree_gt_3 > 4) {
        std::cout << "!!3!!" << std::endl;
        return false;
    }

    if (count_degree_gt_2 > 5) {
        std::cout << "!!4!!" << std::endl;
        return false;
    }

    return true; // Граф планарен, если все проверки прошли
}

std::string example(short int x) {
    short int p = 0, q = 0; // p - вершины, q - рёбра
    std::ifstream file;
    switch (x)
    {
    case 1: {
        p = 4;
        q = 5;
        file.open("example1.txt", std::ios::in);
        break;
    }
    case 2: {
        p = 13;
        q = 10;
        file.open("example2.txt", std::ios::in);
        break;
    }
    case 3: {
        p = 5;
        q = 10;
        file.open("example3.txt", std::ios::in);
        break;
    }
    case 4: {
        p = 6;
        q = 9;
        file.open("example4.txt", std::ios::in);
        break;
    }
    default:
        wrong_message(3);
        exit(0);
    }
    if (!file.is_open()) {
        wrong_message(2);
        exit(0);
    }
    short int** matrix = new short int* [p];
    for (int i = 0; i < p; i++) {
        matrix[i] = new short int[p];
    }
    std::string temp;
    short int row = 0;
    while (getline(file, temp)) {
        for (int i = 0; i < temp.length(); i++) {
            matrix[row][i] = temp[i] - '0'; // Преобразуем символы в цифры
        }
        row++;
    }
    system("cls");
    if (is_planar(matrix, p, q)) {
        return "The graph is planar";
    }
    else {
        return "The graph is not planar";
    }
}

std::string manual_entry_of_graph() {
    short int p, q;
    std::cout << "Enter the number of graph vertices: "; // Количество вершин
    std::cin >> p;
    std::cout << "Enter the number of graph edges: "; // Количество рёбер
    std::cin >> q;
    short int** matrix = new short int* [p];
    for (int i = 0; i < p; i++) {
        matrix[i] = new short int[q];
    }
    for (int i = 0; i < p; i++) {
        for (int j = 0; j < q; j++) {
            system("cls");
            std::cout << "Is vertex " << i + 1 << " intersected by edge " << j + 1 << " ?" << std::endl << "Correct?(0/1): ";
            std::cin >> matrix[i][j];
        }
    }
    system("cls");
    if (is_planar(matrix, p, q)) {
        return "The graph is planar";
    }
    else {
        return "The graph is not planar";
    }
}

int main() {
    short int chouse_method;
    while (true) {
        std::cout << "1. Example 1\v2. Example 2\v3. Example 3" << std::endl
            << "4. Example 4\v\v5. Manually through the incidence matrix" << std::endl
            << std::endl << "Select the method for specifying graphs: ";
        std::cin >> chouse_method;
        if (!cheking_choose(chouse_method)) wrong_message(1);
        else break;
    }
    switch (chouse_method) {
    case 1: {
        system("cls");
        std::cout << example(1);
        break;
    }
    case 2: {
        system("cls");
        std::cout << example(2);
        break;
    }
    case 3: {
        system("cls");
        std::cout << example(3);
        break;
    }
    case 4: {
        system("cls");
        std::cout << example(4);
        break;
    }
    case 5: {
        system("cls");
        std::cout << manual_entry_of_graph();
        break;
    }
    default: wrong_message(1); break;
    }
    return 0;
}
~~~


### Примеры Работы программы

![image](https://github.com/iis-32170x/RPIIS/assets/144806982/dc56c765-fb82-411d-928a-48608205ea16)

![image](https://github.com/iis-32170x/RPIIS/assets/144806982/2bb44e2d-c898-4c52-b03d-fdf97454e8b5)

![image](https://github.com/iis-32170x/RPIIS/assets/144806982/aa4dd20c-a59d-4ed5-b3c9-29d459ccd66e)

![image](https://github.com/iis-32170x/RPIIS/assets/144806982/febae437-eff9-4983-8f37-82aaa1eeb5c2)




### Вывод

В результате выполнения данной работы были получены следующие практические навыки:
- изучены основы теории графов
- изучены способы представления графов
- изучены базовые алгоритмы для работы с графами
