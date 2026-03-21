/*
 * 归并排序算法
 *
 * 时间复杂度：
 *   - O(n log n)
 *
 * 空间复杂度：
 *   - O(n)
 * 
 * 稳定排序
 * 
 * 待优化方向：
 *   - 频繁申请和释放堆内存（Heap Allocation）开销较大
 *     可在在最外层 MergeSort 一次性申请一个和原数组一样大的临时数组 tmp，
 *     然后作为参数传递给递归函数，全程复用这块内存。
 */


#include <iostream>

// 归并函数
void Merge(int* arr, int l, int m, int r)
{
	int *p = new int[r - l + 1];
	int idx = 0;
	int i = l;
	int j = m + 1;

	while (i <= m && j <= r)
	{
		if (arr[i] <= arr[j])
			p[idx++] = arr[i++];
		else
			p[idx++] = arr[j++];
	}

	while (i <= m)
		p[idx++] = arr[i++];

	while (j <= r)
		p[idx++] = arr[j++];

	for (i = l, j = 0; i <= r; i++, j++)
		arr[i] = p[j];

	delete[]p;
}

// 归并排序的递归接口
void MergeSort(int* arr, int begin, int end)
{
	// 递归的结束条件
	if (begin >= end)
		return;

	// 二分
	int mid = (begin + end) / 2;

	// 递
	MergeSort(arr, begin, mid);
	MergeSort(arr, mid + 1, end);

	// 归并，将[begin, mid]和[mid+1, end]两个小段有序的序列合并为一个大段有序的序列
	Merge(arr, begin, mid, end);
}

// 归并排序
void MergeSort(int* arr, int size)
{
	return MergeSort(arr, 0, size - 1);
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

	MergeSort(arr, size);

	for (int v : arr)
	{
		std::cout << v << " ";
	}
	std::cout << std::endl;
}