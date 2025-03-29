/**
 * @file funcoes.c
 * @author Rafael Costa (a31524@alunos.ipca.pt)
 * @brief Implementação das funções
 * @version 1.0
 * @date 2025-03-18
 * 
 * @copyright Copyright (c) 2025
 * 
 */
#include <stdio.h>
#include "funcoes.h"
#include <malloc.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

#pragma region Antenas

/**
 * @brief Função para criar uma nova antenas
 * 
 * Esta função aloca memória para uma nova estrutura "Antena" e retorna um ponteiro para a antena criada.
 * Caso a alocação de memória falhe, retorna 'NULL'.
 * 
 * @param l Linha onde queremos adicionar a Antena
 * @param c Coluna onde queremos adicionar a Antena
 * @param frequencia Frequencia que a Antena irá ter
 * @return Antena* Antena Criada
 */
Antena* CriarAntena(int l, int c, char frequencia){
    Antena* aux;

    aux = (Antena*)malloc(sizeof(Antena));
    if(aux != NULL){
        aux->l = l;
        aux->c = c;
        aux->frequencia= frequencia;
        aux->next= NULL;
    }
    return aux; 
}

/**
 * @brief Insere uma nova antena na lista das Antenas de forma ordenada
 * 
 * A função percorre a lista ligada das antenas e insere uma nova antena na posição correta.
 * Se a lista estiver vazia, a nova Antena torna-se o início da lista.
 * Se não houver nada a inserir o início da lista mantém-se.
 * 
 * A função percorre a lista com ajuda de dois auxiliares á procura da localização correta para a nova Antena.
 * Se os dois auxilires forem iguais, significa que o loop não avançou logo temos de inserir no início. 
 * Se o auxiliar da frente apontar para NULL e e a linha de nova for maior que a linha do auxiliar, ou se forem iguias mas a coluna de nova for maior, adicionamos no fim
 * Caso não seja para adinionar no início nem no fim, adicionamos no meio na localização certa. 
 * 
 * 
 * @param inicio Apontador para o Inicio da lista ligada das Antenas
 * @param nova Apontador para a nova Antena a adicionar
 * @return Antena* Apontador para o início da lista das Antenas já atualizada
 */
Antena* InserirAntena(Antena* inicio, Antena* nova){
    if(inicio == NULL) return nova; 
    if(nova == NULL) return inicio; 

    Antena* aux=inicio;
    Antena* aux2=aux;

    while((aux->next != NULL) && (aux->l < nova->l || (aux->l == nova->l && aux->c < nova->c))){ 
        aux2=aux;
        aux=aux->next;
    }
    
    if(aux == aux2){  // Caso esteja no início
        nova->next = inicio;
        inicio = nova;
        return inicio;
    }

    if(aux->next == NULL && (aux->l < nova->l || (aux->l == nova->l && aux->c < nova->c))){ // Caso esteja no fim           
        aux->next = nova;
        return inicio;
    }
    
    aux2->next = nova;  // Caso não esteja no início nem no fim
    nova->next = aux;
    return inicio;
}

/**
 * @brief Função para remover uma Antena
 * 
 * A função percorre a lista ligada com a ajuda de dois auxiliares á procura da posição correta da Antena a remover.
 * Caso o a eliminar esteja no início, avança o inicio da lista e liberta a primeira posição.
 * Caso esteja no meio ou no fim, coloca a casa do anterior a apontar para a casa seguinte do a eliminar.
 * 
 * @param inicio Apontador para o início da lista
 * @param l Linha onde se encontra a antena a remover
 * @param c Coluna onde se encontra a antena a remover
 * @return Antena* Apontador para o início da lista já atualizada
 */
Antena* RemoverAntena(Antena* inicio, int l, int c){
    if(inicio == NULL) return inicio;

    Antena* aux = inicio;
    Antena* aux2 = aux;

    if(inicio->l == l && inicio->c == c){     
        inicio= inicio->next;
        free(aux);
        return inicio;
    }

    while(aux != NULL && (aux->l != l || aux->c != c)){ 
        aux2=aux;
        aux=aux->next;
    }

    if(aux == NULL)return inicio;  
    
    aux2->next = aux->next;
    free(aux);

    return inicio;
}

/**
 * @brief Remove todas as Antenas que estejam a coincidir com a localização de um efeito 
 * 
 * @param inicio Apontador para o inicio da lista das Antenas
 * @param head Apontador para o inicio da lista dos Efeitos
 * @return Antena* Apontador para o inicio da lista das Antenas já atualizada
 */
Antena* RemoverAllAntenaComEfeito (Antena* inicio, Efeito* head){
    Efeito* aux = head;

    while(aux != NULL){
        inicio = RemoverAntena(inicio, aux->l, aux->c);
        aux = aux->next;
    }
    return inicio;

}

/**
 * @brief Destroi toda a lista das Antenas
 * 
 * @param inicio Apontador para o inicio da lista das Antenas
 * @return Antena* Apontador para o inicio da lista das Antenas mas já destruída
 */
