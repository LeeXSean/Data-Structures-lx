#include <iostream>


// 节点类型
struct Node
{
	int data_;
	Node* next_;
	Node(int data = 0) : data_(data), next_(nullptr) {}
};

// 单链表
class Clink
{
public:
	Clink()
	{
		// head_初始化指向头节点
		head_ = new Node();
	}
	~Clink()
	{
		Node* p = head_;
		while (p != nullptr)
		{
			head_ = head_->next_;
			delete p;
			p = head_;
		}
	}
	// 链表尾插法 O(n) 也可定义tail_尾指针 O(1)
	void InsertTail(int val)
	{
		// 寻找尾节点
		Node* p = head_;
		while (p->next_ != nullptr)
		{
			p = p->next_;
		}

		// 构造新节点
		Node* node = new Node(val);

		// 将新节点挂在尾节点上
		p->next_ = node;
	}

	// 链表头插法 O(1)
	void InsertHead(int val)
	{
		Node* node = new Node(val);
		node->next_ = head_->next_;
		head_->next_ = node;
	}

	// 删除链表中出现的第一个指定值节点 O(n)
	void Remove(int val)
	{
		Node* p = head_->next_;
		Node* q = head_;
		while (p != nullptr)
		{
			if (p->data_ == val)
			{
				// 删除一个节点本身的操作是O(1)
				q->next_ = p->next_;
				delete p;
				return;
			}
			else
			{
				q = p;
				p = p->next_;
			}
		}
	}

	// 删除链表中出现的所有指定值节点 O(n)
	void RemoveAll(int val)
	{
		Node* p = head_->next_;
		Node* q = head_;
		while (p != nullptr)
		{
			if (p->data_ == val)
			{
				q->next_ = p->next_;
				delete p;
				p = q->next_;
			}
			else
			{
				q = p;
				p = p->next_;
			}
		}
	}

