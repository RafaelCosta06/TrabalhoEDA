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
 * @param verificar Auxiliar para verificar se executou corretamente
 * @return Antena* Antena Criada
 */
 Antena* CriarAntena(int l, int c, char frequencia, bool* verificar);

/**
 * @brief Insere uma nova antena na lista das Antenas de forma ordenada
 * 
 * @param inicio Apontador para o Inicio da lista ligada
 * @param nova Apontador para a nova Antena a adicionar
 * @param verificar Auxiliar para verificar se executou corretamente
 * @return Antena* Apontador para o ini­cio da lista já atualizada
 */
 Antena* InserirAntena(Antena* inicio, Antena* nova, Dimensao* matriz, bool* verificar);

/**
 * @brief Função para remover uma Antena
 * 
 * @param inicio Apontador para o iní­cio da lista
 * @param l Linha onde se encontra a antena a remover
 * @param c Coluna onde se encontra a antena a remover
 * @param verificar Auxiliar para verificar se executou corretamente
 * @return Antena* Apontador para o ini­cio da lista já atualizada
 */
 Antena* RemoverAntena(Antena* inicio, int l, int c, bool* verificar);

/**
 * @brief Remove todas as Antenas que estejam a coincidir com a localização de um efeito 
 * 
 * @param inicio Apontador para o inicio da lista das Antenas
 * @param head Apontador para o inicio da lista dos Efeitos
 * @param verificar Auxiliar para verificar se executou corretamente
 * @return Antena* Apontador para o inicio da lista das Antenas já atualizada
 */
 Antena* RemoverAllAntenaComEfeito (Antena* inicio, Efeito* head, bool* verificar);

/**
 * @brief Destroi toda a lista das Antenas
 * 
 * @param inicio Apontador para o inicio da lista das Antenas
 * @param verificar Auxiliar para verificar se executou corretamente
 * @return Antena* Apontador para o inicio da lista das Antenas mas já destruÃ­da
 */
 Antena* DestroiListaAnt(Antena* inicio, Dimensao* matriz, bool* verificar);

#pragma endregion

#pragma region Efeitos
/**
 * @brief Função para criar um efeito novo
 * 
 * @param l Linha onde queremos adicionar o Efeito
 * @param c Coluna onde queremos adicionar o Efeito
 * @param verificar Auxiliar para verificar se executou corretamente
 * @return Efeito* Efeito criado
 */
 Efeito* CriarEfeito(int l, int c, bool* verificar);

/**
 * @brief Insere o novo Efeito na lista dos Efeitos de forma ordenada pela sua coluna "c" e linha "l" 
 * 
 * @param head Apontador para o início da lista ligada
 * @param novo Apontador para o novo Efeito a adicionar
 * @param verificar Auxiliar para verificar se executou corretamente
 * @return Efeito* Apontador para o início da lista já atualizada
 */
 Efeito* InserirEfeito(Efeito* head, Efeito* novo, Dimensao* matriz, bool* verificar);

/**
 * @brief Função para descubrir a localização dos Efeitos
 * 
 * @param inicio Apontador para o início da lista ligada das Antenas. 
 * @param head Apontador para o início da lista ligada dos Efeitos. 
 * @param verificar Auxiliar para verificar se executou corretamente
 * @return * Efeito* Apontador para o início da lista ligada dos Efeitos já atualizada. 
 */
 Efeito* DescubrirEfeito(Antena* inicio, Dimensao* matriz, bool* verificar);

 /**
  * @brief Função para destruir a Lista dos Efeitos
  * 
  * @param head Apontador para o início da lista dos Efeitos
  * @param verificar Auxiliar para verificar se executou corretamente
  * @return Efeito* Apontador para o início da lista dos Efeitos mas já vazia
  */
 Efeito* DestroiListaEfei(Efeito* head, bool* verificar);

 #pragma endregion


 #pragma region Ficheiros

/**
 * @brief Função para ler de um ficeheiro externo '.txt' a matriz que contém as Antenas.
 * 
 * @param Ficheiro Ficheiro que contém a matriz
 * @param verificar Auxiliar para verificar se executou corretamente
 * @return Antena* Apontador para o iní­cio da lista já atualizada
 */
 Antena* CarregarDoFicheiro(char* Ficheiro, Dimensao* matriz, bool* verificar);

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
 * @param verificar Auxiliar para verificar se executou corretamente
 * @return Antena* Apontador para o início da lista ligadas das Antenas
 */
 Antena* LerAntenasBin (char* Ficheiro, Dimensao* matriz, bool* verificar);

 #pragma endregion
