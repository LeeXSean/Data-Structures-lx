#include <iostream>

// 冒泡排序 平均时间复杂度o(n^2)（最好o(n)，最坏o(n^2)） 
// 空间复杂度o(1)  稳定排序
void BubbleSort(int* arr, int size)
{
	// 外层循环，排除内层循环结束后的最后一个元素（最大元素）
	for (int i = 0; i < size - 1; i++)
	{
		// 内层循环是否对数组排序（优化）
		bool flag = false;

		// 内层循环，将当前数组中最大的元素排到最后一个
		for (int j = 0; j < size - 1 - i; j++)
		{
			if (arr[j] > arr[j + 1])
			{
				int tmp = arr[j];
				arr[j] = arr[j + 1];
				arr[j + 1] = tmp;
				flag = true;
			}
		}

		if (!flag)
		{
			return;
		}
	}
}

// 选择排序 平均时间复杂度o(n^2)（最好o(n^2)，最坏o(n^2)） 
// 空间复杂度o(1) 不稳定排序
void ChoiceSort(int* arr, int size)
{
	for (int i = 0; i < size - 1; i++)
	{
		int k = i;
		for (int j = i + 1; j < size; j++)
		{
			if (arr[j] < arr[k])
			{
				k = j;
			}
		}

		// 优化，减少不必要的赋值
		if (k != i)
		{
			int tmp = arr[k];
			arr[k] = arr[i];
			arr[i] = tmp;
		}
	}
	
}

// 插入排序 平均时间复杂度o(n^2)（最好o(n)，最坏o(n^2)） 
// 空间复杂度o(1)  稳定排序 
// 近似有序下效率最高
void InsertSort(int* arr, int size)
{
	for (int i = 1; i < size; i++)
	{
		int value = arr[i];
		int j = i - 1;
		for (; j >= 0; j--)
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

// 希尔排序 依赖不同的增量序列设置平均时间复杂度o(n^1.3)（最好o(n)，最坏o(n^2)） 
// 空间复杂度o(1)  不稳定排序
// 插入排序的优化版，分组进行插入排序，逐步将全局元素趋向于有序，最后全局采用插入排序
void ShellSort(int* arr, int size)
{
	for (int gap = size / 2; gap > 0; gap /= 2) // 基本不影响性能
	{
		// 交叉对同余类的元素进行插入排序
		for (int i = gap; i < size; i++) // o(n)
		{
			int value = arr[i];
			int j = i - gap;
			for (; j >= 0; j -= gap) // o(n)
			{
				if (arr[j] <= value)
				{
					break;
				}
				arr[j + gap] = arr[j];
			}
			arr[j + gap] = value;
		}
	}
}

int main()
{
	int COUNT = 100000;
	int* arr = new int[COUNT];
	int* brr = new int[COUNT];
	int* crr = new int[COUNT];
	int* drr = new int[COUNT];

	srand(time(NULL));

	for (int i = 0; i < COUNT; i++)
	{
		int val = rand() % COUNT;
		arr[i] = val;
		brr[i] = val;
		crr[i] = val;
		drr[i] = val;
	}

	clock_t begin, end;

	begin = clock();
	BubbleSort(arr, COUNT);
	end = clock();
	std::cout << "BubbleSort spend: " << (end - begin) * 1.0 / CLOCKS_PER_SEC << "s" << std::endl;

	begin = clock();
	ChoiceSort(brr, COUNT);
	end = clock();
	std::cout << "ChoiceSort spend: " << (end - begin) * 1.0 / CLOCKS_PER_SEC << "s" << std::endl;

	begin = clock();
	InsertSort(crr, COUNT);
	end = clock();
	std::cout << "InsertSort spend: " << (end - begin) * 1.0 / CLOCKS_PER_SEC << "s" << std::endl;

	begin = clock();
	ShellSort(drr, COUNT);
	end = clock();
	std::cout << "ShellSort spend: " << (end - begin) * 1.0 / CLOCKS_PER_SEC << "s" << std::endl;
}

#if 0
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

	/*
	BubbleSort(arr, size);
	ChoiceSort(arr, size);
	InsertSort(arr, size);
	*/

	ShellSort(arr, size);
	
	for (int v : arr)
	{
		std::cout << v << " ";
	}
	std::cout << std::endl;
}
#endif