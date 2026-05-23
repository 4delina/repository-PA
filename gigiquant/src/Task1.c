/// aici vor fi functiile efective
#include "Task1.h"

double sumaVolatilitateTotal(struct Node *cap_lista, double randMediu)
{
    double sumaVol = 0;
    struct Node *p;
    for (p = cap_lista; p !=NULL && p->next != NULL; p = p->next)
    { /// mergem pana la penultimul elem al listei, calculez randT pt ziua urm la fiecare pas
        double randT;
        randT = p->next->randament;
        sumaVol = sumaVol + ((randT - randMediu) * (randT - randMediu));
    }
    return sumaVol;
}
double sumaRandamentTotal(struct Node *cap_lista)
{

    double sumaRandT = 0;
    struct Node *p;
    for (p = cap_lista; p!=NULL && p->next != NULL; p = p->next)
    {                 /// mergem pana la penultimul elem al listei, calculez randT pt ziua urm la fiecare pas
        double randT; /// valoarea randamentului incepand cu ziua 2 la momentul t
        double pretT; /// pretul incepand din ziua 2
        double pretA; /// pretul anterior, incepe din ziua 1
        pretT = p->next->valoare;
        pretA = p->valoare;
        randT = (pretT - pretA) / pretA;
        p->next->randament = randT;
        sumaRandT += randT;
    }
    return sumaRandT;
}
void stergereLista(struct Node **cap_lista)
{
    struct Node *p;
    while (*cap_lista != NULL)
    {
        p = (*cap_lista)->next;
        free(*cap_lista);
        *cap_lista = p;
    }
    *cap_lista = NULL;
}
void addAtEnd(struct Node **cap_lista, double v)
{
    struct Node *newNode = (struct Node *)malloc(sizeof(struct Node));
    newNode ->valoare = v; // stocheaza informatia nodului nou
    newNode->next = NULL;

    // daca lista este vida , se modifica adresa de inceput
    if (*cap_lista == NULL){
        *cap_lista=newNode;
        return;}

    struct Node *aux = *cap_lista;
    while (aux ->next != NULL)
            aux = aux ->next;
        // se adauga noul element in lista
    aux ->next = newNode;
        newNode ->next = NULL; // final lista
    
}

void rezolvare_1(FILE *fi, FILE *fo){
     /// Introduceti numarul total de observatii al portofoliului studiat
        int nrZile, i;
        fscanf(fi, "%d", &nrZile);
        struct Node *cap_lista = NULL;
        double valoare;
        for (i = 0; i < nrZile; i++)
        {
            fscanf(fi, "%lf", &valoare);
            addAtEnd(&cap_lista, valoare);
        }

        /// RANDAMENT MEDIU CALCUL

        double sumaRandT = sumaRandamentTotal(cap_lista);

        double randMediu = sumaRandT / (nrZile - 1);

        /// VOLATILITATE CALCUL

        double volatilitate = 0;
        double sumaVol = sumaVolatilitateTotal(cap_lista, randMediu);
        volatilitate = sumaVol / (nrZile - 1);
        volatilitate = sqrt(volatilitate);

        /// SHARPE RATIO

        double S = randMediu / volatilitate;

        /// REZULTATE

        fprintf(fo, "%.3lf\n", ((int)(randMediu * 1000)) / 1000.0);
        fprintf(fo, "%.3lf\n", ((int)(volatilitate * 1000)) / 1000.0);
        fprintf(fo, "%.3lf\n", ((int)(S * 1000)) / 1000.0);
        stergereLista(&cap_lista);
}
