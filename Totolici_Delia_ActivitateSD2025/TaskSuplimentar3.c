#define _CRT_SECURE_NO_WARNINGS  
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

struct Document {
    int id;
    char* titlu;
    int numarPagini;
    char* continut;
};

typedef struct Document Document;

Document initializare(const char* titlu, int id, int numarPagini, const char* continut) {
    Document doc;
    if (titlu != NULL) {
        doc.titlu = (char*)malloc(sizeof(char) * (strlen(titlu) + 1));
        strcpy_s(doc.titlu, strlen(titlu) + 1, titlu);
    }
    else {
        doc.titlu = NULL;
    }
    doc.id = id;
    doc.numarPagini = numarPagini;

    if (continut != NULL) {
        doc.continut = (char*)malloc(sizeof(char) * (strlen(continut) + 1));
        strcpy_s(doc.continut, strlen(continut) + 1, continut);
    }
    else {
        doc.continut = NULL;
    }
    return doc;
}

void afisare(Document doc) {
    printf("\nID Document: %d\n", doc.id);
    printf("Titlu: %s\n", doc.titlu);
    printf("Numar de pagini: %d\n", doc.numarPagini);
    printf("Continut: %s\n", doc.continut);
}

void afisareVector(Document* vector, int nrElemente) {
    if (nrElemente > 0 && vector != NULL) {
        for (int i = 0; i < nrElemente; i++) {
            afisare(vector[i]);
            printf("\n");
        }
    }
}

Document citireDocumentDinFisier(FILE* file) {
    char buffer[512];
    char sep[] = ",\n";
    char* aux;
    Document doc;

    if (fgets(buffer, sizeof(buffer), file) != NULL) {
        aux = strtok(buffer, sep);
        doc.id = atoi(aux);
        aux = strtok(NULL, sep);
        doc.titlu = malloc(strlen(aux) + 1);
        strcpy_s(doc.titlu, strlen(aux) + 1, aux);
        aux = strtok(NULL, sep);
        doc.numarPagini = atoi(aux);
        aux = strtok(NULL, sep);
        doc.continut = malloc(strlen(aux) + 1);
        strcpy_s(doc.continut, strlen(aux) + 1, aux);
    }
    else {
        doc.id = -1;
        doc.titlu = NULL;
        doc.numarPagini = 0;
        doc.continut = NULL;
    }
    return doc;
}

int citireVectorDocumente(const char* numeFisier, Document** vector) {
    FILE* file = fopen(numeFisier, "r");
    if (!file) {
        printf("Eroare la deschiderea fisierului %s\n", numeFisier);
        return 0;
    }

    Document* tempVector = NULL;
    int nr = 0;
    Document doc;

    while (!feof(file)) {
        doc = citireDocumentDinFisier(file);
        if (doc.id != -1 && doc.titlu != NULL) {
            tempVector = realloc(tempVector, sizeof(Document) * (nr + 1));
            tempVector[nr++] = doc;
        }
    }

    fclose(file);
    *vector = tempVector;
    return nr;
}

void salvareDocumentInFisier(Document doc, FILE* file) {
    fprintf(file, "%d,%s,%d,%s\n", doc.id, doc.titlu, doc.numarPagini, doc.continut);
}

void salvareVectorDocumenteInFisier(Document* vector, int nrElemente, const char* numeFisier) {
    FILE* file = fopen(numeFisier, "w");
    if (!file) {
        printf("Eroare la deschiderea fisierului %s pentru salvare\n", numeFisier);
        return;
    }
    for (int i = 0; i < nrElemente; i++) {
        salvareDocumentInFisier(vector[i], file);
    }
    fclose(file);
}

void eliberareMemorie(Document** vector, int* nrElemente) {
    if ((*vector) != NULL && (*nrElemente) > 0) {
        for (int i = 0; i < (*nrElemente); i++) {
            free((*vector)[i].titlu);
            free((*vector)[i].continut);
        }
        free(*vector);
        *vector = NULL;
        *nrElemente = 0;
    }
}

int main() {
    Document* vectorCitit = NULL;
    int nrDocumente = citireVectorDocumente("documente.txt", &vectorCitit);
    printf("Documente citite din fisier:\n");
    afisareVector(vectorCitit, nrDocumente);

    int nrElemente = 5;
    Document* vector = malloc(sizeof(Document) * nrElemente);
    vector[0] = initializare("Fructe", 1, 30, "Despre fructe si beneficiile lor");
    vector[1] = initializare("Legume", 2, 30, "Despre legume si beneficiile lor");
    vector[2] = initializare("Cybersecurity", 3, 100, "Jobul tau de viitor");
    vector[3] = initializare("Licenta", 4, 80, "Sistem informational pentru invatarea limbii japoneze");
    vector[4] = initializare("Cocktails", 5, 55, "Invata-le sa le faci de la 0");
 
    salvareVectorDocumenteInFisier(vector, nrElemente, "documente_salvate.txt");

    eliberareMemorie(&vectorCitit, &nrDocumente);
    eliberareMemorie(&vector, &nrElemente);

    return 0;
}