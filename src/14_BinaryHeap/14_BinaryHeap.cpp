#include <iostream>
#include <functional>

// 优先级队列
class PriorityQueue
{
public:
	using Comp = std::function<bool(int, int)>;

	PriorityQueue(int cap = 20, Comp comp = std::greater<int>())
		: size_(0)
		, cap_(cap)
		, comp_(comp)
	{
		que_ = new int[cap_];
	}

	PriorityQueue(Comp comp)
		: PriorityQueue(20, comp)
	{ }

	~PriorityQueue()
	{
		delete[]que_;
		que_ = nullptr;
	}

public:
	// 入堆
	void push(int val)
	{
		if (size_ == cap_)
		{
			expand(2 * cap_);
		}

		// 入堆上浮
		shiftUp(size_, val);
		size_++;
	}

	// 出堆
	void pop()
	{
		if (size_ == 0)
			throw "The container is empty";

		size_--;
		if (size_ > 0)
		{
			// 出堆下沉
			shiftDown(0, que_[size_]);
		}
	}

	bool empty() const { return size_ == 0; }

	int top() const
	{
		if (size_ == 0)
			throw "The container is empty";

		return que_[0];
	}

	int size() const { return size_; }

private:
	// 扩容
	void expand(int cap)
	{
		int* p = new int[cap];

		// 注意：memcpy 仅适用于 POD (Plain Old Data) 类型，如 int。
		// 如果是复杂对象，请使用 std::copy 或循环赋值。
		memcpy(p, que_, size_ * sizeof(int));
		delete[]que_;
		que_ = p;

		cap_ = cap;
	}

	// 上浮调整函数
	void shiftUp(int i, int val)
	{
		while (i > 0)
		{
			int f = (i - 1) / 2;
			if (comp_(val, que_[f]))
			{
				que_[i] = que_[f];
				i = f;
			}
			else
			{
				break;
			}
		}
		que_[i] = val;
	}

	// 下沉调整函数
	void shiftDown(int i, int val)
	{
		while (i < size_ / 2)
		{
			int c = 2 * i + 1;
			if (c + 1 < size_ && comp_(que_[c + 1], que_[c]))
			{
				c = c + 1;
			}

			if (comp_(que_[c], val))
			{
				que_[i] = que_[c];
				i = c;
			}
			else
			{
				break;
			}
		}
		que_[i] = val;
	}
private:
	int* que_;
	int size_;
	int cap_;
	Comp comp_;
};

int main()
{
	PriorityQueue pq;	// 默认大根堆
	PriorityQueue spq([](int a, int b) { return a < b; }); // 测试小根堆
	srand(time(NULL));

	for (int i = 0; i < 10; i++)
	{
		pq.push(rand() % 101);
	}
	
	while (!pq.empty())
	{
		std::cout << pq.top() << " ";
		pq.pop();
	}
	std::cout << std::endl;

	for (int i = 0; i < 10; i++)
	{
		spq.push(rand() % 101);
	}

	while (!spq.empty())
	{
		std::cout << spq.top() << " ";
		spq.pop();
	}
	std::cout << std::endl;

	return 0;
}