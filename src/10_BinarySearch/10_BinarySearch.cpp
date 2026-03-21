#include <iostream>

int BinarySearch(int* arr, int i, int j, int val)
{
	if (i > j)
		return -1;

	int mid = (i + j) / 2;
	if (arr[mid] == val)
		return mid;
	else if (arr[mid] < val)
		return BinarySearch(arr, mid + 1, j, val);
	else
		return BinarySearch(arr, i, mid - 1, val);
}


int BinarySearch(int* arr, int size, int val)
{
	return BinarySearch(arr, 0, size - 1, val);
	/*
	int first = 0;
	int last = size - 1;

	while (first <= last)
	{
		int mid = (first + last) / 2;

		if (arr[mid] == val)
		{
			return mid;
		}
		else if (arr[mid] < val)
		{
			first = mid + 1;
		}
		else
		{
			last = mid - 1;
		}
	}

	return -1;
	*/
}


int main()
{
	int arr[] = { 12, 23, 45, 65, 75, 78, 95, 100 };

	int size = sizeof(arr) / sizeof(arr[0]);

	std::cout << BinarySearch(arr, size, 23) << "\n";
	std::cout << BinarySearch(arr, size, 45) << "\n";
	std::cout << BinarySearch(arr, size, 78) << "\n";
	std::cout << BinarySearch(arr, size, 66) << "\n";
}