#include <iostream>
#include <cstdlib>
#include <clocale>
#include <vector>
#include <algorithm>
#include <cstdio>

using std::size_t;

std::vector< std::vector<bool> > converseGraph(
		const std::vector< std::vector<bool> >& g
		)
{
	std::vector< std::vector<bool> > gC(g.size(),
										std::vector<bool>(g.size()));
	
	for (size_t i = 0; i < g.size(); i++)
	{
		for (size_t j = 0; j < g[i].size(); j++)
		{
			gC[j][i] = g[i][j];
		}
	}
	
	return gC;
}

void topologicalSortDFS(const std::vector< std::vector<bool> >& g, size_t vertex,
                        std::vector<bool>& explored, std::vector<size_t>& order)
{
	explored[vertex] = true;
	
	for (size_t i = 0; i < g.size(); i++)
	{
		if (g[vertex][i] && !explored[i])
		{
			topologicalSortDFS(g, i, explored, order);
		}
	}
	
	order.push_back(vertex);
}

std::vector<size_t> topologicalSort(const std::vector< std::vector<bool> >& g)
{
	std::vector<bool> explored(g.size(), false);
	std::vector<size_t> order;
	
	for (size_t i = 0; i < g.size(); i++)
	{
		if (!explored[i])
		{
			topologicalSortDFS(g, i, explored, order);
		}
	}
	
	std::reverse(order.begin(), order.end());
	
	return order;
}

void getComponent(const std::vector< std::vector<bool> >& gC, size_t vertex,
                  std::vector<bool>& explored, std::vector<size_t>& component)
{
	explored[vertex] = true;
	
	component.push_back(vertex);
	
	for (size_t i = 0; i < gC.size(); i++)
	{
		if (gC[vertex][i] && !explored[i])
		{
			getComponent(gC, i, explored, component);
		}
	}
}

std::vector< std::vector<size_t> > stronglyConnectedComponents(
		const std::vector< std::vector<bool> >& g
		)
{
	std::vector<size_t> order = topologicalSort(g);
	std::vector< std::vector<bool> > gC = converseGraph(g);
	
	std::vector<bool> explored(gC.size(), false);
	std::vector< std::vector<size_t> > components;
	
	for (size_t i = 0; i < gC.size(); i++)
	{
		size_t currentVertex = order[i];
		if (!explored[currentVertex])
		{
			std::vector<size_t> currentComponent;
			getComponent(gC, currentVertex, explored,currentComponent);
			components.push_back(currentComponent);
		}
	}
	
	return components;
}

void userExecution()
{
	std::cout << "Введите количество вершин графа: ";
	size_t vertexCount;
	std::cin >> vertexCount;
	
	std::cout << "Введите матрицу смежности графа:\n";
	std::vector< std::vector<bool> > g(vertexCount,
	                                   std::vector<bool>(vertexCount));
	for (size_t i = 0; i < vertexCount; i++)
	{
		for (size_t j = 0; j < vertexCount; j++)
		{
			int gij;
			std::cin >> gij;
			g[i][j] = static_cast<bool>(gij);
		}
	}
	
	std::vector< std::vector<size_t> > gSCC = stronglyConnectedComponents(g);
	for (std::vector<size_t>& currentComponent : gSCC)
	{
		std::sort(currentComponent.begin(), currentComponent.end());
	}
	
	std::cout << "\nПРИМЕЧАНИЕ: Вершины нумеруются с единицы.\n\n";
	for (size_t i = 0; i < gSCC.size(); i++)
	{
		std::cout << "Все вершины данного графа, входящие " <<
		             ((i + 1 == 2) ? "во " : "в ") << i + 1 << "-ю"
		             " вершину графа конденсации: ";
		for (size_t j = 0; j < gSCC[i].size(); j++)
		{
			std::cout << gSCC[i][j] + 1;
			if (j + 1 < gSCC[i].size())
			{
				std::cout << ", ";
			}
		}
		
		std::cout << '\n';
	}
	std::cout << '\n';
	
	std::cout << "Граф конденсации будет выглядеть следующим образом:\n";
	for (size_t i = 1; i <= gSCC.size(); i++)
	{
		std::cout << i;
		if (i < gSCC.size())
		{
			std::cout << " -> ";
		}
	}
	std::cout << "\n\n";
	
	std::cout << "Матрица смежности графа конденсации выглядит так:\n";
	for (size_t i = 0; i < gSCC.size(); i++)
	{
		for (size_t j = 0; j < gSCC.size(); j++)
		{
			std::cout << ((i + 1 == j) ? 1 : 0) << ' ';
		}
		std::cout << '\n';
	}
}

