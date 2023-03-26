#ifndef __CHEMIN__
#define __CHEMIN__
/*
typedef struct Node {
    int x;
    int y;
    struct Node *prev;
} Node;

typedef struct Stack {
    Node *top;
    int size;
} Stack;
*/
/* Proto Fonction */
/*
void init_stack(Stack *stack);
void push(Stack *stack, int x, int y);
Node* pop(Stack *stack);
void print_path(Stack *stack);*/
int chercher_chemin(int xd,int yd,int xa,int ya,int map [9][9],int coords[10][2]);
void marquer_chemin(int lab[9][9],int x, int y, int coords[10][2]);
void initfile();
void ajouter(int x);
void retirer(int *x);
int filevide();
void afficher_file();

#endif