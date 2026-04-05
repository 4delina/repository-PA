#include "Task1.h"
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
    rezultate(fo, randMediu, volatilitate, S);
    stergereLista(&cap_lista);
    fclose(fi);
    fclose(fo);
    return 0;
}