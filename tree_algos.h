#pragma once

#include "tree.h"

template <typename T, typename T1=T>
class TreeAlgorithm
{
public:
	static bool AreTreesSame(const Tree<T>& tree1, const Tree<T>& tree2);
	static bool AreTreesStructurallySame(const Tree<T>& tree1, const Tree<T1>& tree2);
	static bool AreTreesMirrorImage(const Tree<T>& tree1, const Tree<T1>& tree2);
	static void PrintAllRootToLeafPaths(const Tree<T>& tree);
	static bool HasPathWithSum(const Tree<T>& tree, int sum);
	static void PrintPathWithSum(const Tree<T>& tree, int sum);
	static void ConvertToMirror(Tree<T>& tree);
	static void PrintAllAncestorsOfNode(const Tree<T>& tree, const T& val);
	static bool IsBst(const Tree<T>& tree);
	static bool IsBstBetter(const Tree<T>& tree);
	static bool IsBstStillBetter(const Tree<T>& tree);
	static bool IsBstBest(const Tree<T>& tree);
	static void PrintTree(const Tree<T>& tree);

	//static void ConvertBstToDll(const Tree<T>& tree);
	//static void DllToBst();
	static void SortedArrayToBst(const std::vector<T>& arr, BinarySearchTree<T>& tree);//top down
	//static void SortedArrayToBst(const std::vector<T>& arr, int &current_index, BinarySearchTree<T>& tree);//bottom-up
	//static void SortedListToBst(const std::vector<T>& arr, BinarySearchTree<T>& tree);
	static TNodePtr<T> GetKthSmallestElement(const BinarySearchTree<T>& tree, int k);
	static TNodePtr<T> GetKthLargestElement(const BinarySearchTree<T>& tree, int k);

	static void PrintRange(const BinarySearchTree<T>& tree, const T& low, const T& high);


private:
	//void BuildBinaryTree();
	static bool AreTreesSame(const TNodePtr<T> root1, const TNodePtr<T> root2);
	static bool AreTreesStructurallySame(const TNodePtr<T> root1, const TNodePtr<T1> root2);
	static bool AreTreesMirrorImage(const TNodePtr<T> root1, const TNodePtr<T1> root2);
	static void PrintAllRootToLeafPaths(const TNodePtr<T> root, std::vector<T>& path);
	static bool HasPathWithSum(const TNodePtr<T> root, int sum);
	static void PrintPathWithSum(const TNodePtr<T> root, int sum, std::vector<T>& path);
	static void ConvertToMirror(TNodePtr<T> root);
	//static void ConvertToMirror(TNodePtr<T>& node1, TNodePtr<T>& node2);
	static TNodePtr<T> PrintAllAncestorsOfNode(const TNodePtr<T> root, const T & value);
	static bool IsBst(const TNodePtr<T> root);
	static bool IsBstBetter(const TNodePtr<T> root);
	static bool IsBstStillBetter(const TNodePtr<T> root, T& min, T&max);
	static bool IsBstBest(const TNodePtr<T> root, T& previous);

	static TNodePtr<T>  GetMax(const TNodePtr<T> root);
	static TNodePtr<T>  GetMin(const TNodePtr<T> root);

	static TNodePtr<T> GetKthSmallestElement(const TNodePtr<T> tree, int k, int& count);
	static TNodePtr<T> GetKthLargestElement(const TNodePtr<T> tree, int k, int& count);

	static void PrintRange(const TNodePtr<T> root, const T& low, const T& high);
};

template<typename T, typename T1>
inline void TreeAlgorithm<T, T1>::SortedArrayToBst(const std::vector<T>& arr, BinarySearchTree<T>& tree)
{
	int start = 0;
	int end = arr.size() - 1;
	std::queue<std::pair<int, int>> my_queue;
	my_queue.push(std::make_pair(start, end));
	while (!my_queue.empty())
	{
		auto elem = my_queue.front();
		my_queue.pop();
		start = elem.first;
		end = elem.second;
		if (start == end)
		{
			tree.AddNode(arr[start]);
		}
		else
		{
			int mid = (start + end) / 2;
			my_queue.push(std::make_pair(start,mid-1));
			my_queue.push(std::make_pair(mid+1, end));
				//start,mid-1, mid+1, end
			tree.AddNode(arr[mid]);
		}
	}
}

