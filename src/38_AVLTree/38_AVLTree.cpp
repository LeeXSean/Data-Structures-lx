#include <iostream>
#include <algorithm>

// AVL树
template<typename T>
class AVLTree
{
public:
	AVLTree()
		: root_(nullptr)
	{}

	~AVLTree()
	{
		destroy(root_);
		root_ = nullptr;
	}

	void insert(const T& data)
	{
		root_ = insert(root_, data);
	}

	void remove(const T& data)
	{
		root_ = remove(root_, data);
	}

	void midList() const
	{
		inOrder(root_);
		std::cout << "\n";
	}
private:
	// 节点
	struct Node
	{
		Node (T data = T())
			: data_(data)
			, left_(nullptr)
			, right_(nullptr)
			, height_(1)
		{}

		T data_;
		Node* left_;
		Node* right_;
		int height_;
	};

	// 递归中序遍历
	void inOrder(Node* node) const
	{
		if (node == nullptr)
		{
			return;
		}

		inOrder(node->left_);
		std::cout << node->data_ << " ";
		inOrder(node->right_);
	}

	// 递归增加节点
	Node* insert(Node* node, const T& data)
	{
		if (node == nullptr)
		{
			node = new Node(data);
			return node;
		}

		if (node->data_ > data)
		{
			node->left_ = insert(node->left_, data);
		}
		else if (node->data_ < data)
		{
			node->right_ = insert(node->right_, data);
		}
		else
		{
			return node;
		}

		updateHeight(node);
		return balance(node);
	}

	// 递归删除节点
	Node* remove(Node* node, const T& data)
	{
		if (node == nullptr)
		{
			return node;
		}

		if (node->data_ > data)
		{
			node->left_ = remove(node->left_, data);
		}
		else if (node->data_ < data)
		{
			node->right_ = remove(node->right_, data);
		}
		else
		{
			// 情况一 待删除节点有两个子节点，将情况一转为情况二
			if (node->right_ != nullptr && node->left_ != nullptr)
			{
				// 如果左子树高或高度相等，则删除前驱节点
				if (height(node->left_) >= height(node->right_))
				{
					Node* pre = node->left_;
					while (pre->right_ != nullptr)
					{
						pre = pre->right_;
					}

					node->data_ = pre->data_;
					node->left_ = remove(node->left_, pre->data_);
				}
				// 如果右子树高，则删除后继节点
				else
				{
					Node* post = node->right_;
					while (post->left_ != nullptr)
					{
						post = post->left_;
					}

					node->data_ = post->data_;
					node->right_ = remove(node->right_, post->data_);
				}
				
			}
			// 情况二 待删除节点只有一个子节点
			else
			{
				Node* cur = node;
				node = (node->left_ == nullptr) ? node->right_ : node->left_;

				delete cur;

				return node;
			}
		}

		updateHeight(node);
		return balance(node);
	}

	// 递归析构
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

	// 根据不同情况进行平衡操作
	Node* balance(Node* node)
	{
		int dis = height(node->left_) - height(node->right_);
		if (dis > 1)
		{
			Node* cur = node->left_;
			if (height(cur->left_) >= height(cur->right_))
			{
				return rightRotate(node);
			}
			else if (height(cur->left_) < height(cur->right_))
			{
				return leftBalance(node);
			}
		}
		else if (dis < -1 )
		{
			Node* cur = node->right_;
			if (height(cur->left_) <= height(cur->right_))
			{
				return leftRotate(node);
			}
			else if (height(cur->left_) > height(cur->right_))
			{
				return rightBalance(node);
			}
		}
		return node;
	}

	// 节点的高度
	int height(Node* node)
	{
		return node == nullptr ? 0 : node->height_;
	}

	// 更新节点高度
	void updateHeight(Node* node)
	{
		node->height_ = std::max(height(node->left_), height(node->right_)) + 1;
	}

	// 右旋转操作 以节点Node为轴做右旋转操作
	Node* rightRotate(Node* node)
	{
		Node* child = node->left_;
		node->left_ = child->right_;
		child->right_ = node;

		updateHeight(node);
		updateHeight(child);

		return child;
	}

	// 左旋转操作 以节点Node为轴做左旋转操作
	Node* leftRotate(Node* node)
	{
		Node* child = node->right_;
		node->right_ = child->left_;
		child->left_ = node;

		updateHeight(node);
		updateHeight(child);

		return child;
	}

	// 左平衡操作 左-右旋转
	Node* leftBalance(Node* node)
	{
		node->left_ = leftRotate(node->left_);
		return rightRotate(node);
	}

	// 右平衡操作 右-左旋转
	Node* rightBalance(Node* node)
	{
		node->right_ = rightRotate(node->right_);
		return leftRotate(node);
	}

	Node* root_;
};

int main()
{
	AVLTree<int> avl;
	for (int i = 1; i < 10; i++)
	{
		avl.insert(i);
	}

	avl.midList();
	avl.remove(9);
	avl.remove(3);
	avl.remove(5);
	avl.midList();

	return 0;
}