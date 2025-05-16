/**
 * @file ecra.c
 * @author Rafael Costa (a31524@alunos.ipca.pt)
 * @brief 
 * @version 1.0
 * @date 2025-05-16
 * 
 * @copyright Copyright (c) 2025
 * 
 */


 #include "ecra.h"
 #include <stdio.h>

/**
 * @brief Função para imprimir na Tela as Antenas Visitadas
 * 
 * @param visitadas Apontador para o inicio da lista das Antenas Visitadas
 */
void ImprimirVisitadas (AntenasVisitadas* visitadas){
  for(AntenasVisitadas* aux = visitadas ; aux != NULL ; aux = aux->next){
      printf("Antena (%d , %d) visitada\n", aux->l, aux->c);
  } 
}

/**
 * @brief Função que imprime a Antena e as respectivas adjacencias
 * 
 * @param inicio Apontador para o inicio da lista das Antenas
 */
void ImprimirAdjacencias(Antena* inicio) {
  for (Antena* aux = inicio; aux != NULL; aux = aux->next) {
      printf("Antena (%d, %d) - Frequência: %c\n", aux->l, aux->c, aux->frequencia);
      printf("Adjacências: ");
      for (Adjacencia* adj = aux->Adj; adj != NULL; adj = adj->next) {
          printf("(%d, %d) \n", adj->l, adj->c);
      }
      printf("\n");
  }
}