template<typename T, typename T1>
inline TNodePtr<T> TreeAlgorithm<T, T1>::GetKthSmallestElement(const BinarySearchTree<T>& tree, int k)
{
	int count = 0;
	return GetKthSmallestElement(tree.GetRoot(), k, count);
}

template<typename T, typename T1>
inline TNodePtr<T> TreeAlgorithm<T, T1>::GetKthLargestElement(const BinarySearchTree<T>& tree, int k)
{
	int count = 0;
	return GetKthLargestElement(tree.GetRoot(), k, count);
}

template<typename T, typename T1>
inline void TreeAlgorithm<T, T1>::PrintRange(const BinarySearchTree<T>& tree, const T & low, const T & high)
{
	if (tree.GetRoot() == nullptr)
		return;
	if(low <= high)
		PrintRange(tree.GetRoot(), low, high);
	else
		PrintRange(tree.GetRoot(), high, low);
	std::cout << std::endl;
}


template<typename T, typename T1>
inline bool TreeAlgorithm<T,T1>::AreTreesSame(const TNodePtr<T> root1, const TNodePtr<T> root2)
{
	if (root1 == nullptr && root2 == nullptr)
		return true;
	if (!root1 && root2
		|| root1 && !root2)
		return false;
	return root1->data_ == root2->data_ 
		&& AreTreesSame(root1->left_, root2->left_) 
		&& AreTreesSame(root2->right_, root2->right_);
}

template<typename T, typename T1=T>
inline bool TreeAlgorithm<T,T1>::AreTreesStructurallySame(const TNodePtr<T> root1, const TNodePtr<T1> root2)
{
	if (root1 == nullptr && root2 == nullptr)
		return true;
	if (!root1 && root2
		||root1 && !root2)
		return false;
	return AreTreesStructurallySame(root1->left_, root2->left_) 
		&& AreTreesStructurallySame(root1->right_, root2->right_);
}

template<typename T, typename T1=T>
inline bool TreeAlgorithm<T,T1>::AreTreesMirrorImage(const TNodePtr<T> root1, const TNodePtr<T1> root2)
{
	if (!root1 && !root2)
		return true;
	if (!root1 && root2
		|| root1 && !root2)
	{
		return false;
	}
	
	return root1->data_ == root2->data_ 
		&& AreTreesMirrorImage(root1->left_, root2->right_)
		&& AreTreesMirrorImage(root1->right_, root2->left_);

}

template<typename T, typename T1>
inline void TreeAlgorithm<T,T1>::PrintAllRootToLeafPaths(const TNodePtr<T> root, std::vector<T>& path)
{

	path.push_back(root->data_);
	if (root->left_ == nullptr && root->right_ == nullptr)
	{
		std::cout << std::endl;
		int count = path.size();
		for (auto val : path)
		{
			std::cout << val;
			if(--count != 0)
				std::cout<<"->";
		}
	}
	if(root->left_)
		PrintAllRootToLeafPaths(root->left_, path);
	if(root->right_)
		PrintAllRootToLeafPaths(root->right_, path);
	path.pop_back();
}

template<typename T, typename T1>
inline bool TreeAlgorithm<T,T1>::HasPathWithSum(const TNodePtr<T> root, int sum)
{
	if (sum == 0)
		return true;
	if (root == nullptr || sum < 0)
		return false;
	return HasPathWithSum(root->left_, sum - root->data_)
		|| HasPathWithSum(root->right_, sum - root->data_);

}

template<typename T, typename T1>
inline void TreeAlgorithm<T, T1>::PrintPathWithSum(const TNodePtr<T> root, int sum, std::vector<T>& path)
{
	if (root == nullptr || sum <= 0)
		return;
	path.push_back(root->data_);
	if (sum - root->data_ == 0)
	{
		std::cout << std::endl;
		int count = path.size();
		for (auto val : path)
		{
			std::cout << val;
			if (--count > 0)
				std::cout << "->";
		}
	}
	if (root->left_)
		PrintPathWithSum(root->left_, sum - root->data_, path);
	if(root->right_)
		PrintPathWithSum(root->right_, sum - root->data_, path);
	path.pop_back();	
}

