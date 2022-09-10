#include <stdio.h>
#include <stdlib.h>


typedef struct arvno ArvNo;
struct arvno 
{
    char info;
    ArvNo* left;
    ArvNo* right;
};
 
typedef struct arv{
    ArvNo* root;
}Arv;


/////protótipos////
ArvNo* create_node(char info, ArvNo* left, ArvNo* right);
Arv* create_tree (ArvNo* root);
static void print_tree (ArvNo* r);


///////////////////////
/////MAIN FUNCTION////
int main(void)
{
    Arv* a = create_tree(
                create_node('a',
                    create_node('b',
                        NULL, 
                        create_node('d', NULL, NULL)
                        ),
                        create_node('c',
                            create_node('e', NULL, NULL), create_node('f', NULL, NULL)
                            )
                )
            );
    print_tree(a->root);
    return 0;
}

ArvNo* create_node(char info, ArvNo* left, ArvNo* right)
{
    ArvNo* new = (ArvNo*) malloc(sizeof (ArvNo));
    new->info = info;
    new->left = left;
    new->right = right;
    return new;
}

Arv* create_tree (ArvNo* root)
{
    Arv* tree = (Arv*) malloc(sizeof(Arv));
    tree->root = root;
    return tree;
}

static void print_tree(ArvNo* root)
{   
    printf("<");
    if (root)
    {
        printf("%c", root->info); // mostra a informação
        print_tree(root->left);  // imprime sae
        print_tree(root->right); // imprime sad
    }
    printf(">");
}