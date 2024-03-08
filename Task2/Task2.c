#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

// Karla Kovacs -> K si K -> Melodie Karaoke

struct MelodieKaraoke {
    int id;
    char* titlu;
    char* artist;
    int durata; // in secunde
    int nrNoteFeedback;
    float* noteFeedback;
};

struct MelodieKaraoke citesteMelodie() {
    struct MelodieKaraoke melodie;
    printf("ID: "); scanf("%d", &melodie.id);
    melodie.titlu = (char*)malloc(50 * sizeof(char));
    printf("Titlu: "); scanf("%s", melodie.titlu);
    melodie.artist = (char*)malloc(50 * sizeof(char));
    printf("Artist: "); scanf("%s", melodie.artist);
    printf("Durata (in secunde): "); scanf("%d", &melodie.durata);
    printf("Numar note feedback: "); scanf("%d", &melodie.nrNoteFeedback);
    melodie.noteFeedback = (float*)malloc(melodie.nrNoteFeedback * sizeof(float));
    printf("Note feedback:\n");
    for (int i = 0; i < melodie.nrNoteFeedback; ++i) {
        printf("Nota %d: ", i + 1); scanf("%f", &melodie.noteFeedback[i]);
    }
    return melodie;
}

struct MelodieKaraoke initializeazaMelodie(int id, const char* titlu, const char* artist, int durata, int nrNoteFeedback, float* noteFeedback) {
    struct MelodieKaraoke m;
    m.id = id;
    m.titlu = (char*)malloc(sizeof(char) * (strlen(titlu) + 1));
    strcpy(m.titlu, titlu);
    m.artist = (char*)malloc(sizeof(char) * (strlen(artist) + 1));
    strcpy(m.artist, artist);
    m.durata = durata;
    m.nrNoteFeedback = nrNoteFeedback;
    m.noteFeedback = (float*)malloc(m.nrNoteFeedback * sizeof(float));
    for (int i = 0; i < m.nrNoteFeedback; i++) {
        m.noteFeedback[i] = noteFeedback[i];
    }
    return m;
}

void afiseazaMelodie(struct MelodieKaraoke melodie) {
    printf("ID: %d\n", melodie.id);
    printf("Titlu: %s\n", melodie.titlu);
    printf("Artist: %s\n", melodie.artist);
    printf("Durata: %d secunde\n", melodie.durata);
    printf("Numar note feedback: %d\n", melodie.nrNoteFeedback);
    printf("Note feedback: ");
    for (int i = 0; i < melodie.nrNoteFeedback; ++i) printf("%.2f ", melodie.noteFeedback[i]);
    printf("\n----------------------------\n");
}

void afiseazaVectorMelodii(struct MelodieKaraoke* vectorMelodii, int nrMelodii) {
    for (int i = 0; i < nrMelodii; i++) {
        afiseazaMelodie(vectorMelodii[i]);
    }
}

float calculeazaNotaMedie(struct MelodieKaraoke melodie) {
    float suma = 0;
    for (int i = 0; i < melodie.nrNoteFeedback; i++) {
        suma += melodie.noteFeedback[i];
    }
    return suma / melodie.nrNoteFeedback;
}

void modificaDurata(struct MelodieKaraoke* melodie, int durataNoua) {
    melodie->durata = durataNoua;
}

// filtreaza melodiile care au durata > 300 secunde
struct MelodieKaraoke* filtreazaMelodii1(struct MelodieKaraoke* melodii, int nrMelodii, int* nrMelodiiFiltrate) {
    *nrMelodiiFiltrate = 0;
    for (int i = 0; i < nrMelodii; i++) {
        if (melodii[i].durata > 300) {
            (*nrMelodiiFiltrate)++;
        }
    }
    struct MelodieKaraoke* melodiiFiltrate = (struct MelodieKaraoke*)malloc(*nrMelodiiFiltrate * sizeof(struct MelodieKaraoke));
    int j = 0;
    for (int i = 0; i < nrMelodii; i++) {
        if (melodii[i].durata > 300) {
            melodiiFiltrate[j] = melodii[i];
            j++;
        }
    }
    return melodiiFiltrate;
}