Antena* DestroiLista(Antena* inicio){
    if(inicio == NULL)return inicio;

    Antena* aux;
    while(inicio != NULL){
        aux = inicio;
        inicio = inicio->next;
        free(aux);
    }
    return inicio;
}

#pragma endregion

#pragma region Efeitos

/**
 * @brief Função para criar um efeito novo
 * 
 * Esta função aloca memória para uma nova estrutura "Efeito" e retorna um ponteiro para a efeito criada.
 * Caso a alocação de memória falhe, retorna 'NULL'.
 * 
 * @param l Linha onde queremos adicionar o Efeito
 * @param c Coluna onde queremos adicionar o Efeito
 * @return Efeito* Ponteiro para o inicio da lista dos Efeitos
 */
Efeito* CriarEfeito(int l, int c){
    Efeito* aux;
    
    aux=(Efeito*)malloc(sizeof(Efeito));
    if(aux != NULL){
        aux->l = l;
        aux->c = c;
        aux->next = NULL;
    }
    return aux;
}


/**
 * @brief A fução tem como objetivo inserir o novo Efeito na lista de forma ordenada pela sua coluna "c" e linha "l"
 * 
 * A função percorre a lista ligada daos Efeitos e insere o novo Efeito na posição correta.
 * Se a lista estiver vazia, o novo Efeito torna-se o início da lista.
 * Se não houver nada a inserir o início da lista mantém-se.
 * Se os valores a inserir forem negativos, retoma o inicio da lista sem inserir. 
 * 
 * A função percorre a lista com ajuda de dois auxiliares á procura da localização correta para o novo Efeito.
 * Se os dois auxilires forem iguais, significa que o loop não avançou logo temos de inserir no início. 
 * Se o auxiliar da frente apontar para NULL e a linha do novo for maior que a linha do auxiliar, ou se forem iguias mas a coluna do novo for maior, adicionamos no fim. 
 * Caso não seja para adinionar no início nem no fim, adicionamos no meio na localização certa. 
 * 
 * 
 * @param head Apontador para o Inicio da lista ligada
 * @param novo Apontador para o novo Efeito a adicionar
 * @return Efeito* Apontador para o início da lista já atualizada
 */
Efeito* InserirEfeito(Efeito* head, Efeito* novo){
    if(head == NULL)return novo;
    if(novo == NULL)return head;
    if(novo->l <0 || novo->c < 0)return head; // Garante que os Efeitos não tenham valores negativos

    Efeito* aux= head;
    Efeito* aux2= aux;

    while((aux->next != NULL) && (aux->l < novo->l || (aux->l == novo->l && aux->c < novo->c))){
        aux2 = aux;
        aux = aux->next;
    }

    if(aux == aux2){
        novo->next = head;
        head=novo;
        return head;
    }

    if(aux->next == NULL){
        aux->next = novo;
        return head;
    }

    aux2->next = novo;
    novo->next = aux;
    return head;

}

/**
 * @brief Função para descubrir a localização dos Efeitos
 * 
 * Com a ajuda de dois auxiliares, vamos comparar todas as Antenas umas com as outras. Se a frequência de duas antenas for igual, temos de verificar a distância entre eles. 
 * Caso a distancia seja menor ou igual a 2, existe 3 possibilidades: 1. Estarem na mesma linha  2. Estarem na mesma coluna  3. Estarem na Diagonal
 * 1. Caso estejam na mesma linha, o efeito nefasto vai estar nessa linha em 2 localizações, para a frente da última Antena e para trás da primeira. A distância entre as Antenas e os Efeitos é igual á distâncai entre as Antenas. 
 * 2. Caso estejam na mesma coluna, o procedimento é o mesmo, no entanto o efeito vai estar para cima da primeira Antena e para baixo da ultimo.
 * 3. Caso esteja na Diagonal, o efeito nefasto da antenas de cima irá estar na diagonal para cima, ou seja temos de subtrair á coordenada da Antena a diferença entre as linhas e entre as Colunas. 
 *    Para a Antena mais a baixo, o procedimento é similar, no entanto temos de adicionar as diferenças envés de subtrair.  
 * 
 * @param inicio Apontador para o início da lista ligada das Antenas. 
 * @param head Apontador para o início da lista ligada dos Efeitos. 
 * @return * Efeito* Apontador para o início da lista ligada dos Efeitos já atualizada. 
 */
