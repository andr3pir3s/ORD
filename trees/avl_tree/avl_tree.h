#ifndef AVL_TREE_H
#define AVL_TREE_H

typedef struct node Node;

Node* new_node(int value);
short greater (short a, short b);
short nodeHeight (Node* node);
Node* insert(Node* root, int value);
Node* balance(Node* root);
Node* remove_(Node* root, int key);
void print(Node* root, int level);

Node* left_rotation(Node* root);
Node* right_rotation(Node* root);
Node* left_right_rotation(Node* root);
Node* right_left_rotation(Node* root);
#endif