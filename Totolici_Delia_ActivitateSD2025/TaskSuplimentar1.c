#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct DistribuitorTransport {
    int cod;
    char* denumire;
    int nrProduse;
    float* preturi;
} DistribuitorTransport;

void afisareDistribuitor(DistribuitorTransport articol) {
    printf("Cod: %d\n", articol.cod);
    printf("Denumire: %s\n", articol.denumire);
    printf("Numar produse: %d\n", articol.nrProduse);
    printf("Preturi: ");
    for (int i = 0; i < articol.nrProduse; i++) {
        printf("%.2f ", articol.preturi[i]);
    }
    printf("\n");
}

float calculeazaMediaPreturilor(DistribuitorTransport articol) {
    if (articol.nrProduse == 0) return 0;
    float suma = 0;
    for (int i = 0; i < articol.nrProduse; i++) {
        suma += articol.preturi[i];
    }
    return suma / articol.nrProduse;
}

void modificaDenumire(DistribuitorTransport* articol, const char* nouaDenumire) {
    free(articol->denumire);
    articol->denumire = (char*)malloc(strlen(nouaDenumire) + 1);
    strcpy_s(articol->denumire, strlen(nouaDenumire) + 1, nouaDenumire);
}

DistribuitorTransport citesteDistribuitor() {
    DistribuitorTransport articol;
    printf("Introdu codul articolului: ");
    scanf_s("%d", &articol.cod);
    getchar();
    char buffer[100];
    printf("Introdu denumirea articolului: ");
    fgets(buffer, sizeof(buffer), stdin);
    buffer[strcspn(buffer, "\n")] = 0;
    articol.denumire = (char*)malloc(strlen(buffer) + 1);
    strcpy_s(articol.denumire, strlen(buffer) + 1, buffer);
    printf("Introdu numarul de produse: ");
    scanf_s("%d", &articol.nrProduse);
    articol.preturi = (float*)malloc(articol.nrProduse * sizeof(float));
    for (int i = 0; i < articol.nrProduse; i++) {
        printf("Pretul produsului %d: ", i + 1);
        scanf_s("%f", &articol.preturi[i]);
    }

    return articol;
}

void dezalocare(DistribuitorTransport* articol) {
    free(articol->denumire);
    free(articol->preturi);
}

int main() {
    DistribuitorTransport articol = citesteDistribuitor();
    afisareDistribuitor(articol);

    printf("Media preturilor: %.2f\n", calculeazaMediaPreturilor(articol));

    printf("Introdu noua denumire a articolului: ");
    char buffer[100];
    getchar();
    fgets(buffer, sizeof(buffer), stdin);
    buffer[strcspn(buffer, "\n")] = 0;
    modificaDenumire(&articol, buffer);

    printf("Dupa modificare:\n");
    afisareDistribuitor(articol);

    dezalocare(&articol);

    return 0;
}
