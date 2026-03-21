#include <iostream>

class LinkQueue
{
private:
	struct Node
	{
		int data_;
		Node* pre_;
		Node* next_;

		Node(int val = 0)
			: data_(val)
			, pre_(nullptr)
			, next_(nullptr)
		{}
	};

	Node* head_;
	int size_;

public:
	LinkQueue()
	{
		head_ = new Node();
		head_->next_ = head_;
		head_->pre_ = head_;
	}

	~LinkQueue()
	{
		Node* p = head_->next_;
		while (p != head_)
		{
			head_->next_ = p->next_;
			delete p;
			p = head_->next_;
		}
		delete head_;
		head_ = nullptr;
	}

public:
	void push(int val)
	{
		Node* node = new Node(val);
		node->next_ = head_;
		node->pre_ = head_->pre_;
		head_->pre_->next_ = node;
		head_->pre_ = node;

		size_++;
	}

	void pop()
	{
		Node* p = head_->next_;
		head_->next_ = p->next_;
		p->next_->pre_ = head_;
		delete p;

		size_--;
	}

	int front() const
	{
		if (head_->next_ == head_)
			throw "THE QUEUE IS EMPTY!";

		return head_->next_->data_;
	}

	int back() const
	{
		if (head_->pre_ == head_)
			throw "THE QUEUE IS EMPTY!";

		return head_->pre_->data_;
	}

	bool empty() const
	{
		return head_->next_ == head_;
	}

	int size() const
	{
		return size_;
	}
};

int main()
{
	LinkQueue dc;
	int arr[] = { 72, 56, 75, 95, 71, 26, 64, 100 };

	for (int v : arr)
	{
		dc.push(v);
	}

	std::cout << dc.size() << "\n";

	while (!dc.empty())
	{
		std::cout << dc.front() << " " << dc.back() << "\n";
		dc.pop();
	}

	std::cout << dc.size() << std::endl;
}

#if 0
class DCLQue
{
private:
	struct Node
	{
		int data_;
		Node* pre_;
		Node* next_;

		Node(int val = 0)
			: data_(val)
			, pre_(nullptr)
			, next_(nullptr)
		{}
	};

	Node* head_;
	Node* rear_;
	int size_;

public:
	DCLQue()
	{
		head_ = new Node();
		head_->pre_ = head_;
		head_->next_ = head_;
		rear_ = head_;
	}

	~DCLQue()
	{
		rear_->next_ = nullptr;
		rear_ = head_;
		while (head_ != nullptr)
		{
			rear_ = head_->next_;
			delete head_;
			head_ = rear_;
		}
	}

public:
	void push(int val)
	{
		Node* node = new Node(val);
		rear_->next_ = node;
		head_->pre_ = node;
		node->next_ = head_;
		node->pre_ = rear_;

		rear_ = rear_->next_;

		size_++;
	}

	void pop()
	{
		if (rear_ == head_)
			throw "THE QUEUE IS EMPTY";

		head_->next_ = head_->next_->next_;
		delete head_->next_->pre_;
		head_->next_->pre_ = head_;

		if (head_->pre_ == head_)
		{
			rear_ = head_;
		}


		size_--;
	}

	int front() const
	{
		if (rear_ == head_)
			throw "THE QUEUE IS EMPTY";

		return head_->next_->data_;
	}

	int back() const
	{
		if (rear_ == head_)
			throw "THE QUEUE IS EMPTY";

		return rear_->data_;
	}

	bool empty() const
	{
		if (rear_ == head_)
			return true;
		else
		{
			return false;
		}
	}

	int size() const
	{
		return size_;
	}
};

int main()
{
	DCLQue dc;
	int arr[] = { 72, 56, 75, 95, 71, 26, 64, 100 };

	for (int v : arr)
	{
		dc.push(v);
	}

	std::cout << dc.size() << "\n";

	while (!dc.empty())
	{
		std::cout << dc.front() << " " << dc.back() << "\n";
		dc.pop();
	}

	std::cout << dc.size() << std::endl;
}
#endif