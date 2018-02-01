#pragma once
#include "base_tree.h"
#include <iostream>
#include <queue>
#include <stack>

template <typename T>
class Tree : public ITree<T>
{
protected:
	TNodePtr<T> root_;
public:
	Tree() = default;
	Tree(std::initializer_list<T> l);
	Tree(const Tree&) = delete;
	Tree& operator=(const Tree&) = delete;

	void AddNode(const T& val);
	void DeleteNode(const T& val);
	void InOrderTraversalIterative();
	void PreOrderTraveralIterative();
	void PostOrderTravesalIterative();
	void InOrderTraversalRecursive();
	void PreOrderTraveralRecursive();
	void PostOrderTravesalRecursive();
	void LevelOrderTraversal();
	int GetHeightIterative();
	int GetHeightRecursive();
	int GetDiameter();
	TNodePtr<T> GetMaximumIterative();
	TNodePtr<T> GetMinimumIterative();
	TNodePtr<T> GetMaximumRecursive();
	TNodePtr<T> GetMinimumRecursive();
	TNodePtr<T> LeastCommonAncestor(const T& one, const T& two);
	TNodePtr<T> LeastCommonAncestorBetter(const T& one, const T& two);
	TNodePtr<T> Find(const T& val);
	bool Has(const T & val);
	void PrintStructure();
	const TNodePtr<T> GetRoot() const;
	~Tree();
protected:
	TNodePtr<T> CreateNode(const T& val);
	void DeleteTree(TNodePtr<T> root);
private:
	void InOrderTraversalRecursive(TNodePtr<T> root);
	void PreOrderTraveralRecursive(TNodePtr<T> root);
	void PostOrderTravesalRecursive(TNodePtr<T> root);
	int GetHeightRecursive(TNodePtr<T> root);
	int GetDiameterRecursive(TNodePtr<T> root, int& diameter);
	TNodePtr<T> GetMaximumRecursive(TNodePtr<T> root);
	TNodePtr<T> GetMinimumRecursive(TNodePtr<T> root);
	TNodePtr<T> LeastCommonAncestor(TNodePtr<T> root, const T& one, const T& two);
	TNodePtr<T> LeastCommonAncestorBetter(TNodePtr<T> root, const T& one, const T& two, bool& found_one, bool& found_two);
};

template<typename T>
inline Tree<T>::Tree(std::initializer_list<T> l)
{
	for (auto val : l)
		AddNode(val);
}

template<typename T>
inline void Tree<T>::AddNode(const T & val)
{
	TNodePtr<T> new_node = CreateNode(val);
	if (root_ == nullptr)
	{
		root_ = new_node;
		return;
	}
	TNodePtr<T> root = root_;
	std::queue<TNodePtr<T>> add_queue;
	add_queue.push(root);
	while (!add_queue.empty())
	{
		root = add_queue.front();
		add_queue.pop();
		if (root->left_ == nullptr)
		{
			root->left_ = new_node;
			break;
		}
		else
		{
			add_queue.push(root->left_);
		}
		if (root->right_ == nullptr)
		{
			root->right_ = new_node;
			break;
		}
		else
		{
			add_queue.push(root->right_);
		}
	}
	while (!add_queue.empty())
		add_queue.pop();
}

template<typename T>
static void DeleteDeepestNode(const TNodePtr<T> root, const TNodePtr<T> to_be_deleted)
{
	if (root == nullptr || to_be_deleted == nullptr)
		return;
	TNodePtr<T> temp = root;
	std::queue<TNodePtr<T>> delete_queue;
	delete_queue.push(temp);
	while (!delete_queue.empty())
	{
		temp = delete_queue.front();
		delete_queue.pop();
		if (temp->left_)
		{
			if (temp->left_ == to_be_deleted)
			{
				temp->left_ = nullptr;
				delete to_be_deleted;
				break;
			}
			else
			{
				delete_queue.push(temp->left_);
			}
		}
			
		if (temp->right_)
		{
			if (temp->right_ == to_be_deleted)
			{
				temp->right_ = nullptr;
				delete to_be_deleted;
				break;
			}
			else
			{
				delete_queue.push(temp->right_);
			}
		}
	}
	while (!delete_queue.empty())
		delete_queue.pop();
}

template<typename T>
inline void Tree<T>::DeleteNode(const T & val)
{
	if (root_ == nullptr)
		return;
	TNodePtr<T> root = root_;
	TNodePtr<T> to_be_deleted = nullptr;
	std::queue<TNodePtr<T>> delete_queue;
	delete_queue.push(root);
	while (!delete_queue.empty())
	{
		root = delete_queue.front();
		delete_queue.pop();
		if (root->data_ == val)
		{
			to_be_deleted = root;
		}
		if (root->left_)
			delete_queue.push(root->left_);
		if (root->right_)
			delete_queue.push(root->right_);
	}
	to_be_deleted->data_ = root->data_;
	DeleteDeepestNode(root_, root);
}

