#include <stdio.h>
#include <stdlib.h>

/*
    1.Todo nó é vermelho ou preto.
    2.A raiz é preta.
    3.Toda folha (NIL) é preta.
    4.Se um nó é vermelho, então os seus filhos são pretos.
    5.Para cada nó, todos os caminhos simples do nó até folhas descendentes contêm o mesmo número de nós pretos.

    https://www.geeksforgeeks.org/c-program-red-black-tree-insertion/
*/

typedef struct node{
    int value;
    char color;
    Node *right;
    Node *left;
    Node *parent;
}Node;

Node* new_node(int value)
{
    Node* new = (Node*)malloc(sizeof(Node));
    if (new){
        new->value = value;
        new->color = 'R';
        new->left = NULL;
        new->right = NULL;
        new->parent = NULL;
    }
    else{
        printf("Memoru allocation faild!\n");
        exit(1);
    }
    return new;
}

/*
    *Cada novo nó inserido, por definição possui cor rubro;
    *Faça uma inserção exatamente igual em uma ABB;
    * Após a inserção, verifique se as propriedades ainda se mantém.
    Lembre-se:
    * A raiz da árvore é sempre Negra;
    * Se o parent de new for negro, tudo certo
    * Se o parent de new for rubro, rotações ou alterações de cor precisam ser feitas;
*/
Node* insert(Node* root, int value)
{   
    // if the tree's empty, return a new node
    if (!root){
        Node* new = new_node(value);
        new->color = 'B';
        return new;
    }
    // Otherwise, recur down the tree
    if (value < root->value)
        root->left = insert(root->left, value);
    else if (value > root->value)
        root->right = insert(root->right, value);   
    
}