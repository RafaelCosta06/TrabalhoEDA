/**
 * @file grafos.c
 * @author Rafael Costa (a31524@alunos.ipca.pt)
 * @brief Implementação das funções sobre grafos
 * @version 1.0
 * @date 2025-05-12
 * 
 * @copyright Copyright (c) 2025
 * 
 */

 #include "grafos.h"
 #include <stdio.h>
 #include <malloc.h>
 #include <string.h>
 #include <stdbool.h>

 #pragma region Vertices Antenas

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
 Antena* CriarAntena (char frequencia, int l, int c, bool* verificar){
    Antena* aux;

    aux = (Antena*)malloc(sizeof(Antena));
    if(aux == NULL){
        *verificar = false;
        return NULL;
    }
    aux->frequencia = frequencia;
    aux->c = c;
    aux->l = l;
    aux->Adj = NULL;
    aux->next = NULL;
    *verificar = true;
    return aux;
 }

 /**
  * @brief Insere uma nova antena na lista das Antenas de forma ordenada
  * 
  * A função percorre a lista ligada das antenas e insere uma nova antena na posição correta.
  * A função verifica se essa Antena já existe na lista.
  * Se a lista estiver vazia, a nova Antena torna-se o início da lista.
  * Se não houver nada a inserir o início da lista mantém-se.
  * 
  * A função percorre a lista com ajuda de dois auxiliares á procura da localização correta para a nova Antena.
  * Se os dois auxilires forem iguais, significa que o loop não avançou logo temos de inserir no início. 
  * Se o auxiliar da frente apontar para NULL e e a linha de nova for maior que a linha do auxiliar, ou se forem iguias mas a coluna de nova for maior, adicionamos no fim
  * Caso não seja para adinionar no início nem no fim, adicionamos no meio na localização certa. 
  * 
  * 
  * @param inicio Apontador para o inicip da liosta dos vertices (Antenas)
  * @param nova Apontador para uma nova Atena
  * @param verificar Auxiliar para verificar se executou corretamente
  * @return Antena* Apontador para o inicioo dos vertices (Antenas) 
  */
 Antena* InserirAntena (Antena* inicio, Antena* nova, bool* verificar){
    *verificar = false;

    if(inicio == NULL){
        inicio = nova;
        *verificar = true;
        return inicio;
    }
    if(ExisteAntena(inicio, nova) == true){
        return inicio; // mantem o verificar em false
    } else{
        Antena* aux= inicio;
        Antena* aux2= aux;

        while((aux->next != NULL) && (aux->l < nova->l || (aux->l == nova->l && aux->c < nova->c))){ 
            aux2=aux;
            aux=aux->next;
        }
        
        if(aux == aux2){  // Caso esteja no início
            nova->next = inicio;
            inicio = nova;
            *verificar = true;
            return inicio;
        }
    
        if(aux->next == NULL && (aux->l < nova->l || (aux->l == nova->l && aux->c < nova->c))){ // Caso esteja no fim           
            aux->next = nova;
            *verificar = true;
            return inicio;
        }
        
        aux2->next = nova; // Caso esteja no meio
        nova->next = aux;
        *verificar = true;
        return inicio;
    }

 }

 /**
  * @brief Função para verificar se uma determinada antena já pertence á lista dos vertices
  * 
  * Função compara as coordenadas da Antena a inserir com as coordenadas de todas as Antenas já existentes.
  * 
  * @param inicio Apontador para o inicio da lista dos vertices
  * @param antena Apontador para a antena que queremos verificar
  * @return true Caso essa antena já pertença á lista dos vertices
  * @return false Caso essa antena não pertença á lista dos vertices
  */
 bool ExisteAntena (Antena* inicio, Antena* antena){
    if(inicio == NULL) return false;
    Antena* aux = inicio;
    while(aux != NULL){
        if((aux->c == antena->c) && (aux->l == antena->l))return true;
        aux = aux->next;
    }
    return false;  
 }

 Antena* RemoverAntena (Antena* inicio, int l, int c, bool* verificar){
    *verificar = false;
    if(inicio == NULL) return NULL;

    Antena* aux = inicio;
    Antena* aux2 = aux;

    while( aux != NULL && (aux->c != c || aux->l !=l)){  //Encontra a posição da Antena a remover
        aux2 = aux;
        aux = aux->next;
    }
    if(aux == NULL)return inicio; // Antena não encontrada

    Adjacencia* auxAdj= aux->Adj;  
    Adjacencia* aux2Adj = auxAdj;

    while(auxAdj != NULL){  // Remover todas as adjacencias do vertice em questão
        aux2Adj = auxAdj;
        auxAdj = auxAdj->next;
        free(aux2Adj);
    }
    if(aux == aux2){
        inicio= aux->next;
        free(aux);
        *verificar = true;
        return inicio;
    }

    aux2->next = aux->next;
    free (aux);
    *verificar = true;
    return inicio;
 }

 #pragma endregion

 #pragma region Adjacencias

 Adjacencia* CriarAdj (int l, int c, bool* verificar){
    Adjacencia* aux;

    aux=(Adjacencia*)malloc(sizeof(Adjacencia));
    if(aux == NULL){
        *verificar = false;
        return NULL;
    }
    aux->c = c;
    aux->l = l;
    aux->next = NULL;
    *verificar = true;
    return aux;
 }
 
 //ACABAR







 #pragma endregion

 #pragma region Ficheiro

 Antena* CarregarFicheiro(char* Ficheiro, bool* verificar){
    *verificar = false;

    FILE *ficheiro = fopen(Ficheiro, "r");
    if(ficheiro == NULL){
        *verificar = false;
        return NULL;
    }

    Antena* inicio = NULL;
    int c=0;
    int l=0;
    char caracter;
    bool sucesso;
 }

 while ((caracter = fgetc(ficheiro)) != EOF){
    if(caracter >= 'A' && caracter <= 'Z'){
        Antena* nova = CriarAntena(caarcter, l, c, &sucesso);
        inicio = InserirAntena()
    }
 }


 #pragma endregion