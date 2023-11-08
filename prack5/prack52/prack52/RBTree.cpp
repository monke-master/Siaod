#include "RBTree.h"


Node* RBTree::newNode(string key, int value)
{
	Node* node = new Node;
	node->key = key;
	node->value = value;
	node->left = node->right = 0;
	node->isRed = true;
	keysInserted++;
	return node;
}

Node* RBTree::rotateLeft(Node* node)
{
	Node* p2 = node->right;
	Node* p21 = p2->left;
	p2->left = node;
	node->right = p21;
	rotates++;
	return p2;
}


Node* RBTree::rotateRight(Node* node)
{
	Node* p1 = node->left;
	Node* p12 = p1->right;
	p1->right = node;
	node->left = p12;
	rotates++;
	return p1;
}


void RBTree::fixInsertion(Node** root)
{
	Node* left, * right, * px1, * px2;
	Node* node = *root;
	if (node->isRed) 
		return;
	left = node->left;
	right = node->right;
	if (left && left->isRed) {
		px2 = left->right;				
		if (px2 && px2->isRed)
			left = node->left = rotateLeft(left);
		px1 = left->left;
		if (px1 && px1->isRed) {
			node->isRed = true;
			left->isRed = false;
			if (right && right->isRed) {	
				px1->isRed = true;
				right->isRed = false;
				return;
			}
			*root = rotateRight(node);
			return;
		}
	}
	
	if (right && right->isRed) {
		px1 = right->left;				
		if (px1 && px1->isRed) 
			right = node->right = rotateRight(right);
		px2 = right->right;
		if (px2 && px2->isRed) {
			node->isRed = true;
			right->isRed = false;
			if (left && left->isRed) {	
				px2->isRed = true;
				left->isRed = false;
				return;
			}
			*root = rotateLeft(node);
			return;
		}
	}
}

bool RBTree::insert(string key, int value, Node** root)
{
	Node* node = *root;
	if (!node) 
*root = newNode(key, value);
	else {
		if (key == node->key) return true;
		if (insert(key, value, key < node->key ? &node->left : &node->right)) return true;
		fixInsertion(root);
	}
	return false;
}


void RBTree::insert(string key, int value)
{
	insert(key, value, &root);
	if (root) 
		root->isRed = false;
}

void RBTree::printLevel(Node* node, int level)
{
	if (node != nullptr) {
		printLevel(node->right, level + 1);
		string isRed = node->isRed ? " (Red) " : " (Black) ";
		cout << string(level * 4, ' ') << "-> " << node->key << isRed << endl;
		printLevel(node->left, level + 1);
	}

}

void RBTree::print()
{
	printLevel(root, 0);
}

float RBTree::getAverageRotates()
{
	return (float)rotates / keysInserted;
}


bool RBTree::fixRemoveLeft(Node** root)
{
	Node* node = *root;
	Node* p1 = node->left;
	Node* p2 = node->right;
	if (p1 && p1->isRed) {
		p1->isRed = false; return false;
	}
	if (p2 && p2->isRed) { // случай 1
		node->isRed = true;
		p2->isRed = false;
		node = *root = rotateLeft(node);
		if (fixRemoveLeft(&node->left)) node->left->isRed = false;
		return false;
	}
	unsigned int mask = 0;
	Node* p21 = p2->left;
	Node* p22 = p2->right;
	if (p21 && p21->isRed) mask |= 1;
	if (p22 && p22->isRed) mask |= 2;
	switch (mask)
	{
	case 0:		// случай 2 - if((!p21 || !p21->red) && (!p22 || !p22->red))
		p2->isRed = true;
		return true;
	case 1:
	case 3:		// случай 3 - if(p21 && p21->red)
		p2->isRed = true;
		p21->isRed = false;
		p2 = node->right = rotateRight(p2);
		p22 = p2->right;
	case 2:		// случай 4 - if(p22 && p22->red)
		p2->isRed = node->isRed;
		p22->isRed = node->isRed = false;
		*root = rotateLeft(node);
	}
	return false;
}

bool RBTree::fixRemoveRight(Node** root)
{
	Node* node = *root;
	Node* p1 = node->left;
	Node* p2 = node->right;
	if (p2 && p2->isRed) { p2->isRed = false; return false; }
	if (p1 && p1->isRed) { // случай 1
		node->isRed = true;
		p1->isRed = false;
		node = *root = rotateRight(node);
		if (fixRemoveRight(&node->right)) node->right->isRed = false;
		return false;
	}
	unsigned int mask = 0;
	Node* p11 = p1->left;
	Node* p12 = p1->right;
	if (p11 && p11->isRed) mask |= 1;
	if (p12 && p12->isRed) mask |= 2;
	switch (mask) {
	case 0:		// случай 2 - if((!p12 || !p12->red) && (!p11 || !p11->red))
		p1->isRed = true;
		return true;
	case 2:
	case 3:		// случай 3 - if(p12 && p12->red)
		p1->isRed = true;
		p12->isRed = false;
		p1 = node->left = rotateLeft(p1);
		p11 = p1->left;
	case 1:		// случай 4 - if(p11 && p11->red)
		p1->isRed = node->isRed;
		p11->isRed = node->isRed = false;
		*root = rotateRight(node);
	}
	return false;
}

bool RBTree::minValueNode(Node** root, Node** res)
{
	Node* node = *root;
	if (node->left) {
		if (minValueNode(&node->left, res)) return fixRemoveLeft(root);
	}
	else {
		*root = node->right;
		*res = node;
		return !node->isRed;
	}
	return false;
}

bool RBTree::deleteNode(Node** root, string key)
{
	Node* t, * node = *root;
	if (!node) return false;
	if (node->key < key) {
		if (deleteNode(&node->right, key))	return fixRemoveRight(root);
	}
	else if (node->key > key) {
		if (deleteNode(&node->left, key))	return fixRemoveLeft(root);
	}
	else {
		bool res;
		if (!node->right) {
			*root = node->left;
			res = !node->isRed;
		}
		else {
			res = minValueNode(&node->right, root);
			t = *root;
			t->isRed = node->isRed;
			t->left = node->left;
			t->right = node->right;
			if (res) res = fixRemoveRight(root);
		}
		delete node;
		return res;
	}
	return 0;
}

void RBTree::deleteNode(string key)
{
	deleteNode(&root, key);
}


Node* RBTree::getByKey(string key)
{
	return getByKey(root, key);
}

Node* RBTree::getByKey(Node* node, string key)
{
	if (node == NULL || node->key == key)
		return node;

	if (node->key < key)
		return getByKey(node->right, key);

	return getByKey(node->left, key);
}