template<typename T>
inline void Tree<T>::InOrderTraversalIterative()
{
	if (root_ == nullptr)
		return;
	TNodePtr<T> root = root_;
	std::stack<TNodePtr<T>> my_stack;
	while (true)
	{
		while (root)
		{
			my_stack.push(root);
			root = root->left_;
		}
		if (my_stack.empty())
			break;
		root = my_stack.top();
		my_stack.pop();
		std::cout << root->data_ << " ";
		root = root->right_;
	}
	std::cout << std::endl;
}

template<typename T>
inline void Tree<T>::PreOrderTraveralIterative()
{
	if (root_ == nullptr)
		return;
	TNodePtr<T> root = root_;
	std::stack<TNodePtr<T>> my_stack;
	my_stack.push(root);
	while (!my_stack.empty())
	{
		root = my_stack.top();
		std::cout << root->data_ << " ";
		if (root->right_)
			my_stack.push(root->right_);
		if (root->left_)
			my_stack.push(root->left_);
	}
	std::cout << std::endl;
}

template<typename T>
inline void Tree<T>::PostOrderTravesalIterative()
{
	if (root_ = nullptr)
		return;
	TNodePtr<T> current = root_;
	TNodePtr<T> previous = nullptr;
	std::stack<TNodePtr<T>> my_stack;
	my_stack.push(current);
	while (!my_stack.empty())
	{
		current = my_stack.top();
		if (previous == nullptr //Going down from root
			|| current == previous->left_ //Going down to left subtree
			|| current == previous->right_) //Going down to right subtree
		{
			if (current->left_)
				my_stack.push(current->left_);
			else if (current->right_)
				my_stack.push(current->right_);
		}
		else if (previous == current->left_)
		{//Going up from left subtree
			if (current->right_)
				my_stack.push(current->right_);
		}
		else
		{
			//Going up from right subtree
			std::cout << current->data_;
			my_stack.pop();
		}
		previous = current;
	}
	std::cout << std::endl;
}

template<typename T>
inline void Tree<T>::InOrderTraversalRecursive()
{
	if (root_)
	{
		InOrderTraversalRecursive(root_);
		std::cout << std::endl;
	}
}

template<typename T>
inline void Tree<T>::PreOrderTraveralRecursive()
{
	if (root_)
	{
		PreOrderTraveralRecursive(root_);
		std::cout << std::endl;
	}
}

template<typename T>
inline void Tree<T>::PostOrderTravesalRecursive()
{
	if (root_)
	{
		PostOrderTravesalRecursive(root_);
		std::cout << std::endl;
	}
}

template<typename T>
inline void Tree<T>::LevelOrderTraversal()
{
	if (root_ == nullptr)
		return;
	TNodePtr<T> root = root_;
	std::queue<TNodePtr<T>> my_queue;
	my_queue.push(root);
	while (!my_queue.empty())
	{
		root = my_queue.front();
		my_queue.pop();
		std::cout << root->data_ << " ";
		if (root->left_)
			my_queue.push(root->left_);
		if (root->right_)
			my_queue.push(root->right_);
	}
	std::cout << std::endl;
}

template<typename T>
inline int Tree<T>::GetHeightIterative()
{
	if (root_ == nullptr)
		return 0;
	TNodePtr<T> root = root_;
	std::queue<TNodePtr<T>> my_queue;
	my_queue.push(root);
	my_queue.push(nullptr);
	int height = 0;
	while (!my_queue.empty())
	{
		root = my_queue.front();
		my_queue.pop();
		if (root == nullptr)
		{
			++height;
			if (!my_queue.empty())
				my_queue.push(nullptr);
		}
		else
		{
			if (root->left_)
				my_queue.push(root->left_);
			if (root->right_)
				my_queue.push(root->right_);
		}
	}
	return height;
}

template<typename T>
inline int Tree<T>::GetHeightRecursive()
{
	return GetHeightRecursive(root_);
}

template<typename T>
inline int Tree<T>::GetDiameter()
{
	int diameter = 0;
	GetDiameterRecursive(root_, diameter);
	return diameter;
}

template<typename T>
inline TNodePtr<T> Tree<T>::GetMaximumIterative()
{
	if (root_ == nullptr)
		return nullptr;
	TNodePtr<T> root = root_;
	TNodePtr<T> maximum = root_;
	std::queue<TNodePtr<T>> my_queue;
	my_queue.push(root);
	while (!my_queue.empty())
	{
		root = my_queue.front();
		my_queue.pop();
		if (root->data_ > maximum->data_)
			maximum->data_ = root->data_;
		if (root->left_)
			my_queue.push(root->left_);
		if (root->right_)
			my_queue.push(root->right_);
	}
	return maximum;
}