template<typename T, typename T1>
inline void TreeAlgorithm<T,T1>::ConvertToMirror(TNodePtr<T> root)
{
	if (root == nullptr)
		return;
	if (root->left_ && root->right_)
	{
		TNodePtr<T> temp = root->left_;
		root->left_ = root->right_;
		root->right_ = temp;
	}
	else if(!root->left_ || !root->right_)
	{
		if (root->left_)
		{
			root->right_ = root->left_;
			root->left_ = nullptr;
		}
		else if (root->right_)
		{
			root->left_ = root->right_;
			root->right_ = nullptr;
		}
	}
	ConvertToMirror(root->left_);
	ConvertToMirror(root->right_);
}

template<typename T, typename T1>
inline TNodePtr<T> TreeAlgorithm<T, T1>::PrintAllAncestorsOfNode(const TNodePtr<T> root, const T & value)
{
	if (root == nullptr || root->data_ == value)
		return root;
	TNodePtr<T> left = PrintAllAncestorsOfNode(root->left_, value);
	TNodePtr<T> right = PrintAllAncestorsOfNode(root->right_, value);
	if (left || right)
		std::cout << root->data_ << " ";
	return left ? left : right;
}

template<typename T, typename T1>
inline bool TreeAlgorithm<T, T1>::AreTreesSame(const Tree<T>& tree1, const Tree<T>& tree2)
{
	return AreTreesSame(tree1.GetRoot(), tree2.GetRoot());
}

template<typename T, typename T1>
inline bool TreeAlgorithm<T, T1>::AreTreesStructurallySame(const Tree<T>& tree1, const Tree<T1>& tree2)
{
	return AreTreesStructurallySame(tree1.GetRoot(), tree2.GetRoot());
}

template<typename T, typename T1>
inline bool TreeAlgorithm<T, T1>::AreTreesMirrorImage(const Tree<T>& tree1, const Tree<T1>& tree2)
{
	return AreTreesMirrorImage(tree1.GetRoot(), tree2.GetRoot());
}

template<typename T, typename T1>
inline void TreeAlgorithm<T, T1>::PrintAllRootToLeafPaths(const Tree<T>& tree)
{
	if (tree.GetRoot())
	{
		std::vector<T> path;
		PrintAllRootToLeafPaths(tree.GetRoot(), path);
		std::cout << std::endl;
	}
}

template<typename T, typename T1>
inline bool TreeAlgorithm<T, T1>::HasPathWithSum(const Tree<T>& tree, int sum)
{
	if (tree.GetRoot())
	{
		return HasPathWithSum(tree.GetRoot(), sum);
	}
	return false;
}

template<typename T, typename T1>
inline void TreeAlgorithm<T, T1>::PrintPathWithSum(const Tree<T>& tree, int sum)
{
	if (tree.GetRoot())
	{
		std::vector<T> path;
		PrintPathWithSum(tree.GetRoot(), sum, path);
		std::cout << std::endl;
	}
}

template<typename T, typename T1>
inline void TreeAlgorithm<T, T1>::ConvertToMirror(Tree<T>& tree)
{
	ConvertToMirror(tree.GetRoot());
}

template<typename T, typename T1>
inline void TreeAlgorithm<T, T1>::PrintAllAncestorsOfNode(const Tree<T>& tree, const T & val)
{
	if (tree.GetRoot())
	{
		PrintAllAncestorsOfNode(tree.GetRoot(), val);
		std::cout << std::endl;
	}
}

template<typename T, typename T1>
inline bool TreeAlgorithm<T, T1>::IsBst(const Tree<T>& tree)
{
	return IsBst(tree.GetRoot());
}

template<typename T, typename T1>
inline bool TreeAlgorithm<T, T1>::IsBst(const TNodePtr<T> root)
{
	if (root == nullptr)
		return true;
	if (root->left_ && root->left_->data_ > root->data_)
		return false;
	if (root->right_ && root->right_->data_ < root->data_)
		return false;
	if (!IsBst(root->left_) || !IsBst(root->right_))
		return false;
	return true;

}

template<typename T, typename T1>
inline bool TreeAlgorithm<T, T1>::IsBstBetter(const Tree<T>& tree)
{
	return IsBstBetter(tree.GetRoot());
}

