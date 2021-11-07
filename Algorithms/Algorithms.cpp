#include <iostream>
#include <math.h>
#include <iomanip>
#include <ctime>
#include <algorithm>
#include <list>
#include "Laba7.h"
#include "Laba8.h"
#include "Laba9.h"
#include "Laba10.h"

const float PI = 3.14159265f;

#pragma region Common

// Функция для проверки и обработки ввода ввода
template<typename T>
void InputWrapper(const std::istream& stream, const char* userText,
	const char* userErrorText, T& variable, bool (*checkFunc)(const T&) = nullptr);

// Функция для проверки и очистки ввода 
void HandleInput(const std::istream& stream, bool& hasError);

#pragma endregion

#pragma region Laba1

float RadiansToDegrees(float radians);
float DegreesToRadians(float radians);
float GetAngleFromSides(float sideA, float sideB, float sideC);

#pragma endregion

#pragma region Laba2

int Factorial(int num);
float RecursiveSin(float x, int precision);
float Sin(float x);

#pragma endregion

#pragma region Laba3

void PrintArray(int* arr, size_t size);

int Max(int* arr, size_t size);

#pragma endregion

#pragma region Laba4

bool LinearSearch(int* arr, size_t size, int findElem);

bool BinarySearch(int* arr, size_t size, int findElem);

#pragma endregion

#pragma region Laba5

enum FillType;

void BubbleSort(int* arr, size_t size);
void ShellSort(int* arr, size_t size);
void SelectionSort(int* arr, size_t size);

void FillArr(int* arr, size_t size, FillType fillType, int randRestriction = 0);

#pragma endregion

void Laba1();
void Laba2();
void Laba3();
void Laba4();
void Laba5();
void Laba7();
void Laba8();
void Laba9();
void Laba10();

int main()
{
	srand(time(0));

	int type = -1;
	bool exit = false;

	while (!exit)
	{
		InputWrapper<int>(std::cin, "Enter number of laba or '-1' for exit: ", "", type);

		switch (type)
		{
		case 1:
			system("cls");
			Laba1();
			std::cout << std::endl << std::endl;
			break;
		case 2:
			system("cls");
			Laba2();
			std::cout << std::endl << std::endl;
			break;
		case 3:
			system("cls");
			Laba3();
			std::cout << std::endl << std::endl;
			break;
		case 4:
			system("cls");
			Laba4();
			std::cout << std::endl << std::endl;
			break;
		case 5:
			system("cls");
			Laba5();
			std::cout << std::endl << std::endl;
			break;
		case 7:
			system("cls");
			Laba7();
			std::cout << std::endl << std::endl;
			break;
		case 8:
			system("cls");
			Laba8();
			std::cout << std::endl << std::endl;
			break;
		case 9:
			system("cls");
			Laba9();
			std::cout << std::endl << std::endl;
			break;
		case 10:
			system("cls");
			Laba10();
			std::cout << std::endl << std::endl;
			break;
		case -1:
			exit = true;
			break;
		default:
			system("cls");
			std::cout << "Error input. Try again.\n\n";
			break;
		}
	}

	system("Pause");
	return 0;
}

#pragma region Common