	// 搜索 O(n)
	bool Find(int val)
	{
		Node* p = head_->next_;
		while (p != nullptr)
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

	// 打印链表
	void Show()
	{
		Node* p = head_->next_;
		while (p != nullptr)
		{
			std::cout << p->data_ << " ";
			p = p->next_;
		}
		std::cout << std::endl;
	}
private:
	// 头指针
	Node* head_;
	friend void ReverseLink(Clink& link);
	friend bool GetLastKNode(Clink& link, int k, int& val);
	friend void MergeLink(Clink& link1, Clink& link2);
	friend bool FindCircle(Clink& link, int& val);
};

// 逆序链表
void ReverseLink(Clink& link)
{
	Node* head = link.head_;
	Node* p = head->next_;
	if (p == nullptr)
	{
		return;
	}

	head->next_ = nullptr;
	while (p != nullptr)
	{
		Node* q = p->next_;
		p->next_ = head->next_;
		head->next_ = p;
		p = q;
	}
}

// 链表倒数第k个节点
bool GetLastKNode(Clink& link, int k, int& val)
{
	if (k < 1)
	{
		return false;
	}
	Node* head = link.head_;
	Node* pre = head;
	Node* p = head;
	for (int i = 0; i < k; i++)
	{
		p = p->next_;
		if (p == nullptr)
		{
			return false;
		}
	}
	while (p != nullptr)
	{
		pre = pre->next_;
		p = p->next_;
	}
	val = pre->data_;
	return true;
}

// 合并两个有序链表
void MergeLink(Clink& link1, Clink& link2)
{
	Node* p = link1.head_->next_;
	Node* q = link2.head_->next_;
	Node* last = link1.head_;
	link2.head_->next_ = nullptr;

	while (p != nullptr && q != nullptr)
	{
		if (p->data_ < q->data_)
		{
			last->next_ = p;
			p = p->next_;
		}
		else
		{
			last->next_ = q;
			q = q->next_;
		}
		last = last->next_;
	}

	if (p != nullptr)
	{
		last->next_ = p;
	}
	else
	{
		last->next_ = q;
	}
}

// 判断链表是否存在环，返回环的入口节点值
bool FindCircle(Node* head, int& val)
{
	Node* fast = head;
	Node* slow = head;
	while (fast != nullptr && fast->next_ != nullptr)
	{
		slow = slow->next_;
		fast = fast->next_->next_;

		if (fast == slow)
		{
			fast = head;
			while (fast != slow)
			{
				fast = fast->next_;
				slow = slow->next_;
			}
			val = slow->data_;
			return true;
		}
	}
	return false;
	
}

// 判断两个链表是否相交，返回相交的节点值
bool FindMerge(Node* head1, Node* head2, int& val)
{
	int cnt1 = 0; int cnt2 = 0;
	Node* p = head1; 
	Node* q = head2;

	while (p != nullptr)
	{
		p = p->next_;
		cnt1 += 1;
	}
	while (q != nullptr)
	{
		q = q->next_;
		cnt2 += 1;
	}

	p = head1;
	q = head2;
	if (cnt1 > cnt2)
	{
		int offset = cnt1 - cnt2;
		while (offset-- > 0)
		{
			p = p->next_;
		}
	}
	else
	{
		int offset = cnt2 - cnt1;
		while (offset-- > 0)
		{
			q = q->next_;
		}
	}

	while (p != nullptr && q != nullptr)
	{
		if (p == q)
		{
			val = q->data_;
			return true;
		}
		else
		{
			p = p->next_;
			q = q->next_;
		}
	}
	return false;
}

int main()
{
	int val;
	Node head1;
	Node n11(25), n12(37), n13(45), n14(63), n15(21), n16(68), n17(71);
	head1.next_ = &n11;
	n11.next_ = &n12;
	n12.next_ = &n13;
	n13.next_ = &n14;
	n14.next_ = &n15;
	n15.next_ = &n16;
	n16.next_ = &n17;

	Node head2;
	Node n21(25), n22(37), n23(45), n24(63), n25(21), n26(68), n27(71);
	head2.next_ = &n21;
	n21.next_ = &n22;
	n22.next_ = &n23;
	n23.next_ = &n24;
	n24.next_ = &n25;
	n25.next_ = &n26;
	n26.next_ = &n27;
	n26.next_ = &n17;


	if (FindMerge(&head1, &head2, val))
	{
		std::cout << "相交节点的值是 " << val << std::endl;
	}
	else
	{
		std::cout << "没有相交" << std::endl;
	}
}

#if 0
int main()
{
	int val;
	Node head;
	Node n1(25), n2(37), n3(45), n4(63), n5(21), n6(68), n7(71);
	head.next_ = &n1;
	n1.next_ = &n2;
	n2.next_ = &n3;
	n3.next_ = &n4;
	n4.next_ = &n5;
	n5.next_ = &n6;
	n6.next_ = &n7;

	
	if (FindCircle(&head, val))
	{
		std::cout << "环的起始节点是 " << val << std::endl;
	}
	else
	{
		std::cout << "没有环" << std::endl;
	}
}
#endif

// 合并两个有序列表测试
#if 0
int main()
{
	int arr[] = { 12, 23, 34, 57, 69, 72, 81, 93, 158 };
	int brr[] = { 13, 26, 31, 52, 67, 75, 89, 109 };

	Clink link1;
	Clink link2;

	for (int v : arr)
	{
		link1.InsertTail(v);
	}

	for (int v : brr)
	{
		link2.InsertTail(v);
	}

	link1.Show();
	link2.Show();

	MergeLink(link1, link2);
	link1.Show();
	link2.Show();

}
#endif

// 逆序和倒数第k个节点测试
#if 0
int main()
{
	Clink link1;
	srand(time(0));
	for (int i = 0; i < 10; i++)
	{
		int val = rand() % 100;
		link1.InsertTail(val);
	}
	link1.Show();

	ReverseLink(link1);
	link1.Show();

	int kval;
	int k = 8;
	if (GetLastKNode(link1, k, kval))
	{
		std::cout << "倒数第 " << k << " 个节点的值为 " << kval << std::endl;
	}
}
#endif