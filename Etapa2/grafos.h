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
    bool visitado;
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
 

 /**
  * @brief Função para remover Antena da lista dos vertices
  * 
  * 
  * @param inicio Apontador para a lista dos vertices
  * @param l Linha da Antena a remover
  * @param c Coluna da Antena a remover
  * @param verificar Auxiliar para verificar se executou corretamente
  * @return Antena* Lista dos vertices sem a Antena já.
  */
 Antena* RemoverAntena (Antena* inicio, int l, int c, bool* verificar);

 /**
  * @brief Função que romove todos os vertices (Antenas)
  * 
  * 
  * @param inicio Apontador para o inicio da lista dos vértices
  * @return Antena* Apontador para o inicio da lista dos vertices, a NULL, porque removeu todas as antenas
  */
 Antena* RemoveTodasAntenas(Antena* inicio);


 #pragma endregion

#pragma region Adjacencias

/**
 * @brief Cria uma nova adjacencia para uma antena, com base nas coordenadas fornecidas
 * 
 * 
 * @param l Linha da adjacencia a adicionar
 * @param c Linha da coluna a adicionar
 * @param verificar Auxiliar para verificar se executou corretamente
 * @return Adjacencia* Apontador para a adjacencia criada
 */
Adjacencia* CriarAdj (int l, int c, bool* verificar);

/**
  * @brief Função insere a adjacencia no vertice pretendido
  * 
  * 
  * @param vertice Apontador para o vertice que deseja inserir a adjacencia.
  * @param nova Apontador para a adjacencia que deseja inserir.
  * @return true se adicionar a adjacencia com sucesso
  * @return false se ocorrer algum erro na inserção
  */
bool InsereAdj (Antena* vertice, Adjacencia* nova);

/**
 * @brief A função calcula todas as adjacencias
 * 
 * 
 * @param inicio Apontador para o inicio da lista das Antenas
 * @return true Caso calcule todas as adjacencias com sucesso
 * @return false Caso haja um erro no calculo das adjacencias
 */
bool CalcularAdj (Antena* inicio);

/**
 * @brief Função elimina todas as Adjacencias
 * 
 * 
 * @param inicio Apontador para o inicio da lista das Antenas
 * @return true Caso Remova todas com sucesso
 * @return false Caso haja algum erro a devolver
 */
bool EliminarAllAdj (Antena* inicio);

#pragma endregion

#pragma region Ficheiros

/**
  * @brief Carrega de um ficheiro.txt todos os vertices do grafo.
  * 
  * 
  * @param Ficheiro Ficheiro.txt que contem a matriz
  * @param verificar Auxiliar para verificar se executou corretamente
  * @return Antena* Apontador para o inicio da lista das Antenas
  */
Antena* CarregarFicheiro(char* NomeFicheiro, bool* verificar);

/**
  * @brief Guarda o grafo de antenas num ficheiro binário.
  * 
  * 
  * @param inicio  Ponteiro para o início da lista de antenas.
  * @param NomeFicheiro 
  * @return true se o ficheiro foi guardado com sucesso
  * @return false se ocorreu erro
  */
bool GuardarFicheiroBin (Antena* inicio, char* NomeFicheiro);

/**
 * @brief Carrega um grafo de antenas a partir de um ficheiro binário.
 * 
 *
 * @param NomeFicheiro Ficheiro binario onde será guardado
 * @param verificar Auxiliar para verificar se executou corretamente
 * @return Antena* Apontador para o inicio da lista dos vertices
 */
Antena* CarregarFicheiroBin (char* NomeFicheiro, bool* verificar);


#pragma endregion




void ImprimirAdjacencias(Antena* inicio);