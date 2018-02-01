#include <vector>
#include "tree.h"
#include "bst.h"
#include "tree_algos.h"
#include "expression_tree.h"

static void PrintChar(char ch, int count,const char* title = "");
static void PrintCharLn(char ch, int count, const char* title = "");
static void PrintCharLnLn(char ch, int count, const char* title = "");

void test_trees()
{
	PrintCharLnLn('~', 20, "Tree<int> : START");
	Tree<int> int_tree{ 1, 2, 3, 4, 5, 6, 7 };
	int_tree.PrintStructure();
	std::cout << "Has path with sum 10 ? " << std::boolalpha << TreeAlgorithm<int>::HasPathWithSum(int_tree, 10) << std::endl;
	std::cout << "All paths with sum 10 : " << std::endl;
	TreeAlgorithm<int>::PrintPathWithSum(int_tree, 10);
	std::cout << "All ancestors of 5 : " << std::endl;
	TreeAlgorithm<int>::PrintAllAncestorsOfNode(int_tree, 5);
	PrintCharLnLn('~', 20, "Tree<int> : END");

	PrintCharLnLn('~', 20, "Tree<char> : START");
	Tree<char> char_tree({ 'a','b','c','d','e','f','g' });
	char_tree.PrintStructure();
	std::cout << "All root-to-leaf paths : " << std::endl;
	TreeAlgorithm<char>::PrintAllRootToLeafPaths(char_tree);
	PrintCharLn('-', 20);
	int_tree.PrintStructure();
	char_tree.PrintStructure();
	std::cout << "Are trees structurally same ? " << TreeAlgorithm<int, char>::AreTreesStructurallySame(int_tree, char_tree) << std::endl;
	PrintCharLn('-', 20);
	PrintCharLnLn('~', 20, "Tree<char> : END");

	PrintCharLnLn('~', 20, "BinarySearchTree<int> : START");
	BST<int> int_bst;
	for (auto val : { 4, 2, 6, 1, 3, 5, 7 })
	{
		int_bst.AddNode(val);
	}
	int_bst.PrintStructure();
	int_bst.InOrderTraversalIterative();
	PrintCharLnLn('~', 20, "BinarySearchTree<int> : END");

	PrintCharLnLn('~', 20, "Compare, Convert Trees : START");
	Tree<int> int_tree1{ 1,2,3,4,5,6,7 };
	Tree<int> int_tree2{ 1,2,3,4,5,6,7 };
	int_tree1.PrintStructure();
	int_tree2.PrintStructure();
	std::cout << "Are trees same ? " << std::boolalpha << TreeAlgorithm<int>::AreTreesSame(int_tree1, int_tree2) << std::endl;
	std::cout << "Convert to mirror : " << std::endl;
	TreeAlgorithm<int>::ConvertToMirror(int_tree2);
	int_tree2.PrintStructure();
	std::cout << "Are trees mirror image ? " << TreeAlgorithm<int>::AreTreesMirrorImage(int_tree1, int_tree2) << std::endl;
	PrintCharLnLn('~', 20, "Compare, Convert Trees : END");

	Tree<int> int_tree3{6, 2, 8, 1, 9};
	TreeAlgorithm<int>::PrintTree(int_bst);
	std::cout << "Is tree BST ? " << TreeAlgorithm<int>::IsBst(int_bst) << "-" << TreeAlgorithm<int>::IsBstBetter(int_bst)<< "-" << TreeAlgorithm<int>::IsBstStillBetter(int_bst)<< "-" << TreeAlgorithm<int>::IsBstBest(int_bst)<< std::endl;
	TreeAlgorithm<char>::PrintTree(char_tree);
	std::cout << "Is tree BST ? " << TreeAlgorithm<char>::IsBst(char_tree) << "-" << TreeAlgorithm<char>::IsBstBetter(char_tree) << "-" << TreeAlgorithm<char>::IsBstStillBetter(char_tree) << "-" << TreeAlgorithm<char>::IsBstBest(char_tree) << std::endl;
	TreeAlgorithm<int>::PrintTree(int_tree3);
	std::cout << "Is tree BST ? " << TreeAlgorithm<int>::IsBst(int_tree3) << "-" << TreeAlgorithm<int>::IsBstBetter(int_tree3) << "-" << TreeAlgorithm<int>::IsBstStillBetter(int_tree3) << "-" << TreeAlgorithm<int>::IsBstBest(int_tree3) << std::endl;

	TreeAlgorithm<int>::PrintTree(int_bst);
	std::vector<std::pair<int, int>> int_lca;
	int_lca.push_back(std::make_pair(1, 3));
	int_lca.push_back(std::make_pair(5, 7));
	int_lca.push_back(std::make_pair(2, 5));
	int_lca.push_back(std::make_pair(3, 7));
	int_lca.push_back(std::make_pair(6, 7));
	int_lca.push_back(std::make_pair(3, 10));
	for (auto val : int_lca)
	{
		int val1 = val.first;
		int val2 = val.second;
		TNodePtr<int> lca = int_bst.LeastCommonAncestor(val1, val2);
		TNodePtr<int> lca1 = int_bst.LeastCommonAncestorBetter(val1, val2);
		if (lca || lca1)
			std::cout << "LCA(" << val1 << "," << val2 << ") = ";
		if (lca)
			std::cout <<lca->data_;
		if (lca  && lca1)
			std::cout << "-";
		if (lca1)
			std::cout << lca1->data_;
		if (lca || lca1)
			std::cout<< std::endl;
	}
	PrintCharLn('-', 18, "BST : LCA");
	TNodePtr<int> lca = int_bst.LeastCommonAncestor(3, 10);
	if (lca)
		std::cout << "LCA(3,10) = " << lca->data_ << std::endl;
	lca = int_bst.LeastCommonAncestor(9, 11);
	if (lca)
		std::cout << "LCA(9,11) = " << lca->data_ << std::endl;
	lca = int_bst.LeastCommonAncestor(4, 6);
	if (lca)
		std::cout << "LCA(4,6) = " << lca->data_ << std::endl;

	std::vector<std::pair<char, char>> char_lca;
	char_lca.push_back(std::make_pair('d', 'e'));
	char_lca.push_back(std::make_pair('b', 'g'));
	char_lca.push_back(std::make_pair('d', 'f'));
	char_lca.push_back(std::make_pair('e', 'h'));
	char_lca.push_back(std::make_pair('a', 'a'));
	char_lca.push_back(std::make_pair('c', 'e'));
	TreeAlgorithm<char>::PrintTree(char_tree);
	for (auto val : char_lca)
	{
		auto val1 = val.first;
		auto val2 = val.second;
		TNodePtr<char> lca = char_tree.LeastCommonAncestor(val1, val2);
		TNodePtr<char> lca1 = char_tree.LeastCommonAncestorBetter(val1, val2);
		if (lca || lca1)
			std::cout << "LCA(" << val1 << "," << val2 << ") = ";
		if (lca)
			std::cout << lca->data_;
		if (lca  && lca1)
			std::cout << "-";
		if (lca1)
			std::cout << lca1->data_;
		if (lca || lca1)
			std::cout << std::endl;
	}
	BinarySearchTree<int> arr_to_bst;
	std::vector<int> sorted_arr{10,20,30,40,50,60,70};
	TreeAlgorithm<int>::SortedArrayToBst(sorted_arr, arr_to_bst);
	arr_to_bst.PrintStructure();
	/*
	PrintCharLnLn('~', 20, "Delete Node Trees : START");
	for (int val : { 1, 2, 3, 4, 5, 6, 7 })
	{
	std::cout << "Deleting : " << val<<std::endl;
	int_tree.DeleteNode(val);
	int_tree.PrintStructure();
	}
	for (int val : { 4, 2, 6, 1, 3, 5, 7 })
	{
	std::cout << "Deleting : " << val << std::endl;
	int_bst.DeleteNode(val);
	int_bst.PrintStructure();
	}
	PrintCharLnLn('~', 20, "Delete Node Trees : END");
	*/
	for (auto val : { 1,3,4,9 })
	{
		TNodePtr<int> result = TreeAlgorithm<int>::GetKthSmallestElement(arr_to_bst, val);
		if (result)
		{
			std::cout << val << "th smallest element is " << result->data_ << std::endl;
		}
	}
	for (auto val : { 1,3,4,9 })
	{
		TNodePtr<int> result = TreeAlgorithm<int>::GetKthLargestElement(arr_to_bst, val);
		if (result)
		{
			std::cout << val << "th largest element is " << result->data_ << std::endl;
		}
	}
	arr_to_bst.PrintStructure();
	std::vector<std::pair<int, int>> int_range;
	int_range.push_back(std::make_pair(10, 30));
	int_range.push_back(std::make_pair(50, 70));
	int_range.push_back(std::make_pair(20, 50));
	int_range.push_back(std::make_pair(30, 70));

	for (auto val : int_range)
	{
		int val1 = val.first;
		int val2 = val.second;
		std::cout << "Range(" << val1 << "," << val2 << ") : ";
		TreeAlgorithm<int>::PrintRange(arr_to_bst, val1, val2);
	}
}

void test_expression_tree()
{
	ExpressionTree et{'A','B','C','*','+','D','/' };
	et.PrintTree();
}

int main()
{
	test_trees();
	std::cout << "Nodes Created<int> : " << TreeNode<int>::GetTotalNodesCreated() << ", Nodes Destroyed<int> : " << TreeNode<int>::GetTotalNodesDestroyed() << std::endl;
	std::cout << "Nodes Created<char> : " << TreeNode<int>::GetTotalNodesCreated() << ", Nodes Destroyed<char> : " << TreeNode<int>::GetTotalNodesDestroyed() << std::endl;
	//test_expression_tree();
	_CrtDumpMemoryLeaks();
	return 0;
}

static void PrintChar(char ch, int count, const char* title)
{
	if (count <= 0)
		return;
	int half = count / 2;
	while (count--)
	{
		std::cout << ch;
		if (count == half)
			std::cout << title;
	}
}
static void PrintCharLn(char ch, int count, const char* title)
{
	PrintChar(ch, count, title);
	std::cout << std::endl;
}

static void PrintCharLnLn(char ch, int count, const char* title)
{
	std::cout << std::endl;
	PrintChar(ch, count, title);
	std::cout << std::endl;
}