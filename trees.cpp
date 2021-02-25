// Original author: Morgan McKinney 2/2020

#define NULL 0
#include <stdlib.h>
#include <bits/stdc++.h>
#include <iostream>
using namespace std;

// Point structure
typedef struct points {
	int key; // What value a tree is sorted by
	int x;
	int y;
	int z;
} point;

// Tree node structure
// (Referenced CS315 notes from lecture 5)
typedef struct treeNodes {
	point data; // Contains (X, Y, Z) and key
	treeNodes *left, *right;
} treeNode;

// Make node
// (Referenced CS315 notes from lecture 5)
treeNode *makeNode(point data) {
	treeNode *answer = (treeNode *) malloc(sizeof(treeNode));
	answer->data = data;
	answer->left = NULL;
	answer->right = NULL;
	return answer;
} // makeNode()

// Find closest value
// (Referenced www.geeksforgeeks.org/find-closest-element-binary-search-tree/)
void findClosestValue(treeNode *tree, int key, int &minDiff, int &closestKey) {
	// Tree is empty
	if(tree == NULL) {
		return;
	}
	// Exact match of key found
	else if(tree->data.key == key) {
		closestKey = key;
		return;
	}
	// Continue searching
	else {
		// Update minDiff and closestKey based on current leaf
		if(minDiff > abs(tree->data.key - key)) {
			minDiff = abs(tree->data.key - key);
			closestKey = tree->data.key;
		}
		// Traverse tree
		if(key < tree->data.key) { // Key is smaller, go left
			findClosestValue(tree->left, key, minDiff, closestKey);
		}
		else { // Key is greater, go right
			findClosestValue(tree->right, key, minDiff, closestKey);
		}
	}
} // findClosestValue()

// Search tree
// (Referenced CS315 notes from lecture 5)
treeNode *searchTree(treeNode *tree, int key) {
	// Find closest match to key
	int minDiff = INT_MAX; // Min difference between closest and desired key
	int closestKey = -1; // Closest key to desired key
	findClosestValue(tree, key, minDiff, closestKey);
	// Search for closest key
	if(tree == NULL) { // Tree is empty
		return(NULL);
	}
	else if(tree->data.key == closestKey) { // Key found
		return(tree);
	}
	else if(closestKey < tree->data.key) { // Key is smaller, go left
		return(searchTree(tree->left, closestKey));
	}
	else { // Key is greater, go right
		return(searchTree(tree->right, closestKey));
	}
} // searchTree()

// Update key
point updateKey(point data, int key) {
	switch(key) {
		case 1: // Sorted on X value
			data.key = data.x;
			break;
		case 2: // Sorted on Y value
			data.key = data.y;
			break;
		case 3: // Sorted on Z value
			data.key = data.z;
			break;
		default:
			cout << "ERROR: Invalid variable to update key!" << endl;
			break;
	}
	return data;
} // updateKey()

// Insert tree
// (Referenced CS315 notes from lecture 5)
void insertTree(treeNode *tree, point data, int key) {
	// Update keys
	data = updateKey(data, key);
	tree->data = updateKey(tree->data, key);
	// Assumes empty tree is pseudo-node with infinite data
	treeNode *parent = NULL;
	treeNode *newNode = makeNode(data);
	while(tree != NULL) { // Dive down tree
		tree->data = updateKey(tree->data, key); // Update leaves
		parent = tree;
		if(data.key <= tree->data.key) { // Key is smaller, go left
			tree = tree->left;
		}
		else { // Key is greater, go right
			tree = tree->right;
		}
	}
	// Compare key to last parent to determine where to insert	
	if(data.key <= parent->data.key) { // Key is smaller, insert on left
		parent->left = newNode;
	}
	else { // Key is greater, insert on right
		parent->right = newNode;
	}
} // insertTree()

// Visit tree, print each point to standard output on separate line
void visit(treeNode *tree) {
	if(tree == NULL) { // Check for valid leaf
		cout << "ERROR: No point to print!" << endl;
	}
	else {
		cout << "(" << tree->data.x;
		cout << ", " << tree->data.y;
		cout << ", " << tree->data.z << ")" << endl;
	}
}

// Symmetric traversal
// (Referenced CS315 notes from lecture 5)
void symmetric(treeNode *tree) {
	if(tree == NULL) { // Do nothing
	}
	else {
		symmetric(tree->left);
		visit(tree);
		symmetric(tree->right);
	}
} // symmetric()

// Preorder traversal
// (Referenced CS315 notes from lecture 5)
void preorder(treeNode *tree1, treeNode *tree2) {
	if(tree1 == NULL) { // Do nothing
	}
	else {
		insertTree(tree2, tree1->data, 2); // Insert into T2
		preorder(tree1->left, tree2);
		preorder(tree1->right, tree2);
	} // Not empty
} // preorder()

// Postorder traversal
// (Referenced CS315 notes from lecture 5)
void postorder(treeNode *tree) {
	if(tree == NULL) { // Do nothing
	}
	else {
		postorder(tree->left);
		postorder(tree->right);
		visit(tree);
	} // Not empty
} // postorder()

int main(int argc, char* argv[]) {
	// Take single int parameter: n data points in tree
	if(argc != 2) { // Check for correct amount of parameters
		cout << "Usage: ./randGen.pl seed | trees n";
		return 0;
	}
	// Read n points from standard input with 3 int components: X, Y, and Z
	int n = atoi(argv[1]);
	// Initialize root of T1
	point data;
	cin >> data.x >> data.y >> data.z;
	data.key = data.x; // T1 is sorted on X value
	treeNode *T1 = makeNode(data);
	for(int i = 1; i < n; i += 1) { // Initialize n leaves
		cin >> data.x >> data.y >> data.z;
		insertTree(T1, data, 1); // Insert into T1
	}
	// Traverse T1 in symmetric order
	symmetric(T1);
	// Initialize root of T2
	data.key = data.y; // Update key for root of T2
	treeNode *T2 = makeNode(data);
	// Traverse T1 in preorder
	preorder(T1, T2);
	// Traverse T2 in postorder
	postorder(T2);
	// Read one more int from standard input: probe p, a Y value
	int probe;
	cin >> probe;
	// Search for p in T2, printing last point it ecounters through T2
	// May have p itself as Y value, or Y value may simply be close
	visit(searchTree(T2, probe));
	return 0; // Exit program
} // main()
