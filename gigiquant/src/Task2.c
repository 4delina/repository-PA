/// aici vor fi functiile efective
#include "Task2.h"
void push(struct Elem **top, double v)
{ /// adaugare element in stiva
    struct Elem *newNode = (struct Elem *)malloc(sizeof(struct Elem));
    newNode->val = v;
    newNode->next = *top;
    *top = newNode;
}
int isEmpty(const struct Elem *top)
{
    return top == NULL;
}
void stergereStiva(struct Elem **top)
{
    
    while ((*top) != NULL)
    { struct Elem *aux;
        aux = *top;
        *top = (*top)->next;
        free(aux);
    }
}
double pop(struct Elem **top)
{
    // returneaza informatia stocata in varf si sterge nodul
    if (isEmpty(*top))
        return -1.0;
    // stocheaza adresa varfului in temp
    struct Elem *temp = (*top);
    // stocheaza valoarea din varf in aux
    double aux = temp->val;
    // sterge elementul din varf
    *top = (*top)->next;
    free(temp);
    return aux;
}
void citire(struct Elem **P1, struct Elem **P2, struct Elem **P3, FILE *fi, char S1[], char S2[], char S3[])
{
    char rand[50];
    double valoare;
    int nr_stiva = 0;
    while (fgets(rand, sizeof(rand), fi) != NULL)
    {   rand[strcspn(rand, "\r\n")] = 0;
        if (sscanf(rand, "%lf", &valoare) == 1)
        {
            if (nr_stiva == 1)
                push(P1, valoare);
            else if (nr_stiva == 2)
                push(P2, valoare);
            else if (nr_stiva == 3)
                push(P3, valoare);
        }
        else
        {
            nr_stiva++;
            if (nr_stiva == 1)
                strcpy(S1, rand);
            if (nr_stiva == 2)
                strcpy(S2, rand);
            if (nr_stiva == 3)
                strcpy(S3, rand);
        }
    }
}
void afisare(struct Elem *P1, struct Elem *P2, struct Elem *P3, const char S1[], const char S2[],const char S3[], FILE *fo)
{
    int zi = 1;
    while (!isEmpty(P1) && !isEmpty(P2) && !isEmpty(P3))
    {
        double Stiva1, Stiva2, Stiva3;
        Stiva1 = pop(&P1);
        Stiva2 = pop(&P2);
        Stiva3 = pop(&P3);
        if (Stiva1 == Stiva2 && Stiva1 != Stiva3)
        {
            fprintf(fo, "ziua %d - %.2lf - %s\n", zi, fabs(Stiva1-Stiva3), S3);
        }
        if (Stiva1 == Stiva3 && Stiva2 != Stiva3)
            fprintf(fo, "ziua %d - %.2lf - %s\n", zi, fabs(Stiva2-Stiva3), S2);
        if (Stiva3 == Stiva2 && Stiva2 != Stiva1)
            fprintf(fo, "ziua %d - %.2lf - %s\n", zi, fabs(Stiva1-Stiva3), S1);
        zi++;
    }
    stergereStiva(&P1);
    stergereStiva(&P2);
    stergereStiva(&P3);

}
void rezolvare_2(FILE *fi, FILE *fo){
     ////TASK 2

        struct Elem *P1 = NULL;
        struct Elem *P2 = NULL;
        struct Elem *P3 = NULL;
        char S1[50] = "";
        char S2[50] = "";
        char S3[50] = "";
        citire(&P1, &P2, &P3, fi, S1, S2, S3);
        afisare(P1, P2, P3, S1, S2, S3, fo);
}

