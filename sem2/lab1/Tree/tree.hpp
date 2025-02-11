#ifndef TREE_HPP
#define TREE_HPP 1.1

#include <cstdlib> // Для size_t

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
		 */
		void insertChild(const T &val)
		{
			for (size_t i = 0; i < ARITY; i++)
			{
				if (this->children[i] == nullptr)
				{
					this->children[i] = new m_Node(val, this);
					break;
				}
			}
		}
		
		/**
		 * @brief Удаление всех потомков (сынов, внуков и т. д.).
		 *
		 */
		void removeChildren()
		{
			for (size_t i = 0; i < ARITY; i++)
			{
				if (this->children[i] != nullptr)
				{
					this->children[i]->removeChildren();
					
					delete this->children[i];
					this->children[i] = nullptr;
				}
			}
			
			this->value.~T();
		}
	} *m_root = nullptr;
	
	/**
	 * @brief Добавление вершины в определённое место дерева (рекурс.).
	 *
	 * @param currentStep - текущий шаг в дереве (для нахождения нужной вершины).
	 * @param val - значение добавляемой вершины.
	 * @param currentBrotherIndex - индекс текущего элемента в массиве сыновей родителя (братьев).
	 * @param currentNode - текущая вершина.
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
			this->m_insertNode(currentStep + 1, val,
			                   0, currentNode->children[0]);
			break;
		case 'r': // вправо (к брату, схема доступа: текущ.->родитель->след. сын)
			this->m_insertNode(currentStep + 1, val,
			                   currentBrotherIndex + 1,
			                   currentNode->parent->children[currentBrotherIndex + 1]);
			break;
		default:
			return; // указана некорректная строка в качестве пути
		}
	}
	
	/**
	 * @brief Удаление определённой вершины дерева (рекурс.).
	 *
	 * @param currentStep - текущий шаг в дереве (для нахождения нужной вершины).
	 * @param currentBrotherIndex - индекс текущего элемента в массиве сыновей родителя (братьев).
	 * @param currentNode - текущая вершина.
	 */
	void m_removeNode(const char *currentStep,
	                  size_t currentBrotherIndex, m_Node *&currentNode)
	{
		switch (*currentStep)
		{
		case '\0': // место найдено
			currentNode->removeChildren();
			
			delete currentNode;
			currentNode = nullptr;
			break;
		case 'd': // вниз
			this->m_removeNode(currentStep + 1,
			                   0, currentNode->children[0]);
			break;
		case 'r': // вправо
			this->m_removeNode(currentStep + 1,
			                   currentBrotherIndex + 1,
			                   currentNode->parent->children[currentBrotherIndex + 1]);
			break;
		default:
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
	 * @brief Деструктор для Tree
	 */
	~Tree()
	{
		this->removeNode("");
	}
};

#endif