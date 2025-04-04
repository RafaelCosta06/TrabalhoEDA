/**
 * @file funcoes.h
 * @author Rafael Costa (a31524@alunos.ipca.pt)
 * @brief Declaração das funções e das estruturas
 * @version 1.0
 * @date 2025-03-18
 * 
 * @copyright Copyright (c) 2025
 * 
 */
#include <stdbool.h>

 #pragma once

 #define TAM 250

#pragma region Estruturas

 /// @brief Estrutura para antenas contendo as suas coordenadas, frequencia e um apontador para outra estrutura deste genero
 typedef struct Antena{
    int l,c;
    char frequencia;
    struct Antena* next;
 }Antena;
 
 /// @brief Estrutura para as localizações com efeito nefasto
 typedef struct Efeito{
    int l,c;
    struct Efeito* next;
 }Efeito;

 /// @brief Estrutura das Antenas para guardar/carregar de um ficheiro binário
 typedef struct AntenaFicheiro{
    int l,c;
    char frequencia;
 }AntenaFicheiro;

 /// @brief Estrutura para armazenar a dimensão da Matriz
 typedef struct Dimensao{
   int l;
   int c;
 }Dimensao;

#pragma endregion

#pragma region Antenas

/**
 * @brief Função para criar uma nova antenas
 * 
 * @param l Linha onde queremos adicionar a Antena
 * @param c Coluna onde queremos adicionar a Antena
 * @param frequencia Frequencia que a Antena irá ter
 * @return Antena* Antena Criada
 */
 Antena* CriarAntena(int l, int c, char frequencia);

/**
 * @brief Insere uma nova antena na lista das Antenas de forma ordenada
 * 
 * @param inicio Apontador para o Inicio da lista ligada
 * @param nova Apontador para a nova Antena a adicionar
 * @return Antena* Apontador para o ini­cio da lista já atualizada
 */
 Antena* InserirAntena(Antena* inicio, Antena* nova, Dimensao* matriz);

/**
 * @brief Função para remover uma Antena
 * 
 * @param inicio Apontador para o iní­cio da lista
 * @param l Linha onde se encontra a antena a remover
 * @param c Coluna onde se encontra a antena a remover
 * @return Antena* Apontador para o ini­cio da lista já atualizada
 */
 Antena* RemoverAntena(Antena* inicio, int l, int c);

/**
 * @brief Remove todas as Antenas que estejam a coincidir com a localização de um efeito 
 * 
 * @param inicio Apontador para o inicio da lista das Antenas
 * @param head Apontador para o inicio da lista dos Efeitos
 * @return Antena* Apontador para o inicio da lista das Antenas já atualizada
 */
 Antena* RemoverAllAntenaComEfeito (Antena* inicio, Efeito* head);

/**
 * @brief Destroi toda a lista das Antenas
 * 
 * @param inicio Apontador para o inicio da lista das Antenas
 * @return Antena* Apontador para o inicio da lista das Antenas mas já destruÃ­da
 */
 Antena* DestroiListaAnt(Antena* inicio, Dimensao* matriz);

#pragma endregion

#pragma region Efeitos
/**
 * @brief Função para criar um efeito novo
 * 
 * @param l Linha onde queremos adicionar o Efeito
 * @param c Coluna onde queremos adicionar o Efeito
 * @return Efeito* Efeito criado
 */
 Efeito* CriarEfeito(int l, int c);

/**
 * @brief Insere o novo Efeito na lista dos Efeitos de forma ordenada pela sua coluna "c" e linha "l" 
 * 
 * @param head Apontador para o início da lista ligada
 * @param novo Apontador para o novo Efeito a adicionar
 * @return Efeito* Apontador para o início da lista já atualizada
 */
 Efeito* InserirEfeito(Efeito* head, Efeito* novo, Dimensao* matriz);

/**
 * @brief Função para descubrir a localização dos Efeitos
 * 
 * @param inicio Apontador para o início da lista ligada das Antenas. 
 * @param head Apontador para o início da lista ligada dos Efeitos. 
 * @return * Efeito* Apontador para o início da lista ligada dos Efeitos já atualizada. 
 */
 Efeito* DescubrirEfeito(Antena* inicio, Dimensao* matriz);

 /**
  * @brief Função para destruir a Lista dos Efeitos
  * 
  * @param head Apontador para o início da lista dos Efeitos
  * @return Efeito* Apontador para o início da lista dos Efeitos mas já vazia
  */
 Efeito* DestroiListaEfei(Efeito* head);

 #pragma endregion

 #pragma region Listar na tela

/**
 * @brief Função para apresentar na tela as Antenas de forma tabular
 * 
 * @param inicio Apontador para o início da lista ligada das Antenas
 */
 void ListarAntenas(Antena* inicio);

/**
 * @brief Função para apresentar na tela Efeitos de forma tabular
 * 
 * @param head Apontador para o início da lista ligada dos Efeitos
 */
 void ListarEfeitos(Efeito* head);

 /**
  * @brief Função para imprimir na tela a Matriz
  * 
  * @param inicio Apontador para o início da lista das Antenas
  * @param head Apontador para o início da lista dos Efeitod
  * @param matriz Estrutura que contém os limites da Matriz
  */
 void Matriz (Antena* inicio, Efeito* head, Dimensao* matriz);

 #pragma endregion

 #pragma region Ficheiros

/**
 * @brief Função para ler de um ficeheiro externo '.txt' a matriz que contém as Antenas.
 * 
 * @param Ficheiro Ficheiro que contém a matriz
 * @return Antena* Apontador para o iní­cio da lista já atualizada
 */
 Antena* CarregarDoFicheiro(char* Ficheiro, Dimensao* matriz);

/**
 * @brief Função para guardar as Antenas num ficheiro binário
 * Retorna 1 em caso de sucesso, 0 em caso de falha
 * 
 * @param inicio Apontador para o iní­cio da lista das Antenas
 * @param Ficheiro Ficheiro onde vamos guardar as Antenas
 */
 bool GuardarAntenasBin(Antena* inicio, char* Ficheiro); 

/**
 * @brief Ficheiro para ler as Antenas atraváves de um ficheiro binário
 * 
 * @param Ficheiro Ficheiro Binário que contém as Antenas
 * @return Antena* Apontador para o início da lista ligadas das Antenas
 */
 Antena* LerAntenasBin (char* Ficheiro, Dimensao* matriz);

 #pragma endregion
