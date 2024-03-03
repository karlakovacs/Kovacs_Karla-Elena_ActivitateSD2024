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

void afiseazaMelodie(struct MelodieKaraoke melodie) {
    printf("ID: %d\n", melodie.id);
    printf("Titlu: %s\n", melodie.titlu);
    printf("Artist: %s\n", melodie.artist);
    printf("Durata: %d secunde\n", melodie.durata);
    printf("Numar note feedback: %d\n", melodie.nrNoteFeedback);
    printf("Note feedback: ");
    for (int i = 0; i < melodie.nrNoteFeedback; ++i) printf("%.2f ", melodie.noteFeedback[i]);
}

float calculNotaMedie(struct MelodieKaraoke melodie) {
    float suma = 0;
    for (int i = 0; i < melodie.nrNoteFeedback; i++) {
        suma += melodie.noteFeedback[i];
    }
    return suma / melodie.nrNoteFeedback;
}

void modificaDurata(struct MelodieKaraoke* melodie, int durataNoua) {
    melodie->durata = durataNoua;
}

int main() {
    struct MelodieKaraoke melodieCitita = citesteMelodie();

    printf("\n");
    printf("Melodie citita:\n");
    afiseazaMelodie(melodieCitita);

    printf("\n");
    printf("Nota medie a melodiei: %.2f", calculNotaMedie(melodieCitita));

    printf("\n");
    modificaDurata(&melodieCitita, 300);
    printf("Noua durata a melodiei citite: %d secunde\n", melodieCitita.durata);

    free(melodieCitita.titlu);
    free(melodieCitita.artist);
    free(melodieCitita.noteFeedback);

    return 0;
}
