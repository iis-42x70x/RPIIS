


# Расчетная работа 

## Цель:

Ознакомиться с основами теории графов, способами представления графов, базовыми алгоритмами для работы с разными видами графов.

## Условие задания:

>*Вариант 3.1*

Реализовать на Python код, который может генерировать граф указанного обхвата.

Используется неориентированный граф.

Конечный граф предствляется ввиде матрицы смежности.

### Ключевые понятия:
`Граф` - математическая абстракция реальной системы любой природы, объекты которой обладают парными связями.

`Неориентированный граф` —  граф, рёбрам которого не присвоено направление.

`Список смежности(инцидентности)` - один из способов представления графа в виде коллекции списков вершин. Каждой вершине графа соответствует список, состоящий из «соседей» этой вершины.

`Обхват графа` - длина наименьшего цикла, содержащегося в данном графе.

`Цикл` — граф, состоящий из единственного цикла, или, другими словами, некоторого числа вершин, соединённых замкнутой цепью /// путь, в котором начальная и конечная вершины совпадают

`Смежность` — понятие, используемое в отношении только двух рёбер либо только двух вершин: Два ребра, инцидентные одной вершине, называются смежными; две вершины, инцидентные одному ребру, также называются смежными. 

## Реализация на Python

Код, выполняющий генерацию
``` python
import networkx as nx
import matplotlib.pyplot as plt
import numpy as np
import random


class Graph:
    def __init__(self, girth):
        self.girth = girth
        self.graph = nx.Graph()
        self.edges = []
        self.adjacency_matrix = np.zeros((self.girth, self.girth), dtype=int)

    def create_nodes(self):
        self.picks = [k for k in range(1,self.girth - 1)]

    def create_circular_edges(self):
        self.edges.append((1, self.girth))
        for k in range(1, self.girth):
            self.edges.append((k, k + 1))

    def add_branches(self):
        self.node1 = random.choice(self.picks)
        self.node2 = random.choice(self.picks)
        self.add_nodes = self.girth - abs(self.node1 - self.node2) - 1
        for k in range(1,self.add_nodes):
            self.graph.add_node(girth+k)
        self.graph.add_edge(self.girth+1,self.node1)
        self.graph.add_edge(self.girth+self.add_nodes,self.node2)
        self.graph.add_edges_from(self.edges)
        for k in range(self.girth + 1, self.girth + self.add_nodes):
            self.graph.add_edge(k, k + 1)

    def build_and_show_adjacency_matrix(self):
        print(f"Матрица смежности для клетки, обхвата {girth}:")
        for k in range(len(self.adjacency_matrix[0])):
            for j in range(len(self.adjacency_matrix[0])):
                if (k + 1,j + 1) in self.edges or (j + 1,k + 1) in self.edges:
                    self.adjacency_matrix[k][j]=1
                print(self.adjacency_matrix[k][j],end = " ")
            print()

    def visualize_graph(self):
        plt.figure(figsize=(8, 6))
        plt.title(f'Сгенерированный неориентированный граф с обхватом {self.girth}')
        nx.draw(self.graph, with_labels=True, node_size=700, node_color='lightblue', font_size=10, font_weight='bold')
        plt.show()

girth = int(input("Введите обхват графа: "))
if girth < 3:
    raise ValueError("Длина цикла должна быть не менее 3.")

graph = Graph(girth)
graph.create_nodes()
graph.create_circular_edges()
graph.add_branches()
graph.build_and_show_adjacency_matrix()
graph.visualize_graph()

```
## Разбор кода: 
- `import networkx` - библиотека для работы с графами
  
- `import matplotlib.pyplot` - библиотека, позволяющая рисовать графики

- `import numpy` - библиотека, необходимая работы с матрицами и массивами

- `import random` - библиотека для работы со случайными значениями

- `class Graph {` - объявление класса `Graph`
  - `def __init__(self, girth)` - добавление конструкора, в котором создаются поля для обхвата, ребер, матрицы смежности и самого графа
  - `def create_nodes(self)` — метод для создания списка вершин.
  - `def create_circular_edges(self):`- метод для добавления ребер, создавая замкнутый цикл
  - `def add_branches(self)` — метод, в котором добавляются ветки к уже созданному кольцу.
  - `def build_and_show_adjacency_matrix(self)` — метод для создания матрицы смежности на основе построенного графа
  - `def visualize_graph(self)` — метод для визуализации графа, используется библиотека matplotlib
- Итог:
Программа позволяет пользователю вводить обхват графа, затем строит граф, используя эту значение. Программа случайно генерирует последовательсть вершин и соединяющих их ребер. Программа выводит графическое представление и матрицу смежности созданного графа.

### Пример работы программы 
# Пример 1

- Запускаем прогрмму и вводим обхват графа.

- Получаем матрицу смежности:



 ![{B62CF8B9-F75D-4F5A-9B38-1BF3E18D3D15}](https://github.com/dekada314/RPIIS/blob/patch-1/РР/screens/matrix1.jpg)
- Получаем графическое представление:



 ![{B62CF8B9-F75D-4F5A-9B38-1BF3E18D3D15}](https://github.com/dekada314/RPIIS/blob/patch-1/РР/screens/ex1.jpg))

# Пример 2

- Запускаем прогрмму и вводим обхват графа.

- Получаем матрицу смежности:



 ![{B62CF8B9-F75D-4F5A-9B38-1BF3E18D3D15}](https://github.com/dekada314/RPIIS/blob/patch-1/РР/screens/matrix2.jpg)
- Получаем графическое представление:



 ![{B62CF8B9-F75D-4F5A-9B38-1BF3E18D3D15}](https://github.com/dekada314/RPIIS/blob/patch-1/РР/screens/ex2.jpg))
## Вывод
В результате я приобрела следующие навыки:
- изучил основы теории графов
- изучил базовые алгоритмы для работы с графами
- изучил способы представления графов
- изучил базовые алгоритмы работы с графами в Python

  
