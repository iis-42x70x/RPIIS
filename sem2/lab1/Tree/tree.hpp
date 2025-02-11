#include <cstdlib>

template<size_t ARITY, typename T>
class Tree
{
private:
	struct m_Node
	{
		T value;
		m_Node *parent;
		m_Node *children[ARITY];
		
		explicit m_Node(const T &val = T(), m_Node *par = nullptr)
			: value(val), parent(par)
		{
			for (size_t i = 0; i < ARITY; i++)
			{
				this->children[i] = nullptr;
			}
		}
		
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
	
	void m_insertNode(const char *currentStep, const T &val,
					  size_t currentBrotherIndex, m_Node *currentNode)
	{
		if (*currentStep == 'd')
		{
			this->m_insertNode(currentStep + 1, val,
							   0, currentNode->children[0]);
		}
		if (*currentStep == 'r')
		{
			this->m_insertNode(currentStep + 1, val,
							   currentBrotherIndex + 1,
							   currentNode->parent->children[currentBrotherIndex + 1]);
		}
		
		if (*currentStep == '\0')
		{
			currentNode->insertChild(val);
		}
	}
	
	void m_removeNode(const char *currentStep,
					  size_t currentBrotherIndex, m_Node *&currentNode)
	{
		if (*currentStep == 'd')
		{
			this->m_removeNode(currentStep + 1,
			                   0, currentNode->children[0]);
		}
		if (*currentStep == 'r')
		{
			this->m_removeNode(currentStep + 1,
			                   currentBrotherIndex + 1,
			                   currentNode->parent->children[currentBrotherIndex + 1]);
		}
		
		if (*currentStep == '\0')
		{
			currentNode->removeChildren();
			
			delete currentNode;
			currentNode = nullptr;
		}
	}
public:
	explicit Tree(const T &rootVal = T())
		: m_root(new m_Node(rootVal))
	{}
	
	void insertNode(const char *path, const T &val)
	{
		this->m_insertNode(path, val, 0, this->m_root);
	}
	
	void removeNode(const char *path)
	{
		this->m_removeNode(path, 0, this->m_root);
	}
	
	~Tree()
	{
		this->removeNode("");
	}
};