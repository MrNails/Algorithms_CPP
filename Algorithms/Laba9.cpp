#include "Laba9.h"

int Book::_globalNumber = 0;

Book::Book() : Book::Book(++_globalNumber)
{}

Book::Book(int number)
{
	_number = number;
	_authorInitials = nullptr;
	_name = nullptr;

	_publishedYear = 0;
	_bookAmount = 1;
}

Book::~Book()
{

}

int Book::GetNumber() const
{
	return _number;
}

int Book::GetPublishedYear() const
{
	return _publishedYear;
}

int Book::GetBookAmount() const
{
	return _bookAmount;
}

const char* Book::GetAuthorInitials() const
{
	return _authorInitials;
}

const char* Book::GetName() const
{
	return _name;
}

void Book::SetPublishedYear(int pYear)
{
	_publishedYear = pYear;
}

void Book::SetBookAmount(int amount)
{
	if (amount < 0)
		_bookAmount = 0;
	else
		_bookAmount = amount;
}

void Book::SetAuthorInitials(const char* initials)
{
	if (initials != nullptr)
		_authorInitials = initials;
}

void Book::SetName(const char* name)
{
	if (name != nullptr)
		_name = name;
}

