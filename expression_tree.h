#pragma once

#include <iostream>

struct ExpNode
{
	int data_;
	ExpNode* left_;
	ExpNode* right_;
};

class ExpressionTree
{
	ExpNode* root_;
public:
	ExpressionTree() = default;
	ExpressionTree(const std::initializer_list<char>& list);
	void PrintTree();
private:
	ExpNode * CreateNode(char val);
	void CreateTree(const std::initializer_list<char>& list);
};