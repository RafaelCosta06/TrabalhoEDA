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
#include "ecra.h"

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
    Dimensao matriz = {0,0};
    bool verificar1;
    bool verificar2;
    
    printf("CARREGAR DO FICHEIRO\n");
    Antenas = CarregarDoFicheiro ("matriz.txt", &matriz,&verificar1);
    if(verificar1){
        printf("Matriz Carregada do Ficheiro com sucesso!\n");
        Matriz (Antenas, Efeitos, &matriz);
    }else {
        printf("Erro ao carregar a matriz do Ficheiro\n");
    }

    printf("INSERIR ANTENA!\n");
    aux = CriarAntena(5,5,'B', &verificar1);
    if(verificar1){
        Antenas = InserirAntena(Antenas, aux, &matriz, &verificar2);
        if(verificar2){
            printf("Antenas Inserida com sucesso!\n");
            Matriz (Antenas, Efeitos, &matriz);
        } else{
            printf("Erro ao Inserir a Antena!\n");
        }
    } else{
        printf("Erro ao Criar Antena!\n");
    }

    printf("REMOVER ANTENA!\n");
    Antenas = RemoverAntena(Antenas,5,5, &verificar1);
    if(verificar1){
        printf("Antena Removida com Sucesso!\n");
        Matriz (Antenas, Efeitos, &matriz);
    }else {
        printf("Erro ao remover Antena!\n");
    }
    
   printf("CALCULAR EFEITOS!\n");
    Efeitos = DescubrirEfeito(Antenas, &matriz, &verificar1);
    if(verificar1){
        printf("Efeitos encontrados!\n");
        Matriz (Antenas, Efeitos, &matriz);
    }else {
        printf("Efeitos não encontrados!\n");
    }

    printf("REMOVER ANTENAS EM CONFLITO E CALCULAR NOVO EFEITO\n");
    Antenas = RemoverAllAntenaComEfeito(Antenas, Efeitos, &verificar1);
    if(verificar1){
        printf("Antenas em conflito removidas!\n");
    }else {
        printf("Nenhuma antena removida!\n");
    }

    Efeitos = DescubrirEfeito (Antenas, &matriz, &verificar1);
    if(verificar1){
        printf("Novos Efeitos Encontrados!\n");
        Matriz (Antenas, Efeitos, &matriz);
    }else {
        printf("Erro ao calcular efeitos!\n");
    }
    
    
    printf("GUARDAR DADOS EM FICHEIROS\n");
    ficheiro = GuardarAntenasBin(Antenas, "Antenas.bin");
    
    if(ficheiro){
        printf("Dados guardados com sucesso!\n");
    }else {
        printf("Erro ao guardar dados no ficheiro!\n");
    }

    printf("DESTRUIR LISTAS\n");
    Antenas = DestroiListaAnt(Antenas, &matriz, &verificar1);
    if(verificar1){
        printf("Lista das Antenas Destruida!\n");
    }else {
        printf("Erro ao destruir lista das Antenas!\n");
    }
    Efeitos = DestroiListaEfei(Efeitos, &verificar1);
    if(verificar1){
        printf("Lista dos Efeiros Destruida!\n");
    }else {
        printf("Erro ao destruir lista dos Efeitos!\n");
    }

    printf("LER DE UM FICHEIRO BIN\n");
    Antenas = LerAntenasBin("Antenas.bin", &matriz, &verificar1);
    if(verificar1){
        printf("Lido com sucesso!\n");
        Matriz (Antenas, Efeitos, &matriz);
    }

    return 0;
    

}