#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "cidades.h"

int main(){
    const char *arquivoEntrada = "src/teste02.txt";

    // Teste da função getEstrada
    Estrada *estrada = getEstrada(arquivoEntrada);

    if (estrada != NULL) {
        printf("Estrada carregada com sucesso!\n");
        printf("Comprimento da Estrada (T): %d\nTotal de Cidades (N): %d\n\n", estrada->T, estrada->N);
        
        for (int i = 0; i < estrada->N; i++) {
            printf("Cidade: %s, Posicao: %d\n", estrada->C[i].Nome, estrada->C[i].Posicao);
        }

        // Teste da função calcularMenorVizinhanca
        double menorVizinhanca = calcularMenorVizinhanca(arquivoEntrada);

        if (menorVizinhanca >= 0) {
            printf("\nMenor vizinhanca: %.1f\n", menorVizinhanca);
        } else {
            printf("Falha ao calcular a menor vizinhanca.\n");
        }

        // Teste da função cidadeMenorVizinhanca
        char *cidadeMenor = cidadeMenorVizinhanca(arquivoEntrada);
        if (cidadeMenor != NULL) {
            printf("Cidade com menor vizinhanca: %s\n", cidadeMenor);
            free(cidadeMenor);
        } else {
            printf("Falha ao encontrar a cidade com menor vizinhanca.\n");
        }

        // Libera a memória alocada para a estrada
        free(estrada->C);
        free(estrada);
        
    } else {
        printf("Falha ao carregar a estrada (retorno NULL)\n");
    }

    return 0;
}