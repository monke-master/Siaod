#include "BinarySearchTree.h"

node* BinarySearchTree::newNode(string item, int value)
{
    struct node* temp = new node();
    temp->key = item;
    temp->value = value;
    temp->left = temp->right = NULL;
    return temp;
}

node* BinarySearchTree::insert(node* node, string key, int value)
{
    if (node == NULL) return newNode(key, value);

    if (key < node->key)
        node->left = insert(node->left, key, value);
    else
        node->right = insert(node->right, key, value);

    return node;
}

node* BinarySearchTree::getByKey(node* root, string key)
{
    if (root == NULL || root->key == key)
        return root;

    if (root->key < key)
        return getByKey(root->right, key);

    return getByKey(root->left, key);
}

node* BinarySearchTree::minValueNode(node* node)
{
    struct node* current = node;

    while (current && current->left != NULL)
        current = current->left;

    return current;
}

node* BinarySearchTree::deleteNode(node* root, string key)
{
    if (root == NULL) return root;

    if (key < root->key)
        root->left = deleteNode(root->left, key);
    else if (key > root->key)
        root->right = deleteNode(root->right, key);
    else {
        if (root->left == NULL) {
            struct node* temp = root->right;
            free(root);
            return temp;
        }
        else if (root->right == NULL) {
            struct node* temp = root->left;
            free(root);
            return temp;
        }
      
        struct node* temp = minValueNode(root->right);

     
        root->key = temp->key;
        root->value = temp->value;

        root->right = deleteNode(root->right, temp->key);
    }
    return root;

}

void BinarySearchTree::printTree(node* node, int level)
{
    if (!node)
        return;
    printTree(node->right, level + 1);
    cout << string(level * 4, ' ') << "-> " << node->key << endl;
    printTree(node->left, level + 1);
}
