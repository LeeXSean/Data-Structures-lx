/*
 * 基数排序算法
 *
 * 时间复杂度：
 *   - O(nd)
 *
 * 空间复杂度：
 *   - O(n)
 *
 * 稳定排序
 *
 */

#include <cstdlib>
#include <ctime>
#include <iostream>
#include <string>
#include <vector>

// 基数排序函数（仅适用于整数）
void RadixSort(int* arr, int size)
{
	// 边界保护
	if (!arr || size <= 1) return;

	int MaxData = std::abs(arr[0]);
	for (int i = 1; i < size; i++)
	{
		if (MaxData < std::abs(arr[i]))
		{
			MaxData = std::abs(arr[i]);
		}
	}

	int len = std::to_string(MaxData).size();

	std::vector<std::vector<int>> vecs(20);						// 考虑负数排序，安排二十个桶（有效桶为19个，为方便阅读设计20个）
	int mod = 10;
	int dev = 1;

	for (int i = 0; i < len; mod *= 10, dev *= 10, i++)		// 时间复杂度 O(nd)
	{

		// 按照元素的第i位（从右向左，从个位数开始）排进不同序号的桶里
		for (int j = 0; j < size; j++)
		{
			int index = arr[j] % mod / dev + 10;			// [-9, 9]，+10后映射到 [1, 19]（0号桶一般不会用到）
			vecs[index].push_back(arr[j]);
		}

		// 将桶里的元素重新排入到原数组，若从小到大则从0开始，若从大到小则从19开始
		// 这里按桶序（0 -> 19）回写到原数组，实现从小到大
		int idx = 0;
		for (const auto& vec : vecs)						// 时间复杂度 O(n)
		{
			for (int v : vec)
			{
				arr[idx++] = v;
			}
		}

		for (auto& vec : vecs) vec.clear();					// 进行一次桶排序后，需要清空桶
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
	
	// 测试负数
	arr[0] = -18;
	arr[6] = -39;

	for (int v : arr)
	{
		std::cout << v << " ";
	}
	std::cout << std::endl;

	RadixSort(arr, size);

	for (int v : arr)
	{
		std::cout << v << " ";
	}
	std::cout << std::endl;
}