template<typename T, typename T1>
inline bool TreeAlgorithm<T, T1>::IsBstBetter(const TNodePtr<T> root)
{
	if (root == nullptr)
		return true;
	if (root->left_ && root->data_ < GetMax(root->left_)->data_)
		return false;
	if (root->right_ && root->data_ > GetMin(root->right_)->data_)
		return false;
	if (!IsBstBetter(root->left_) || !IsBstBetter(root->right_))
		return false;
	return true;
}

template<typename T, typename T1>
inline bool TreeAlgorithm<T, T1>::IsBstStillBetter(const Tree<T>& tree)
{
	T min = std::numeric_limits<T>::min();
	T max = std::numeric_limits<T>::max();
	return IsBstStillBetter(tree.GetRoot(), min, max);
}

template<typename T, typename T1>
inline bool TreeAlgorithm<T, T1>::IsBstStillBetter(const TNodePtr<T> root, T& min, T& max)
{
	if (root == nullptr)
		return true;
	return
		(root->data_ > min && root->data_ < max)
		&& IsBstStillBetter(root->left_, min, root->data_)
		&& IsBstStillBetter(root->right_, root->data_, max);
	return false;
}

template<typename T, typename T1>
inline bool TreeAlgorithm<T, T1>::IsBstBest(const TNodePtr<T> root, T& previous)
{
	if (!root)
		return true;
	if (!IsBstBest(root->left_, previous))
		return false;
	if (root->data_ < previous)
		return false;
	previous = root->data_;
	return IsBstBest(root->right_, previous);
}

template<typename T, typename T1>
inline TNodePtr<T> TreeAlgorithm<T, T1>::GetMax(const TNodePtr<T> root)
{
	if (root == nullptr)
		return nullptr;
	TNodePtr<T> temp = root;
	while (temp->right_)
		temp = temp->right_;
	return temp;
}

template<typename T, typename T1>
inline TNodePtr<T> TreeAlgorithm<T, T1>::GetMin(const TNodePtr<T> root)
{
	if (root == nullptr)
		return nullptr;
	TNodePtr<T> temp = root;
	while (temp->left_)
		temp = root->left_;
	return temp;
}

template<typename T, typename T1>
inline TNodePtr<T> TreeAlgorithm<T, T1>::GetKthSmallestElement(const TNodePtr<T> root, int k, int & count)
{
	if (root == nullptr)
		return nullptr;
	TNodePtr<T> left =  GetKthSmallestElement(root->left_, k, count);
	if (left)
		return left;
	if (++count == k)
		return root;
	TNodePtr<T> right = GetKthSmallestElement(root->right_, k, count);
	if (right)
		return right;
	return nullptr;


}

template<typename T, typename T1>
inline TNodePtr<T> TreeAlgorithm<T, T1>::GetKthLargestElement(const TNodePtr<T> root, int k, int & count)
{
	if (root == nullptr)
		return nullptr;
	TNodePtr<T> right = GetKthLargestElement(root->right_, k, count);
	if (right)
		return right;
	if (++count == k)
		return root;
	TNodePtr<T> left = GetKthLargestElement(root->left_, k, count);
	if (left)
		return left;
	return nullptr;
}

template<typename T, typename T1>
inline void TreeAlgorithm<T, T1>::PrintRange(const TNodePtr<T> root, const T & low, const T & high)
{
	if (root == nullptr)
		return;
	if (root->data_ >= low)
		PrintRange(root->left_, low, high);
	if (root->data_ >= low && root->data_ <= high)
		std::cout << root->data_ << " ";
	if (root->data_ <= high)
		PrintRange(root->right_, low, high);
}


template<typename T, typename T1>
inline bool TreeAlgorithm<T, T1>::IsBstBest(const Tree<T>& tree)
{
	T min = std::numeric_limits<T>::min();
	return IsBstBest(tree.GetRoot(), min);
}

template<typename T, typename T1>
inline void TreeAlgorithm<T, T1>::PrintTree(const Tree<T>& tree)
{
	TNodePtr<T> root = tree.GetRoot();
	if (root == nullptr)
		return;
	TNodePtr<T> marker = new TNode<T>;
	bool is_first_node = true;
	int space_one = 0;
	int space_two = 0;
	int height = 3;// GetHeightIterative();
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
			else if (height >= 0)
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
