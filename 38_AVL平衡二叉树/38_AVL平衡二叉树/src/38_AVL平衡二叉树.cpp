#include <iostream>
#include <cmath>

// AVL树
template<typename T>
class AVLTree
{
public:
private:
	// 节点
	struct Node
	{
		Node (T data = T())
			: data_(data)
			, left_(nullptr)
			, right_(nullptr)
			, height_(0)
		{}

		T data_;
		Node* left_;
		Node* right_;
		int height_;
	};

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