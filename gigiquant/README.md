Proiect PA - Manager de portofoliu la GigiQuant

Acest proiect implementează patru task-uri diferite, independente, în limbajul C, fiecare lucrând cu date financiare citite din fișiere.

## Task 1 - Randament, volatilitate și Sharpe Ratio

Pentru Task-ul 1 citesc toate valorile zilnice ale unui portofoliu și calculez
- randament mediu
- volatilitate
- Sharpe Ratio

Valorile sunt memorate într-o listă simplu înlănțuită, iar randamentele sunt calculate pe baza diferenței dintre două zile consecutive. Rezultatele sunt afișate apoi cu trei zecimale.

Funcțiile prezente în Task1.c sunt următoarele:
    void addAtEnd ( struct Node **cap_lista, double v)
Funcția se ocupă cu adăugarea la final a unui element într-o listă.
    void stergereLista (struct Node ** cap_lista)
Funcția are rolul de a elibera spațiul ocupat de o listă după ce aceasta nu mai este necesară.
    double sumaRandamentTotal ( struct Node *cap_lista)
Funcția aceasta calculeaza randamentul de la o zi la alta și returnează suma acestora. Ulterior rezultatul este împărțit la numărul de zile observate - 1 deoarece prima zi nu are randament propriu. Cu ajutorul acestei funcții reușim să aflăm primul lucru căutat, anume randamentul mediu.
    double sumaVolatilitateTotal (struct Node *cap_lista, double randMediu)
Asemenea funcției sumaRandamentTotal, funcția sumaVolatilitateTotal nu face nimic altceva decât să parcurgă lista, calculând pe parcurs volatilitatea portofoliului.
    void rezolvare_1 (FILE *fi, FILE *fo)
Funcția aceasta nu face decât să unească citirea, toate funcțiile anterioare și afișarea într-un mod simplu de urmărit și ușor de apelat din main.

## Task 2 - Oportunitate de arbitraj

Pentru Task-ul 2 citesc numele a trei piețe și un număr necunoscut de prețuri în ordine cronologică pentru fiecare.
Valorile sunt memorate în 3 stive, iar oportunitatea de arbitraj apare atunci când prețul are aceeași valoare pentru 2 piețe și unul diferit pe cea de-a treia.Scot pe rând câte un element din fiecare stivă și le compar pentru a vedea dacă am oportunitate de arbitraj sau nu. Atunci când acest fenomen se petrece afișez ziua, diferența absolută a valorii acțiunii și numele pieței diferite. Mă opresc în momentul în care oricare dintre cele trei stive s-a golit.

Funcțiile folosite pentru Task2.c sunt următoarele:
    void push( struct Elem **top, double v)
Funcția se ocupă cu adăugarea unui element într-o stivă.
    int isEmpty (const struct Elem * top)
Funcția are rolul de a verifica dacă o stivă este goală sau nu.
    void stergereStiva (struct ELem **top)
Funcția aceasta se ocupă cu eliberarea memoriei ocupate de o stivă.
    double pop (struct Elem **top)
Funcția aceasta scoate din stivă elementul din vârf și îî returnează valoarea.
    void rezolvare_2 (FILE *fi, FILE *fo)
Funcția aceasta nu face decât să unească citirea, toate funcțiile anterioare și afișarea într-un mod simplu de urmărit și ușor de apelat din main.

## Task 3 - Diversificarea portofoliului

Pentru Task-ul 3 citesc toate abrevierile numelor acțiunilor, separate prin virgulă, iar apoi valorile acestora pe mai multe zile. Scopul task-ului este să observ evoluția fiecărei acțiuni și să determin perechile de acțiuni care au avut comportamente complet opuse. Pentru a face acest lucru, folosesc o listă simplu înlănțuită în care memorez simbolurile acțiunilor în ordinea în care apar în fișier. Construiesc apoi un arbore binar bazat pe evoluția valorilor. La fiecare pas, acțiunile în două categorii:
- cele ce scad față de ziua anterioară sunt trimise în stânga
- cele ce cresc sau rămân constante față de ziua anterioară sunt trimise în dreapta
La final, caut frunzele arborelui și compar drumurile până la acestea. Dacă două acțiuni ajung frunze ale căror drumuri sunt complet opuse, atunci acestea formează o pereche și o afișez.

Funcțiile prezente în Task3.c sunt următoarele:
    void add_listaactiuni_BEG ( Stocklist **cap_lista, const char sir[])
Funcția se ocupă cu adăugarea la început a unui element într-o listă.
    void add_listaactiuni_END (Stocklist **cap_lista, const char sir[])
Funcția are rolul de a elibera spațiul ocupat de o listă după ce aceasta nu mai este necesară.
    void stergere_lista (Stocklist **head)
Funcția are rolul de a elibera spațiul ocupat de o listă după ce aceasta nu mai este necesară.
    int index_actiune ( Stocklist *head, const char s[])
Funcția aceasta află indexul unei acțiuni în șirul inițial. Indexul acesta va fi folosit mai departe pentru a accesa valoarea corespunzătoare acțiunii în matricea de valori.
    void citire_task3 (FILE *fi, char sir[], Stocklist **head)
