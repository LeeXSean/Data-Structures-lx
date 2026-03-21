#include <iostream>
#include <functional>
#include <stack>
#include <queue>

// BST树 不含重复元素
template<typename T, typename Cmp = std::less<T>>
class BSTree
{
public:
	BSTree() : root_(nullptr) {}
	~BSTree() 
	{
		destroy(root_);
	}

public:
	// 非递归增加元素
	void n_insert(const T& data)
	{
		if (root_ == nullptr)
		{
			root_ = new Node(data);
			return;
		}

		Node* father = nullptr;			// 指向父节点
		Node* cur = root_;				// 指向当前节点
		while (cur != nullptr)
		{
			// 判断输入参数与当前节点对象的大小关系
			if (cmp_(data, cur->data_))
			{
				father = cur;
				cur = cur->left_;
			}
			else if (cmp_(cur->data_, data))
			{
				father = cur;
				cur = cur->right_;
			}
			else
			{
				// 不含重复元素
				return;
			}
		}

		if (cmp_(data, father->data_))
		{
			father->left_ = new Node(data);
		}
		else
		{
			father->right_ = new Node(data);
		}
	}

	// 递归增加元素                   
	void insert(const T& data)
	{
		root_ = insert(root_, data);
	}

	// 非递归删除元素
	void n_remove(const T& data)
	{
		Node* father = nullptr;			// 指向父节点
		Node* cur = root_;				// 指向当前节点
		while (cur != nullptr)
		{
			// 判断输入参数与当前节点对象的大小关系
			if (cmp_(data, cur->data_))
			{
				father = cur;
				cur = cur->left_;
			}
			else if (cmp_(cur->data_, data))
			{
				father = cur;
				cur = cur->right_;
			}
			else
			{
				// 不含重复元素
				break;
			}
		}

		if (cur == nullptr)
		{
			return;
		}

		// 如果待删除节点有两个子节点，选取前驱节点覆盖待删除节点的值，将问题转化为删除前驱节点
		if (cur->left_ != nullptr && cur->right_ != nullptr)
		{
			Node* pre = cur->left_;
			father = cur;
			while (pre->right_ != nullptr)
			{
				father = pre;
				pre = pre->right_;
			}
			cur->data_ = pre->data_;	// 前驱节点的值覆盖待删除节点的值
			cur = pre;					// 当前节点指向前驱节点，将问题转化为删除前驱节点
		}

		// 如果待删除节点有一个子节点或无子节点（例如前驱节点）
		Node* child = cur->left_;
		if (child == nullptr)
		{
			child = cur->right_;
		}
		// 处理边界情况，如果只有两个节点，且删除根节点时，会引用空指针，还会丢失BST树的入口地址
		if (father == nullptr)
		{
			root_ = child;
		}
		else
		{
			// 将子节点的地址写入父节点的地址域
			if (father->left_ == cur)
			{
				father->left_ = child;
			}
			else
			{
				father->right_ = child;
			}
		}

		// 释放待删除节点的内存
		delete cur;
	}

	// 递归删除元素
	void remove(const T& data)
	{
		root_ = remove(root_, data);
	}

	// 非递归查询元素
	bool n_query(const T& data) const
	{
		Node* cur = root_;				// 指向当前节点
		while (cur != nullptr)
		{
			// 判断输入参数与当前节点对象的大小关系
			if (cmp_(data, cur->data_))
			{
				cur = cur->left_;
			}
			else if (cmp_(cur->data_, data))
			{
				cur = cur->right_;
			}
			else
			{
				// 不含重复元素
				return true;
			}
		}

		return false;
	}

	// 递归查询元素
	bool query(const T& data) const
	{
		return query(root_, data);
	}

	// 非递归前序遍历 VLR
	void n_preOrder() const
	{
		std::cout << "[非递归]前序遍历：";

		if (root_ == nullptr)
		{
			return;
		}

		std::stack<Node*> s;
		s.push(root_);

		while (!s.empty())
		{
			Node* top = s.top();
			s.pop();

			std::cout << top->data_ << " ";

			if (top->right_ != nullptr)
			{
				s.push(top->right_);
			}
			if (top->left_ != nullptr)
			{
				s.push(top->left_);
			}
		}

		std::cout << std::endl;
	}

