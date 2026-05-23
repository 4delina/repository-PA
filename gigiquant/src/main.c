#include "Task1.h"
#include "Task2.h"
#include "Task3.h"
#include "Task4.h"
int main(int argc, const char *argv[])
{
    if (argc < 3)
        return 1;
    /// Deschidere fisiere de citire si scriere
    FILE *fi = fopen(argv[1], "r");
    FILE *fo = fopen(argv[2], "w");
    if (fi == NULL || fo == NULL)
    {
        printf("Eroare la deschiderea fisierelor!");
        return 1;
    }
    const char *fisiere[] = {"data1.in", "data2.in", "data3.in", "data4.in", "data5.in", "data6.in", "data7.in", "data8.in", "data9.in", "data10.in", "data11.in", "data12.in", "data13.in", "data14.in", "data15.in", "data16.in", "data17.in", "data18.in", "data19.in", "data20.in"};
    int task = 0;
    for (int i = 0; i <= 19; i++)
    {
        if (strstr(argv[1], fisiere[i]) != 0)
        {
            task = i / 5 + 1;
            break;
        }
    }

    if (task == 1)
        rezolvare_1(fi, fo);

    if (task == 2)
        rezolvare_2(fi, fo);

    if (task == 3)
        rezolvare_3(fi, fo);
    
    if (task == 4)
        rezolvare_4(fi, fo);

    fclose(fi);
    fclose(fo);
    return 0;
}