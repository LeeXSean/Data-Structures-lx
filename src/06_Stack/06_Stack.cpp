#include <iostream>

class SeqStack
{
private:
	int* m_Stack;
	int m_Top;		// 栈顶
	int m_Cap;		// 栈空间大小

public:
	SeqStack(int size = 10)
		: m_Top(0)
		, m_Cap(size)
	{
		m_Stack = new int[m_Cap];
	}
	~SeqStack()
	{
		delete[] m_Stack;
		m_Stack = nullptr;
	}

public:
	// 入栈
	void push(int val)
	{
		if (m_Top == m_Cap)
		{
			expand(2 * m_Cap);
		}
		m_Stack[m_Top++] = val;
	}

	// 出栈
	void pop()
	{
		if (m_Top == 0)
		{
			throw "THE STACK IS EMPTY!";
		}
		m_Top--;
	}

	// 访问栈顶元素
	int top() const
	{
		if (m_Top == 0)
		{
			throw "THE STACK IS EMPTY!";
		}
		return m_Stack[m_Top - 1];
	}

	// 查询栈是否为空
	bool empty() const
	{
		return m_Top == 0;
	}

	// 栈元素数目
	int size() const
	{
		return m_Top;
	}

private:
	// 扩容
	void expand(int size)
	{
		int* p = new int[size];
		memcpy(p, m_Stack, m_Top * sizeof(int));
		delete[] m_Stack;
		m_Stack = p;
		m_Cap = size;
	}
};

int main()
{
	int arr[] = { 21, 75, 86, 24, 64, 100 };
	SeqStack s;

	for (int v : arr)
	{
		s.push(v);
	}

	std::cout << "栈中的元素数目为 " << s.size() << std::endl;

	std::cout << "从栈顶开始访问: ";
	while (!s.empty())
	{
		std::cout << s.top() << " ";
		s.pop();
	}
	std::cout << std::endl;
}