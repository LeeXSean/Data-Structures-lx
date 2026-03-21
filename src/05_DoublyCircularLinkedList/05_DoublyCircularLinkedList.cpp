#include <iostream>

struct Node
{
	int data_;
	Node* pre_;
	Node* next_;

	Node(int data = 0)
		: data_(data)
		, pre_(nullptr)
		, next_(nullptr)
	{ }

};

class DoubleCircleLink
{
public:
	DoubleCircleLink()
	{
		head_ = new Node();
		head_->pre_ = head_;
		head_->next_ = head_;
	}

	~DoubleCircleLink()
	{
		Node* p = head_->next_;
		while (p != head_)
		{
			head_->next_ = p->next_;
			p->next_->pre_ = head_;
			delete p;
			p = head_->next_;
		}
		delete head_;
		head_ = nullptr;
	}

public:
	// 尾插法
	void InsertTail(int val)
	{
		Node* node = new Node(val);
		Node* p = head_->pre_;
		p->next_ = node;
		node->pre_ = p;
		node->next_ = head_;
		head_->pre_ = node;
	}

	// 头插法
	void InsertHead(int val)
	{
		Node* node = new Node(val);
		node->next_ = head_->next_;
		node->pre_ = head_;
		head_->next_->pre_ = node;
		head_->next_ = node;
	}

	// 删除
	void Remove(int val)
	{
		Node* p = head_->next_;
		while (p != head_)
		{
			if (p->data_ == val)
			{
				p->pre_->next_ = p->next_;
				p->next_->pre_ = p->pre_;
				Node* next = p->next_;
				delete p;
				p = next;
			}
			else
			{
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
			p = p->next_;
		}
		return false;
	}

	// 打印
	void Show() const
	{
		Node* p = head_->next_;
		while (p != head_)
		{
			std::cout << p->data_ << " ";
			p = p->next_;
		}
		std::cout << std::endl;
	}

private:
	Node* head_;
};


int main()
{
	DoubleCircleLink dl;
	
	dl.InsertHead(100);

	dl.InsertTail(12);
	dl.InsertTail(25);
	dl.InsertTail(41);
	dl.InsertTail(12);
	dl.InsertTail(75);
	dl.InsertTail(25);
	dl.InsertTail(67);
	dl.InsertTail(12);

	dl.InsertHead(200);

	dl.Show();

	dl.Remove(12);
	dl.Show();

	int value = 75;
	if (dl.Find(value))
	{
		std::cout << value << "存在" << std::endl;
	}
	else
	{
		std::cout << value << "不存在" << std::endl;
	}
}