template<typename T>
inline TNodePtr<T> Tree<T>::GetMinimumIterative()
{
	if (root_ == nullptr)
		return nullptr;
	TNodePtr<T> root = root_;
	TNodePtr<T> minimum = root_;
	std::queue<TNodePtr<T>> my_queue;
	my_queue.push(root);
	while (!my_queue.empty())
	{
		root = my_queue.front();
		my_queue.pop();
		if (root->data_ < minimum->data_)
			minimum->data_ = root->data_;
		if (root->left_)
			my_queue.push(root->left_);
		if (root->right_)
			my_queue.push(root->right_);
	}
	return minimum;
}

template<typename T>
inline TNodePtr<T> Tree<T>::GetMaximumRecursive()
{
	return GetMaximumRecursive(root_);
}

template<typename T>
inline TNodePtr<T> Tree<T>::GetMinimumRecursive()
{
	return GetMinimumRecursive(root_);
}

template<typename T>
inline TNodePtr<T> Tree<T>::LeastCommonAncestor(const T & one, const T & two)
{
	return LeastCommonAncestor(root_, one, two);
}

template<typename T>
inline TNodePtr<T> Tree<T>::LeastCommonAncestor(TNodePtr<T> root, const T & one, const T & two)
{
	if (root == nullptr)
		return nullptr;
	if (root->data_ == one)
		return root;
	if (root->data_ == two)
		return root;
	TNodePtr<T> left = LeastCommonAncestor(root->left_, one, two);
	TNodePtr<T> right = LeastCommonAncestor(root->right_, one, two);
	if (left && right)
		return root;
	return left ? left : right;
}

template<typename T>
inline TNodePtr<T> Tree<T>::LeastCommonAncestorBetter(const T & one, const T & two)
{
	bool found_one = false, found_two = false;
	TNodePtr<T> lca = LeastCommonAncestorBetter(Tree<T>::root_, one, two, found_one, found_two);
	if (found_one && found_two)
		return lca;
	return nullptr;
}

template<typename T>
inline TNodePtr<T> Tree<T>::LeastCommonAncestorBetter(TNodePtr<T> root, const T & one, const T & two, bool & found_one, bool & found_two)
{
	if (root == nullptr)
		return nullptr;
	if (root->data_ == one)
	{
		found_one = true;
		return root;
	}
	if (root->data_ == two)
	{
		found_two = true;
		return root;
	}
	TNodePtr<T> left = LeastCommonAncestorBetter(root->left_, one, two, found_one, found_two);
	TNodePtr<T> right = LeastCommonAncestorBetter(root->right_, one, two, found_one, found_two);
	if (left && right)
		return root;
	return left ? left : right;
}

template<typename T>
inline TNodePtr<T> Tree<T>::Find(const T & val)
{
	if (root_ == nullptr)
		return nullptr;
	TNodePtr<T> root = root_;
	std::queue<TNodePtr<T>> my_queue;
	my_queue.push(root);
	while (!my_queue.empty())
	{
		root = my_queue.front();
		my_queue.pop();
		if (root->data_ == val)
		{
			break;
		}
		if (root->left_)
			my_queue.push(root->left_);
		if (root_->right_)
			my_queue.push(root->right_);
	}
	while (!my_queue.empty())
		my_queue.pop();
	return root;
}

template<typename T>
inline bool Tree<T>::Has(const T & val)
{
	return Find(val) ? true : false;
}

static void PrintChars(char ch, int count)
{
	if (count <= 0) 
		return;
	while (count--)
		std::cout << ch;
}

template<typename T>
inline void Tree<T>::PrintStructure()
{
	if (root_ == nullptr)
		return;
	TNodePtr<T> root = root_;
	TNodePtr<T> marker = CreateNode(0);
	bool is_first_node = true;
	int space_one = 0;
	int space_two = 0;
	int height = GetHeightIterative();
	int level = 1;
	int N = std::pow(2, height);
	std::queue <TNodePtr<T>> my_queue;
	my_queue.push(root);
	my_queue.push(nullptr);
	space_one = N / std::pow(2, level);
	space_two = N / std::pow(2, level - 1);
	/*std::cout <<std::endl;
	PrintChars('~', 25);
	std::cout << std::endl;*/
	while (!my_queue.empty())
	{
		root = my_queue.front();
		my_queue.pop();
		if (root == nullptr)
		{
			if (!my_queue.empty() && height >= 0)
			{
				std::cout << std::endl;
				my_queue.push(nullptr);
				is_first_node = true;
				++level;
				--height;
				space_one = N / std::pow(2, level);
				space_two = N / std::pow(2, level - 1);
			}
		}
		else if (root == marker)
		{
			if (height >= 0)
			{
				if (is_first_node)
					PrintChars(' ', space_one);
				else
					PrintChars(' ', space_two + 1);
				is_first_node = false;
				my_queue.push(marker);
				my_queue.push(marker);
			}
		}
		else
		{
			if (is_first_node)
				PrintChars(' ', space_one);
			else
				PrintChars(' ', space_two);
			std::cout << root->data_;
			is_first_node = false;
			if (root->left_)
				my_queue.push(root->left_);
			else if (height >=0 )
				my_queue.push(marker);
			if (root->right_)
				my_queue.push(root->right_);
			else if (height >= 0)
				my_queue.push(marker);
		}
	}
	while (!my_queue.empty())
		my_queue.pop();
	delete marker;
	/*std::cout << std::endl;
	PrintChars('~', 25);
	std::cout << std::endl;*/
}

