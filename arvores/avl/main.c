#include <stdio.h>
#include <stdlib.h>


typedef struct node
{
    int value;
    struct node* left;
    struct node* right;
    short height;
}Node;

// PROTÓTIPOS
Node* newNode(int value);
short greater (short a, short b);
short nodeHeight (Node* node);
Node* insert(Node* root, int value);
Node* balance(Node* root);

int main(int argc, char const *argv[])
{
    
    return 0;
}

Node* newNode(int value)
{
    Node* new =(Node*) malloc(sizeof(Node));

    if (new){
        new->value = value;
        new->left = NULL;
        new->right = NULL;
        new->height = 0;
    }else{
        printf("\nallocation failed in newNode!\n");
        exit(1);
    }
    return new;
}

short greater (short a, short b)
{
    return (a > b) ? a : b;
}

short nodeHeight (Node* node)
{
    if (!node)
        return -1;
    else
        return node->height;
}

short balancingFactor (Node* node)
{
    if (node)
        return ( nodeHeight(node->left) - nodeHeight(node->right) );
    else
        return 0;
}

Node* left_rotation(Node* root)
{
    Node *y, *f;

    y = root->right;// y aponta para a sub-árvore direita da raiz root
    f = y->left; // f aponta para o filho esquerdo de y
    y->left = root; // o filho esquerdo de y passa a ser a raiz root
    root->right = f; // o filho direito de r passa a ser f

    //recalcula a altura dos nós que foram movimentados
    root->height = greater(nodeHeight(root->left), nodeHeight(root->right)) + 1;
    y->height = greater(nodeHeight(y->left), nodeHeight(y->right)) + 1;

    return y;
}

Node* right_rotation(Node* root)
{
    Node *y, *f;

    y = root->left;
    f = y->right;
    y->right = root;
    root->left = f;

    root->height = greater(nodeHeight(root->left), nodeHeight(root->right)) + 1;
    y->height = greater(nodeHeight(y->left), nodeHeight(y->right)) + 1;

    return y;
}

Node* left_right_rotation(Node* root)
{
    root->left = left_rotation(root->left);
    return right_rotation(root);
}

Node* right_left_rotation(Node* root)
{
    root->right = right_rotation(root->right);
    return left_rotation(root);
}

/*
    Insere um novo nó na árvore
    root -> raiz da árvore
    x -> valor a ser inserido
    retorno: endereço do novo nó ou nova raiz após o balanceamento
 */
Node* insert(Node* root, int value)
{
    if (!root)
        return newNode(value);
    else{
        if (value < root->value)
            root->left = insert(root->left, value);
        else if (value > root->value)
            root->right = insert(root->right, value);
        else
            printf("\nInsertion failed!\n Element %d already exists in tree!\n", value);
    }
    
    //Recalcula a altura de todos os nós entre a raiz e o novo nó inserido
    root->height = greater(nodeHeight(root->left), nodeHeight(root->right))+1;

    //verifica a necessidade de rebalancear a àrvore
    root = balance(root);

    return root;
}

Node* balance(Node* root)
{
    short bf = balancingFactor(root);

    //left rotation
    if(bf < -1 && balancingFactor(root->right) <= 0)
        root = left_rotation(root);
    //right totation
    else if(bf < 1 && balancingFactor(root->left) >= 0)
        root = right_rotation(root);
    //left-right rotation
    else if(bf > 1 && balancingFactor(root->left) < 0)
        root = left_right_rotation(root);
    //right-left rotation
    else if (bf < -1 && balancingFactor(root->right) > 0)
        root = right_left_rotation(root);
    return root;
}