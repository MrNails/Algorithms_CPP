#pragma once

template<class T>
class Stack
{
private:
	struct Node
	{
		T value;
		Node* previous;
	};

	Node* _end;
	size_t _length;
public:
	Stack()
	{
		_end = nullptr;
		_length = 0;
	}
	~Stack()
	{
		Clear();
	}

	void Push(T elem)
	{
		_length++;

		if (_end == nullptr)
		{
			_end = new Node();
			_end->value = elem;
			_end->previous = nullptr;

			return;
		}

		Node* newNode = new Node();
		newNode->value = elem;
		newNode->previous = _end;

		_end = newNode;
	}

	T Pop() 
	{
		T value;

		if (_end->previous == nullptr)
		{
			value = _end->value;

			delete _end;

			_end = nullptr;
		}
		else
		{
			value = _end->value;
			auto previous = _end->previous;

			delete _end;

			_end = previous;
		}

		return value;
	}

	size_t Length() const
	{
		return _length;
	}

	void Clear()
	{
		Node* current = _end;

		while (current != nullptr)
		{
			Node* temp = current;

			current->value = nullptr;
			current = current->previous;

			delete temp;
		}

		_end = nullptr;
	}
};

class Product
{
private:
	const char* _name;
	float _price;

public:
	Product();
	Product(const char* name, float price);

	void SetName(const char* name);
	void SetPrice(float price);

	const char* GetName() const;
	float GetPrice() const;
};

class Warehouse
{
private:
	Stack<Product* > _products;
	const char* _name;
	size_t _maxProductAmount;
public:
	static const size_t WAREHOUSE_MAX_RPODUCT_AMOUNT = 100;

	Warehouse();
	Warehouse(const char* name, size_t maxProductAmount = WAREHOUSE_MAX_RPODUCT_AMOUNT);

	void SetWarehouseName(const char* name);
	void SetMaxProductAmount(size_t maxProductAmount);

	const char* GetWarehouseName() const;
	size_t GetMaxProductAmount() const;
	size_t GetCurrentProductAmount() const;

	void AddProduct(Product* product);
	Product* GetLastProduct();
	
	void Clear();
};