#include <iostream>

// 整形数组，把偶数调整到数组的左边，把奇数调整到数组的右边
void EvenOddSeparate(int arry[], int size)
{
	int* p = arry;
	int* q = arry + size - 1;
	while (p < q)
	{
		while (p < q)
		{
			if ((*p & 0x1) == 1)
			{
				break;
			}
			p++;
		}
		while (p < q)
		{
			if ((*q & 0x1) == 0)
			{
				break;
			}
			q--;
		}

		if (p < q)
		{
			int tmp = *p;
			*p = *q;
			*q = tmp;
			q--;
			p++;
		}
	}
}

int main()
{
	int array[10] = {};
	srand(time(0));
	for (int i = 0; i < 10; i++)
	{
		array[i] = rand() % 100;
	}
	for (int i : array)
	{
		std::cout << i << " ";
	}
	std::cout << std::endl;

	EvenOddSeparate(array, 10);
	for (int i : array)
	{
		std::cout << i << " ";
	}
	std::cout << std::endl;
}
#if 0
// 逆序字符串
void Reverse(char array[], int size)
{
	char* p = array;
	char* q = array + size - 1;
	while (p < q)
	{
		char tmp = *p;
		*p = *q;
		*q = tmp;
		p++;
		q--;
	}
}
int main()
{
	char CharArray[] = "hello world";
	std::cout << CharArray << std::endl;
	Reverse(CharArray, strlen(CharArray));
	std::cout << CharArray << std::endl;

}
#endif

#if 0
class Array
{
private:
	int* mArry;
	int mCap;
	int mCur;

	// 内部数组扩容接口
	void expand(int size)
	{
		int* ptr = new int[size]();
		memcpy(ptr, mArry, mCur * sizeof(int));
		mArry = ptr;
		ptr = nullptr;

		mCap = size;
	}

public:
	Array(int size = 10) : mCap(size), mCur(0)
	{
		mArry = new int[size]();
	}

	~Array()
	{
		delete[] mArry;
		mArry = nullptr;
	}

	// 末尾位置增加元素
	void push_back(int val)
	{
		if (mCur == mCap)
		{
			expand(2 * mCap);
		}
		mArry[mCur++] = val;
	}

	// 末尾位置删除元素
	void pop_back()
	{
		if (mCur == 0)
		{
			return;
		}
		mCur--;
	}

	// 中间位置插入元素
	void insert(int pos, int val)
	{
		if (pos < 0 || pos >= mCap)
		{
			std::cout << "POSITION INVALID" << std::endl;
			return;
		}

		if (mCur == mCap)
		{
			expand(2 * mCap);
		}

		if (pos >= mCur)
		{
			push_back(val);
		}

		for (int i = mCur - 1; i >= pos; i--)
		{
			mArry[i + 1] = mArry[i];
		}

		mArry[pos] = val;
		mCur++;
	}

	// 按位置删除元素
	void erase(int pos)
	{
		if (pos < 0 || pos >= mCap)
		{
			std::cout << "POSITION INVALID" << std::endl;
			return;
		}

		if (pos >= mCur - 1)
		{
			pop_back();
		}

		for (int i = pos + 1; i < mCur; i++)
		{
			mArry[i - 1] = mArry[i];
		}
		mCur--;
	}

	// 元素查询
	int find(int val)
	{
		for (int i = 0; i < mCur; i++)
		{
			if (mArry[i] == val)
				return i;
		}
		return -1;
	}

	// 查看数据
	void show() const
	{
		for (int i = 0; i < mCur; i++)
		{
			std::cout << mArry[i] << " ";
		}
		std::cout << "" << std::endl;
	}
};

int main() {
	Array arr;

	srand(time(0));
	for (int i = 0; i < 10; i++)
	{
		arr.push_back(rand() % 100);
	}

	arr.show();

	arr.pop_back();
	arr.show();

	arr.insert(3, 41);
	arr.show();

	arr.erase(6);
	arr.show();

	int result = arr.find(41);
	if (result != -1)
	{
		arr.erase(result);
		arr.show();
	}

	std::cin.get();
}
#endif