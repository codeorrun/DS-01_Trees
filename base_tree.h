#pragma once

#include "debug.h"

template<typename T>
struct TreeNode
{
	T data_;
	TreeNode* left_;
	TreeNode* right_;
	static int total_nodes_created_;
	static int total_nodes_destroyed_;
	TreeNode() { ++total_nodes_created_; }
	~TreeNode() { ++total_nodes_destroyed_; };
	static int GetTotalNodesCreated() { return total_nodes_created_; }
	static int GetTotalNodesDestroyed() { return total_nodes_destroyed_; }
};

template<typename T>
int TreeNode<T>::total_nodes_created_ = 0;

template<typename T>
int TreeNode<T>::total_nodes_destroyed_ = 0;

template <typename T>
using TNode = TreeNode<T>;//Alias template

template <typename T>
using TNodePtr = TreeNode<T>*; //Alias template

template <typename T>
class ITree
{
public:
	virtual void AddNode(const T& val) = 0;
	virtual void DeleteNode(const T& val) = 0;
	virtual void InOrderTraversalIterative() = 0;
	virtual void PreOrderTraveralIterative() = 0;
	virtual void PostOrderTravesalIterative() = 0;
	virtual void InOrderTraversalRecursive() = 0;
	virtual void PreOrderTraveralRecursive() = 0;
	virtual void PostOrderTravesalRecursive() = 0;
	virtual void LevelOrderTraversal() = 0;
	virtual int GetHeightIterative() = 0;
	virtual int GetHeightRecursive() = 0;
	virtual int GetDiameter() = 0;
	virtual TNodePtr<T> GetMaximumIterative() = 0;
	virtual TNodePtr<T> GetMinimumIterative() = 0;
	virtual TNodePtr<T> GetMaximumRecursive() = 0;
	virtual TNodePtr<T> GetMinimumRecursive() = 0;
	virtual TNodePtr<T> Find(const T& val) = 0;
	virtual bool Has(const T & val) = 0;
	virtual ~ITree() = 0 {}; //If we don't give a body to this we get this error -> "unresolved external symbol "public: virtual __thiscall ITree<int>::~ITree<int>(void)"
};