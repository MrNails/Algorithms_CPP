#include "Laba10.h"

void AdjacencyMatrix::ResizeField(int oldSize, int newSize)
{
	if (oldSize > newSize)
	{
		AdjacencyElement*** newField = new AdjacencyElement * *[newSize];

		for (size_t i = 0, oldI = 0; i < newSize; i++, oldI++)
		{
			if (_field[i] == nullptr)
			{
				i--;
				continue;
			}

			newField[i] = new AdjacencyElement * [newSize];

			for (size_t j = 0, oldj = 0; j < newSize; j++, oldj++)
			{
				if (_field[oldI][oldj] == nullptr)
				{
					j--;
					continue;
				}

				newField[i][j] = _field[oldI][oldj];
				_field[oldI][oldj] = nullptr;
			}

			delete[] _field[i];
		}

		delete[] _field;

		_field = newField;
	}
	else if (oldSize < newSize)
	{
		AdjacencyElement*** newField = new AdjacencyElement * *[newSize];

		for (size_t i = 0; i < newSize; i++)
		{
			newField[i] = new AdjacencyElement * [newSize];

			if (i < oldSize) 
			{
				for (size_t j = 0; j < oldSize; j++)
				{
					newField[i][j] = _field[i][j];
					_field[i][j] = nullptr;
				}

				delete[] _field[i];
			}
		}

		delete[] _field;

		_field = newField;
	}
}

AdjacencyMatrix::AdjacencyMatrix()
{
	_field = nullptr;
	_elementAmount = 0;
}

AdjacencyMatrix::~AdjacencyMatrix()
{
	Clear();
}

bool AdjacencyMatrix::AddVertex(int vertex)
{
	if (_field == nullptr)
	{
		_field = new AdjacencyElement * *[1];
		_field[0] = new AdjacencyElement * [1];
		_field[0][0] = new AdjacencyElement(vertex, vertex);

		_elementAmount++;
		return true;
	}

	if (ContainsVertex(vertex))
		return false;

	ResizeField(_elementAmount, _elementAmount + 1);

	for (size_t i = 0, vI = 0; i < _elementAmount + 1; i++, vI++)
	{
		if (i < _elementAmount)
			_field[i][_elementAmount] = new AdjacencyElement(_field[i][vI]->GetXKey(), vertex);
		else
			for (size_t j = 0; j < _elementAmount + 1; j++)
				_field[i][j] = new AdjacencyElement(vertex, _field[i - 1][j]->GetYKey());
	}

	_elementAmount++;

	return true;
}

bool AdjacencyMatrix::RemoveVertex(int vertex)
{
	if (_elementAmount = 0)
		return false;

	bool isDeleted = false;

	for (size_t i = 0; i < _elementAmount; i++)
	{
		if (_field[i][0]->GetXKey() == vertex)
		{
			for (size_t j = 0; j < _elementAmount; j++)
				delete _field[i][j];

			delete[] _field[i];

			_field[i] = nullptr;

			continue;
		}

		for (size_t j = 0; j < _elementAmount; j++)
		{
			auto currElem = _field[i][j];

			if (currElem->GetXKey() == vertex || currElem->GetYKey() == vertex)
			{
				delete _field[i][j];
				
				_field[i][j] = nullptr;
				break;
			}
		}
	}

	_elementAmount--;

	if (_elementAmount == 0)
		Clear();

	return isDeleted;
}

void AdjacencyMatrix::SetVertexWeight(int vertex1, int vertex2, int weight)
{
	for (size_t i = 0; i < _elementAmount; i++)
	{
		for (size_t j = 0; j < _elementAmount; j++)
		{
			auto currElem = _field[i][j];

			if (currElem->GetXKey() == vertex1 && currElem->GetYKey() == vertex2) 
			{
				currElem->SetWeight(weight);
				return;
			}
		}
	}
}

int AdjacencyMatrix::GetVertexWeight(int vertex1, int vertex2) const
{
	for (size_t i = 0; i < _elementAmount; i++)
	{
		for (size_t j = 0; j < _elementAmount; j++)
		{
			auto currElem = _field[i][j];

			if (currElem->GetXKey() == vertex1 && currElem->GetYKey() == vertex2)
				return currElem->GetWeight();
		}
	}

	return 0;
}

int AdjacencyMatrix::GetElementAmount() const
{
	return _elementAmount;
}

void AdjacencyMatrix::Clear()
{
	for (size_t i = 0; i < _elementAmount; i++)
	{
		for (size_t j = 0; j < _elementAmount; j++)
			delete _field[i][j];

		delete[] _field[i];
	}

	delete[] _field;

	_field = nullptr;
}

AdjacencyElement*** AdjacencyMatrix::GetField() const
{
	return _field;
}

bool AdjacencyMatrix::ContainsVertex(int vertex)
{
	if (_elementAmount == 0)
		return false;

	for (size_t j = 0; j < _elementAmount; j++)
		if (_field[0][j]->GetXKey() == vertex)
			return true;

	return false;
}