/**
 * @file grafos.h
 * @author Rafael Costa (a31524@alunos.ipca.pt)
 * @brief Definiçao das estruturas de dados e das funções sobtr grafos
 * @version 1.0
 * @date 2025-05-12
 * 
 * @copyright Copyright (c) 2025
 * 
 */

 #pragma once

 #include <stdbool.h>

 #pragma region Estrutura de dados

 /// @brief Estrutura de dados para as adjacencias
 typedef struct Adjacencia{
    int l,c; 
    struct Adjacencia* next;
 }Adjacencia;

 typedef struct Antena{
    char frequencia;
    int l,c;
    struct Antena * next;        // falta meter visitado
    struct Adjacencia * Adj;
 }Antena;

 #pragma endregion

 #pragma region Vertices (Antenas)

/**
 * @brief Função para criar uma nova antena (vertice)
 * 
 * Esta função aloca memória para uma nova estrutura "Antena" e retorna um ponteiro para a antena criada.
 * Caso a alocação de memória falhe, retorna 'NULL'.
 * 
 * @param frequencia Frequencia que a Antena irá ter
 * @param l Linha onde queremos adicionar a Antena
 * @param c Coluna onde queremos adicionar a Antena
 * @param verificar Auxiliar para verificar se executou corretamente
 * @return Antena* 
*/
 Antena* CriarAntena( char frequencia, int l, int c, bool* verificar);

 /**
  * @brief Insere uma nova antena na lista das Antenas de forma ordenada
  * 
  * @param inicio Apontador para o inicip da liosta dos vertices (Antenas)
  * @param nova Apontador para uma nova Atena
  * @param verificar Auxiliar para verificar se executou corretamente
  * @return Antena* Apontador para o inicioo dos vertices (Antenas)
  */
 Antena* InserirAntena (Antena* inicio, Antena* nova, bool* verificar);

/**
 * @brief Função para verificar se uma determinada antena já pertence á lista dos vertices
 * 
 * @param inicio Apontador para o inicio da lista dos vertices
 * @param antena Apontador para a antena que queremos verificar
 * @return true Caso essa antena já pertença á lista dos vertices
 * @return false Caso essa antena não pertença á lista dos vertices
 */
 bool ExisteAntena (Antena* inicio, Antena* antena);

 Antena* RemoverAntena (Antena* inicio, int l, int c, bool* verificar);

 #pragma endregion

#pragma region Adjacencias

 Adjacencia* CriarAdj (int l, int c, bool* verificar);

 //Adjacencia* InsereAdj (Adjacencia* head)


#pragma endregion

#pragma region Ficheiros

Antena* CarregarFicheiro(char* NomeFicheiro, bool* verificar);



#pragma endregion
