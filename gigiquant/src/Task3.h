#include <stdio.h>
#include <string.h>
#include <stdlib.h>
/// structura lista pt actiuni, retine doar numele actiuniilor in ordinea introducerii
typedef struct Stocklist
{
    char symbol[5];
    struct Stocklist *next;
} Stocklist;

/// structura nod de arbore, cotnine lista de actiuni si st dr
typedef struct TreeNode
{
    Stocklist *stocks;
    struct TreeNode *left;
    struct TreeNode *right;
    int depth;
} TreeNode;

/// structura pentru path-ul frunzelor
typedef struct LeafPath
{
    TreeNode *leaf;
    int path[10];
    int lungime;
} LeafPath;

/// add lista in the beggining modificata pt stocks
void add_listaactiuni_BEG(Stocklist **cap, const char sir[]);
/// add lista at the end modificata pt stocks
void add_listaactiuni_END(Stocklist **cap, const char sir[]);
void stergere_lista(Stocklist **head);
/// functie care afla indexul unei actiuni in sirul initial
int index_actiune(Stocklist *head, const char s[]);
/// citesc intr-un sir toate actiunile si le introduc intr-o lista
void citire_task3(FILE *fi, char sir[], Stocklist **head);
/// CREEZ ARBORELE ACUM
TreeNode *creeare_arbore(Stocklist *l1, Stocklist *l2, double valori[][10], int col, int nrLinii);
/// ELIBEREZ ARBORELE
void stergere_arbore(TreeNode *root);
/// functie care verifica daca un nod e arbore
int este_frunza(const TreeNode *node);
/// functie care verifica daca sunt pathuri opuse
int path_opuse(const int v1[], int lung1, const int v2[], int lung2);
/// functie crae imi copiaza path-ul catre o frunza
void copiaza_path(int destinatie[], const int sursa[], int lungime);
/// functie ce imi colecteaza frunzele
void colectez_frunze(TreeNode *root, int path[], int lungime, LeafPath frunze[], int *nrFrunze);
int lista_contine(Stocklist *head, const char symbol[]);
int frunza_actiunii(LeafPath frunze[], int nrFrunze, char symbol[]);
/// gasesc frunzele opuse
void frunze_opuse(TreeNode *root, Stocklist *lista_initiala, FILE *fo);
void rezolvare_3(FILE *fi, FILE *fo);