#include <iostream>
#include <stdlib.h>
#include <minmax.h>

using namespace std;
// dinh nghia Node
typedef int item;
typedef struct Node {
	item data;
	struct Node* left;
	struct Node* right;
	item height;
};
void init(Node* T) {
	T = NULL;
}
int Max(int a, int b) {
	return (a > b) ? a : b;
}
int height(Node* T) {
	if (T == NULL)
		return 0;
	return T->height;
}
// tao 1 node moi
Node* makeNode(int data) {
	Node* p = new Node;
	p->data = data;
	p->left = NULL;
	p->right = NULL;
	return p;
}
//tim node co gia tri x
Node* search(Node* T, int x) {
	if (T == NULL || T->data == x)
		return T;
	if (T->data < x)
		return search(T->right, x);
	return search(T->left, x);
}
// quay phai tai node T
Node* Qright(Node* T) {
	Node* x = T->left;
	Node* T2 = x->right;
	// xoay
	x->right = T;
	T->left = T2;
	// cap nhat chieu cao
	T->height = Max(height(T->left), height(T->right)) + 1;
	x->height = Max(height(x->left), height(x->right)) + 1;

	return x;
}
// quay trai tai node T
Node* Qleft(Node* T) {
	Node* y = T->right;
	Node* T2 = y->left;
	// xoay
	y->left = T;
	T->right = T2;
	// cap nhat chieu cao
	T->height = Max(height(T->left), height(T->right)) + 1;
	y->height = Max(height(y->left), height(y->right)) + 1;

	return y;
}
int getCB(Node* T) {
	if (T == NULL)
		return 0;
	return height(T->left) - height(T->right);
}
Node* Insert(Node* node, int data) {
	// B1
	if (node == NULL) {
		return (makeNode(data));
	}
	if (data < node->data) {
		node->left = Insert(node->left, data);
	}
	else
		node->right = Insert(node->right, data);
	//B2

	node->height = max(height(node->left), height(node->right)) + 1;

	//B3
	int CB = getCB(node);
	// left - left - case
	if (CB > 1 && data < node->left->data)
		return Qright(node);
	// right - right - case
	if (CB <-1 && data > node->right->data)
		return Qleft(node);
	// left right case
	if (CB > 1 && data > node->left->data) {
		node->left = Qleft(node->left);
		return Qright(node->right);
	}
	// right left case
	if (CB < -1 && data < node->right->data) {
		node->right = Qright(node->right);
		return Qleft(node);
	}
	return node;
}
void NLR(Node* root) {//duyet NLR
	if (root != NULL) {
		cout << root->data;
		NLR(root->left);
		NLR(root->right);
	}
}
void LNR(Node* root) {//duyet LNR
	if (root != NULL) {
		LNR(root->left);
		cout << root->data;
		LNR(root->right);
	}
}
void LRN(Node* root) {//duyet LRN
	if (root != NULL) {
		LRN(root->left);
		LRN(root->right);
		cout << root->data;
	}
}
Node* minValueNode(Node* node) {
	Node* current = node;
	while (current->left != NULL)
		current = current->left;
	return current;
}
Node* deleteNode(Node* root, int key) {
	if (root == NULL)
		return root;
	if (key < root->data)
		root->left = deleteNode(root->left, key);
	else if (key > root->data)
		root->right = deleteNode(root->right, key);
	else {
		if ((root->left == NULL) || (root->right == NULL)) {
			Node* temp = root->left ? root->left : root->right;
			if (temp == NULL) {
				temp = root;
				root = NULL;
			}
			else
				*root = *temp;
			free(temp);
		}
		else {
			Node* temp = minValueNode(root->right);
			root->data = temp->data;
			root->right = deleteNode(root->right, temp->data);
		}
	}
	if (root == NULL)
		return root;
	root->height = max(height(root->left), height(root->right)) + 1;
	int CB = getCB(root);
	if (CB > 1 && getCB(root->left) >= 0)
		return Qright(root);
	if (CB > 1 && getCB(root->left) < 0) {
		root->left = Qleft(root->left);
		return Qright(root);
	}
	if (CB < -1 && getCB(root->right) <= 0)
		return Qleft(root);
	if (CB < -1 && getCB(root->right) > 0) {
		root->right = Qright(root->right);
		return Qleft(root);
	}
	return root;
}
//tim do cao cua cay
int maxDepth(Node* node) {
	if (node == NULL)
		return 0;
	else {
		int lDepth = maxDepth(node->left);
		int rDepth = maxDepth(node->right);
		if (lDepth > rDepth)
			return(lDepth + 1);
		else return(rDepth + 1);
	}
}
int main() {
	Node* root = NULL;
	Node* tmp;
	int data, LC;
	do {
		system("cls");
		cout << "