Efeito* DescubrirEfeito(Antena* inicio){

    Efeito* head = NULL;
    Efeito* efeito1;
    Efeito* efeito2;
    
    for(Antena* aux = inicio; aux != NULL; aux = aux->next){

        for(Antena* aux2 = aux->next; aux2 != NULL ; aux2 = aux2->next){
            if(aux->frequencia == aux2->frequencia){
                int difColuna = aux2->c - aux->c;
                int difLinha = aux2->l - aux->l;

                if((abs(difColuna) == 2 || abs(difColuna) == 1) && difLinha == 0){ // Caso estejam na mesma linha
                    efeito1 = CriarEfeito(aux->l, aux->c - difColuna); 
                    head = InserirEfeito(head, efeito1);                                        
                    efeito2 = CriarEfeito(aux2->l, aux2->c + difColuna);
                    head = InserirEfeito(head, efeito2);
                }

                if((abs(difLinha) == 2 || abs(difLinha) == 1) && difColuna == 0){ // Caso estejam na mesma coluna
                    efeito1 = CriarEfeito(aux->l - difLinha, aux->c);                        
                    head = InserirEfeito(head, efeito1);
                    efeito2 = CriarEfeito(aux2->l + difLinha, aux2->c);
                    head = InserirEfeito(head, efeito2);
                }
                if((abs(difColuna) == 2 || abs(difColuna) == 1 ) && (abs(difLinha) == 2 || abs(difLinha) == 1)){ // Caso estejam na Vertical
                    efeito1 = CriarEfeito(aux->l -difLinha, aux->c - difColuna); 
                    head = InserirEfeito(head, efeito1);
                    efeito2 = CriarEfeito(aux2->l + difLinha, aux2->c + difColuna);
                    head= InserirEfeito(head, efeito2);
                }
            }
        }
    }
    return head;

}

#pragma endregion

#pragma region Listar Na Tela

/**
 * @brief Função para apresentar na tela as Antenas de forma tabular
 * 
 * A função percorre a lista todas e imprime na telas as coordenadas onde têm Antenas.
 * 
 * @param inicio Apontador para o início da lista ligada das Antenas
 */
void ListarAntenas (Antena* inicio) {
    Antena* aux;
    printf("Lista das Antenas:\n");
    printf("Linha | Coluna | Frequencia\n");
    for(aux=inicio ; aux != NULL ; aux= aux->next){
        printf("| %d   |  %d     | %c \n", aux->l, aux->c, aux->frequencia);
    }
}

/**
 * @brief Função para apresentar na tela Efeitos de forma tabular
 * 
 * A função percorre a lista todas e imprime na telas as coordenadas onde têm os Efeitos.
 * 
 * @param head Apontador para o início da lista ligada dos Efeitos
 */
void ListarEfeitos(Efeito* head) {
    Efeito* aux;
    printf("Lista dos Efeitos:\n");
    printf("Linha | Coluna \n");
    for(aux=head ; aux != NULL ; aux= aux->next){
        printf("| %d   |  %d  |\n", aux->l, aux->c);
    }
}

#pragma endregion

#pragma region Ficheiros

/**
 * @brief Função para ler de um ficeheiro externo '.txt' a matriz que contém as Antenas.
 * 
 * A função lê caracter a caracter do ficheiro, se contiver uma letra, cria uma nova Antena e insere-a na lista com a sua localização da matriz.
 * 
 * @param Ficheiro Ficheiro que contém a matriz
 * @return Antena* Apontador para o início da lista já atualizada
 */
Antena* CarregarDoFicheiro(char* Ficheiro){
    FILE* ficheiro=fopen(Ficheiro, "r");
    if(ficheiro == NULL){
        return NULL;
    }

    Antena* inicio = NULL;
    int l=0;
    int c=0;                                        
    char caracter;

    while((caracter = fgetc(ficheiro)) != EOF){
        if (caracter >= 'A' && caracter <= 'Z'){
            Antena* nova = CriarAntena(l, c, caracter);  // MUDAR DOCUMENTAÇÃO
            inicio= InserirAntena(inicio, nova);
            c++;
        }
        else if(caracter== '.'){
            c++;
        }

        else if(caracter=='\n'){
            l++;
            c=0;
        }
    }

    fclose(ficheiro);
    return inicio;
}

/**
 * @brief Função para guardar as Antenas num ficheiro binário
 * 
 * @param inicio Apontador para o início da lista das Antenas
 * @param Ficheiro Ficheiro onde vamos guardar a informação
 */
bool GuardarAntenasBin(Antena* inicio, char* Ficheiro){ 
    FILE* ficheiro = fopen(Ficheiro, "wb");
    if(ficheiro == NULL){
        return false;
    }

    Antena* aux= inicio;
    AntenaFicheiro antenaFich;

    while(aux != NULL){
        antenaFich.l = aux->l;
        antenaFich.c = aux->c;
        antenaFich.frequencia = aux->frequencia;
        fwrite(&antenaFich, 1, sizeof(antenaFich), ficheiro);
        aux = aux->next;
    }

    fclose(ficheiro);
    return true;
}

/**
 * @brief Ficheiro para ler as Antenas através de um ficheiro binário
 * 
 * @param Ficheiro Ficheiro Binário que contém as Antenas
 * @return Antena* Apontador para o início da lista ligadas das Antenas
 */
Antena* LerAntenasBin (char* Ficheiro){
    FILE* ficheiro = fopen(Ficheiro, "rb");
    if(ficheiro == NULL)return NULL;

    AntenaFicheiro antenaFich;
    Antena* aux;
    Antena* inicio = NULL;

    while(fread(&antenaFich, sizeof(antenaFich), 1, ficheiro)){
        aux = CriarAntena(antenaFich.l, antenaFich.c, antenaFich.frequencia);
        inicio = InserirAntena(inicio, aux);
    }
    fclose(ficheiro);
    return inicio;
}
#pragma endregion

