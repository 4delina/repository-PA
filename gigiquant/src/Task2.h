///aici vor fi bibliotecile necesare si headerele de functii
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <limits.h>
#include <string.h>
struct Elem
{
    float val;
    struct Elem *next;
};
struct coada
{
    char oras[25];
    float diferenta;
    int zi;
    struct coada *next;
};
struct Q{
struct coada *front ,* rear ;
};
typedef struct Q Queue;
Queue *createQueue();
int isEmptyQueue(const Queue q);
void enQueue(Queue *q, const char s[], int x, float y);
void deleteQueue(Queue *q);
int este_oras(const char s[]);
void push(struct Elem **top, int v);
int isEmpty(const struct Elem *top);
int pop(struct Elem **top);
void citire(struct Elem **P1, struct Elem **P2, struct Elem **P3, FILE *fi, char S1[], char S2[], char S3[]);
void afisare(struct Elem *P1, struct Elem *P2, struct Elem *P3, FILE *fi, char S1[], char S2[], char S3[], FILE *fo);