	// 递归前序遍历 VLR
	void preOrder() const
	{
		std::cout << "[递归]前序遍历：";
		preOrder(root_);
		std::cout << std::endl;
	}
	
	// 非递归中序遍历 LVR
	void n_inOrder() const
	{
		std::cout << "[非递归]中序遍历：";
		
		if (root_ == nullptr)
		{
			return;
		}

		std::stack<Node*> s;
		Node* cur = root_;
		
		while (cur != nullptr || !s.empty())
		{
			if (cur != nullptr)
			{
				s.push(cur);
				cur = cur->left_;
			}
			else
			{
				Node* top = s.top();
				s.pop();
				std::cout << top->data_ << " ";
				cur = top->right_;
			}
		}
		std::cout << std::endl;
	}

	// 递归中序遍历 LVR
	void inOrder() const
	{
		std::cout << "[递归]中序遍历：";
		inOrder(root_);
		std::cout << std::endl;
	}

	// 非递归后序遍历 LRV
	void n_postOrder() const
	{
		std::cout << "[非递归]后序遍历：";

		if (root_ == nullptr)
		{
			return;
		}

		std::stack<Node*> s;
		std::stack<Node*> r;
		s.push(root_);

		while (!s.empty())
		{
			Node* top = s.top();
			s.pop();

			r.push(top);

			if (top->left_ != nullptr)
			{
				s.push(top->left_);
			}
			if (top->right_ != nullptr)
			{
				s.push(top->right_);
			}
		}

		while (!r.empty())
		{
			std::cout << r.top()->data_ << " ";
			r.pop();
		}

		std::cout << std::endl;
	}

	// 递归后序遍历 LRV
	void postOrder() const
	{
		std::cout << "[递归]后序遍历：";
		postOrder(root_);
		std::cout << std::endl;
	}

	// 非递归层序遍历
	void n_levelOrder() const
	{
		std::cout << "[非递归]层序遍历：";
		if (root_ == nullptr)
		{
			return;
		}

		std::queue<Node*> que;
		que.push(root_);

		while (!que.empty())
		{
			Node* front = que.front();
			que.pop();

			std::cout << front->data_ << " ";

			if (front->left_ != nullptr)
			{
				que.push(front->left_);
			}
			if (front->right_ != nullptr)
			{
				que.push(front->right_);
			}
		}

		std::cout << std::endl;
	}

	// 递归层序遍历
	void levelOrder() const
	{
		std::cout << "[递归]层序遍历：";
		int h = height(root_);
		for (int i = 0; i < h; i++)
		{
			levelOrder(root_, i);
		}
		std::cout << std::endl;
	}

	// 递归求二叉树层数
	int height() const
	{
		return height(root_);
	}

	// 递归求二叉树节点数
	int number() const
	{
		return number(root_);
	}
private:
	// 定义节点的数据结构
	struct Node
	{
		Node(T data = T())
			: data_(data)
			, left_(nullptr)
			, right_(nullptr)
		{}

		T data_;						// 当前节点存储的对象
		Node* left_;					// 左子节点地址
		Node* right_;					// 右子节点地址
	};

	// 递归增加元素封装
	Node* insert(Node* node, const T& data)
	{
		// 递归结束的条件，找到插入节点的位置，生成新节点并返回新节点的地址
		if (node == nullptr)
		{
			return new Node(data);
		}

		if (cmp_(data, node->data_))
		{
			// 更新左子树地址域
			node->left_ = insert(node->left_, data);
		}
		else if (cmp_(node->data_, data))
		{
			// 更新右子树地址域
			node->right_ = insert(node->right_, data);
		}
		// 更新地址域
		return node;
	}

