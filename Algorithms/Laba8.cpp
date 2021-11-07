#include "Laba8.h"
#include <iostream>

Product::Product() : Product::Product("<empty>", 0.0f)
{
}

Product::Product(const char* name, float price)
{
	SetName(name);
	SetPrice(price);
}

void Product::SetName(const char* name)
{
	if (name == nullptr)
		return;

	_name = name;
}

void Product::SetPrice(float price)
{
	if (price < 0)
		return;

	_price = price;
}

const char* Product::GetName() const
{
	return _name;
}

float Product::GetPrice() const
{
	return _price;
}


Warehouse::Warehouse() : Warehouse::Warehouse("<empty>")
{
}

Warehouse::Warehouse(const char* name, size_t maxProductAmount)
{
	SetWarehouseName(name);
	SetMaxProductAmount(maxProductAmount);
}

void Warehouse::SetWarehouseName(const char* name)
{
	if (name == nullptr)
		return;

	_name = name;
}

void Warehouse::SetMaxProductAmount(size_t maxProductAmount)
{
	_maxProductAmount = maxProductAmount;
}

const char* Warehouse::GetWarehouseName() const
{
	return _name;
}

size_t Warehouse::GetMaxProductAmount() const
{
	return _maxProductAmount;
}

size_t Warehouse::GetCurrentProductAmount() const
{
	return _products.Length();
}

void Warehouse::AddProduct(Product* product)
{
	_products.Push(product);
	std::cout << "\nAdded product: " << product->GetName() << " with price " << product->GetPrice();
}

Product* Warehouse::GetLastProduct()
{
	auto product = _products.Pop();

	std::cout << "\nRemoved product: " << product->GetName() << " with price " << product->GetPrice();
	return product;
}

void Warehouse::Clear()
{
	_products.Clear();
}
