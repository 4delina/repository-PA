#include "Task3.h"
/// add lista in the beggining modificata pt stocks
void add_listaactiuni_BEG(Stocklist **cap, const char sir[])
{
    Stocklist *newNode = (Stocklist *)malloc(sizeof(Stocklist));
    strcpy(newNode->symbol, sir);
    newNode->next = *cap;
    *cap = newNode;
}

/// add lista at the end modificata pt stocks
void add_listaactiuni_END(Stocklist **cap, const char sir[])
{
    if (*cap == NULL){
        add_listaactiuni_BEG(cap, sir);
    return;}
    Stocklist *aux = *cap;
    while (aux->next != NULL)
        aux = aux->next;
    Stocklist *newNode = (Stocklist *)malloc(sizeof(Stocklist));
    strcpy(newNode->symbol, sir);
    newNode->next = NULL;
    aux->next = newNode;
}

void stergere_lista(Stocklist **head){
    Stocklist *headcopy;
    while(*head!=NULL){
        headcopy=(*head)->next;
        free(*head);
        *head=headcopy;}
        *head=NULL;
}
///functie care afla indexul unei actiuni in sirul initial
int index_actiune(Stocklist *head, const char s[]){
    int i=0;
    while(head!=NULL){
        if(strcmp(head->symbol, s)==0)
            return i;
        i++;
        head=head->next;
    }
    return -1;
}

/// citesc intr-un sir toate actiunile si le introduc intr-o lista
void citire_task3(FILE *fi, char sir[], Stocklist **head)
{
    fgets(sir, 100, fi);
    sir[strcspn(sir, "\n")] = '\0'; /// scot newline de la final ca fgets il citeste cu totul
    char sir_copie[100];
    strcpy(sir_copie, sir);
    char *p = strtok(sir_copie, ",");
    while (p != NULL)
    {
        add_listaactiuni_END(head, p);
        p = strtok(NULL, ",");
    }
}

///CREEZ ARBORELE ACUM
TreeNode *creeare_arbore(Stocklist *l1, Stocklist *l2, double valori[][10], int col, int nrLinii){
    if(l2==NULL)
        return NULL;
    TreeNode *node=malloc(sizeof(TreeNode));
    node->stocks=l2;
    node->left=NULL;
    node->right=NULL;
    node->depth=col;
    if(col>=nrLinii-1)
        return node;
    Stocklist *dreapta=NULL;
    Stocklist *stanga=NULL;
    Stocklist *aux=l2;
    while(aux!=NULL){
        int i=index_actiune(l1, aux->symbol);
        if(valori[col+1][i]<valori[col][i])
            add_listaactiuni_END(&stanga, aux->symbol);
        else add_listaactiuni_END(&dreapta, aux->symbol);
    aux=aux->next;
    }
    if(stanga!=NULL)
        node->left=creeare_arbore(l1, stanga, valori, col+1, nrLinii);
    if(dreapta!=NULL)
       node->right=creeare_arbore(l1, dreapta, valori, col+1, nrLinii);
    return node;
}
///CAUT NODURILE BUNE IN ARBORE
///ELIBEREZ ARBORELE
void stergere_arbore(TreeNode *root){
    if(root==NULL)
        return;
    stergere_arbore(root->left);
    stergere_arbore(root->right);
    if(root->stocks!=NULL)
        stergere_lista(&(root->stocks));
    free(root);
}

///functie care verifica daca un nod e arbore
int este_frunza(const TreeNode *node){
    if(node!=NULL && node->left==NULL && node->right==NULL)
        return 1;
    else return 0;
}

///functie care verifica daca sunt pathuri opuse 
int path_opuse(const int v1[], int lung1,const int v2[], int lung2){
    if(lung1!=lung2)
        return 0;
    for(int i=0; i<lung1; i++)
        if(v1[i]==v2[i])
            return 0;
    return 1;
}

///functie crae imi copiaza path-ul catre o frunza
void copiaza_path(int destinatie[],const int sursa[], int lungime){
    for(int i=0; i<lungime; i++)
        destinatie[i]=sursa[i];
}

///colectez frunzele 
void colectez_frunze(TreeNode *root, int path[], int lungime, LeafPath frunze[], int *nrFrunze){
    if(root==NULL)
        return;
    if(este_frunza(root)){
        frunze[*nrFrunze].leaf=root;
        frunze[*nrFrunze].lungime=lungime;
        copiaza_path(frunze[*nrFrunze].path, path, lungime);
        (*nrFrunze)++;
        return;
    }
    if(root->left!=NULL){
        path[lungime]=0;
        colectez_frunze(root->left, path, lungime+1, frunze, nrFrunze);

    }
    if(root->right!=NULL){
        path[lungime]=1;
        colectez_frunze(root->right, path, lungime+1, frunze, nrFrunze);

    }
}
int lista_contine(Stocklist *head, const char symbol[]){
    while(head!=NULL){
        if(strcmp(head->symbol, symbol)==0)
            return 1;
        head=head->next;
    }
    return 0;
}
int frunza_actiunii(LeafPath frunze[], int nrFrunze, char symbol[]){
    for(int i=0; i<nrFrunze; i++)
        if(lista_contine(frunze[i].leaf->stocks, symbol))
            return i;
    return -1;
}
///gasesc frunzele opuse
void frunze_opuse(TreeNode *root,Stocklist *lista_initiala, FILE *fo){
    LeafPath frunze[100];
    int nrFrunze=0;
    int path[10];
    int ok=1;
    colectez_frunze(root, path, 0, frunze, &nrFrunze);
    for(Stocklist *a=lista_initiala; a!=NULL; a=a->next){
        int frunzaA=frunza_actiunii(frunze, nrFrunze, a->symbol);
        if(frunzaA==-1)
            continue;
        for(Stocklist *b=a->next; b!=NULL; b=b->next){
            int frunzaB=frunza_actiunii(frunze, nrFrunze, b->symbol);
            if(frunzaB==-1)
                continue;
            if(path_opuse(frunze[frunzaA].path, frunze[frunzaA].lungime, frunze[frunzaB].path, frunze[frunzaB].lungime)){
                if(!ok)
                    fprintf(fo, "\n");
                fprintf(fo, "%s-%s", a->symbol, b->symbol);
                ok=0;
            }
                
        }
    }
}
void rezolvare_3(FILE *fi, FILE *fo){
     char sir_actiuni_initiale[100] = "";
        Stocklist *lista_initiala = NULL;
        citire_task3(fi, sir_actiuni_initiale, &lista_initiala);
        /// citesc valorile portofoliilor si formez arborele
        double valori[5][10];
        int nrLinii = 0;
        while (fscanf(fi, "%lf, %lf, %lf, %lf, %lf, %lf, %lf, %lf ,%lf, %lf", &valori[nrLinii][0], &valori[nrLinii][1], &valori[nrLinii][2], &valori[nrLinii][3], &valori[nrLinii][4], &valori[nrLinii][5], &valori[nrLinii][6], &valori[nrLinii][7], &valori[nrLinii][8], &valori[nrLinii][9]) == 10)
         nrLinii++; /// toate valorile portofoliilor, inclusiv cele initiale
        
        /// momentan am lista initiala de actiuni in ordine si toate valoriile portofoliilor
        TreeNode *root = creeare_arbore(lista_initiala, lista_initiala, valori, 0, nrLinii);
        frunze_opuse(root, lista_initiala, fo);
        stergere_arbore(root);
}