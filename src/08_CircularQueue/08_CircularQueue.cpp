#include <iostream>
#include <memory>

class Queue
{
private:
	int* pQue_;
	int front_;
	int rear_;
	int cap_;
	int size_;
public:
	Queue(int cap=10)
		: front_(0)
		, rear_(0)
		, cap_(cap)
	{
		pQue_ = new int[cap_];
	}

	~Queue()
	{
		delete[] pQue_;
		pQue_ = nullptr;
	}

public:
	void push(int val)
	{
		if ((rear_ + 1) % cap_ == front_)
		{
			expand(2 * cap_);
		}
		pQue_[rear_] = val;
		rear_ = (rear_ + 1) % cap_;
		size_++;
	}

	void pop(int val)
	{
		if (rear_ == front_)
		{
			throw "";
		}
		front_ = (front_ + 1) % cap_;
		size_--;
	}

	int front() const
	{
		if (rear_ == front_)
		{
			throw "";
		}
		return pQue_[front_];
	}

	int back() const
	{
		if (rear_ == front_)
		{
			throw "";
		}
		return pQue_[(rear_ + cap_ - 1) % cap_];
	}

	bool empty() const
	{
		if (rear_ == front_)
		{
			return true;
		}
		else
		{
			return false;
		}
	}

	int size() const
	{
		return size_;
		/*
		int size = 0;
		for (int i = front_; i != rear_; i = (i + 1) % cap_)
		{
			size++;
		}
		return size;
		*/
	}

private:
	void expand(int cap)
	{
		int* p = new int[cap];
		for (int i = 0, j = front_; j != rear_; i++, j = (j + 1) % cap_)
		{
			p[i] = pQue_[j];
		}
		delete[] pQue_;
		pQue_ = p;
		cap_ = cap;
		front_ = 0;
		rear_ = size_;
	}
};

int main()
{
	Queue q;

	q.push(200);
	q.push(300);
	q.push(100);

	std::cout << q.front() << std::endl;
	std::cout << q.back() << std::endl;
	std::cout << q.size() << std::endl;
	
}

#if 0
class CircleArray
{
private:
	int first_;		// ��ͷ
	int rear_;		// ��β
	int* ptr_;		// ָ�������ָ��
	int size_;		// ���ζ��������С
public:
	CircleArray(int size = 10)
		: first_(0)
		, rear_(0)
		, size_(size)
	{
		ptr_ = new int[size_];
	}

	~CircleArray()
	{
		delete[] ptr_;
		ptr_ = nullptr;
	}

public:
	void push(int val)
	{
		if ((rear_ + 1) % size_ == first_)
		{
			expand(2 * size_);
		}
		ptr_[rear_] = val;
		rear_ = (rear_ + 1) % size_;
	}

	void pop()
	{
		if (rear_ == first_)
		{
			throw "THE CIRCLEARRAY IS EMPTY";
		}
		first_ = (first_ + 1) % size_;
	}

	bool find(int val) const
	{
		int p = first_;
		while (p != rear_)
		{
			if (ptr_[p] == val)
				return true;
		
			p = (p + 1) % size_;
		}
		return false;
	}

	void show() const
	{
		int p = first_;
		while (p != rear_)
		{
			std::cout << ptr_[p] << " ";
			p = (p + 1) % size_;
		}
		std::cout << std::endl;
	}

private:
	void expand(int size)
	{
		int count = (rear_ + size_ - first_) % size_;
		int* p = new int[size];
		for (int i = 0; i < count; i++)
		{
			p[i] = ptr_[(first_ + i) % size_];
		}
		delete[] ptr_;
		ptr_ = p;
		size_ = size;
		first_ = 0;
		rear_ = count;
	}
};

int main()
{
	CircleArray ca;
	srand(time(0));

	ca.push(200);

	for (int i = 0; i < 6; i++)
	{
		ca.push(rand() % 100);
	}
	ca.push(200);
	ca.push(300);

	ca.show();

	int num = 300;
	if (ca.find(num))
		std::cout << "���� " << num << " ����" << std::endl;

	ca.pop();
	ca.show();

	ca.push(300); 
	ca.push(300);
	ca.push(300);
	ca.show();
}
#endif