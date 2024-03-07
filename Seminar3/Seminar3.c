#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include <stdlib.h>

struct Masina {
	int id;
	char* producator;
	int nrUsi;
	float pret;
};

struct Masina* adaugareInVector(struct Masina* masini, struct Masina m, int* nrMasini) {
	struct Masina* aux = (struct Masina*)malloc(sizeof(struct Masina) * ((*nrMasini) + 1)); // e prioritizata dereferentierea lui nrMasini
	for (int i = 0; i < *nrMasini; i++) {
		aux[i] = masini[i]; // shallow copy
	}
	aux[*nrMasini] = m;
	(*nrMasini)++;
	if (masini != NULL) free(masini); // stergem vectorul, dar pointerii raman
	return aux;
}

struct Masina* citireFisier(const char* numeFisier, int* nrMasini) {
	FILE* file = fopen(numeFisier, "r");
	// citirea se poate realiza cu fscanf (citeste doar pana la spatiu)
	// noi vrem sa citim toata linia -> vom folosi functia fgets (file get string)
	// fgets: buffer (unde sa citeasca linia respectiva), max count (cate sa citeasca maxim), fisierul
	char buffer[100];
	char delimitare[4] = ",\n";
	struct Masina* masini = NULL;
	(*nrMasini) = 0;
	while (fgets(buffer, 100, file) != NULL) {
		char* element = strtok(buffer, delimitare); // token, element
		struct Masina m;
		// atoi = ascii to int; strtod = string to double; strtoi = string to int
		m.id = atoi(element);
		element = strtok(NULL, delimitare);
		m.producator = malloc(strlen(element) + 1);
		strcpy(m.producator, element);
		element = strtok(NULL, delimitare);
		m.nrUsi = atoi(element);
		element = strtok(NULL, delimitare);
		m.pret = atof(element);
		masini = adaugareInVector(masini, m, nrMasini);
	}
	fclose(file);
	return masini;
}

int main() {
	struct Masina* masini = NULL;
	int nrMasini = 0;
	masini = citireFisier("masini.txt", &nrMasini); // e important sa nu lasam linii goale
	for (int i = 0; i < nrMasini; i++) {
		printf("ID: %d\n", masini[i].id);
		printf("Producator: %s\n", masini[i].producator);
		printf("Nr usi: %d\n", masini[i].nrUsi);
		printf("Pret: %5.2f\n", masini[i].pret);
		printf("\n");
	}
	return 0;
}
