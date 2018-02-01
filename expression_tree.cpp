#include <stack>
#include <queue>
#include "expression_tree.h"

ExpressionTree::ExpressionTree(const std::initializer_list<char>& list):root_(nullptr)
{
	CreateTree(list);
}
static bool is_operator(char ch)
{
	switch (ch)
	{
	case '/':
	case '*':
	case '-':
	case '+':
		return true;
	}
	return false;
}
ExpNode * ExpressionTree::CreateNode(char val)
{
	ExpNode* new_node = new ExpNode;
	new_node->data_ = val;
	new_node->left_ = nullptr;
	new_node->right_ = nullptr;
	return new_node;
}
void ExpressionTree::CreateTree(const std::initializer_list<char>& list)
{
	std::stack<ExpNode*> my_stack;
	for (auto val : list)
	{
		if (!is_operator(val))
		{
			ExpNode* new_node = CreateNode(val);
			my_stack.push(new_node);
		}
		else
		{
			ExpNode* operand1 = nullptr, *operand2 = nullptr;
			if (!my_stack.empty())
			{
				operand1 = my_stack.top();
				my_stack.pop();
			}
			if (!my_stack.empty())
			{
				operand2 = my_stack.top();
				my_stack.pop();
			}
			ExpNode* opr = CreateNode(val);
			opr->left_ = operand2;
			opr->right_ = operand1;
			my_stack.push(opr);
		}
	}
	if (!my_stack.empty())
	{
		root_ = my_stack.top();
		my_stack.pop();
	}
}


static void PrintChars(char ch, int count)
{
	if (count <= 0)
		return;
	while (count--)
		std::cout << ch;
}

void ExpressionTree::PrintTree()
{
	if (root_ == nullptr)
		return;
	ExpNode* root = root_;
	ExpNode* marker = CreateNode(0);
	bool is_first_node = true;
	int space_one = 0;
	int space_two = 0;
	int height = 3;// GetHeightIterative();
	int level = 1;
	int N = std::pow(2, height);
	std::queue<ExpNode*> my_queue;
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
			std::cout << char(root->data_);
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

