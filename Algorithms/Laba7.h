#pragma once
#include <vector>

template<class T>
class LinkedList
{
private:
	struct Node
	{
		T value;
		Node* next;
	};

	Node* _start;
	Node* _end;
	int _length;
public:
	LinkedList()
	{
		_start = nullptr;
		_end = nullptr;
		_length = 0;
	}

	~LinkedList()
	{
		Clear();
	}

	void Add(T elem)
	{
		_length++;

		if (_start == nullptr)
		{
			_start = new Node();
			_start->value = elem;
			_start->next = nullptr;

			_end = _start;

			return;
		}

		Node* newNode = new Node();
		newNode->value = elem;
		newNode->next = nullptr;

		_end->next = newNode;
		_end = newNode;
	}

	bool Remove(T elem)
	{
		if (_start == _end)
		{
			if (_start->value != elem)
				return false;

			_start->value = nullptr;

			delete _start;
			delete _end;

			_start = nullptr;
			_end = nullptr;

			return true;
		}
		else if (_start->value == elem)
		{
			auto temp = _start->next;

			delete _start;

			_start = temp;
		}

		Node* current = _start;
		Node* previous = _start;

		while (current != nullptr)
		{
			if (current->value == elem)
			{
				if (current->next != nullptr)
				{
					previous->next = current->next;
					current->value = nullptr;
				}
				else
				{
					previous->next = nullptr;
					_end = previous;
				}

				delete current;

				_length--;

				return true;
			}

			previous = current;
			current = current->next;
		}

		return false;
	}

	int Length() const
	{
		return _length;
	}

	void Clear()
	{
		Node* current = _start;

		while (current != nullptr)
		{
			Node* temp = current;

			current->value = nullptr;
			current = current->next;

			delete temp;
		}

		_start = nullptr;
		_end = nullptr;
	}

	template<typename Func>
	void ForEach(Func forEachHanlder)
	{
		Node* current = _start;

		while (current != nullptr)
		{
			forEachHanlder(current->value);

			current = current->next;
		}
	}
};

enum BusState
{
	Idle,
	InWay
};

class Bus
{
private:
	const char* _number,
		* _driverSurnameAndInitials,
		* _wayNumber;
	BusState _state;
public:
	Bus();
	Bus(const char number[13]);
	Bus(const char number[13], const char driverSurnameAndInitials[100]);
	Bus(const char number[13], const char driverSurnameAndInitials[100], const char wayNumber[12]);

	const char* GetNumber() const;
	const char* GetDriverSurnameAndInitials() const;
	const char* GetWayNumber() const;
	BusState GetState() const;

	bool SetNumber(const char number[13]);
	bool SetDriverSurnameAndInitials(const char dsai[100]);
	bool SetWayNumber(const char wayNumber[12]);
	bool SetBusState(BusState state);
};

class BusPark
{
private:
	LinkedList<Bus*> _buses;
	const char* _parkName;
	int _maxBusesAmount;

	const char* GetStringState(BusState state) const;

	void InternalPrintBusesFromState(BusState state);
public:
	const int DEFAULT_PARK_MAX_BUS_AMOUNT = 40;

	BusPark();
	BusPark(const char parkName[255], int maxBusesAmount);

	const char* GetParkName() const;
	int GetMaxBusesAmount() const;

	void SetParkName(const char name[255]);
	void SetMaxBusesAmount(int busAmoun);

	void AddBus(Bus* bus);
	bool RemoveBus(Bus* bus);
	bool RemoveBus(const char* number);

	bool SendBusToWay(const char* number);
	bool SendBusToPark(const char* number);

	void PrintBusesInWay();
	void PrintIdleBuses();
	void PrintBusesInfo();
};
