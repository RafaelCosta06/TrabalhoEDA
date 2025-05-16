/**
 * @file ecra.c
 * @author Rafael Costa (a31524@alunos.ipca.pt)
 * @brief Implementação das funções que apresentam informação no ecra
 * @version 1.0
 * @date 2025-04-29
 * 
 * @copyright Copyright (c) 2025
 * 
 */

 #include "ecra.h"
 #include <stdio.h>
 #include <string.h>

 /**
  * @brief Função para imprimir na tela a Matriz
  * 
  * @param inicio Apontador para o início da lista das Antenas
  * @param head Apontador para o início da lista dos Efeitod
  * @param matriz Estrutura que contém os limites da Matriz
  */
void Matriz (Antena* inicio, Efeito* head, Dimensao* matriz){

    Antena* auxAntena;
    Efeito* auxEfeito;

    for(int l =0; l<matriz->l; l++){
        for(int c=0 ; c<matriz->c; c++){
            char caracter = '.'; // preencher por padrão como vazio

            for(auxAntena = inicio; auxAntena != NULL ; auxAntena = auxAntena->next){
                if(auxAntena->l == l && auxAntena->c == c){
                    caracter = auxAntena->frequencia;
                }
            }

            for(auxEfeito = head ; auxEfeito != NULL ; auxEfeito = auxEfeito->next){
                if(auxEfeito->l == l && auxEfeito->c == c){
                    if(caracter != '.'){
                        caracter = '!';
                    }else{
                        caracter = '#';
                    }
                }
            }

            printf("%c", caracter);

        }
        printf("\n"); // trocar de linha quando acabam as colunas
    }
 }
