#include <stdio.h>
#include <malloc.h>

struct Cofetarie {
    char* nume;
    int nrAngajati;
    float* salarii;
};

void afiseazaCofetarie(struct Cofetarie c) {
    if (c.nume != NULL) printf("Nume: %s\n", c.nume);
    printf("Numar angajati: %d\n", c.nrAngajati);
    if (c.salarii != NULL) {
        printf("Salarii: ");
        for (int i = 0; i < c.nrAngajati; i++) {
            printf("%5.2f, ", c.salarii[i]);
        }
    }
    printf("\n");
}

struct Cofetarie initializareCofetarie(const char* nume, int nrAngajati, const float* salarii) {
    struct Cofetarie c;
    c.nume = malloc(strlen(nume) + 1);
    strcpy(c.nume, nume);
    c.nrAngajati = nrAngajati;
    c.salarii = malloc(sizeof(float) * nrAngajati);
    for (int i = 0; i < c.nrAngajati; i++) {
        c.salarii[i] = salarii[i];
    }
    return c;
}

void stergeCofetarie(struct Cofetarie* c) { // trebuie prin pointer
    if (c->nume != NULL) free(c->nume);
    free(c->salarii);
    c->nume = NULL;
    c->salarii = NULL;
}

int main()
{
    // declaram un obiect de tipul Cofetarie
    struct Cofetarie cofetarie1;

    // numele cofetariei: Dulce
    cofetarie1.nume = (char*)malloc(strlen("Dulce") + 1); // nu putem sa alocam cu new
    // malloc e o functie, primeste dimensiunea exprimata in bytes/octeti, returneaza void*
    // trebuie sa alocam pentru un caracter in plus, ca sa nu ne dea eroare la stergere
    strcpy(cofetarie1.nume, "Dulce");

    cofetarie1.nrAngajati = 3;
    cofetarie1.salarii = (float*)malloc(sizeof(float) * cofetarie1.nrAngajati);
    for (int i = 0; i < cofetarie1.nrAngajati; i++) {
        cofetarie1.salarii[i] = (i + 1) * 1000;
    }

    afiseazaCofetarie(cofetarie1);

    float* vector = malloc(sizeof(float) * 2); // hardcodare 2
    vector[0] = 4567;
    vector[1] = 3456;
    struct Cofetarie cofetarie2 = initializareCofetarie("Mara", 2, vector);

    afiseazaCofetarie(cofetarie2);

    free(vector);

    /*
    // in cautarea erorii daca nu punem + 1
    printf("%s", cofetarie1.nume);
    free(cofetarie1.nume); // EROARE
    free(cofetarie1.salarii);
    */

    // trebuie sa scriem din nou: free(cofetarie2.nume); si free(cofetarie2.salarii);
    // se repeta liniile de dezalocare, deci facem o functie

    stergeCofetarie(&cofetarie2);
    return 0;
}