template<typename T>
inline const TNodePtr<T> Tree<T>::GetRoot() const
{
	return root_;
}

template<typename T>
inline Tree<T>::~Tree()
{
	if (root_)
	{
		DeleteTree(root_);
		root_ = nullptr;
	}
}

template<typename T>
inline TNodePtr<T> Tree<T>::CreateNode(const T & val)
{
	TNodePtr<T> new_node = DBG_NEW TNode<T>;
	new_node->data_ = val;
	new_node->left_ = nullptr;
	new_node->right_ = nullptr;
	return new_node;
}

template<typename T>
inline void Tree<T>::InOrderTraversalRecursive(TNodePtr<T> root)
{
	if (root == nullptr)
		return;
	InOrderTraversalRecursive(root->left_);
	std::cout << root->data_ << " ";
	InOrderTraversalRecursive(root->right_);
}

template<typename T>
inline void Tree<T>::PreOrderTraveralRecursive(TNodePtr<T> root)
{
	if (root == nullptr)
		return;
	std::cout << root->data_ << " ";
	PreOrderTraveralRecursive(root->left_);
	PreOrderTraveralRecursive(root->right_);
}

template<typename T>
inline void Tree<T>::PostOrderTravesalRecursive(TNodePtr<T> root)
{
	if (root == nullptr)
		return;
	PostOrderTravesalRecursive(root->left_);
	PostOrderTravesalRecursive(root->right_);
	std::cout << root->data_ << " ";
}

template<typename T>
inline int Tree<T>::GetHeightRecursive(TNodePtr<T> root)
{
	if (root == nullptr)
		return 0;
	int left_ht = GetHeightRecursive(root->left_);
	int right_ht = GetHeightRecursive(root->right_);
	return std::max(left_ht, right_ht) + 1;
}

template<typename T>
inline int Tree<T>::GetDiameterRecursive(TNodePtr<T> root, int& diameter)
{
	if (root == nullptr)
		return 0;
	int left_ht = GetDiameterRecursive(root->left_, diameter);
	int right_ht = GetDiameterRecursive(root->right_, diameter);
	if (diameter < left_ht + right_ht + 1)
		diameter = left_ht + right_ht + 1;
	return std::max(left_ht, right_ht) + 1;
}

template<typename T>
inline TNodePtr<T> Tree<T>::GetMaximumRecursive(TNodePtr<T> root)
{
	if (root == nullptr)
		return nullptr;
	TNodePtr<T> max_from_left = GetMaximumRecursive(root->left_);
	TNodePtr<T> max_from_right = GetMaximumRecursive(root->right_);
	TNodePtr<T> max_temp = root;
	if (max_from_left && max_from_left->data_ > max_temp->data_)
	{
		max_temp = max_from_left;
	}
	if (max_from_right && max_from_right->data_ > max_temp->data_)
	{
		max_temp = max_from_right;
	}
	return max_temp;
}

template<typename T>
inline TNodePtr<T> Tree<T>::GetMinimumRecursive(TNodePtr<T> root)
{
	if (root == nullptr)
		return nullptr;
	TNodePtr<T> min_from_left = GetMinimumRecursive(root->left_);
	TNodePtr<T> min_from_right = GetMinimumRecursive(root->right_);
	TNodePtr<T> min_temp = root;
	if (min_from_left && min_from_left->data_ < min_temp->data_)
	{
		min_temp = min_from_left;
	}
	if (min_from_right && min_from_right->data_ < min_temp->data_)
	{
		min_temp = min_from_right;
	}
	return min_temp;
}

template<typename T>
inline void Tree<T>::DeleteTree(TNodePtr<T> root)
{
	if (root == nullptr)
		return;
	DeleteTree(root->left_);
	DeleteTree(root->right_);
	delete root;
}

