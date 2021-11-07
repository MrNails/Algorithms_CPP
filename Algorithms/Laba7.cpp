#include "Laba7.h"
#include <iostream>

Bus::Bus() : Bus::Bus("0000000000000", "<empty>", "000000000000")
{ }

Bus::Bus(const char number[13]) : Bus::Bus(number, "<empty>", "000000000000")
{ }

Bus::Bus(const char number[13], const char driverSurnameAndInitials[100]) : Bus::Bus(number, driverSurnameAndInitials, "000000000000")
{ }

Bus::Bus(const char number[13], const char driverSurnameAndInitials[100], const char wayNumber[12])
{
	SetNumber(number);
	SetDriverSurnameAndInitials(driverSurnameAndInitials);
	SetWayNumber(wayNumber);
	SetBusState(Idle);
}

const char* Bus::GetNumber() const
{
	return _number;
}

const char* Bus::GetDriverSurnameAndInitials() const
{
	return _driverSurnameAndInitials;
}

const char* Bus::GetWayNumber() const
{
	return _wayNumber;
}

BusState Bus::GetState() const
{
	return _state;
}

bool Bus::SetNumber(const char number[13])
{
	if (number == nullptr)
		return false;

	bool hasError = true;

	for (size_t i = 0; i < 14; i++)
	{
		if (number[i] == '\0' && i < 14)
		{
			hasError = false;
			break;
		}
	}

	if (!hasError)
		_number = number;

	return !hasError;
}

bool Bus::SetDriverSurnameAndInitials(const char dsai[100])
{
	if (dsai == nullptr)
		return false;

	bool hasError = true;

	for (size_t i = 0; i < 101; i++) 
	{
		if (dsai[i] == '\0' && i < 101)
		{
			hasError = false;
			break;
		}
	}

	if (!hasError)
		_driverSurnameAndInitials = dsai;

	return !hasError;
}

bool Bus::SetWayNumber(const char wayNumber[12])
{
	if (wayNumber == nullptr)
		return false;

	bool hasError = true;

	for (size_t i = 0; i < 13; i++)
	{
		if (wayNumber[i] == '\0' && i < 13)
		{
			hasError = false;
			break;
		}
	}

	if (!hasError)
		_wayNumber = wayNumber;

	return !hasError;
}

bool Bus::SetBusState(BusState state)
{
	_state = state;

	return true;
}


const char* BusPark::GetStringState(BusState state) const
{
	switch (state)
	{
	case Idle:
		return "in park";
	case InWay:
		return "in way";
	default:
		return "unknown state";
	}
}

void BusPark::InternalPrintBusesFromState(BusState state)
{
	auto forEachHandler = [this, state](const Bus* arg)
	{
		if (arg->GetState() == state)
			std::cout << "Number: " << arg->GetNumber() << std::endl;
	};

	_buses.ForEach(forEachHandler);
}

BusPark::BusPark() : BusPark::BusPark("empty", DEFAULT_PARK_MAX_BUS_AMOUNT)
{}

BusPark::BusPark(const char parkName[255], int maxBusesAmount)
{
	SetParkName(parkName);
	SetMaxBusesAmount(maxBusesAmount);
}

const char* BusPark::GetParkName() const
{
	return _parkName;
}

int BusPark::GetMaxBusesAmount() const
{
	return _maxBusesAmount;
}

void BusPark::SetParkName(const char name[255])
{
	if (name == nullptr)
		return;

	bool hasError = true;

	for (size_t i = 0; i < 256; i++)
		if (name[i] != '\0' && i > 254)
			hasError = false;

	if (!hasError)
		_parkName = name;
}

void BusPark::SetMaxBusesAmount(int busAmoun)
{
	if (busAmoun >= 0)
		_maxBusesAmount = busAmoun;
}

void BusPark::AddBus(Bus* bus)
{
	if (_buses.Length() + 1 > _maxBusesAmount)
		return;

	_buses.Add(bus);
}

bool BusPark::RemoveBus(Bus* bus)
{
	return _buses.Remove(bus);
}

bool BusPark::RemoveBus(const char* number)
{
	bool result = false;
	const Bus* foundBus;

	auto forEachHandler = [result, number, &foundBus](const Bus* arg) mutable
	{
		if (std::strcmp(arg->GetNumber(), number) == 0)
		{
			result = true;
			foundBus = arg;
		}
	};

	_buses.ForEach(forEachHandler);

	_buses.Remove((Bus*)foundBus);

	return result;
}

bool BusPark::SendBusToWay(const char* number)
{
	bool result = false;

	auto forEachHandler = [result, number](Bus* arg) mutable
	{
		if (std::strcmp(arg->GetNumber(), number) == 0 )
		{
			if (arg->GetState() == Idle) 
			{
				arg->SetBusState(InWay);

				std::cout << "\nBus " << arg->GetNumber() << " send to way";
			}
			else
				std::cout << "\nBus " << arg->GetNumber() << " already in way.";
		}
	};

	_buses.ForEach(forEachHandler);

	return result;
}

bool BusPark::SendBusToPark(const char* number)
{
	bool result = false;

	auto forEachHandler = [result, number](Bus* arg) mutable
	{
		if (std::strcmp(arg->GetNumber(), number) == 0 )
		{
			if (arg->GetState() == InWay) 
			{
				arg->SetBusState(Idle);

				std::cout << "\nBus " << arg->GetNumber() << " return to park.";
			}
			else
				std::cout << "\nBus " << arg->GetNumber() << " already in park.";
		}	
	};

	_buses.ForEach(forEachHandler);

	return result;
}

void BusPark::PrintBusesInWay()
{
	std::cout << "\nBusses in way:\n";
	InternalPrintBusesFromState(InWay);
}

void BusPark::PrintIdleBuses()
{
	std::cout << "\nBusses in park:\n";
	InternalPrintBusesFromState(Idle);
}

void BusPark::PrintBusesInfo()
{
	std::cout << "\nBusses info:\n";
	auto forEachHandler = [this](const Bus* arg)
	{
		std::cout << "\n\tNumber: " << arg->GetNumber()
			<< ";\n\tDriver full name: " << arg->GetDriverSurnameAndInitials()
			<< ";\n\tWay number: " << arg->GetWayNumber()
			<< ";\n\tBus status: " << GetStringState(arg->GetState());
	};

	_buses.ForEach(forEachHandler);
}

