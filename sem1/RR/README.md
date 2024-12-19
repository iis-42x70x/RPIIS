<h1 align= "center"> Рассчетная работа</h1>

## Цель работы

1) Изучить основные понятия в теории графов.
2) Научиться различать виды графов.
3) Уметь использовать основные алгоритмы при работе с графами.

## Условие задания
1) Выполнить свой вариант рассчетной работы
2) Перенести получившееся решение на язык программирования Java

## Вариант 
Для рассчетной работы мне был выдан вариант **1.6 Связный граф**. Для хранения графов нужно использовать списки смежности

## Теоретические сведения для выполнения расчетной работы
- **Граф** - совокупность двух множеств множества самих объектов, называемого множеством вершин, и множества их парных связей, называемого множеством рёбер.
- **Связный граф** - граф, в котором существует путь между любой парой вершин. Из каждой вершины по рёбрам можно добраться до любой другой вершины. В связном графе нет изолированных вершин или групп, которые не связаны с остальными частями графа
- **Спискок смежности** — один из способов представления графа в виде коллекции списков вершин. Каждой вершине графа соответствует список, состоящий из «соседей» этой вершины.

## Алгоритмы для выполнения расчетной работы

### Алгоритм обхода в глубину
Алгоритм обхода в глубину представляет собой способ исследования графа, начиная с какой-либо вершины и исследуя как можно глубже вдоль каждой ветви до тех пор, пока не будет достигнут конец или вершина, не имеющая непосещённых соседей. Затем процесс продолжается с последней посещённой вершины, и так далее, пока все вершины не будут посещены.

Код на Java:
```
public class GraphConnectivity {
    private int vertices;
    private List<List<Integer>> adjacencyList;
    
    public GraphConnectivity(int vertices) {
        this.vertices = vertices;
        adjacencyList = new ArrayList<>(vertices);
        for (int i = 0; i < vertices; i++) {
            adjacencyList.add(new ArrayList<>());
        }
    }

    public void addEdge(int firstVertex, int secondVertex) {
        adjacencyList.get(firstVertex).add(secondVertex);
        adjacencyList.get(secondVertex).add(firstVertex);
    }

    private void dfs(int currentVertex, boolean[] visited) {
        visited[currentVertex] = true;
        for (int neighbor : adjacencyList.get(currentVertex)) {
            if (!visited[neighbor]) {
                dfs(neighbor, visited);
            }
        }
    }

    public boolean isConnected() {
        boolean[] visited = new boolean[vertices];

        dfs(0, visited);

        for (boolean v : visited) {
            if (!v) return false;
        }
        return true;
    }

    @Override
    public String toString() {
        StringBuilder sb = new StringBuilder();
        sb.append("Adjacency List Representation:\n");
        for (int i = 0; i < adjacencyList.size(); i++) {
            sb.append(i).append(": ");
            for (int neighbor : adjacencyList.get(i)) {
                sb.append(neighbor).append(" ");
            }
            sb.append("\n");
        }
        return sb.toString();
    }

    public static void main(String[] args) {
        System.out.println("Тестирование первого графа:");
        GraphConnectivity graph1 = new GraphConnectivity(4);
        graph1.addEdge(0, 1);
        graph1.addEdge(1, 2);
        graph1.addEdge(1, 3);

        if (graph1.isConnected()) {
            System.out.println("Граф 1 является связным");
        } else {
            System.out.println("Граф 1 не является связным");
        }
        
        System.out.println("\nТестирование второго графа:");
        GraphConnectivity graph2 = new GraphConnectivity(4);
        graph2.addEdge(0, 1);
        graph2.addEdge(2, 3);

        if (graph2.isConnected()) {
            System.out.println("Граф 2 является связным");
        } else {
            System.out.println("Граф 2 не является связным");
        }
    }
}
```
## Пример работы 
