///aici vor fi bibliotecile necesare si headerele de functii
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <limits.h>
#include <string.h>
struct Node4
{
    double valoare;
    struct Node4 *next;
};
struct Fractie{
    int numarator;
    int numitor;
};
typedef struct Fractie Fractie;
void StergereLista(struct Node4 **cap_lista);
void AddAtEnd(struct Node4 **cap_lista, double v);
void rezolvare_4(FILE *fi, FILE *fo);
int cmmdc(int a, int b);
Fractie reduce_fractie(int numarator, int numitor);
Fractie adunare(Fractie a, Fractie b);
void citire_task4(FILE *fi, int *nr_obs, double *dist, int *zi, double *start, double *target, struct Node4 **cap, double *minim);
void calcul_prob(Fractie vector[], const int a[][20], Fractie prob[][20]);
Fractie produs(Fractie a, Fractie b);