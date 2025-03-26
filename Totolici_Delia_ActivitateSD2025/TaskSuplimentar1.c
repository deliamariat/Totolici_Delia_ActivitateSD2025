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

Document citesteDocument() {
    Document doc;
    char titlu[100];
    char continut[500];

    printf("Introduceti ID-ul documentului: ");
    scanf("%d", &doc.id);

    getchar();

    printf("Introduceti titlul documentului: ");
    fgets(titlu, 100, stdin);
    titlu[strcspn(titlu, "\n")] = 0;

    printf("Introduceti numarul de pagini: ");
    scanf("%d", &doc.numarPagini);

    getchar();

    printf("Introduceti continutul documentului: ");
    fgets(continut, 500, stdin);
    continut[strcspn(continut, "\n")] = 0;

    doc = initializare(titlu, doc.id, doc.numarPagini, continut);

    return doc;
}

int calculeazaNumarLitereTitlu(Document doc) {
    int numarLitere = 0;
    for (int i = 0; doc.titlu[i] != '\0'; i++) {
        if (isalpha(doc.titlu[i])) {
            numarLitere++;
        }
    }
    return numarLitere;
}

void modificaTitlu(Document* doc, const char* noulTitlu) {
    free(doc->titlu);
    doc->titlu = (char*)malloc((strlen(noulTitlu) + 1) * sizeof(char));
    strcpy_s(doc->titlu, strlen(noulTitlu) + 1, noulTitlu);
}

void afisare(Document doc) {
    printf("\nID Document: %d\n", doc.id);
    printf("Titlu: %s\n", doc.titlu);
    printf("Numar de pagini: %d\n", doc.numarPagini);
    printf("Continut: %s\n", doc.continut);
}

void eliberareMemorie(Document* doc) {
    if (doc->titlu != NULL) {
        free(doc->titlu);
    }
    if (doc->continut != NULL) {
        free(doc->continut);
    }
}

int main() {
    Document doc1 = citesteDocument();
    afisare(doc1);
    modificaTitlu(&doc1, "Titlu nou va rog");
    printf("\nDocument dupa modificare:\n");
    afisare(doc1);
    int numarLitere = calculeazaNumarLitereTitlu(doc1);
    printf("\nNumarul de litere din titlul nou: %d\n", numarLitere);
    eliberareMemorie(&doc1);

    return 0;
}
