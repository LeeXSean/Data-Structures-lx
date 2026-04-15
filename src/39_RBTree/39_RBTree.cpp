#include <iostream>

template <typename T>
class RBTree
{
public:
	RBTree(): root_(nullptr) {}
	~RBTree()
	{
		destroy(root_);
	}

	// 红黑树的插入操作
	void insert(const T& val)
	{
		if (root_ == nullptr)
		{
			root_ = new Node(val);
			return;
		}
		
		Node* parent = nullptr;
		Node* cur = root_;
		while (cur != nullptr)
		{
			parent = cur;
			if (cur->data_ > val)
			{
				cur = cur->left_;
			}
			else if (cur->data_ < val)
			{
				cur = cur->right_;
			}
			else
			{
				return;
			}
		}

		cur = new Node(val, parent, nullptr, nullptr, RED);
		if (parent->data_ > val)
		{
			parent->left_ = cur;
		}
		else
		{
			parent->right_ = cur;
		}

		if (GetColor(parent) == RED)
		{
			FixAfterInsert(cur);
		}

	}

	// 红黑树的删除操作
	void remove(const T& val)
	{
		if (root_ == nullptr)
		{
			return;
		}

		Node* cur = root_;
		while (cur != nullptr)
		{
			if (cur->data_ > val)
			{
				cur = cur->left_;
			}
			else if (cur->data_ < val)
			{
				cur = cur->right_;
			}
			else
			{
				break;
			}
		}
		if (cur == nullptr)
		{
			return;
		}

		if (cur->left_ != nullptr && cur->right_ != nullptr)
		{
			Node* pre = cur->left_;
			while (pre->right_ != nullptr)
			{
				pre = pre->right_;
			}
			cur->data_ = pre->data_;
			cur = pre;
		}
		
		Node* child = cur->left_;
		if (child == nullptr)
		{
			child = cur->right_;
		}

		if (child != nullptr)
		{
			child->parent_ = cur->parent_;
			if (cur->parent_ == nullptr)
			{
				root_ = child;
			}
			else
			{
				if (cur->parent_->left_ == cur)
				{
					cur->parent_->left_ = child;
				}
				else
				{
					cur->parent_->right_ = child;
				}
			}

			Color c = GetColor(cur);
			delete cur;

			if (c == BLACK)
			{
				FixAfterRemove(child);
			}
		}
		else  // child == nullptr
		{
			if (cur->parent_ == nullptr)
			{
				delete cur;
				root_ = nullptr;
				return;
			}
			else
			{
				if (GetColor(cur) == BLACK)
				{
					FixAfterRemove(cur);
				}

				if (cur->parent_->left_ == cur)
				{
					cur->parent_->left_ = nullptr;
				}
				else
				{
					cur->parent_->right_ = nullptr;
				}

				delete cur;
			}
		}

		
	}

private:
	// 节点的颜色
	enum Color
	{
		BLACK,
		RED
	};

	// 节点的结构
	struct Node
	{
		Node(T data = T(), Node* parent = nullptr,
			Node* left = nullptr, Node* right = nullptr,
			Color color = BLACK)
			: data_(data)
			, parent_(parent)
			, left_(left)
			, right_(right)
			, color_(color)
		{}

		T data_;			// 节点储存的数据
		Node* parent_;		// 节点的父指针
		Node* left_;		// 节点的左孩子
		Node* right_;		// 节点的右孩子
		Color color_;		// 节点的颜色
	};

	// 返回节点的颜色
	Color GetColor(Node* node)
	{
		if (node == nullptr) { return BLACK; }
		return node->color_;
	}
	// 设置节点的颜色
	void SetColor(Node* node, Color color)
	{
		if (node == nullptr) { return; }
		node->color_ = color;
	}
	// 返回节点的父指针
	Node* GetParent(Node* node)
	{
		if (node == nullptr) { return nullptr; }
		return node->parent_;
	}
	// 返回节点的左孩子
	Node* GetLeft(Node* node)
	{
		if (node == nullptr) { return nullptr; }
		return node->left_;
	}
	// 返回节点的右孩子
	Node* GetRight(Node* node)
	{
		if (node == nullptr) { return nullptr; }
		return node->right_;
	}