void HandleInput(const std::istream& stream, bool& hasError)
{
	hasError = std::cin.fail();
	if (hasError)
		std::cin.clear();

	//std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

template<typename T>
void InputWrapper(const std::istream& stream, const char* userText,
	const char* userErrorText, T& variable, bool (*checkFunc)(const T&))
{
	bool inputError;

	while (true)
	{
		std::cout << userText;
		std::cin >> variable;
		HandleInput(std::cin, inputError);

		inputError = inputError || (checkFunc && !checkFunc(variable));

		if (inputError)
			std::cout << userErrorText;
		else
			break;
	}
}

#pragma endregion

#pragma region Laba1

float RadiansToDegrees(float radians)
{
	return radians * (180.0 / PI);
}

float DegreesToRadians(float degrees)
{
	return degrees * (PI / 180);
}

float GetAngleFromSides(float sideA, float sideB, float sideC)
{
	return RadiansToDegrees(acos((pow(sideB, 2) + pow(sideC, 2) - pow(sideA, 2)) / (2.0f * sideB * sideC)));
}

#pragma endregion

#pragma region Laba2

int Factorial(int num)
{
	if (num < 2)
		return 1;

	return num * Factorial(num - 1);
}

float RecursiveSin(float x, int precision)
{
	if (precision == 0)
		return x;

	return (precision % 2 == 0 ? 1 : -1) * (pow(x, 2 * precision + 1) / Factorial(2 * precision + 1)) +
		RecursiveSin(x, precision - 1);
}

float Sin(float x)
{
	return RecursiveSin(x, 3);
}

#pragma endregion

#pragma region Laba3

void PrintArray(int* arr, size_t size)
{
	if (arr == nullptr)
		return;

	for (size_t i = 0; i < size; i++)
		std::cout << arr[i] << " ";
	std::cout << std::endl;
}

int Max(int* arr, size_t size)
{
	if (arr == nullptr)
		return INT_MIN;

	int max = arr[0];

	for (size_t i = 1; i < size; i++)
		if (arr[i] > max)
			max = arr[i];

	return max;
}

#pragma endregion

#pragma region Laba4

int searchCount = 0;

bool LinearSearch(int* arr, size_t size, int findElem)
{
	for (size_t i = 0; i < size; i++)
	{
		searchCount++;
		if (arr[i] == findElem)
			return true;
	}

	return false;
}

bool BinarySearch(int* arr, int size, int findElem)
{
	int arrMediana = -1, findStart = 0, findEnd = size;

	do
	{
		arrMediana = findStart + (findEnd - findStart) / 2;

		searchCount++;

		if (findElem < arr[arrMediana])
			findEnd = arrMediana - 1;
		else if (findElem > arr[arrMediana])
		{
			findStart = arrMediana + 1;
			searchCount++;
		}
		else
			return true;

		searchCount++;

		if (findStart > findEnd)
			return false;

	} while (true);

	return false;
}

bool IntCmp(int left, int right)
{
	return left < right;
}

#pragma endregion

#pragma region Laba5

long long compareCount = 0,
swapCount = 0;

enum FillType
{
	AscSortFill,
	RandNumberFill,
	DescSortFill
};

void BubbleSort(int* arr, size_t size)
{
	for (size_t i = 0; i < size; i++)
	{
		for (size_t j = 0; j < size - i - 1; j++)
		{
			compareCount++;
			if (arr[j] > arr[j + 1])
			{
				std::swap(arr[j], arr[j + 1]);
				swapCount++;
			}
		}
	}
}

void ShellSort(int* arr, size_t size)
{
	size_t step = size / 2;

	while (step > 0)
	{
		for (int i = 0; i < (size - step); i++)
		{
			for (int j = i; j >= 0 && arr[j] > arr[j + step]; j--)
			{
				compareCount++;
				swapCount++;
				std::swap(arr[j], arr[j + step]);
			}
		}

		step = step / 2;
	}
}

void SelectionSort(int* arr, size_t size)
{
	for (int i = 0; i < size - 1; i++)
	{
		for (int j = i + 1; j < size; j++)
		{
			compareCount++;
			if (arr[j] < arr[i])
			{
				swapCount++;
				std::swap(arr[j], arr[i]);
			}
		}
	}
}

void FillArr(int* arr, size_t size, FillType fillType, int randRestriction)
{
	switch (fillType)
	{
	case AscSortFill:
		for (size_t i = 0; i < size; i++)
			arr[i] = i;
		break;
	case RandNumberFill:
		for (size_t i = 0; i < size; i++)
			arr[i] = rand() % randRestriction;
		break;
	case DescSortFill:
		for (size_t i = 0; i < size; i++)
			arr[i] = size - i;
		break;
	}
}

#pragma endregion

#pragma region Laba10

const int Laba10FieldSize = 8;
bool visited[Laba10FieldSize][Laba10FieldSize] = { false };

void PrintMatrix(const AdjacencyMatrix& matrix)
{
	auto matField = matrix.GetField();

	std::cout << std::setw(2) << " ";
	for (size_t i = 0; i < matrix.GetElementAmount(); i++)
		std::cout << std::setw(3) << matField[0][i]->GetYKey() << " ";

	std::cout << std::endl;

	for (size_t i = 0; i < matrix.GetElementAmount(); i++)
	{
		std::cout << matField[i][0]->GetXKey() << " ";

		for (size_t j = 0; j < matrix.GetElementAmount(); j++)
			std::cout << std::setw(3) << matField[i][j]->GetWeight() << " ";

		std::cout << std::endl;
	}
}

void ResetVisitedArr()
{
	for (size_t i = 0; i < Laba10FieldSize; i++)
		for (size_t j = 0; j < Laba10FieldSize; j++)
			visited[i][j] = false;
}

int FindShortWayStepCountRecursive(const AdjacencyMatrix& matrix, int currentYIndex, int findVertex, 
								   std::list<AdjacencyElement* >* path)
{
	auto field = matrix.GetField();

	for (size_t i = 0; i < matrix.GetElementAmount(); i++)
	{
		//std::cout << "Visited point: " << currentYIndex << ";" << i << std::endl;

		auto currentElem = field[currentYIndex][i];

		if (currentElem->GetWeight() != 0 && currentElem->GetYKey() == findVertex) 
		{
			path->push_back(currentElem);
			return 1;
		}
		else if (!visited[currentYIndex][i] && currentElem->GetWeight() != 0)
		{
			visited[currentYIndex][i] = true;
			visited[i][currentYIndex] = true;

			path->push_back(currentElem);

			int stepCount = FindShortWayStepCountRecursive(matrix, i, findVertex, path);

			if (stepCount == -1)
			{
				path->pop_back();
				visited[i][currentYIndex] = false;
				continue;
			}
			else
				return stepCount + 1;
		}
	}

	return -1;
}

std::list<AdjacencyElement*>* FindShortWayStepCount(const AdjacencyMatrix& matrix, int from, int to)
{
	auto path = new std::list<AdjacencyElement* >();
	auto minPath = new std::list<AdjacencyElement* >();
	
	if (from == to)
		return minPath;

	auto field = matrix.GetField();
	int stepCount = -1;
	int weight = 0;

	std::cout << std::endl;

	for (size_t i = 0; i < matrix.GetElementAmount(); i++)
	{
		if (field[i][0]->GetXKey() == from)
		{
			for (size_t j = 0; j < matrix.GetElementAmount(); j++)
			{
				if (field[i][j]->GetWeight() != 0)
				{
					int tempWeight = 0;
					int foundStepCount = 0;

					if (field[i][j]->GetYKey() != to)
					{
						//Проставляем все "пристутствия" на текущую вершину у остальных вершин
						for (size_t vI = 0; vI < matrix.GetElementAmount(); vI++)
							visited[vI][i] = true;

						visited[i][j] = true;

						path->push_back(field[i][j]);

						foundStepCount = FindShortWayStepCountRecursive(matrix, j, to, path);

						for (auto itr = path->begin(); itr != path->end(); itr++)
						{
							tempWeight += (*itr)->GetWeight();
						}

						//std::cout << "\n\nFound step count: " << foundStepCount << std::endl;
					}
					else
					{
						foundStepCount++;
						tempWeight = field[i][j]->GetWeight();
					}

					if (stepCount == -1)
					{
						stepCount = foundStepCount;
						
						for (auto itr = path->begin(); itr != path->end(); itr++) 
						{
							minPath->push_back(*itr);
						}

						weight = tempWeight;
						path->clear();
					}
					else if (foundStepCount != -1 && stepCount > foundStepCount && weight > tempWeight)
					{
						minPath->clear();

						for (auto itr = path->begin(); itr != path->end(); itr++)
						{
							minPath->push_back(*itr);
						}

						path->clear();

						stepCount = foundStepCount;

						weight = tempWeight;
					}

					ResetVisitedArr();
				}
			}

			return minPath;
		}
	}

	return minPath;
}

#pragma endregion


void Laba1()
{
	float sideA, sideB, sideC, angleA, angleB, angleC;
	bool inputError;
	char sideTriangleType[25];
	char angleTriangleType[25];

	auto checkSideLength = [](const float& arg) { return arg > 0; };					//Лямбда для проверки введённой длины стороны
	auto errorText = "Error input. Try again!\n";

	InputWrapper<float>(std::cin, "Enter length of side a: ", errorText, sideA, checkSideLength);
	system("cls");

	InputWrapper<float>(std::cin, "Enter length of side b: ", errorText, sideB, checkSideLength);
	system("cls");

	InputWrapper<float>(std::cin, "Enter length of side c: ", errorText, sideC, checkSideLength);
	system("cls");

	if (sideA + sideB > sideC &&
		sideB + sideC > sideA &&
		sideC + sideA > sideB)
	{
		angleA = GetAngleFromSides(sideA, sideB, sideC);
		angleB = GetAngleFromSides(sideB, sideA, sideC);
		angleC = GetAngleFromSides(sideC, sideB, sideA);

		if (angleA > 90 || angleB > 90 || angleC > 90)
			strcpy_s(angleTriangleType, "obtuse");
		else if (angleA == 90 || angleB == 90 || angleC == 90)
			strcpy_s(angleTriangleType, "rectangular");
		else
			strcpy_s(angleTriangleType, "acute");

		if (sideA == sideB && sideB == sideC)
			strcpy_s(sideTriangleType, "equilateral");
		else if (sideA == sideB || sideB == sideC || sideA == sideC)
			strcpy_s(sideTriangleType, "isosceles");
		else
			strcpy_s(sideTriangleType, "versatile");

		std::cout << "Created triangle have:\n\tSides "
			<< sideA << ", " << sideB << ", " << sideC
			<< ";\n\tAngles "
			<< angleA << ", " << angleB << ", " << angleC
			<< ";\nIt's a " << angleTriangleType << " and " << sideTriangleType << " triangle.\n";
	}
	else
		std::cout << "Triangle cannot be created due to wrong given sides (sum of each two sides must be bigger than third one).\n";
}

void Laba2()
{
	int n, m;
	float angle, sinX, result = 0;

	auto checkInputNum = [](const int& arg) { return arg >= 0; };

	InputWrapper<int>(std::cin, "Enter n: ", "Wrong input or n less than 0. Try again.\n", n, checkInputNum);
	InputWrapper<int>(std::cin, "Enter m: ", "Wrong input or m less than 0. Try again.\n", m, checkInputNum);
	InputWrapper<float>(std::cin, "Enter x: ", "Wrong input. Try again.\n", angle);

	if (n - m == 0)
	{
		std::cout << "n and m cannot be equal (n - m = 0).";
		return;
	}

	sinX = Sin(DegreesToRadians(angle));

	result = (Factorial(n) - Factorial(m)) / (n - m) + sinX;

	std::cout << "sin(" << angle << ") = " << sinX << std::endl;
	std::cout << "Result of formula (n!-m!)/(n-m) + sin(x) = " << result << std::endl;
}

void Laba3()
{
#pragma region Task 1
	const int arrSize = 10;
	int arr[arrSize], positiveArrSize = 0;
	int* positiveArr;

	for (size_t i = 0; i < arrSize; i++)
		arr[i] = rand() % 101 - 40;

	std::cout << "Generated arr:\n";
	PrintArray(arr, arrSize);

	for (size_t i = 0; i < arrSize; i++)
		if (arr[i] >= 0)
			positiveArrSize++;

	positiveArr = new int[positiveArrSize];

	for (size_t i = 0, posArrI = 0; i < arrSize; i++)
	{
		if (arr[i] >= 0)
		{
			positiveArr[posArrI] = arr[i];
			posArrI++;
		}
	}

	std::cout << "\nArr with only positive elements:\n";
	PrintArray(positiveArr, positiveArrSize);

	std::cout << "\nMax elem in positive arr: " << Max(positiveArr, positiveArrSize) << std::endl;

	delete[] positiveArr;
#pragma endregion

#pragma region Task 2
	int matSizeCol, matSizeRow, maxMatElem = INT_MIN, maxMatElemCol = -1, maxMatElemRow = -1;
	int** matrix;

	auto sizeCheck = [](const int& arg) { return arg > 0; };

	InputWrapper<int>(std::cin, "Enter number of matrix columns: ", "Error inpur columns. It's either wrong input or num of columns less or equal than 0. Try again.\n", matSizeCol, sizeCheck);
	InputWrapper<int>(std::cin, "Enter number of matrix rows: ", "Error inpur columns. It's either wrong input or num of rows less or equal than 0. Try again.\n", matSizeRow, sizeCheck);

	std::cout << "\nInput mat elems:\n";
	matrix = new int* [matSizeRow];
	for (size_t i = 0; i < matSizeRow; i++)
	{
		matrix[i] = new int[matSizeCol];

		for (size_t j = 0; j < matSizeCol; j++)
		{
			int elem = -1;

			InputWrapper<int>(std::cin, "Enter element [" + i + ';' + j + *"] of matrix ", "Error input. Try again.\n", elem);

			matrix[i][j] = elem;

			if (elem > maxMatElem)
			{
				maxMatElem = elem;
				maxMatElemCol = j;
				maxMatElemRow = i;
			}
		}
	}

	std::cout << std::endl << "Created matrix:\n";

	for (size_t i = 0; i < matSizeRow; i++)
		PrintArray(matrix[i], matSizeCol);

	std::cout << "Max element of mat [" << matSizeRow << ";" << matSizeCol << "] is " << maxMatElem << " and it coordinate is " << maxMatElemRow + 1 << ";" << maxMatElemCol + 1 << std::endl;

	for (size_t i = 0; i < matSizeRow; i++)
		delete[] matrix[i];
#pragma endregion
}

void Laba4()
{
	const int laba4ArrSize = 500;
	int maxRandNum = 1000, matchCount = 0;
	int arr1[laba4ArrSize], arr2[laba4ArrSize];

	for (size_t i = 0; i < laba4ArrSize; i++)
	{
		arr1[i] = rand() % maxRandNum;
		arr2[i] = rand() % maxRandNum;
	}

	std::cout << "Arr1:\n";
	PrintArray(arr1, laba4ArrSize);

	std::cout << "\n\nArr2:\n";
	PrintArray(arr2, laba4ArrSize);

	//Указатель на laba4ArrSize + 1 элемент необходим, чтобы сортировало весь массив
	std::sort<int*>(&arr1[0], (&arr1[0] + laba4ArrSize), IntCmp);
	std::sort<int*>(&arr2[0], (&arr2[0] + laba4ArrSize), IntCmp);

	for (int i = 0; i <= 500; i++)
	{
		if (LinearSearch(arr1, laba4ArrSize, i) && LinearSearch(arr2, laba4ArrSize, i))
		{
			std::cout << "\nThere was found math for element " << i << " in arr1 and arr2";
			matchCount++;
		}
	}

	std::cout << "\nHow many iterations it took for find all mathes in both array using linear search: " << searchCount
		<< "\nMathes count: " << matchCount;

	matchCount = 0;
	searchCount = 0;

	std::cout << std::endl << std::endl;

	for (int i = 0; i <= 500; i++)
	{
		if (BinarySearch(arr1, laba4ArrSize, i) && BinarySearch(arr2, laba4ArrSize, i))
		{
			std::cout << "\nThere was found match for element " << i << " in arr1 and arr2";
			matchCount++;
		}
	}

	std::cout << "\nHow many iterations it took for find all mathes in both array using binary search: " << searchCount
		<< "\nMathes count: " << matchCount;
}

void Laba5()
{
	int arrSize;
	int* arr;
	FillType fType;

	auto arrSizeChecker = [](const int& arg) { return arg > 0; };
	//auto arrFillChecker = [](const int& arg) { return arg >= 0 && arg < 3; };

	InputWrapper<int>(std::cin, "Enter array size: ", "\nWrong input. Either entered size less or equal than 0 or int parsing error. Try again.", arrSize, arrSizeChecker);

	arr = new int[arrSize];

	//InputWrapper<int>(std::cin, "Enter array filling (0 - Ascend sort filling, 1 - Random number filling, 2 - Descend sort filling): ", "\nWrong input. Either entered fill type out of range or int parsing error. Try again.", arrFill, arrFillChecker);

	//fType = (FillType)arrFill;

	for (size_t i = 0; i < 3; i++)
	{
		fType = (FillType)i;

		switch (fType)
		{
		case AscSortFill:
			std::cout << "Ascending fill type:\n";
			break;
		case RandNumberFill:
			std::cout << "Random number fill type:\n";
			break;
		case DescSortFill:
			std::cout << "Descending fill type:\n";
			break;
		}

		FillArr(arr, arrSize, fType, 1000);

		//std::cout << "Arr before bubble sort:\n";
		//PrintArray(arr, arrSize);

		BubbleSort(arr, arrSize);

		//std::cout << "\n\nArr after bubble sort:\n";
		//PrintArray(arr, arrSize);

		std::cout << "\nBubble sort compare count: " << compareCount
			<< "\nBubble sort swap count: " << swapCount;

		compareCount = 0;
		swapCount = 0;

		FillArr(arr, arrSize, fType, 1000);

		//std::cout << "\n\nArr before shell sort:\n";
		//PrintArray(arr, arrSize);

		ShellSort(arr, arrSize);

		//std::cout << "\n\nArr after shell sort:\n";
		//PrintArray(arr, arrSize);

		std::cout << "\nShell sort compare count: " << compareCount
			<< "\nShell sort swap count: " << swapCount;

		compareCount = 0;
		swapCount = 0;

		FillArr(arr, arrSize, fType, 1000);

		/*std::cout << "\n\nArr before selection sort:\n";
		PrintArray(arr, arrSize);*/

		SelectionSort(arr, arrSize);

		//std::cout << "\n\nArr after selection sort:\n";
		//PrintArray(arr, arrSize);

		std::cout << "\nSelection sort compare count: " << compareCount
			<< "\nSelection sort swap count: " << swapCount;

		compareCount = 0;
		swapCount = 0;

		std::cout << std::endl << std::endl;
	}
}

void Laba7()
{
	BusPark park("Park 1", 30);

	std::cout << "Park info:\n\tName: " << park.GetParkName() << "\n\tMax buses amount: " << park.GetMaxBusesAmount() << std::endl;

	park.AddBus(new Bus("000000000001", "A. Petrovych", "00000000001"));
	park.AddBus(new Bus("000000000002", "A. Simonovych", "000d0000001"));
	park.AddBus(new Bus("000000000003", "E. Doroshenko", "00005000004"));
	park.AddBus(new Bus("000000000004", "N. Zmishenko", "00z000000005"));
	park.AddBus(new Bus("000000000005", "N. Andrienko", "0000000g007"));

	park.PrintBusesInfo();

	std::cout << std::endl;

	park.SendBusToWay("000000000001");
	park.SendBusToWay("000000000002");

	std::cout << std::endl;

	park.PrintBusesInWay();

	std::cout << std::endl;

	park.PrintIdleBuses();

	std::cout << std::endl;

	park.SendBusToPark("000000000002");
	park.SendBusToWay("000000000003");

	park.RemoveBus("000000000002");

	std::cout << std::endl;

	park.PrintBusesInfo();

	std::cout << std::endl;

	park.RemoveBus("000000000005");

	std::cout << std::endl;

	park.PrintBusesInfo();
}

void Laba8()
{
	Warehouse warehouse("Warehouse 1");

	warehouse.AddProduct(new Product("Product 1", 1.0f));
	warehouse.AddProduct(new Product("Product 2", 5.4f));
	warehouse.AddProduct(new Product("Product 3", 2.45f));
	warehouse.AddProduct(new Product("Product 4", 1.34f));
	warehouse.AddProduct(new Product("Product 5", 0.99f));
	warehouse.AddProduct(new Product("Product 6", 7.545f));
	warehouse.AddProduct(new Product("Product 7", 3.5f));
	warehouse.AddProduct(new Product("Product 8", 5.555f));
	warehouse.AddProduct(new Product("Product 9", 2.0f));
	warehouse.AddProduct(new Product("Product 10", 1.545f));

	warehouse.GetLastProduct();
	warehouse.GetLastProduct();
	warehouse.GetLastProduct();

	warehouse.AddProduct(new Product("Product 54", 2.564f));

	warehouse.GetLastProduct();
	warehouse.GetLastProduct();
}

const char* PadLeft(int padLevel)
{
	if (padLevel < 1)
		return "";

	char* padding = new char[padLevel + 1];

	for (size_t i = 0; i < padLevel; i++)
		padding[i] = ' ';

	padding[padLevel] = '\0';

	return padding;
}

void Laba9()
{
	srand(time(0));

	BinaryTree<Book*> books;

	const char** names = new const char* [] { "Book 1", "Book 2", "Book 3", "Book 4" };
	const char** authors = new const char* [] { "Author 1", "Author 2", "Author 3", "Author 4" };
	int numbers[4] = { 0 };

	auto printProduct = [](Book* book, int depthLevel)
	{
		std::cout << "\tNumber: " << book->GetNumber()
				  << "\n\tName: " << book->GetName() 
				  << "\n\tAuthors initials: " << book->GetAuthorInitials()
				  << "\n\tPublished year: " << book->GetPublishedYear() 
				  << "\n\tAmount: " << book->GetBookAmount()
			      << "\n===================================================\n";
	};

	numbers[0] = rand() % 150 + 1;
	numbers[1] = rand() % 150 + 1;
	numbers[2] = rand() % 150 + 1;
	numbers[3] = rand() % 150 + 1;

	for (size_t i = 0; i < 10; i++)
	{
		int index = rand() % 4;
		int number = numbers[index];

		//fix this
		try
		{
			auto existBook = books.GetElement(number);
			existBook->SetBookAmount(existBook->GetBookAmount() + 1);
		}
		catch (const std::exception&)
		{
			Book* newBook = new Book(number);
			newBook->SetName(names[index]);
			newBook->SetAuthorInitials(authors[index]);
			newBook->SetPublishedYear(rand() % 2021);

			books.InsertElement(number, newBook);
		}
	}

	std::cout << std::endl;
	books.PrintKeys();

	std::cout << "\nAvailable books:\n";
	books.ForeEach(printProduct);

	int numberToDelete = numbers[rand() % 4];
	auto existElem = books.GetElement(numberToDelete);
	existElem->SetBookAmount(1);

	std::cout << "\nDeleting book with number " << numberToDelete << std::endl;

	if (existElem->GetBookAmount() > 1)
		existElem->SetBookAmount(existElem->GetBookAmount() - 1);
	else
	{
		books.DeleteElement(numberToDelete);
		delete existElem;
	}


	std::cout << "\nAvailable books:\n";
	books.ForeEach(printProduct);

	delete[] names;
	delete[] authors;
}

void Laba10()
{
	AdjacencyMatrix mat;

	for (size_t i = 1; i <= Laba10FieldSize; i++)
		mat.AddVertex(i);

	mat.SetVertexWeight(2, 1, 13);
	mat.SetVertexWeight(2, 3, 15);
	mat.SetVertexWeight(2, 7, 16);
	mat.SetVertexWeight(3, 2, 15);
	mat.SetVertexWeight(3, 6, 12);
	mat.SetVertexWeight(4, 5, 8);
	mat.SetVertexWeight(4, 8, 13);
	mat.SetVertexWeight(5, 4, 8);
	mat.SetVertexWeight(5, 7, 13);
	mat.SetVertexWeight(6, 5, 5);
	mat.SetVertexWeight(6, 3, 12);
	mat.SetVertexWeight(6, 1, 21);
	mat.SetVertexWeight(7, 5, 13);
	mat.SetVertexWeight(7, 2, 16);
	mat.SetVertexWeight(8, 1, 14);
	mat.SetVertexWeight(8, 3, 14);
	mat.SetVertexWeight(8, 4, 13);

	PrintMatrix(mat);

	int from = 3, to = 7;

	auto checkVertex = [](const int& arg) { return arg > 0 && arg < 9; };

	InputWrapper<int>(std::cin, "\nEnter start vertex (availables vertices are 1 - 8): ", "\nWrong input. Try again.", from, checkVertex);
	InputWrapper<int>(std::cin, "\nEnter end vertex (availables vertices are 1 - 8): ", "\nWrong input. Try again.", to, checkVertex);

	auto path = FindShortWayStepCount(mat, from, to);

	std::cout << "Path: ";
	for (auto itr = path->begin(); itr != path->end(); itr++)
		std::cout << (* itr)->GetXKey() << "->";
	std::cout << to;

	std::cout << "\n\nStep count: " << path->size() << std::endl;
}