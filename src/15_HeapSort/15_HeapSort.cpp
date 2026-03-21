/*
 * 堆排序算法
 *
 * 时间复杂度：
 *   - O(n log n)
 *
 * 空间复杂度：
 *   - O(1)
 *
 * 不稳定排序
 *
 */

#include <iostream>

// 堆下沉调整函数
void ShiftDown(int* arr, int i, int size)
{
	int val = arr[i];
	while (i < size/2)
	{
		int c = 2 * i + 1;
		if (c + 1 < size && arr[c + 1] > arr[c])
		{
			c = c + 1;
		}

		if (val < arr[c])
		{
			arr[i] = arr[c];
			i = c;
		}
		else
		{
			break;
		}
	}
	arr[i] = val;
}

// 堆排序
void HeapSort(int* arr, int size)
{
	int n = size - 1;

	for (int i = (n - 1) / 2; i >= 0; i--)
	{
		ShiftDown(arr, i, size);
	}

	for (int i = n; i > 0; i--)
	{
		int tmp = arr[0];
		arr[0] = arr[i];
		arr[i] = tmp;

		ShiftDown(arr, 0, i);
	}
}

int main()
{
	int arr[10];
	int size = sizeof(arr) / sizeof(arr[0]);
	srand(time(NULL));

	for (int i = 0; i < size; i++)
	{
		arr[i] = rand() % 100 + 1;
	}

	for (int v : arr)
	{
		std::cout << v << " ";
	}
	std::cout << std::endl;

	HeapSort(arr, size);

	for (int v : arr)
	{
		std::cout << v << " ";
	}
	std::cout << std::endl;
}