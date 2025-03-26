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

void copiereDocumenteCuNumarMicPagini(Document* vector, int nrElemente, int pragPagini, Document** vectorNou, int* dimensiune) {
    *dimensiune = 0;
    for (int i = 0; i < nrElemente; i++) {
        if (vector[i].numarPagini <= pragPagini) {
            (*dimensiune)++;
        }
    }
    *vectorNou = malloc(sizeof(Document) * (*dimensiune));
    int contor = 0;
    for (int i = 0; i < nrElemente; i++) {
        if (vector[i].numarPagini <= pragPagini) {
            (*vectorNou)[contor] = initializare(vector[i].titlu, vector[i].id,
                vector[i].numarPagini, vector[i].continut);
            contor++;
        }
    }
}

void concatenare(Document* vector1, int nrElemente1, Document* vector2, int nrElemente2, Document** vectorNou, int* nrElementeNou) {
    *nrElementeNou = nrElemente1 + nrElemente2;
    *vectorNou = malloc(sizeof(Document) * (*nrElementeNou));

    for (int i = 0; i < nrElemente1; i++) {
        (*vectorNou)[i] = vector1[i];
        (*vectorNou)[i].titlu = malloc(sizeof(char) * (strlen(vector1[i].titlu) + 1));
        strcpy_s((*vectorNou)[i].titlu, strlen(vector1[i].titlu) + 1, vector1[i].titlu);
        (*vectorNou)[i].continut = malloc(sizeof(char) * (strlen(vector1[i].continut) + 1));
        strcpy_s((*vectorNou)[i].continut, strlen(vector1[i].continut) + 1, vector1[i].continut);
    }

    for (int i = 0; i < nrElemente2; i++) {
        (*vectorNou)[nrElemente1 + i] = vector2[i];
        (*vectorNou)[nrElemente1 + i].titlu = malloc(sizeof(char) * (strlen(vector2[i].titlu) + 1));
        strcpy_s((*vectorNou)[nrElemente1 + i].titlu, strlen(vector2[i].titlu) + 1, vector2[i].titlu);
        (*vectorNou)[nrElemente1 + i].continut = malloc(sizeof(char) * (strlen(vector2[i].continut) + 1));
        strcpy_s((*vectorNou)[nrElemente1 + i].continut, strlen(vector2[i].continut) + 1, vector2[i].continut);
    }
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
    int nrElemente = 5;
    Document* vector = malloc(sizeof(Document) * nrElemente);
    vector[0] = initializare("Fructe", 1, 30, "Despre fructe si beneficiile lor");
    vector[1] = initializare("Legume", 2, 30, "Despre legume si beneficiile lor");
    vector[2] = initializare("Cybersecurity", 3, 100, "Jobul tau de viitor");
    vector[3] = initializare("Licenta", 4, 80, "Sistem informational pentru invatarea limbii japoneze");
    vector[4] = initializare("Cocktails", 5, 55, "Invata-le sa le faci de la 0");

    printf("Vector de documente:\n");
    afisareVector(vector, nrElemente);

    printf("\n\nDocumente cu un numar de pagini < 50:\n");
    int dim = 0, pragPagini = 50;
    Document* vectorNou = NULL;
    copiereDocumenteCuNumarMicPagini(vector, nrElemente, pragPagini, &vectorNou, &dim);
    afisareVector(vectorNou, dim);
    eliberareMemorie(&vectorNou, &dim);

    printf("\n\nConcatenare vectori:\n");
    int nrElemente2 = 3;
    Document* vector2 = malloc(sizeof(Document) * nrElemente2);
    vector2[0] = initializare("Top secret", 6, 60, "----------");
    vector2[1] = initializare("Korean skincare", 7, 70, "The best skincare products");
    vector2[2] = initializare("Tourists scams", 8, 56, "Be careful around the world");

    Document* vectorConcatenat = NULL;
    int nrElementeConcatenat = 0;
    concatenare(vector, nrElemente, vector2, nrElemente2, &vectorConcatenat, &nrElementeConcatenat);
    afisareVector(vectorConcatenat, nrElementeConcatenat);

    eliberareMemorie(&vector, &nrElemente);
    eliberareMemorie(&vector2, &nrElemente2);
    eliberareMemorie(&vectorConcatenat, &nrElementeConcatenat);

    return 0;
}
