#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct StructuraMasina {
	int id;
	int nrUsi;
	float pret;
	char* model;
	char* numeSofer;
	unsigned char serie;
};
typedef struct StructuraMasina Masina;

struct Nod {
	Masina info;
	struct Nod* next;
};
typedef struct Nod Nod;

Masina citireMasinaDinFisier(FILE* file) {
	char buffer[100];
	char sep[3] = ",\n";
	fgets(buffer, 100, file);
	char* aux;
	Masina m1;
	aux = strtok(buffer, sep);
	m1.id = atoi(aux);
	m1.nrUsi = atoi(strtok(NULL, sep));
	m1.pret = atof(strtok(NULL, sep));
	aux = strtok(NULL, sep);
	m1.model = malloc(strlen(aux) + 1);
	strcpy(m1.model, aux);
	aux = strtok(NULL, sep);
	m1.numeSofer = malloc(strlen(aux) + 1);
	strcpy(m1.numeSofer, aux);
	aux = strtok(NULL, sep);
	m1.serie = aux[0];
	return m1;
}

void afisareMasina(Masina masina) {
		printf("Id: %d\n", masina.id);
		printf("Nr. usi : %d\n", masina.nrUsi);
		printf("Pret: %.2f\n", masina.pret);
		printf("Model: %s\n", masina.model);
		printf("Nume sofer: %s\n", masina.numeSofer);
		printf("Serie: %c\n\n", masina.serie);
	}

void afisareListaMasini(Nod* nod) {
	while (nod) {
		afisareMasina(nod->info);
		nod = nod->next;
	}
}

void adaugaMasinaInListaFinal(Nod** lista, Masina masinaNoua) {
	Nod* nodNou = malloc(sizeof(Nod));
	nodNou->info = masinaNoua;
	nodNou->next = NULL;
	if (!(*lista)) {
		*lista = nodNou;
	}
	else {
		Nod* aux = *lista;
		while (aux->next) aux = aux->next;
		aux->next = nodNou;
	}
}

Nod* citireListaMasiniDinFisier(const char* numeFisier) {
	FILE* f = fopen(numeFisier, "r");
	Nod* lista = NULL;
	if (!f) return NULL;

	while (!feof(f)) {
		Masina masina = citireMasinaDinFisier(f);
		if (masina.model != NULL)
			adaugaMasinaInListaFinal(&lista, masina);
	}
	fclose(f);
	return lista;
}

void dezalocareListaMasini(Nod** lista) {
	while (*lista) {
		Nod* p = *lista;
		*lista = (*lista)->next;
		free(p->info.model);
		free(p->info.numeSofer);
		free(p);
	}
}

void stergerePozitie(Nod** lista, int pozitie) {
	if (*lista == NULL || pozitie < 0) return;
	Nod* temp = *lista;

	if (pozitie == 0) {
		*lista = (*lista)->next;
		free(temp->info.model);
		free(temp->info.numeSofer);
		free(temp);
		return;
	}

	for (int i = 0; temp && i < pozitie - 1; i++) {
		temp = temp->next;
	}

	if (temp == NULL || temp->next == NULL) return;

	Nod* deSters = temp->next;
	temp->next = temp->next->next;
	free(deSters->info.model);
	free(deSters->info.numeSofer);
	free(deSters);
}

void inserareSortata(Nod** lista, Masina m) {
	Nod* nou = malloc(sizeof(Nod));
	nou->info = m;
	nou->next = NULL;

	if (*lista == NULL || (*lista)->info.pret > m.pret) {
		nou->next = *lista;
		*lista = nou;
		return;
	}

	Nod* curent = *lista;
	while (curent->next && curent->next->info.pret < m.pret) {
		curent = curent->next;
	}
	nou->next = curent->next;
	curent->next = nou;
}

Masina* filtrareMasiniDupaPret(Nod* lista, float prag, int* dim) {
	*dim = 0;
	Nod* temp = lista;
	while (temp) {
		if (temp->info.pret > prag) (*dim)++;
		temp = temp->next;
	}
	if (*dim == 0) return NULL;
	Masina* vector = malloc(sizeof(Masina) * (*dim));
	int index = 0;
	while (lista) {
		if (lista->info.pret > prag) {
			vector[index].id = lista->info.id;
			vector[index].nrUsi = lista->info.nrUsi;
			vector[index].pret = lista->info.pret;

			vector[index].model = malloc(strlen(lista->info.model) + 1);
			strcpy(vector[index].model, lista->info.model);

			vector[index].numeSofer = malloc(strlen(lista->info.numeSofer) + 1);
			strcpy(vector[index].numeSofer, lista->info.numeSofer);

			vector[index].serie = lista->info.serie;
			index++;
		}
		lista = lista->next;
	}
	for (int i = 0; i < *dim - 1; i++) {
		for (int j = i + 1; j < *dim; j++) {
			if (vector[i].pret > vector[j].pret) {
				Masina temp = vector[i];
				vector[i] = vector[j];
				vector[j] = temp;
			}
		}
	}
	return vector;
}

void interschimbaPozitii(Nod* lista, int pos1, int pos2) {
	if (pos1 == pos2) return;
	Nod* p1 = NULL, * p2 = NULL;
	int index = 0;
	Nod* temp = lista;

	while (temp) {
		if (index == pos1) p1 = temp;
		if (index == pos2) p2 = temp;
		temp = temp->next;
		index++;
	}

	if (p1 && p2) {
		Masina aux = p1->info;
		p1->info = p2->info;
		p2->info = aux;
	}
}


int main() {
	Nod* lista = citireListaMasiniDinFisier("masini.txt");
	printf("----------Lista initiala----------\n");
	afisareListaMasini(lista);

	printf("----------Stergem masina de pe pozitia 2-----------\n");
	stergerePozitie(&lista, 2);
	afisareListaMasini(lista);

	printf("----------Inseram masina----------\n");
	Masina mNou;
	mNou.id = 100;
	mNou.nrUsi = 5;
	mNou.pret = 76000.0f;
	mNou.model = malloc(strlen("Tesla") + 1);
	strcpy(mNou.model, "Tesla");
	mNou.numeSofer = malloc(strlen("Ionescu") + 1);
	strcpy(mNou.numeSofer, "Ionescu");
	mNou.serie = 'X';

	inserareSortata(&lista, mNou);
	afisareListaMasini(lista);

	printf("----------Masini mai scumpe de 50000----------\n");
	int dim = 0;
	Masina* vector = filtrareMasiniDupaPret(lista, 50000.0f, &dim);
	for (int i = 0; i < dim; i++) {
		afisareMasina(vector[i]);
	}
	for (int i = 0; i < dim; i++) {
		free(vector[i].model);
		free(vector[i].numeSofer);
	}
	free(vector);

	printf("----------Interschimbare pozitii----------\n");
	interschimbaPozitii(lista, 0, 2);
	afisareListaMasini(lista);
	dezalocareListaMasini(&lista);
	return 0;
}
