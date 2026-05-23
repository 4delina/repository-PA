/// aici vor fi functiile efective
#include "Task4.h"
int cmmdc(int a, int b)
{
    while (b != 0)
    {
        int r = a % b;
        a = b;
        b = r;
    }
    return a;
}
Fractie reduce_fractie(int numarator, int numitor)
{
    Fractie f;
    if (numarator == 0)
    {
        f.numarator = 0;
        f.numitor = 1;
        return f;
    }
    int d = cmmdc(numarator, numitor);
    f.numitor = numitor / d;
    f.numarator = numarator / d;
    return f;
}
Fractie adunare(Fractie a, Fractie b)
{
    return reduce_fractie(a.numarator * b.numitor + b.numarator * a.numitor, a.numitor * b.numitor);
}
void StergereLista(struct Node4 **cap_lista)
{
    struct Node4 *p;
    while (*cap_lista != NULL)
    {
        p = (*cap_lista)->next;
        free(*cap_lista);
        *cap_lista = p;
    }
    *cap_lista = NULL;
}
void AddAtEnd(struct Node4 **cap_lista, double v)
{
    struct Node4 *newNode = (struct Node4 *)malloc(sizeof(struct Node4));
    newNode->valoare = v; // stocheaza informatia nodului nou
    newNode->next = NULL;

    // daca lista este vida , se modifica adresa de inceput
    if (*cap_lista == NULL)
    {
        *cap_lista = newNode;
        return;
    }

    struct Node4 *aux = *cap_lista;
    while (aux->next != NULL)
        aux = aux->next;
    // se adauga noul element in lista
    aux->next = newNode;
    newNode->next = NULL; // final lista
}
Fractie produs(Fractie a, Fractie b)
{
    return reduce_fractie(a.numarator * b.numarator, a.numitor * b.numitor);
}
void calcul_prob(Fractie vector[], const int a[][20], Fractie prob[][20])
{
    Fractie nou[20];
    for (int i = 0; i < 20; i++)
    {
        Fractie x, suma;
        suma.numarator = 0;
        suma.numitor = 1;
        for (int k = 0; k < 20; k++)
            if (a[k][i] != 0)
            {
                x = produs(prob[k][i], vector[k]);
                suma = adunare(suma, x);
            }
        nou[i] = suma;
    }
    for (int i = 0; i < 20; i++)
        vector[i] = nou[i];
}
void citire_task4(FILE *fi, int *nr_obs, double *dist, int *zi, double *start, double *target, struct Node4 **cap, double *minim)
{
    fscanf(fi, "%d", nr_obs);
    fscanf(fi, "%lf", dist);
    fscanf(fi, "%d", zi);
    fscanf(fi, "%lf", start);
    fscanf(fi, "%lf", target);
    (*start) = (*start) - fmod(*start, *dist);
    (*target) = (*target) - fmod(*target, *dist);
    double x;
    double m = -1;
    for (int i = 0; i < (*nr_obs); i++)
    {
        fscanf(fi, "%lf", &x);
        x = x - fmod(x, *dist);
        if (m == -1)
            m = x;
        else if (x < m)
            m = x;
        AddAtEnd(cap, x);
    }
    *minim = m;
}
void rezolvare_4(FILE *fi, FILE *fo)
{
    int nr_obs;
    double dist;          /// dist=dimensiunea intervalului
    int zi;               /// numarul de zile la care ne vom raporta pentru probabilitatea lui target
    double start, target; /// P_start si P_target;
    double minim;         /// voi salva cea mai mica valoare din lista cu preturi observate, ca sa pot forma o ordine
    struct Node4 *cap = NULL;
    citire_task4(fi, &nr_obs, &dist, &zi, &start, &target, &cap, &minim);
    /// in citire am citit toate cele 10 observatii si am format lista cu datele modificate la valoarea intervalului de care apartin
    /// parcurg lista cu valori, formez matricea de adiacenta;
    int a[20][20] = {0};
    struct Node4 *aux = cap;
    double x = aux->valoare;
    aux = aux->next;
    /// parcurg lista si stochez in matrice de cate ori este fiecare interval accesat si devine activ, i-intervalul precedent, j-intervalul nou activat
    while (aux != NULL)
    {
        double y = aux->valoare;
        int i, j;
        i = (x - minim) / dist;
        j = (y - minim) / dist;
        a[i][j]++;
        x = y;
        aux = aux->next;
    }
    /// PROBABILITATEA DE TARGET IN PRIMA ZI
    if (start == target)
        fprintf(fo, "%d\n", 1);
    else
        fprintf(fo, "%d\n", 0);
    Fractie prob[20][20];
    /// aici formez matricea de probabilitati din prima zi
    for (int i = 0; i < 20; i++)
    {
        int numit = 0;
        for (int j = 0; j < 20; j++)
            if (a[i][j] != 0)
                numit += a[i][j];
        for (int j = 0; j < 20; j++)
            if (numit == 0)
            {
                prob[i][j].numarator = 0;
                prob[i][j].numitor = 1;
            }
            else
                prob[i][j] = reduce_fractie(a[i][j], numit);
    }
    /// in prob am practic sagetile orientate din diferite valori in diferite valori si probabilitatea ca o valoare sa devina activa din alta
    /// acum trebuie pentru nr de zile (zi) iteratii sa calculez probabilitatea in fiecare valoare dintr-un vector si apoi sa afisez la fiecare iteratie probabiliatea pentru target
    Fractie vector[20];
    for (int i = 0; i < 20; i++){
        int index_start=(int)((start - minim) / dist);
        if (i == index_start)
        {
            vector[i].numarator = 1;
            vector[i].numitor = 1;
        }
        else
        {
            vector[i].numarator = 0;
            vector[i].numitor = 1;
        }
    }
    int target_index=(int)((target - minim) / dist);
    for (int i = 1; i < zi-1; i++)
    {
        calcul_prob(vector, a, prob);
        if(vector[target_index].numitor==1)
            fprintf(fo, "%d\n", vector[target_index].numarator);
        else
             fprintf(fo, "%d/%d\n", vector[target_index].numarator, vector[target_index].numitor);
    }
    calcul_prob(vector, a, prob);
        if(vector[target_index].numitor==1)
            fprintf(fo, "%d", vector[target_index].numarator);
        else
             fprintf(fo, "%d/%d", vector[target_index].numarator, vector[target_index].numitor);
    StergereLista(&cap);
}