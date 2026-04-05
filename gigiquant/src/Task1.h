///aici vor fi bibliotecile necesare si headerele de functii
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
struct Node
{
    double valoare;
    double randament;
    struct Node *next;
};
double sumaVolatilitateTotal(struct Node *cap_lista,double randMediu);
double sumaRandamentTotal(struct Node *cap_lista);
void stergereLista(struct Node **cap_lista);
void addAtEnd(struct Node **cap_lista, double v);
