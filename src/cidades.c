#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cidades.h"

// Inicializa cidades no TAD indicado acima.
Estrada *getEstrada(const char *nomeArquivo){
    FILE *fp = fopen(nomeArquivo, "r");
    if (fp == NULL) {
        perror("Erro ao abrir o arquivo");
        return NULL;
    }

    Estrada *estrada = (Estrada *)malloc(sizeof(Estrada));
    if (estrada == NULL) {
        perror("Erro ao alocar memória para Estrada");
        fclose(fp);
        return NULL;
    }

    fscanf(fp, "%d %d\n", &estrada->T, &estrada->N);

    // Verificar 3 ≤ T ≤ 10^6
    if (estrada->T < 3 || estrada->T > 1000000) {
        free(estrada);
        fclose(fp);
        return NULL;
    }
    
    // Verificar 2 ≤ N ≤ 10^4
    if (estrada->N < 2 || estrada->N > 10000) {
        free(estrada);
        fclose(fp);
        return NULL;
    }

    estrada->C = (Cidade *)malloc(estrada->N * sizeof(Cidade));
    if (estrada->C == NULL) {
        perror("Erro ao alocar memória para Cidade");
        free(estrada);
        fclose(fp);
        return NULL;
    }

    // Array para verificar posições únicas
    int *posicoes = (int *)calloc(estrada->T + 1, sizeof(int));
    if (posicoes == NULL) {
        free(estrada->C);
        free(estrada);
        fclose(fp);
        return NULL;
    }

    for (int i = 0; i < estrada->N; i++) {
        int posicao;
        char nome[256];
        fscanf(fp, "%d %[^\n]\n", &posicao, nome);

        // Verificar 0 < Xi < T
        if (posicao <= 0 || posicao >= estrada->T) {
            free(posicoes);
            free(estrada->C);
            free(estrada);
            fclose(fp);
            return NULL;
        }

        // Verificar Xi ≠ Xj (posições únicas)
        if (posicoes[posicao] == 1) {
            free(posicoes);
            free(estrada->C);
            free(estrada);
            fclose(fp);
            return NULL;
        }
        posicoes[posicao] = 1;

        estrada->C[i].Posicao = posicao;
        strcpy(estrada->C[i].Nome, nome);
    }

    free(posicoes);
    fclose(fp);
    return estrada;
}    

// Retorna a menor vizinhança.
double calcularMenorVizinhanca(const char *nomeArquivo) {
    Estrada *estrada = getEstrada(nomeArquivo);
    if (estrada == NULL) return -1.0;

    // Ordena as cidades por posição
    for (int i = 0; i < estrada->N - 1; i++) {
        for (int j = 0; j < estrada->N - i - 1; j++) {
            if (estrada->C[j].Posicao > estrada->C[j + 1].Posicao) {
                Cidade temp = estrada->C[j];
                estrada->C[j] = estrada->C[j + 1];
                estrada->C[j + 1] = temp;
            }
        }
    }

    double menorVizinhanca = estrada->T;
    for (int i = 0; i < estrada->N; i++) {
        double vizinhanca;
        if (i == 0) { // Primeira cidade
            vizinhanca = ((estrada->C[i].Posicao + estrada->C[i + 1].Posicao) / 2.0) - 0;
        } else if (i == estrada->N - 1) { // Última cidade
            vizinhanca = estrada->T - ((estrada->C[i].Posicao + estrada->C[i - 1].Posicao) / 2.0);
        } else { // Cidades do meio
            double esquerda = (estrada->C[i].Posicao + estrada->C[i - 1].Posicao) / 2.0;
            double direita = (estrada->C[i].Posicao + estrada->C[i + 1].Posicao) / 2.0;
            vizinhanca = direita - esquerda;
        }
        if (vizinhanca < menorVizinhanca) {
            menorVizinhanca = vizinhanca;
        }
    }

    free(estrada->C);
    free(estrada);
    return menorVizinhanca;
}

// Retorna a cidade que tem menor vizinhança.
char *cidadeMenorVizinhanca(const char *nomeArquivo) {
    Estrada *estrada = getEstrada(nomeArquivo);
    if (estrada == NULL) return NULL;

    // Ordena as cidades por posição
    for (int i = 0; i < estrada->N - 1; i++) {
        for (int j = 0; j < estrada->N - i - 1; j++) {
            if (estrada->C[j].Posicao > estrada->C[j + 1].Posicao) {
                Cidade temp = estrada->C[j];
                estrada->C[j] = estrada->C[j + 1];
                estrada->C[j + 1] = temp;
            }
        }
    }

    double menorVizinhanca = estrada->T;
    int indiceMenor = 0;
    for (int i = 0; i < estrada->N; i++) {
        double vizinhanca;
        if (i == 0) { // Primeira cidade
            vizinhanca = ((estrada->C[i].Posicao + estrada->C[i + 1].Posicao) / 2.0) - 0;
        } else if (i == estrada->N - 1) { // Última cidade
            vizinhanca = estrada->T - ((estrada->C[i].Posicao + estrada->C[i - 1].Posicao) / 2.0);
        } else { // Cidades do meio
            double esquerda = (estrada->C[i].Posicao + estrada->C[i - 1].Posicao) / 2.0;
            double direita = (estrada->C[i].Posicao + estrada->C[i + 1].Posicao) / 2.0;
            vizinhanca = direita - esquerda;
        }
        if (vizinhanca < menorVizinhanca) {
            menorVizinhanca = vizinhanca;
            indiceMenor = i;
        }
    }

    char *nome = strdup(estrada->C[indiceMenor].Nome);
    free(estrada->C);
    free(estrada);
    return nome;
}