#ifndef TREE_HPP
#define TREE_HPP 1.21

#include <cstdlib> // size_t
#include <iostream> // std::ostream, std::endl
#include <stdexcept> // std::invalid_argument, std::out_of_range

/**
 * @class Tree
 *
 * @brief Класс, представляющий собой N-арное дерево.
 *
 * @tparam ARITY - арность дерева (макс. кол-во непосредственных потомков (сыновей) для одной вершины).
 * @tparam T - тип значений, хранящихся в дереве.
 */
template<size_t ARITY, typename T>
class Tree
{
private:
	/**
	 * @struct m_Node
	 *
	 * @brief Вершина (узел) дерева.
	 */
	struct m_Node
	{
		T value; // значение вершины
		m_Node *parent; // непосредственный предок (родитель)
		m_Node *children[ARITY]; // массив непосредственных потомков (сыновей)
		
		/**
		 * @brief Конструктор для объектов m_Node.
		 *
		 * @param val - значение вершины.
		 * @param par - родитель.
		 */
		explicit m_Node(const T &val = T(), m_Node *par = nullptr)
			: value(val), parent(par)
		{
			for (size_t i = 0; i < ARITY; i++)
			{
				this->children[i] = nullptr;
			}
		}
		
		/**
		 * @brief Добавление сына для вершины.
		 *
		 * @param val - значение вершины-сына.
		 *
		 * @throws std::out_of_range если к вершине невозможно добавить ребёнка по причине того, что количество
		 * 	детей у данной вершины равно N (где N - арность дерева).
		 */
		void insertChild(const T &val)
		{
			for (size_t i = 0; i < ARITY; i++)
			{
				if (this->children[i] == nullptr)
				{
					this->children[i] = new m_Node(val, this);
					return;
				}
			}
			throw std::out_of_range("Can\'t insert one more child. The amount of children is already " +
			        std::to_string(ARITY) + "!");
		}
		
		/**
		 * @brief Удаление всех потомков (сыновей, внуков и т. д.).
		 */
		void removeDescendants()
		{
			for (size_t i = 0; i < ARITY; i++)
			{
				if (this->children[i] != nullptr)
				{
					this->children[i]->removeDescendants();
					
					delete this->children[i];
					this->children[i] = nullptr;
				}
			}
			
			this->value.~T();
		}
		
		/**
		 * @brief Вывод вершины на экран.
		 *
		 * @param out - поток вывода.
		 * @param current_level - текущий уровень.
		 */
		void print(std::ostream &out, size_t current_level = 0)
		{
			for (size_t i = 0; i < current_level; i++)
			{
				out << '\t';
			}
			
			out << this->value << std::endl;
			
			for (size_t i = 0; i < ARITY; i++)
			{
				if (this->children[i] != nullptr)
				{
					this->children[i]->print(out, current_level + 1);
				}
			}
		}
	} *m_root = nullptr;
	
	/**
	 * @brief Добавление вершины в определённое место дерева (рекурс.).
	 *
	 * @param currentStep - текущий шаг в дереве (для нахождения нужной вершины).
	 * @param val - значение добавляемой вершины.
	 * @param currentBrotherIndex - индекс текущего элемента в массиве сыновей родителя (братьев).
	 * @param currentNode - текущая вершина.
	 *
	 * @throws std::domain_error, если вершины, к которой нужно привязать новую вершину, не существует.
	 * @throws std::invalid_argument, если в качестве пути указана некорректная строка.
	 */
	void m_insertNode(const char *currentStep, const T &val,
	        size_t currentBrotherIndex, m_Node *currentNode)
	{
		switch (*currentStep)
		{
			case '\0': // место найдено
				currentNode->insertChild(val);
				break;
			case 'd': // вниз (к сыну)
				if (currentNode->children[0] != nullptr)
				{
					this->m_insertNode(currentStep + 1, val,
					        0, currentNode->children[0]);
					break;
				}
				throw std::domain_error("There is no such node.");
				break;
			case 'r': // вправо (к брату, схема доступа: текущ.->родитель->след. сын)
				if (currentNode->parent != nullptr)
				{
					if (currentNode->parent->children[currentBrotherIndex + 1] != nullptr)
					{
						this->m_insertNode(currentStep + 1, val,
							currentBrotherIndex + 1,
						        currentNode->parent->children[currentBrotherIndex + 1]);
						break;
					}
				}
				throw std::domain_error("There is no such node.");
				break;
			default:
				throw std::invalid_argument("Invalid path.");
				return; // указана некорректная строка в качестве пути
		}
	}
	
	/**
	 * @brief Удаление определённой вершины дерева (рекурс.).
	 *
	 * @param currentStep - текущий шаг в дереве (для нахождения нужной вершины).
	 * @param currentBrotherIndex - индекс текущего элемента в массиве сыновей родителя (братьев).
	 * @param currentNode - текущая вершина.
	 *
	 * @throws std::domain_error, если вершины, к которой нужно привязать новую вершину, не существует.
	 * @throws std::invalid_argument, если в качестве пути указана некорректная строка.
	 */
	void m_removeNode(const char *currentStep,
	        size_t currentBrotherIndex, m_Node *&currentNode)
	{
		switch (*currentStep)
		{
			case '\0': // место найдено
				currentNode->removeDescendants();
				
				delete currentNode;
				currentNode = nullptr;
				break;
			case 'd': // вниз
				if (currentNode->children[0] != nullptr)
				{
					this->m_removeNode(currentStep + 1,
					        0, currentNode->children[0]);
					break;
				}
				throw std::domain_error("There is no such node.");
				break;
			case 'r': // вправо
				if (currentNode->parent != nullptr)
				{
					if (currentNode->parent->children[currentBrotherIndex + 1] != nullptr)
					{
						this->m_removeNode(currentStep + 1,
						        currentBrotherIndex + 1,
					        	currentNode->parent->children[currentBrotherIndex + 1]);
						break;
					}
				}
				throw std::domain_error("There is no such node.");
				break;
			default:
				throw std::invalid_argument("Invalid path.");
				return;
		}
	}
public:
	/**
	 * @brief Конструктор для объектов Tree.
	 *
	 * @param rootVal - значение, находящееся в корне дерева.
	 */
	explicit Tree(const T &rootVal = T())
		: m_root(new m_Node(rootVal))
	{}
	
	/**
	 * @brief Добавление вершины в определённое место дерева.
	 *
	 * @param path - путь до вершины.
	 * @param val - значение вершины.
	 */
	void insertNode(const char *path, const T &val)
	{
		this->m_insertNode(path, val, 0, this->m_root);
	}
	
	/**
	 * @brief Удаление определённой вершины из дерева.
	 *
	 * @param path - путь до удаляемой вершины.
	 */
	void removeNode(const char *path)
	{
		this->m_removeNode(path, 0, this->m_root);
	}
	
	/**
	 * @brief Вывод дерева на экран.
	 * 
	 * @param out - поток вывода.
	 */
	void print(std::ostream &out) const
	{
		this->m_root->print(out);
	}
	
	/**
	 * @brief Деструктор для Tree
	 */
	~Tree()
	{
		this->removeNode("");
	}
};

#endif