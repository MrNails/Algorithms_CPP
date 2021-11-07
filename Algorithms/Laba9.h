#pragma once
#include <iostream>
#include <iomanip>

template<class T>
class BinaryTree
{
private:
	struct Node
	{
		int key;
		T element;
		Node* left;
		Node* right;

		Node()
		{
			key = -1;
			element = nullptr;
			left = nullptr;
			right = nullptr;
		}
	};

	int _count;
	Node* _root;

	void ClearInternal(Node* root)
	{
		if (root->left != nullptr)
		{
			ClearInternal(root->left);
			root->left = nullptr;
		}
		if (root->right != nullptr)
		{
			ClearInternal(root->right);
			root->right = nullptr;
		}

		root->element = nullptr;
		delete root;
	}
	void ForeEachInternal(Node* root, void (*handler)(T, int _depthLevel), int depthLevel = 0) const
	{
		if (root->left != nullptr)
			ForeEachInternal(root->left, handler, depthLevel + 1);

		handler(root->element, depthLevel);

		if (root->right != nullptr)
			ForeEachInternal(root->right, handler, depthLevel + 1);
	}
	void PrintKeysInternal(Node* root, int depthLevel = 0)
	{
		if (root->left != nullptr)
			PrintKeysInternal(root->left, depthLevel + 1);

		std::cout << std::setw(depthLevel * 5) << root->key << std::endl;

		if (root->right != nullptr)
			PrintKeysInternal(root->right, depthLevel + 1);
	}
	bool DeleteInternal(Node** nodePtr, int key)
	{
		Node* node = *nodePtr;
		bool isDeleted = false;

		if (node->key == key)
		{
			_count--;
			isDeleted = true;

			if (node->right != nullptr)
			{
				Node* previous = nullptr;

				do
				{
					node->key = node->right->key;
					node->element = node->right->element;
					previous = node;

					node = node->right;
				} while (node->right != nullptr);

				if (node->left == nullptr)
					previous->right = nullptr;
				else
					previous->right = node->left;

				node->element = nullptr;
				delete node;
			}
			else if (node->left != nullptr)
			{
				Node* left = node->left;

				node->left = nullptr;
				node->element = nullptr;

				delete node;

				(*nodePtr) = left;
			}
			else
			{
				node->element = nullptr;

				delete node;

				(*nodePtr) = nullptr;
			}
		}
		else
		{
			if (node->left != nullptr)
				DeleteInternal(&node->left, key);
			if (node->right != nullptr)
				DeleteInternal(&node->right, key);
		}

		return isDeleted;
	}

	Node* GetLastNode(Node* root, int key)
	{
		if (root->key == key || root->left == nullptr && root->right == nullptr)
			return root;
		if (root->key > key && root->left != nullptr)
			return GetLastNode(root->left, key);
		if (root->key < key && root->right != nullptr)
			return GetLastNode(root->right, key);
	}
public:
	BinaryTree()
	{
		_count = 0;
		_root = nullptr;
	}

	~BinaryTree()
	{
		ClearInternal(_root);
		_count = 0;
	}

	bool InsertElement(int key, T element)
	{
		if (_root == nullptr)
		{
			_root = new Node();
			_root->key = key;
			_root->element = element;
			_count++;

			return true;
		}

		Node* lastNode = GetLastNode(_root, key);

		if (lastNode->key == key)
			return false;

		Node* newNode = new Node();
		newNode->key = key;
		newNode->element = element;

		if (lastNode->key < key)
			lastNode->right = newNode;
		else
			lastNode->left = newNode;

		_count++;

		return true;
	}

	bool DeleteElement(int key)
	{
		return DeleteInternal(&_root, key);
	}

	T GetElement(int key)
	{
		if (_root == nullptr)
			throw std::exception("Tree have no elements.");

		Node* lastNode = GetLastNode(_root, key);

		if (lastNode->key != key)
			throw std::exception("Element not found.");

		return lastNode->element;
	}

	int GetCount() const
	{
		return _count;
	}

	void Clear()
	{
		ClearInternal(_root);
		_count = 0;
	}

	void ForeEach(void (*handler)(T, int depthLevel)) const
	{
		ForeEachInternal(_root, handler);
	}

	void PrintKeys()
	{
		PrintKeysInternal(_root);
	}
};

class Book
{
private:
	int _number, _publishedYear, _bookAmount;
	const char* _authorInitials,* _name;

	static int _globalNumber;
public:
	Book();
	Book(int number);
	~Book();

	int GetNumber() const;
	int GetPublishedYear() const;
	int GetBookAmount() const;
	const char* GetAuthorInitials() const;
	const char* GetName() const;

	void SetPublishedYear(int pYear);
	void SetBookAmount(int amount);
	void SetAuthorInitials(const char* initials);
	void SetName(const char* name);
};