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
    struct Antena * next;        
    struct Adjacencia * Adj;
    bool visitado;
 }Antena;

 typedef struct AntenasVisitadas{
    int l;
    int c;
    struct AntenasVisitadas* next;
 }AntenasVisitadas;

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

#pragma region Visitados

/**
 * @brief Função para cria um AntenasVisitado
 * 
 * A função aloca memoria para uma estrutura do tipo AntenasVisitado 
 * e passa as coordenadas passadas por parametro para a struct.
 * Coloca o apontador a NULL.
 * 
 * @param l Linha da Antena Visitada
 * @param c Coluna da Antena visitada
 * @param verificar Auxiliar para verificar se executou corretamente
 * @return AntenasVisitadas* Apontador para uma AntenaVisitada criada
 */
AntenasVisitadas* CriarVisitado (int l, int c, bool* verificar);

/**
 * @brief Insere uma AntenaVisitada na lista de Antenas Visitadas
 * 
 * @param inicio Apontador para o inicio da lista das antenas visitadas
 * @param nova Apontador para a antena visitada a inserir
 * @param verificar Auxiliar para verificar se executou corretamente
 * @return AntenasVisitadas* Apontador para a inicio da lista das Antenas Visitadas
 */
AntenasVisitadas* InserirVisitadas(AntenasVisitadas* inicio, AntenasVisitadas* nova, bool* verificar);


/**
 * @brief Função para limpar o parametro visitado das Antenas
 * 
 * @param inicio Apontador para o inicio da lista das Antenas
 * @return true Caso troque todos os parametros para false
 * @return false caso aconteça algum erro
 */
bool LimparVisitado (Antena* inicio);


#pragma endregion

#pragma region Travessia

/**
 * @brief Inicio de uma travessia em profundidade
 * 
 * Esta função limpa os marcadores de visita de todas as antenas no grafo e inicia
 * uma travessia em profundidade a partir da antena localizada nas coordenadas (l, c).
 * As antenas visitadas são armazenadas numa lista ligada "AntenasVisitadas".
 * 
 * @param inicio Apontador para o inicio da lista das Antenas
 * @param l linha da Antena de partida
 * @param c Coluna da Antena de partida
 * @return AntenasVisitadas* Apontador para o inicio da lista das Antenas visitadas
 */
AntenasVisitadas* IniciarTravProfu(Antena* inicio, int l, int c);

/**
 * @brief Travessia do grafo em profundidade
 * 
 * 
 * @param vertice Apontador para um vertice
 * @param inicio Apontador para a lista das Antenas
 * @param visitadas Apontador para a lista das Antenas Visitadas
 * @return AntenasVisitadas* Apontador para uma lista que contem todas as Antenas Visitadas
 */
AntenasVisitadas* TravProfu (Antena* vertice,Antena* inicio, AntenasVisitadas* visitadas);

/**
 * @brief Função que realiza a travessia completa
 * 
 * @param inicio Apontador para o inicio da lista das Antenas
 * @return AntenasVisitadas* Apontador para o inicio da listas das Antenas Visitadas
 */
AntenasVisitadas* TravessiaCompleta(Antena* inicio);

#pragma endregion





















void ImprimirAdjacencias(Antena* inicio);