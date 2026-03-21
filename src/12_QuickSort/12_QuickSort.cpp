/*
 * 快速排序算法
 *
 * 时间复杂度：
 *   - 平均：O(n log n)
 *   - 最好：O(n log n)
 *   - 最坏：O(n^2)
 *     [原因]：当数据原本有序（或接近有序）且基准值选择不当时，递归树退化为链表，深度为 n。
 *
 * 空间复杂度：
 *   - O(log n) ~ O(n)
 *     [原因]：主要消耗在于递归调用的栈空间。
 *     - 平均情况递归深度为 log n。
 *     - 最坏情况递归深度为 n。
 * 
 * 不稳定排序
 */


#include <iostream>

// 针对区间的插入排序算法
void InsertSort(int* arr, int begin, int end)
{
	for (int i = begin + 1; i <= end; i++)
	{
		int value = arr[i];
		int j = i - 1;
		for (; j >= begin; j--)
		{
			if (arr[j] <= value)
			{
				break;
			}
			arr[j + 1] = arr[j];
		}
		arr[j + 1] = value;
	}
}

// 快排分割函数
int Partition(int* arr, int l, int r)
{
	// 优化二：基准数采取三数取中法
	int mid = (l + r) / 2;
	
	if (arr[l] > arr[mid])
	{
		int tmp = arr[mid];
		arr[mid] = arr[l];
		arr[l] = tmp;
	}

	if (arr[mid] > arr[r])
	{
		int tmp = arr[r];
		arr[r] = arr[mid];
		arr[mid] = tmp;
	}

	if (arr[l] > arr[mid])
	{
		int tmp = arr[mid];
		arr[mid] = arr[l];
		arr[l] = tmp;
	}

	int tmp = arr[mid];
	arr[mid] = arr[l];
	arr[l] = tmp;

	// 记录基准数
	int val = arr[l];

	// 一次快排处理
	while (l < r)
	{
		while (l < r && arr[r] > val)
		{
			r--;
		}

		if (l < r)
		{
			arr[l] = arr[r];
			l++;
		}
		
		while (l < r && arr[l] <= val)
		{
			l++;
		}

		if (l < r)
		{
			arr[r] = arr[l];
			r--;
		}
	}

	// l == r 的位置，即基准数的位置
	arr[l] = val;
	return l;
}

// 快速排序的递归接口
void QuickSort(int* arr, int begin, int end)
{
	// 快排递归的结束条件
	if (begin >= end)
		return;

	// 优化一：小范围下数据趋于有序，采用插入排序（具体范围依赖测试数据集）
	if (end - begin < 5)
		return InsertSort(arr, begin, end);

	// 在[begin, end]区间做一次快排分割处理
	int pos = Partition(arr, begin, end);

	// 对基准数左边和右边的序列分别做快排（递归）
	QuickSort(arr, begin, pos - 1);
	QuickSort(arr, pos + 1, end);
}

// 快速排序
void QuickSort(int* arr, int size)
{
	return QuickSort(arr, 0, size - 1);
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

	QuickSort(arr, size);

	for (int v : arr)
	{
		std::cout << v << " ";
	}
	std::cout << std::endl;
}