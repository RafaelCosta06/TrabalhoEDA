/**
 * @file main.c
 * @author Rafael Costa (a31524@alunos.ipca.pt)
 * @brief Teste das função implementadas
 * @version 1.0
 * @date 2025-03-29
 * 
 * @copyright Copyright (c) 2025
 * 
 */
#include <stdio.h>
#include <stdbool.h>
#include "funcoes.h"

/**
 * @brief Função principal do programa, que chama e testa todas as funções criadas
 * 
 * @return int Retorna 0 caso o prograna execute corretamente
 */
int main(){
    Antena* Antenas = NULL;
    Efeito* Efeitos = NULL;
    Antena* aux;
    bool ficheiro;
    
    printf("\n");
    printf("MATRIZ CARREGADA DO FICHEIRO:\n");
    Antenas = CarregarDoFicheiro ("matriz.txt");
    ListarAntenas(Antenas);
    // Imprimir a Matriz

    printf("\n");
    printf("INSERIDA UMA ANTENA:\n");
    aux = CriarAntena(5,5,'B');
    Antenas = InserirAntena(Antenas, aux);
    ListarAntenas(Antenas);
    // Imprimir a Matriz

    printf("\n");
    printf("ANTENA REMOVIDA:\n");
    Antenas = RemoverAntena(Antenas,5,5);
    ListarAntenas(Antenas);
    // Imprimir a Matriz

    printf("\n");
    printf("CALCULAR EFEITOS:\n");
    Efeitos = DescubrirEfeito(Antenas);
    ListarEfeitos (Efeitos);

    printf("\n");
    printf("REMOVER ANTENAS EM CONFLITO E CALCULAR NOVO EFEITO\n");
    Antenas = RemoverAllAntenaComEfeito(Antenas, Efeitos);
    Efeitos = DescubrirEfeito (Antenas);
    ListarAntenas (Antenas);
    ListarEfeitos (Efeitos);

    // Imprimir matriz com efeitos e coordenadas

    ficheiro = GuardarAntenasBin(Antenas, "Antenas.bin");
    printf("\n");
    printf("Ficheiro: %d\n", ficheiro);

    Antenas = DestroiLista(Antenas);
    printf("\n");
    printf("Antenas depois da lista ser destruida:\n");
    ListarAntenas (Antenas);

    Antenas = LerAntenasBin("Antenas.bin");
    printf("\n");
    printf("Antenas depois de serem lidas do ficheiro:\n");
    ListarAntenas (Antenas);


    return 0;
    

}