#include "Task1.h"
#include "Task2.h"
int main(int argc, const char *argv[])
{
    /// Deschidere fisiere de citire si scriere
    FILE *fi = fopen(argv[1], "r");
    FILE *fo = fopen(argv[2], "w");
    if (fi == NULL || fo == NULL)
    {
        printf("Eroare la deschiderea fisierelor!");
        return 1;
    }
    const char *fisiere[]={ "data1.in", "data2.in", "data3.in", "data4.in", "data5.in", "data6.in", "data7.in", "data8.in", "data9.in", "data10.in","data11.in", "data12.in", "data13.in", "data14.in", "data15.in", "data16.in", "data17.in", "data18.in", "data19.in", "data20.in"};
    int task=0;
    for(int i=0; i<=19; i++){
        if(strcmp(argv[1], fisiere[i])==0){
            task = i/5 + 1 ;
            break;}
    }
    if(task==1){
    /// Introduceti numarul total de observatii al portofoliului studiat
    int nrZile, i;
    fscanf(fi, "%d", &nrZile);
    struct Node *cap_lista=NULL;
    double valoare;
    for(i=0; i<nrZile; i++){
        fscanf(fi, "%lf", &valoare);
        addAtEnd(&cap_lista, valoare);
    }

    /// RANDAMENT MEDIU CALCUL

    double sumaRandT = sumaRandamentTotal(cap_lista);

    double randMediu = sumaRandT / (nrZile-1);

    /// VOLATILITATE CALCUL

    double volatilitate = 0;
    double sumaVol = sumaVolatilitateTotal(cap_lista, randMediu);
    volatilitate = sumaVol / (nrZile-1);
    volatilitate = sqrt(volatilitate);

    /// SHARPE RATIO

    double S = randMediu / volatilitate;

    /// REZULTATE
    
    fprintf(fo,"%.3lf\n", ((int)(randMediu*1000))/1000.0);
    fprintf(fo, "%.3lf\n", ((int)(volatilitate*1000))/1000.0);
    fprintf(fo, "%.3lf\n", ((int)(S*1000))/1000.0);
    stergereLista(&cap_lista); }

    if(task == 2){
        /// CREARE STIVE PT CELE TREI PIETE
    struct Elem *P1 = NULL;
    struct Elem *P2 = NULL;
    struct Elem *P3 = NULL;
    char S1[25]=""; char S2[25]=""; char S3[25]="";
    citire(&P1, &P2, &P3, fi, S1, S2, S3);
    afisare(P1, P2, P3, fi, S1, S2, S3, fo);
    }
    fclose(fi);
    fclose(fo);
    return 0;
}