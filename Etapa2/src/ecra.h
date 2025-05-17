/**
 * @file ecra.h
 * @author Rafael Costa (a31524@alunos.ipca.pt)
 * @brief Definição de funções para mostrar no ecra
 * @version 1.0
 * @date 2025-05-16
 * 
 * @copyright Copyright (c) 2025
 * 
 */
#pragma once

 #include "grafos.h"

/**
 * @brief Função para imprimir na Tela as Antenas Visitadas
 * 
 * @param visitadas Apontador para o inicio da lista das Antenas Visitadas
 */
 void ImprimirVisitadas (AntenasVisitadas* lista);

/**
 * @brief Função que imprime a Antena e as respectivas adjacencias
 * 
 * @param inicio Apontador para o inicio da lista das Antenas
 */
 void ImprimirAdjacencias(Antena* inicio);
