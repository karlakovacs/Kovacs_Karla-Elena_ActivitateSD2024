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

void citireMatrice(const char* numeFisier, struct Masina** matrice, int* nrLinii, int* nrColoane) {
	FILE* file = fopen(numeFisier, "r");
	char buffer[100];
	char delimitare[4] = ",\n";
	while (fgets(buffer, 100, file) != NULL) {
		char* element = strtok(buffer, delimitare); // token, element
		struct Masina m;
		m.id = atoi(element);
		element = strtok(NULL, delimitare);
		m.producator = malloc(strlen(element) + 1);
		strcpy(m.producator, element);
		element = strtok(NULL, delimitare);
		m.nrUsi = atoi(element);
		element = strtok(NULL, delimitare);
		m.pret = atof(element);
		matrice[m.nrUsi - 2] = adaugareInVector(matrice[m.nrUsi - 2], m, &nrColoane[m.nrUsi - 2]);
	}
	fclose(file);
}

void afisareMatrice(struct Masina** matrice, int nrLinii, int* nrCol) {
	for (int i = 0; i < nrLinii; i++) {
		for (int j = 0; j < nrCol[i]; j++) {
			printf("%d, %s, %d, %.2f\t", matrice[i][j].id, matrice[i][j].producator, matrice[i][j].nrUsi, matrice[i][j].pret);
		}
		printf("\n");
	}
}

// pret mediu al masinilor cu nr de usi dat ca parametru
float pretMediu(struct Masina** matrice, int nrLinii, int* nrColoane, int nrUsi) {
	if (nrUsi < 1 || nrUsi > 4) {
		return 0;
	}
	float pretTotal = 0;
	int index = nrUsi - 2;
	if (nrColoane[index] == 0) {
		return 0;
	}
	for (int i = 0; i < nrColoane[index]; i++) {
		pretTotal += matrice[index][i].pret;
	}
	return pretTotal / nrColoane[index];
}

// functie care sa ne returneze masina cu un id primit
struct Masina cautaMasinaDupaID(struct Masina** matrice, int nrLinii, int* nrCol, int id) {
	for (int i = 0; i < nrLinii; i++) {
		for (int j = 0; j < nrCol[i]; j++) {
			if (matrice[i][j].id == id) {
				return matrice[i][j];
			}
		}
	}
	struct Masina m;
	m.id = -1;
	m.producator = NULL;
	m.nrUsi = -1;
	m.pret = -1;
	return m;
}

void dezalocareMatrice(struct Masina** matrice, int nrLinii, int** nrCol) {
	for (int i = 0; i < nrLinii; i++) {
		for (int j = 0; j < (*nrCol)[i]; j++) {
			free((*matrice)[i][j].producator);
		}
		free((*matrice)[i]);
	}
	free((*nrCol));
	(*nrCol) = NULL;
	free((*matrice));
	(*matrice) = NULL;
}

int main() {
	struct Masina** matrice;
	int nrLinii = 3;
	int* nrCol;
	nrCol = (int*)malloc(sizeof(int) * nrLinii); // vectorul de lungimi
	matrice = (struct Masina**)malloc(sizeof(struct Masina*) * nrLinii);
	for (int i = 0; i < nrLinii; i++) {
		nrCol[i] = 0;
		matrice[i] = NULL;
	}
	citireMatrice("masini.txt", matrice, nrLinii, nrCol);
	afisareMatrice(matrice, nrLinii, nrCol);
	printf("Pretul mediu este: %5.2f", pretMediu(matrice, nrLinii, nrCol, 3));
	struct Masina masinaCautata = cautaMasinaDupaID(matrice, nrLinii, nrCol, 6);
	printf("\n\n%d, %s, %d, %.2f\t", masinaCautata.id, masinaCautata.producator, masinaCautata.nrUsi, masinaCautata.pret);

	dezalocareMatrice(&matrice, nrLinii, &nrCol);
	return 0;
}