	// 递归查询元素封装
	bool query(Node* node, const T& data) const
	{
		if (node == nullptr)
		{
			return false;
		}

		if (cmp_(data, node->data_))
		{
			return query(node->left_, data);
		}
		else if (cmp_(node->data_, data))
		{
			return query(node->right_, data);
		}
		else
		{
			return true;
		}
	}

	// 递归删除元素封装
	Node* remove(Node* node, const T& data)
	{
		// 递归结束的条件，找到待删除节点的位置
		if (node == nullptr)
		{
			return nullptr;
		}

		if (cmp_(data, node->data_))
		{
			// 更新左子树地址域
			node->left_ = remove(node->left_, data);
		}
		else if (cmp_(node->data_, data))
		{
			// 更新右子树地址域
			node->right_ = remove(node->right_, data);
		}
		else
		{
			// 如果待删除节点有两个子节点，选取前驱节点覆盖待删除节点的值，将问题转化为删除前驱节点
			if (node->left_ != nullptr && node->right_ != nullptr)
			{
				Node* pre = node->left_;
				while (pre->right_ != nullptr)
				{
					pre = pre->right_;
				}
				node->data_ = pre->data_;
				// 转化为：在左子树中，递归删除那个前驱节点
				node->left_ = remove(node->left_, pre->data_);
			}
			else
			{
				// 如果待删除节点有一个子节点或无子节点（例如前驱节点）
				Node* child = node->left_;
				if (child == nullptr)
				{
					child = node->right_;
				}

				// 释放待删除节点的内存
				delete node;

				return child;
			}
		}

		// 更新地址域
		return node;
	}

	// 递归前序遍历封装 VLR
	void preOrder(const Node* node) const
	{
		if (node == nullptr)
		{
			return;
		}

		std::cout << node->data_ << " ";
		preOrder(node->left_);
		preOrder(node->right_);
	}

	// 递归中序遍历封装 LVR
	void inOrder(const Node* node) const
	{
		if (node == nullptr)
		{
			return;
		}

		inOrder(node->left_);
		std::cout << node->data_ << " ";
		inOrder(node->right_);
	}

	// 递归后序遍历封装 LRV
	void postOrder(const Node* node) const
	{
		if (node == nullptr)
		{
			return;
		}

		postOrder(node->left_);
		postOrder(node->right_);
		std::cout << node->data_ << " ";
	}

	// 递归层序遍历封装
	void levelOrder(const Node* node, int i) const
	{
		if (node == nullptr)
		{
			return;
		}

		if (i == 0)
		{
			std::cout << node->data_ << " ";
		}

		levelOrder(node->left_, i-1);
		levelOrder(node->right_, i-1);
	}

	// 递归求二叉树层数封装
	int height(const Node* node) const
	{
		if (node == nullptr)
		{
			return 0;
		}

		int left = height(node->left_);
		int right = height(node->right_);

		return left > right? left + 1 : right + 1;
	}

	// 递归求二叉树节点数封装
	int number(const Node* node) const
	{
		if (node == nullptr)
		{
			return 0;
		}

		int left = number(node->left_);
		int right = number(node->right_);

		return left + right + 1;
	}

	// 递归析构每个节点
	void destroy(Node* node)
	{
		if (node == nullptr)
		{
			return;
		}

		destroy(node->left_);
		destroy(node->right_);
		delete node;
	}

	Node* root_;						// 根节点地址
	Cmp cmp_;							// 比较函数
};


int main()
{
	BSTree<int> bst;
	int arr[] = { 58, 47, 69, 32, 21, 56, 99, 78 };

	for (int v : arr)
	{
		bst.insert(v);
	}

	bst.preOrder();
	bst.n_preOrder();
	bst.inOrder();
	bst.n_inOrder();
	bst.postOrder();
	bst.n_postOrder();
	bst.levelOrder();
	bst.n_levelOrder();

	std::cout << "二叉树高度：" << bst.height() << "\n";
	std::cout << "二叉树节点数目：" << bst.number() << "\n";
	
	std::cout << bst.query(56) << "\n";
	bst.remove(56);
	std::cout << bst.query(56) << std::endl;
}