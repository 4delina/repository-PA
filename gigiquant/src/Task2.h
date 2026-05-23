///aici vor fi bibliotecile necesare si headerele de functii
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <limits.h>
#include <string.h>
struct Elem
{
    double val;
    struct Elem *next;
};
void push(struct Elem **top, double v);
int isEmpty(const struct Elem *top);
void stergereStiva(struct Elem **top);
double pop(struct Elem **top);
void citire(struct Elem **P1, struct Elem **P2, struct Elem **P3, FILE *fi, char S1[], char S2[], char S3[]);
void afisare(struct Elem *P1, struct Elem *P2, struct Elem *P3, const char S1[], const char S2[], const char S3[], FILE *fo);
void rezolvare_2(FILE *fi, FILE *fo);