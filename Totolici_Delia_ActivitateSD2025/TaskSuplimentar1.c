#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

struct Articol {
    int id;
    char* titlu;
    int numarPagini;
    char* continut;
};

typedef struct Articol Articol;

Articol initializare(const char* titlu, int id, int numarPagini, const char* continut) {
    Articol art;
    if (titlu != NULL) {
        art.titlu = (char*)malloc(sizeof(char) * (strlen(titlu) + 1));
        strcpy_s(art.titlu, strlen(titlu) + 1, titlu);
    }
    else {
        art.titlu = NULL;
    }
    art.id = id;
    art.numarPagini = numarPagini;

    if (continut != NULL) {
        art.continut = (char*)malloc(sizeof(char) * (strlen(continut) + 1));
        strcpy_s(art.continut, strlen(continut) + 1, continut);
    }
    else {
        art.continut = NULL;
    }

    return art;
}

Articol citesteArticol() {
    Articol art;
    char titlu[100];
    char continut[500];

    printf("Introduceti ID-ul articolului: ");
    scanf("%d", &art.id);

    getchar();

    printf("Introduceti titlul articolului: ");
    fgets(titlu, 100, stdin);
    titlu[strcspn(titlu, "\n")] = 0;

    printf("Introduceti numarul de pagini: ");
    scanf("%d", &art.numarPagini);

    getchar();

    printf("Introduceti continutul articolului: ");
    fgets(continut, 500, stdin);
    continut[strcspn(continut, "\n")] = 0;

    art = initializare(titlu, art.id, art.numarPagini, continut);

    return art;
}

int calculeazaNumarLitereTitlu(Articol art) {
    int numarLitere = 0;
    for (int i = 0; art.titlu[i] != '\0'; i++) {
        if (isalpha(art.titlu[i])) {
            numarLitere++;
        }
    }
    return numarLitere;
}

void modificaTitlu(Articol* art, const char* noulTitlu) {
    free(art->titlu);
    art->titlu = (char*)malloc((strlen(noulTitlu) + 1) * sizeof(char));
    strcpy_s(art->titlu, strlen(noulTitlu) + 1, noulTitlu);
}

void afisare(Articol art) {
    printf("\nID Articol: %d\n", art.id);
    printf("Titlu: %s\n", art.titlu);
    printf("Numar de pagini: %d\n", art.numarPagini);
    printf("Continut: %s\n", art.continut);
}

void eliberareMemorie(Articol* art) {
    if (art->titlu != NULL) {
        free(art->titlu);
    }
    if (art->continut != NULL) {
        free(art->continut);
    }
}

int main() {
    Articol art1 = citesteArticol();
    afisare(art1);
    modificaTitlu(&art1, "Titlu nou va rog");
    printf("\nArticol dupa modificare:\n");
    afisare(art1);
    int numarLitere = calculeazaNumarLitereTitlu(art1);
    printf("\nNumarul de litere din titlul nou: %d\n", numarLitere);
    eliberareMemorie(&art1);

    return 0;
}