// filtreaza melodiile care au media notelor feedback > 5
struct MelodieKaraoke* filtreazaMelodii2(struct MelodieKaraoke* melodii, int nrMelodii, int* nrMelodiiFiltrate) {
    *nrMelodiiFiltrate = 0;
    for (int i = 0; i < nrMelodii; i++) {
        if (calculeazaNotaMedie(melodii[i]) > 5) {
            (*nrMelodiiFiltrate)++;
        }
    }
    struct MelodieKaraoke* melodiiFiltrate = (struct MelodieKaraoke*)malloc(*nrMelodiiFiltrate * sizeof(struct MelodieKaraoke));
    int j = 0;
    for (int i = 0; i < nrMelodii; i++) {
        if (calculeazaNotaMedie(melodii[i]) > 5) {
            melodiiFiltrate[j] = melodii[i];
            j++;
        }
    }
    return melodiiFiltrate;
}

struct MelodieKaraoke* concateneazaVectori(struct MelodieKaraoke* vector1, int dim1, struct MelodieKaraoke* vector2, int dim2, int* dimC) {
    *dimC = dim1 + dim2;
    struct MelodieKaraoke* vectorConcatenat = (struct MelodieKaraoke*)malloc((*dimC) * sizeof(struct MelodieKaraoke));
    for (int i = 0; i < dim1; i++) vectorConcatenat[i] = vector1[i];
    for (int i = 0; i < dim2; i++) vectorConcatenat[dim1 + i] = vector2[i];
    return vectorConcatenat;
}

void elibereazaMemorie(struct MelodieKaraoke melodie) {
    if (melodie.titlu != NULL) free(melodie.titlu);
    if (melodie.artist != NULL) free(melodie.artist);
    if (melodie.noteFeedback != NULL) free(melodie.noteFeedback);
}

void elibereazaMemorieVector(struct MelodieKaraoke* vectorMelodii, int nrMelodii) {
    for (int i = 0; i < nrMelodii; i++) {
        elibereazaMemorie(vectorMelodii[i]);
    }
    free(vectorMelodii);
}

int main() {
    int nrMelodii = 5;
    struct MelodieKaraoke* vectorMelodii = (struct MelodieKaraoke*)malloc(nrMelodii * sizeof(struct MelodieKaraoke));
    for (int i = 0; i < nrMelodii; i++) {
        float noteFeedback[3] = { i + 1, i + 3 };
        vectorMelodii[i] = initializeazaMelodie(i + 1, "Titlu", "Artist", (i + 1) * 100, 2, noteFeedback);
    }
    afiseazaVectorMelodii(vectorMelodii, nrMelodii);

    printf("Melodii filtrate 1:\n");
    int nrMelodiiFiltrate1 = 0;
    struct MelodieKaraoke* vectorMelodiiFiltrate1 = filtreazaMelodii1(vectorMelodii, nrMelodii, &nrMelodiiFiltrate1);
    afiseazaVectorMelodii(vectorMelodiiFiltrate1, nrMelodiiFiltrate1);

    printf("Melodii filtrate 2:\n");
    int nrMelodiiFiltrate2 = 0;
    struct MelodieKaraoke* vectorMelodiiFiltrate2 = filtreazaMelodii2(vectorMelodii, nrMelodii, &nrMelodiiFiltrate2);
    afiseazaVectorMelodii(vectorMelodiiFiltrate2, nrMelodiiFiltrate2);
    
    printf("Concatenare vectori:\n");
    int dimC = 0;
    struct MelodieKaraoke* vectorConcatenat = concateneazaVectori(vectorMelodiiFiltrate1, nrMelodiiFiltrate1, vectorMelodiiFiltrate2, nrMelodiiFiltrate2, &dimC);
    afiseazaVectorMelodii(vectorConcatenat, dimC);
    
    elibereazaMemorieVector(vectorMelodii, nrMelodii);
    
    return 0;
}