Funcția citește prima linie din fișierul de intrare, adică lista simbolurilor acțiunilor pe care le separă de virgule și le introduce într-o listă simplu înlănțuită.
    TreeNode *creeare_arbore (Stocklist *l1, Stocklist *l2, double valori [][10], int col, int nrLinii)
Funcția construiește arborele binar al evoluției acțiunilor. Pentru fiecare nivel al arborelui se compară valorile acțiunilor de pe două zile consecutive. Dacp valoarea scade, e trimisă în subarborele stâng. Dacă nu scade, e trimisă în subarborele drept. Arborele se construiește recursiv până când nu mai există suficiente zile de comparat.
    void stergere_arbore (TreeNode *root)
Funcția eliberează memoria ocupată de arbore după ce acesta nu mai este necesar.
    int este_frunza(const TreeNode *node)
Funcția verifică dacă un nod este frunză, adică dacă nu are nici fiu stâng, nici fiu drept.
    int path_opuse (const int v1[], int lung1, const int v2[], int lung2)
Funcția verifică dacă două drumuri din arbore sunt opuse, adică dacă au aceeași lungime și pe fiecare poziție direcții diferite.
    void copiază_path (int destinatie[], const int sursa[], int lungime)
Funcția copiază un drum din arbore într-un alt vector. Este folosită atunci când se salvează drumul până la o frunză.
    void colectez_frunze ( TreeNode *root, int path[], int lungime, LeafPath frunze[], int *nrFrunze)
Funcția parcurge arborele și salvează toate frunzele, împreună cu drumul parcurs până la ele. Drumul este format din 0 (deplasare în stânga) și 1 (deplasare în dreapta) 
    int lista_contine (Stocklist *head, const char symbol[])
Funcția verifică dacă o anumită acțiune se află într-o listă. Este folosită pentru a determina în ce frunză a ajuns o acțiune.
    int frunza_actiunii (LeafPath frunze[], int nrFrunze, char symbol[])
Funcția caută frunza în care se află o anumită acțiune și returnează poziția acesteia în vectorul de frunze.
    void frunze_opuse (TreeNode *root, Stocklist *lista_initiala, FILE *fo)
Funcția caută perechile de acțiuni are au ajuns în frunze cu drumuri opuse. Parcurge acțiunile în ordinea inițială, identifică frunza fiecăreia și compară drumurile dintre perechi. Dacă drumurile sunt opuse, perechea este afișată în fișierul de ieșire.
    void rezolvare_3 (FILE *fi, FILE *fo)
Funcția aceasta nu face decât să unească citirea, toate funcțiile anterioare și afișarea într-un mod simplu de urmărit și ușor de apelat din main.

## Task 4 - Lanțuri Markov

Pentru Task-ul 4 citesc:
- numărul de zile pentru care am observații
- dimensiunea intervalelor
- ziua pentru care vreau să urmăresc probabilitatea unui preț
- prețul de start
- prețul target

Pe baza lor, găsesc minimul, formez cu acesta indecși începând de la 0 pentru intervale și formez o matrice a, asemănătoare unei matrice de adiacență pentru un graf orientat. Diferența este că în loc de 0 sau 1 voi introduce direct de câte ori trece un preț dintr-o stare în alta, de ci vom avea valori mai mari de 1. Apoi pe baza acestei matrice, formez matricea prob, ce va reține probabilitatea sub forma de fracție ca un preț să treacă dintr-o stare în alta. Cu ajutorul lor calculez zi de zi probabilitatea ca un preț să se afle într-o stare și recalculez pentru câte iterații ne cere problema. La final adfișez ce mi se cere.

Funcțiile folosite pentru Task4.c sunt următoarele:
    int cmmdc(int a, int b)
Funcția aceasta calculează cmmdc a două numere. Va fi folosită în calculul cu fracții.
    Fractie reduce_fractie(int numarator, int numitor)
Funcția aceasta aduce o fracție în forma sa ireductibilă.
    Fractie adunare(Fractie a, Fractie b)
Funcția aceasta efectuează suma a două fracții și întoarce rezultatul sub formă de fracție ireductibilă.
    void StergereLista(struct Node4 **cap_lista)
Funcția are rolul de a elibera spațiul ocupat de o listă după ce aceasta nu mai este necesară.
    void AddAtEnd(struct Node4 **cap_lista, double v)
Funcția se ocupă cu adăugarea la final a unui element într-o listă.
    Fractie produs(Fractie a, Fractie b)
Funcția aceasta efectuează produsul a două fracții și întoarce rezultatul sub formă de fracție ireductibilă.
    void calcul_prob(Fractie vector[], const int a[][20], Fractie prob[][20])
Funcția se ocupă de calculul probabilității fiecărui preț din interval într-o zi. 
    void citire_task4(FILE *fi, int *nr_obs, double *dist, int *zi, double *start, double *target, struct Node4 **cap, double *minim)
Funcția aceasta fce citirele inițiale din fișier și găsește minimul valorii din toate observațiile.
    void rezolvare_4 (FILE *fi, FILE *fo)
Funcția aceasta nu face decât să unească citirea, toate funcțiile anterioare și afișarea într-un mod simplu de urmărit și ușor de apelat din main.





