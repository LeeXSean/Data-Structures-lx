#include <iostream>

struct Node
{
	int data_;
	Node* next_;

	Node(int val = 0) : data_(val), next_(nullptr) {}
};

void Joseph(Node* head, int k, int m)
{
	Node* p = head;
	Node* q = head;
	
	while (q->next_ != p)
	{
		q = q->next_;
	}

	for (int i = 1; i < k; i++)
	{
		p = p->next_;
		q = q->next_;
	}

	while (true)
	{
		for (int i = 1; i < m; i++)
		{
			p = p->next_;
			q = q->next_;
		}
		std::cout << p->data_ << " ";

		if (q == p)
		{
			delete p;
			q = p = nullptr;
			std::cout << std::endl;
			break;
		}

		q->next_ = p->next_;
		delete p;
		p = q->next_;
	}
}

int main()
{
	Node* head = new Node(1);
	Node* n2 = new Node(2);
	Node* n3 = new Node(3);
	Node* n4 = new Node(4);
	Node* n5 = new Node(5);
	Node* n6 = new Node(6);
	Node* n7 = new Node(7);
	Node* n8 = new Node(8);

	head->next_ = n2;
	n2->next_ = n3;
	n3->next_ = n4;
	n4->next_ = n5;
	n5->next_ = n6;
	n6->next_ = n7;
	n7->next_ = n8;
	n8->next_ = head;

	Joseph(head, 5, 3);
}

#if 0
class CircleLink
{
private:
	struct Node
	{
		int data_;
		Node* next_;

		Node(int val = 0): data_(val), next_(nullptr) {}
	};

	Node* head_;
	Node* tail_;

public:
	CircleLink()
	{
		head_ = new Node();
		head_->next_ = head_;
		tail_ = head_;
	}
	~CircleLink()
	{
		tail_->next_ = nullptr;
		while (head_ != nullptr)
		{
			tail_ = head_;
			head_ = head_->next_;
			delete tail_;
		}
		tail_ = nullptr;
	}

	// 尾插法
	void InsertTail(int val)
	{
		Node* node = new Node(val);
		node->next_ = head_;
		tail_->next_ = node;
		tail_ = node;
	}

	// 头插法
	void InsertHead(int val)
	{
		Node* node = new Node(val);
		node->next_ = head_->next_;
		head_->next_ = node;
		if (node->next_ == head_)
		{
			tail_ = node;
		}
	}

	// 删除一个节点
	void Remove(int val)
	{
		Node* p = head_->next_;
		Node* q = head_;
		while (p != head_)
		{
			if (p->data_ == val)
			{
				q->next_ = p->next_;
				delete p;
				if (q->next_ == head_)
				{
					tail_ = q;
				}
				return;
			}
			else
			{
				q = q->next_;
				p = p->next_;
			}
		}
	}

	// 查询
	bool Find(int val)
	{
		Node* p = head_->next_;
		while (p != head_)
		{
			if (p->data_ == val)
			{
				return true;
			}
			else
			{
				p = p->next_;
			}
		}
		return false;
	}

	// 打印
	void Show()
	{
		Node* p = head_->next_;
		while (p != head_)
		{
			std::cout << p->data_ << " ";
			p = p->next_;
		}
		std::cout << std::endl;
	}
};

int main()
{
	CircleLink Clink;
	srand(time(0));

	Clink.InsertHead(100);

	for (int i = 0; i < 10; i++)
	{
		Clink.InsertTail(rand() % 100);
	}

	Clink.InsertTail(200);

	Clink.Show();

	Clink.Remove(100);
	
	Clink.Show();
}

#endif