void runTestCase(int testCaseNumber)
{
	std::cout << "Тестовые пример №" << testCaseNumber << ":\n";
	
	size_t vertexCount;
	std::cin >> vertexCount;
	
	std::vector< std::vector<bool> > g(vertexCount,
	                                   std::vector<bool>(vertexCount));
	for (size_t i = 0; i < vertexCount; i++)
	{
		for (size_t j = 0; j < vertexCount; j++)
		{
			int gij;
			std::cin >> gij;
			g[i][j] = static_cast<bool>(gij);
		}
	}
	
	std::cout << "Количество вершин в графе: " << vertexCount << '\n';
	std::cout << "Матрица смежности графа:\n";
	for (size_t i = 0; i < vertexCount; i++)
	{
		for (size_t j = 0; j < vertexCount; j++)
		{
			std::cout << ((g[i][j]) ? 1 : 0) << ' ';
		}
		std::cout << '\n';
	}
	
	std::vector< std::vector<size_t> > gSCC = stronglyConnectedComponents(g);
	for (std::vector<size_t>& currentComponent : gSCC)
	{
		std::sort(currentComponent.begin(), currentComponent.end());
	}
	
	std::cout << "\nПРИМЕЧАНИЕ: Вершины нумеруются с единицы.\n\n";
	for (size_t i = 0; i < gSCC.size(); i++)
	{
		std::cout << "Все вершины данного графа, входящие " <<
		             ((i + 1 == 2) ? "во " : "в ") << i + 1 << "-ю"
		             " вершину графа конденсации: ";
		for (size_t j = 0; j < gSCC[i].size(); j++)
		{
			std::cout << gSCC[i][j] + 1;
			if (j + 1 < gSCC[i].size())
			{
				std::cout << ", ";
			}
		}
		
		std::cout << '\n';
	}
	std::cout << '\n';
	
	std::cout << "Граф конденсации будет выглядеть следующим образом:\n";
	for (size_t i = 1; i <= gSCC.size(); i++)
	{
		std::cout << i;
		if (i < gSCC.size())
		{
			std::cout << " -> ";
		}
	}
	std::cout << "\n\n";
	
	std::cout << "Матрица смежности графа конденсации выглядит так:\n";
	for (size_t i = 0; i < gSCC.size(); i++)
	{
		for (size_t j = 0; j < gSCC.size(); j++)
		{
			std::cout << ((i + 1 == j) ? 1 : 0) << ' ';
		}
		std::cout << '\n';
	}
	std::cout << "\n";
}

int main()
{
	std::setlocale(LC_ALL, "rus");
	
	std::cout << "Вы хотите ввести значения для выполнения программы "
	             "самостоятельно или проверить программу на пяти заранее "
	             "определённых тестовых примерах?\n"
	             "Для ввода своих значений введите в консоль 1.\n"
	             "Для проверки на тестовых примерах введите 2.\n"
	             "Для выхода из программы введите любое другое число.\n";
	int userAction;
	std::cin >> userAction;
	
	switch (userAction)
	{
		case 1:
			userExecution();
			break;
		case 2:
			freopen("input.txt", "r", stdin);
			for (int i = 1; i <= 5; i++)
			{
				runTestCase(i);
			}
			break;
		default:
			std::cout << "Выход из программы...\n";
	}
	
	return EXIT_SUCCESS;
}
