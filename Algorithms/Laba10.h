#pragma once

class AdjacencyElement
{
private:
	int _xKey, _yKey, _weight;

public:
	AdjacencyElement(int xKey, int yKey) : AdjacencyElement(xKey, yKey, 0)
	{}

	AdjacencyElement(int xKey, int yKey, int weight)
	{
		_xKey = xKey;
		_yKey = yKey;
		SetWeight(weight);
	}

	void SetWeight(int weight)
	{
		_weight = weight;
	}

	int GetXKey() const
	{
		return _xKey;
	}

	int GetYKey() const
	{
		return _yKey;
	}

	int GetWeight() const
	{
		return _weight;
	}
};

class AdjacencyMatrix
{
private:
	AdjacencyElement*** _field;
	int _elementAmount;

	void ResizeField(int oldSize, int newSize);

public:
	AdjacencyMatrix();
	~AdjacencyMatrix();

	bool AddVertex(int vertex);
	bool RemoveVertex(int vertex);

	void SetVertexWeight(int vertex1, int vertex2, int weight);

	int GetVertexWeight(int vertex1, int vertex2) const;
	int GetElementAmount() const;

	bool ContainsVertex(int vertex);

	AdjacencyElement*** GetField() const;

	void Clear();
};