	// 左旋转操作
	void LeftRotate(Node* node)
	{
		Node* child = node->right_;
		child->parent_ = node->parent_;
		if (node->parent_ == nullptr)
		{
			root_ = child;
		}
		else
		{
			if (node->parent_->left_ == node)
			{
				node->parent_->left_ = child;
			}
			else
			{
				node->parent_->right_ = child;
			}
		}

		node->right_ = child->left_;
		if (child->left_ != nullptr)
		{
			child->left_->parent_ = node;
		}

		child->left_ = node;
		node->parent_ = child;
	}
	// 右旋转操作
	void RightRotate(Node* node)
	{
		Node* child = node->left_;
		child->parent_ = node->parent_;
		if (node->parent_ == nullptr)
		{
			root_ = child;
		}
		else
		{
			if (node->parent_->left_ == node)
			{
				node->parent_->left_ = child;
			}
			else
			{
				node->parent_->right_ = child;
			}
		}

		node->left_ = child->right_;
		if (child->right_ != nullptr)
		{
			child->right_->parent_ = node;
		}

		child->right_ = node;
		node->parent_ = child;
	}
	// 插入调整操作
	void FixAfterInsert(Node* node)
	{
		while (GetColor(GetParent(node)) == RED)
		{
			if (GetLeft(GetParent(GetParent(node))) == GetParent(node))
			{
				Node* uncle = GetRight(GetParent(GetParent(node)));

				if (GetColor(uncle) == RED)
				{
					SetColor(GetParent(GetParent(node)), RED);
					SetColor(GetParent(node), BLACK);
					SetColor(uncle, BLACK);
					// 此时顶部为红色，需要继续向上
					node = GetParent(GetParent(node));
				}
				else
				{
					if (GetRight(GetParent(node)) == node)
					{
						node = GetParent(node);
						LeftRotate(node);
					}

					SetColor(GetParent(GetParent(node)), RED);
					SetColor(GetParent(node), BLACK);
					RightRotate(GetParent(GetParent(node)));
					// 此时顶部节点为黑色，无需继续向上
					break;
				}
			}
			else
			{
				Node* uncle = GetLeft(GetParent(GetParent(node)));

				if (GetColor(uncle) == RED)
				{
					SetColor(GetParent(GetParent(node)), RED);
					SetColor(GetParent(node), BLACK);
					SetColor(uncle, BLACK);
					// 此时顶部为红色，需要继续向上
					node = GetParent(GetParent(node));
				}
				else
				{
					if (GetLeft(GetParent(node)) == node)
					{
						node = GetParent(node);
						RightRotate(node);
					}

					SetColor(GetParent(GetParent(node)), RED);
					SetColor(GetParent(node), BLACK);
					LeftRotate(GetParent(GetParent(node)));
					// 此时顶部节点为黑色，无需继续向上
					break;
				}
			}
		}

		// 将根节点固定设为黑色
		SetColor(root_, BLACK);
	}
	// 删除调整操作
	void FixAfterRemove(Node* node)
	{
		while (node != root_ && GetColor(node) == BLACK)
		{
			if (GetLeft(GetParent(node)) == node)
			{
				Node* brother = GetRight(GetParent(node));

				if (GetColor(brother) == RED)
				{
					SetColor(GetParent(node), RED);
					SetColor(brother, BLACK);
					brother = GetLeft(brother);
					LeftRotate(GetParent(node));
				}

				if (GetColor(GetLeft(brother)) == BLACK
					&& GetColor(GetRight(brother)) == BLACK)
				{
					SetColor(brother, RED);
					node = GetParent(node);
				}
				else
				{
					if (GetColor(GetRight(brother)) == BLACK)
					{
						SetColor(GetLeft(brother), BLACK);
						SetColor(brother, RED);
						RightRotate(brother);
						brother = GetParent(brother);
					}

					SetColor(brother, GetColor(GetParent(node)));
					SetColor(GetParent(node), BLACK);
					SetColor(GetRight(brother), BLACK);
					LeftRotate(GetParent(node));
					break;
				}
			}
			else // GetRight(GetParent(node)) == node
			{
				Node* brother = GetLeft(GetParent(node));

				if (GetColor(brother) == RED)
				{
					SetColor(GetParent(node), RED);
					SetColor(brother, BLACK);
					brother = GetRight(brother);
					RightRotate(GetParent(node));
				}

				if (GetColor(GetLeft(brother)) == BLACK
					&& GetColor(GetRight(brother)) == BLACK)
				{
					SetColor(brother, RED);
					node = GetParent(node);
				}
				else
				{
					if (GetColor(GetLeft(brother)) == BLACK)
					{
						SetColor(GetRight(brother), BLACK);
						SetColor(brother, RED);
						LeftRotate(brother);
						brother = GetParent(brother);
					}

					SetColor(brother, GetColor(GetParent(node)));
					SetColor(GetParent(node), BLACK);
					SetColor(GetLeft(brother), BLACK);
					RightRotate(GetParent(node));
					break;
				}
			}
		}

		SetColor(node, BLACK);
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

	Node* root_;	// 指向红黑树的根节点
};

int main()
{
	RBTree<int> rbt;
	for (int i = 1; i < 11; i++)
	{
		rbt.insert(i);
	}

	return 0;
}