#include <stdio.h>
#include <stdlib.h>
#include "avl_tree.h"

typedef struct node
{
    int value;
    struct node* left;
    struct node* right;
    short height;
}Node;

/*
    Creates and return a new Node
*/
Node* new_node(int value)
{
    Node* new =(Node*)malloc(sizeof(Node));

    if (new){
        new->value = value;
        new->left = NULL;
        new->right = NULL;
        new->height = 0;
    } else {
        printf("No memory available\n");
        exit(1);
    }
    return new;
}

short greater (short a, short b)
{
    return (a > b) ? a : b;
}

short node_height (Node* node)
{
    if (!node)
        return -1;
    else
        return node->height;
}

short balancingFactor (Node* node)
{
    if (node)
        return ( node_height(node->left) - node_height(node->right) );
    else
        return 0;
}

Node* balance(Node* root)
{
    short bf = balancingFactor(root);

    //left rotation
    if(bf < -1 && balancingFactor(root->right) <= 0)
        root = left_rotation(root);
    //right totation
    else if(bf > 1 && balancingFactor(root->left) >= 0)
        root = right_rotation(root);
    //left-right rotation
    else if(bf > 1 && balancingFactor(root->left) < 0)
        root = left_right_rotation(root);
    //right-left rotation
    else if (bf < -1 && balancingFactor(root->right) > 0)
        root = right_left_rotation(root);
    return root;
}

///////////////////////////// Rotations/////////////////////////////////////

Node* left_rotation(Node* root)
{
    Node *y, *f;

    y = root->right;// y aponta para a sub-árvore direita da raiz root
    f = y->left; // f aponta para o filho esquerdo de y
    y->left = root; // o filho esquerdo de y passa a ser a raiz root
    root->right = f; // o filho direito de r passa a ser f

    //recalcula a altura dos nós que foram movimentados
    root->height = greater(node_height(root->left), node_height(root->right)) + 1;
    y->height = greater(node_height(y->left), node_height(y->right)) + 1;

    return y;
}

Node* right_rotation(Node* root)
{
    Node *y, *f;

    y = root->left;
    f = y->right;
    y->right = root;
    root->left = f;

    root->height = greater(node_height(root->left), node_height(root->right)) + 1;
    y->height = greater(node_height(y->left), node_height(y->right)) + 1;

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
        return new_node(value);
    else{
        if (value < root->value)
            root->left = insert(root->left, value);
        else if (value > root->value)
            root->right = insert(root->right, value);
        else
            printf("\nInsertion failed!\n Element %d already exists in tree!\n", value);
    }
    
    //Recalcula a altura de todos os nós entre a raiz e o novo nó inserido
    root->height = greater(node_height(root->left), node_height(root->right))+1;

    //verifica a necessidade de rebalancear a àrvore
    root = balance(root);

    return root;
}


Node* remove_(Node* root, int key)
{
    if(!root){
        printf("Error: Root not found\n");
        return NULL;
    }else{
        // procura o nó a remove_
        if (root->value == key){
            // remove nós folhas (nós sem filhos)
            if(!root->left && !root->right){
                free(root);
                printf("Leaf element sucessfuly removed: %d\n", key);
                return NULL;
            }
            else{
                //remove_ nós que possuem 2 filhos
                if(root->left && root->right){
                    Node* aux = root->left;
                    while(aux->right)
                        aux = aux->right;
                    root->value = aux->value;
                    aux->value = key;
                    printf("Elemente sucessfuly changed: %d\n", key);
                    root->left = remove_(root->left, key);
                    return root;
                }
                else{
                    // remove_ nós que possuem apenas 1 filho
                    Node* aux;
                    if(root->left)
                        aux = root->left;
                    else
                        aux = root->right;
                    free(root);
                    printf("Elemento com 1 filho removido: %d\n", key);
                    return aux;
                }
            }
        }else{
            if (key < root->value)
                root->left = remove_(root->left, key);
            else
                root->right = remove_(root->right, key);
        }

        // Recalcula a altura de todos os nós entre a raiz e o novo nó inserido
        root->height = greater(node_height(root->left), node_height(root->right)) + 1;

        // Verifica a necessidade de rebalancear a àrvore e retorna a raiz;
        return  balance(root);
    }
}

/*
    Prints the avl tree
*/
void print(Node* root, int nivel){
    int i;
    if(root){
        print(root->right, nivel + 1);
        printf("\n\n");

        for(i = 0; i < nivel; i++)
            printf("\t");

        printf("%d", root->value);
        print(root->left, nivel + 1);
    }
}