#include <stdio.h>
#include <malloc.h>

struct Farmacie {
	int id;
	char* nume;
	float suprafata;

};

// functie pt initializarea parametrilor
struct Farmacie initializareFarmacie(int id, const char* nume, float suprafata) {
	struct Farmacie f;

	f.id = id;
	f.nume = (char*)malloc(sizeof(char*) * (strlen(nume) + 1));
	strcpy(f.nume, nume);
	f.suprafata = suprafata;

	return f;
}

void afisareFarmacie(struct Farmacie f) {
	/*
	printf("ID: %d\n", f.id);
	printf("Nume: %s\n", f.nume);
	printf("Suprafata: %.2f\n", f.suprafata);
	*/

	printf("%d. %s are o suprafata de %5.2f\n", f.id, f.nume, f.suprafata);
}

void afisareVectorFarmacii(struct Farmacie* farmacii, int nrFarmacii) {
	for (int i = 0; i < nrFarmacii; i++) {
		// recomandat e sa avem o alta functie care sa afiseze o farmacie
		afisareFarmacie(farmacii[i]);
	}

	// printf("%5.2f", (float)sizeof(farmacii) / (float)sizeof(struct Farmacie));
	// cand avem o structura, pe langa sizeof date se adauga si metadate
}

// functie care sa copieze intr-un nou vector primele n elemente, n primit ca parametru
struct Farmacie* copiazaNElemente(struct Farmacie* vector, int nrFarmacii, int nrObiecteCopiate) {
	if (nrObiecteCopiate <= nrFarmacii && nrObiecteCopiate > 0) {
		struct Farmacie* copiat = (struct Farmacie*)malloc(sizeof(struct Farmacie) * nrObiecteCopiate);
		for (int i = 0; i < nrObiecteCopiate; i++) {
			// copiat[i] = vector[i]; // shallow copy, va duce la o situatie de dangling pointer cand incercam sa stergem ambii vectori
			copiat[i] = initializareFarmacie(vector[i].id, vector[i].nume, vector[i].suprafata);
		}
		return copiat;
	}
	else { // in mod normal am arunca o exceptie, dar nu suntem in C++
		return NULL;
	}
}

// functie care sa imi copieze farmaciile care au suprafata mai mica decat o valoare data prin parametru
struct Farmacie* copiazaFarmaciiMici(struct Farmacie* farmacii, int nrFarmacii, float pragSuprafata, int* nrFarmaciiMici) {
	*nrFarmaciiMici = 0;
	for (int i = 0; i < nrFarmacii; i++) {
		if (farmacii[i].suprafata < pragSuprafata) {
			(*nrFarmaciiMici)++; // dereferentiere si incrementare
		}
	}

	struct Farmacie* vector = (struct Farmacie*)malloc(sizeof(struct Farmacie) * (*nrFarmaciiMici));

	int k = 0;
	for (int i = 0; i < nrFarmacii; i++) {
		if (farmacii[i].suprafata < pragSuprafata) {
			vector[k++] = initializareFarmacie(farmacii[i].id, farmacii[i].nume, farmacii[i].suprafata); // k++ - postincrementare, mai intai atribuirea (k=0), dupa k=1
		}
	}

	return vector;
}

// functie de dezalocare
// * -> adresa primului element
// ** -> adresa unde tin adresa primului element
// daca pun * as avea dangling pointer
void dezalocareVectorFarmacii(struct Farmacie** vector, int* nrFarmacii) {
	for (int i = 0; i < *nrFarmacii; i++) { // dereferentiere
		free((*vector)[i].nume);
	}

	free(*vector);
	*nrFarmacii = 0;
	*vector = NULL;
}

// get farmacie by ID
struct Farmacie getFarmacieByID(struct Farmacie* vector, int nrFarmacii, int idCautat) {
	for (int i = 0; i < nrFarmacii; i++) {
		if (vector[i].id == idCautat) {
			return initializareFarmacie(vector[i].id, vector[i].nume, vector[i].suprafata);
		}
	}

	return initializareFarmacie(0, "N/A", 0); // N/A - not applicable
}

int main() {
	// struct Farmacie dona = initializareFarmacie(1, "Dona", 55.5);
	// afisareFarmacie(dona);
	// ce este un vector? o structura de date omogena (cu elemente de acelasi tip) cu accesare directa, liniara, ocupa o zona de memorie contigua
	// creare vector de farmacii
	// int v1[10]; // alocare statica, pe stiva
	// int* v2 = ...; // alocare dinamica, pe heap (cu malloc)
	int nrFarmacii = 4;
	struct Farmacie* farmacii = (struct Farmacie*)malloc(sizeof(struct Farmacie) * nrFarmacii);
	for (int i = 0; i < nrFarmacii; i++) {
		farmacii[i] = initializareFarmacie(i + 1, "Farmacie", 30 * i + 10);
	}

	afisareVectorFarmacii(farmacii, nrFarmacii);

	int nrFarmaciiCopiate = 2;
	struct Farmacie* farmaciiCopiate = copiazaNElemente(farmacii, nrFarmacii, nrFarmaciiCopiate);
	printf("\n\n");
	afisareVectorFarmacii(farmaciiCopiate, nrFarmaciiCopiate);

	int nrFarmaciiMici = 0;

	farmacii[3].suprafata = 20;

	struct Farmacie* farmaciiMici = copiazaFarmaciiMici(farmacii, nrFarmacii, 50, &nrFarmaciiMici);
	printf("\n\n");
	afisareVectorFarmacii(farmaciiMici, nrFarmaciiMici);

	struct Farmacie farmacieCautata = getFarmacieByID(farmacii, nrFarmacii, 3);
	printf("\nFarmacie cautata:\n");
	afisareFarmacie(farmacieCautata);
	free(farmacieCautata.nume);

	dezalocareVectorFarmacii(&farmacii, &nrFarmacii);
	dezalocareVectorFarmacii(&farmaciiCopiate, &nrFarmaciiCopiate);
	dezalocareVectorFarmacii(&farmaciiMici, &nrFarmaciiMici);

	return 0;
}
