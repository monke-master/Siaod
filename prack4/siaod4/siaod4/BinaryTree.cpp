#include "BinaryTree.h"

BinaryTree::BinaryTree(int size)
{
	this->size = size;
	this->root = createNode(size);
}

TreeNode* BinaryTree::createNode(int n)
{
	if (n <= 0)
		return nullptr;
	auto node = new TreeNode();
	int x;
	cout << "Enter x \n";
	cin >> x;
	node->value = x;
	node->left = createNode(n / 2);
	node->right = createNode(n - n / 2 - 1);
	return node;
}



int BinaryTree::countPositiveLeaves()
{
	queue<TreeNode*> queue;
	queue.push(root);
	int k = 0;
	while (!queue.empty()) {
		TreeNode* node = queue.front();
		queue.pop();
		if (node->value > 0 && (node->left == nullptr) && (node->right == nullptr))
		{
			k++;
			continue;
		}
	    if (node->left != nullptr)
			queue.push(node->left);
		if (node->right != nullptr)
			queue.push(node->right);
	}
	return k;
}

int BinaryTree::countWithNumber(int number)
{
	queue<TreeNode*> queue;
	queue.push(root);
	int k = 0;
	while (!queue.empty()) {
		TreeNode* node = queue.front();
		queue.pop();
		if (node->value == number)
			k++;
		if (node->left != nullptr)
			queue.push(node->left);
		if (node->right != nullptr)
			queue.push(node->right);
	}
	return k;
}

void BinaryTree::doubleValues()
{
	queue<TreeNode*> queue;
	queue.push(root);
	while (!queue.empty()) {
		TreeNode* node = queue.front();
		queue.pop();
		node->value = node->value * 2;
		if (node->left != nullptr)
			queue.push(node->left);
		if (node->right != nullptr)
			queue.push(node->right);
	}
}


void BinaryTree::print()
{
	printLevel("", root, "   ");

}

void BinaryTree::printLevel(const std::string& prefix, TreeNode* node, const std::string& separator)
{
	if (node == nullptr) {
		return;
	}
		

	std::cout << prefix;

	std::cout << (separator);
	std::cout << node->value << std::endl;
	printLevel(prefix + (separator), node->left, separator);
	printLevel(prefix + (separator), node->right, separator);

}






