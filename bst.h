#pragma once
#include "tree.h"

template<typename T>
class BinarySearchTree : public Tree<T>
{
public:
	void AddNode(const T& val);
	void DeleteNode(const T& val);
	TNodePtr<T> GetMaximumIterative();
	TNodePtr<T> GetMinimumIterative();
	TNodePtr<T> GetMaximumRecursive();
	TNodePtr<T> GetMinimumRecursive();
	TNodePtr<T> LeastCommonAncestor(const T& one, const T& two);
	TNodePtr<T> Find(const T& val);
private:
	TNodePtr<T> AddNode(TNodePtr<T> root, const T& val);
	TNodePtr<T> DeleteNode(TNodePtr<T> root, const T& val);
	TNodePtr<T> GetMaximumRecursive(TNodePtr<T> root);
	TNodePtr<T> GetMinimumRecursive(TNodePtr<T> root);
	
};

template<typename T>
using BST = BinarySearchTree<T>;

template<typename T>
inline void BinarySearchTree<T>::AddNode(const T& val)
{
	//To access base class members in template inheritance, we must use fully qualified name or via this pointer
  //	this->root_ = AddNode(Tree<T>::root_, val);
	//or
	Tree<T>::root_ = AddNode(Tree<T>::root_, val);
}

template<typename T>
inline TNodePtr<T> BinarySearchTree<T>::AddNode(TNodePtr<T> root, const T& val)
{
	if (root == nullptr)
		return Tree<T>::CreateNode(val);
	if (val < root->data_)
	{
		root->left_ = AddNode(root->left_, val);
	}
	else if (val > root->data_)
	{
		root->right_ = AddNode(root->right_, val);
	}
	return root;
}

template<typename T>
inline TNodePtr<T> BinarySearchTree<T>::DeleteNode(TNodePtr<T> root, const T & val)
{
	if (root == nullptr)
		return nullptr;
	if (val < root->data_)
	{
		root->left_ = DeleteNode(root->left_, val);
	}                                                                                      
	else if (val > root->data_)
	{
		root->right_ = DeleteNode(root->right_, val);
	}
	else
	{
		if (root->left_ && root->right_)
		{
			TNodePtr<T> max_from_left = GetMaximumRecursive(root->left_);
			root->data_ = max_from_left->data_;
			root->left_ = DeleteNode(root->left_, max_from_left->data_);
		}
		else
		{
			TNodePtr<T> temp = root;
			if (root->left_ == nullptr)
				root = root->right_;
			else if (root->right_ == nullptr)
				root = root->left_;
			delete temp;
		}
		/*
		//has no child
		if (root->left_ == nullptr && root->right_ == nullptr)
		{
			delete root;
			return nullptr;
		}
		//has one or two child
		if (root->right_)
		{
			TNodePtr<T> min_from_right = GetMinimumRecursive(root->right_);
			root->data_ = min_from_right->data_;
			root->right_ = DeleteNode(root->right_, min_from_right->data_);
		}
		else if (root->left_)
		{
			TNodePtr<T> max_from_left = GetMaximumRecursive(root->left_);
			root->data_ = max_from_left->data_;
			root->left_ = DeleteNode(root->left_, max_from_left->data_);
		}*/
	}
	return root;
}

template<typename T>
inline void BinarySearchTree<T>::DeleteNode(const T & val)
{
	Tree<T>::root_ = DeleteNode(Tree<T>::root_, val);
}

template<typename T>
inline TNodePtr<T> BinarySearchTree<T>::GetMaximumIterative()
{
	TNodePtr<T> root = Tree<T>::root_;
	while (root && root->right_)
	{
		root = root->right_;
	}
	return root;
}

template<typename T>
inline TNodePtr<T> BinarySearchTree<T>::GetMinimumIterative()
{
	TNodePtr<T> root = Tree<T>::root_;
	while (root && root->left_)
	{
		root = root->left_;
	}
	return root;
}

template<typename T>
inline TNodePtr<T> BinarySearchTree<T>::GetMaximumRecursive()
{
	return GetMaximumRecursive(Tree<T>::root_);
}

template<typename T>
inline TNodePtr<T> BinarySearchTree<T>::GetMinimumRecursive()
{
	return GetMinimumRecursive(Tree<T>::root_);
}

template<typename T>
inline TNodePtr<T> BinarySearchTree<T>::LeastCommonAncestor(const T & one, const T & two)
{
	if (Tree<T>::root_ == nullptr)
		return nullptr;
	TNodePtr<T> root = Tree<T>::root_;
	while (true)
	{
		if (root == nullptr)
			return nullptr;
		if (one < root->data_ && root->data_ < two
			|| one > root->data_ && root->data_ > two)
		{
			return root;
		}
		if (one < root->data_)
			root = root->left_;
		else
			root = root->right_;
	}
}



template<typename T>
inline TNodePtr<T> BinarySearchTree<T>::Find(const T & val)
{
	if (Tree<T>::root_ == nullptr)
		return nullptr;
	TNodePtr<T> root = Tree<T>::root_;
	while (root)
	{
		if (root->data_ == val)
		{
			break;
		}
		else if (val < root->data_)
		{
			root = root->left_;
		}
		else
		{
			root = root->right_;
		}
	}
	return root;
}

template<typename T>
inline TNodePtr<T> BinarySearchTree<T>::GetMaximumRecursive(TNodePtr<T> root)
{
	if (root == nullptr)
		return nullptr;
	if (root->right_)
		return GetMaximumRecursive(root->right_);
	return root;
}

template<typename T>
inline TNodePtr<T> BinarySearchTree<T>::GetMinimumRecursive(TNodePtr<T> root)
{
	if (root == nullptr)
		return nullptr;
	if (root->left_)
		return GetMinimumRecursive(root->left_);
	return root;
}

