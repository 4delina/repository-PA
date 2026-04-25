/// aici vor fi functiile efective
#include "Task2.h"
Queue *createQueue()
{
    Queue *q;
    q = (Queue *)malloc(sizeof(Queue));
    if (q == NULL)
        return NULL;
    q->front = q->rear = NULL;
    return q;
}
int isEmptyQueue(const Queue *q){
    return q->front == NULL;
}
void enQueue(Queue *q, const char s[], int x, float y)
{
    struct coada *newNode = (struct coada *)malloc(sizeof(struct coada));
    newNode->zi = x;
    newNode->diferenta = y;
    strcpy(newNode->oras, s);
    newNode->next = NULL;
    // nodurile noi se adauga la finalul cozii
    // daca nu exista niciun nod in coada
    if (q->rear == NULL)
        q->rear = newNode;
    else
    {
        (q->rear)->next = newNode;
        (q->rear) = newNode;
    }
    // daca exita un singur element in coada
    if (q->front == NULL)
        q->front = q->rear;
}
void deleteQueue(Queue *q)
{
    
    while (!isEmptyQueue(q))
    {
        struct coada *aux;
        aux = q->front;
        q->front = q->front->next;
        // printf (”%d” ,aux - ¿ val );
        free(aux);
    }
    free(q);
}
void push(struct Elem **top, float v)
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
float pop(struct Elem **top)
{
    // returneaza informatia stocata in varf si sterge nodul
    if (isEmpty(*top))
        return INT_MIN;
    // stocheaza adresa varfului in temp
    struct Elem *temp = (*top);
    // stocheaza valoarea din varf in aux
    float aux = temp->val;
    // sterge elementul din varf
    *top = (*top)->next;
    free(temp);
    return aux;
}
int este_oras(const char s[])
{
    for (int i = 0; s[i] != 0; i++)
        if (strchr("0123456789", s[i]) != NULL)
            return 0;
    return 1;
}
void citire(struct Elem **P1, struct Elem **P2, struct Elem **P3, FILE *fi, char S1[], char S2[], char S3[])
{
    char rand[256];
    float valoare;
    int nr_stiva = 0;
    while (fgets(rand, sizeof(rand), fi) != NULL)
    {
        if (este_oras(rand) == 0)
        {
            if (nr_stiva == 1)
            {
                sscanf(rand, "%f", &valoare);
                push(P1, valoare);
            }
            else if (nr_stiva == 2)
            {
                sscanf(rand, "%f", &valoare);
                push(P2, valoare);
            }
            else if (nr_stiva == 3)
            {
                sscanf(rand, "%f", &valoare);
                push(P3, valoare);
            }
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
void afisare(struct Elem *P1, struct Elem *P2, struct Elem *P3, FILE *fi, char S1[], char S2[], char S3[], FILE *fo)
{
    Queue *q;
    q = createQueue();
    int zi = 1;
    while (!isEmpty(P1) && !isEmpty(P2) && !isEmpty(P3))
    {
        float Stiva1, Stiva2, Stiva3;
        Stiva1 = pop(&P1);
        Stiva2 = pop(&P2);
        Stiva3 = pop(&P3);
        if (Stiva1 == Stiva2 && Stiva1 != Stiva3)
        {
            enQueue(q, S3, zi, fabs(Stiva3 - Stiva1));
        }
        if (Stiva1 == Stiva3 && Stiva2 != Stiva3)
            enQueue(q, S2, zi, fabs(Stiva2 - Stiva3));
        if (Stiva3 == Stiva2 && Stiva2 != Stiva1)
            enQueue(q, S1, zi, fabs(Stiva2 - Stiva1));
        zi++;
    }

    /// afisare coada
    while (!isEmptyQueue(q))
    {
        const struct coada *aux = q->front;
        fprintf(fi, "ziua %d - %f - %s", aux->zi, aux->diferenta, aux->oras);
        q->front = (q->front)->next;
        if (q->front == NULL)
            q->rear = NULL;
    }
    deleteQueue(q);
}
