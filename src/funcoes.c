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
 * @param verificar Auxiliar para verificar se executou corretamente
 * @return Antena* Antena Criada
 */
Antena* CriarAntena(int l, int c, char frequencia, bool* verificar){
    Antena* aux;

    aux = (Antena*)malloc(sizeof(Antena));
    if(aux != NULL){
        aux->l = l;
        aux->c = c;
        aux->frequencia= frequencia;
        aux->next= NULL;
        *verificar = true;
    }else {
        *verificar = false;
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
 * @param verificar Auxiliar para verificar se executou corretamente
 * @return Antena* Apontador para o início da lista das Antenas já atualizada
 */
Antena* InserirAntena(Antena* inicio, Antena* nova, Dimensao* matriz, bool* verificar){
    if(inicio == NULL){
        *verificar = false;
        return nova;
    }
    if(nova == NULL){
        *verificar = false;
        return inicio;
    } 

    if(nova->l >= matriz->l){
        matriz->l = nova->l +1;
    }

    if(nova->c >= matriz->c){
        matriz->c = nova->c +1;
    }

    Antena* aux=inicio;
    Antena* aux2=aux;

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
    
    aux2->next = nova;  // Caso não esteja no início nem no fim
    nova->next = aux;
    *verificar = true;
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
 * @param verificar Auxiliar para verificar se executou corretamente
 * @return Antena* Apontador para o início da lista já atualizada
 */
Antena* RemoverAntena(Antena* inicio, int l, int c, bool* verificar){
    if(inicio == NULL){
        *verificar = false;
        return inicio;
    }

    Antena* aux = inicio;
    Antena* aux2 = aux;

    if(inicio->l == l && inicio->c == c){     
        inicio= inicio->next;
        free(aux);
        *verificar = true;
        return inicio;
    }

    while(aux != NULL && (aux->l != l || aux->c != c)){ 
        aux2=aux;
        aux=aux->next;
    }

    if(aux == NULL){
        *verificar = false;
        return inicio;
    } 
    
    aux2->next = aux->next;
    free(aux);
    *verificar = true;
    return inicio;
}

/**
 * @brief Remove todas as Antenas que estejam a coincidir com a localização de um efeito 
 * 
 * @param inicio Apontador para o inicio da lista das Antenas
 * @param head Apontador para o inicio da lista dos Efeitos
 * @param verificar Auxiliar para verificar se executou corretamente
 * @return Antena* Apontador para o inicio da lista das Antenas já atualizada
 */
Antena* RemoverAllAntenaComEfeito (Antena* inicio, Efeito* head, bool* verificar){
    Efeito* aux = head;
    bool sucesso;
    *verificar = false;

    while(aux != NULL){
        inicio = RemoverAntena(inicio, aux->l, aux->c, &sucesso);  
        if(sucesso){
            *verificar = true;
        }  
            aux = aux->next;
        
    }
    return inicio;

}

/**
 * @brief Destroi toda a lista das Antenas
 * 
 * @param inicio Apontador para o inicio da lista das Antenas
 * @param verificar Auxiliar para verificar se executou corretamente
 * @return Antena* Apontador para o inicio da lista das Antenas mas já destruída
 */
Antena* DestroiListaAnt(Antena* inicio, Dimensao* matriz, bool* verificar){
    if(inicio == NULL){
        *verificar = false;
        return inicio;
    }
    if(matriz != NULL){
        matriz->c = 0;
        matriz->l = 0;
    }

    Antena* aux;
    while(inicio != NULL){
        aux = inicio;
        inicio = inicio->next;
        free(aux);
    }
    *verificar = true;
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
 * @param verificar Auxiliar para verificar se executou corretamente
 * @return Efeito* Ponteiro para o inicio da lista dos Efeitos
 */
Efeito* CriarEfeito(int l, int c, bool* verificar){
    Efeito* aux;
    
    aux=(Efeito*)malloc(sizeof(Efeito));
    if(aux != NULL){
        aux->l = l;
        aux->c = c;
        aux->next = NULL;
        *verificar = true;
    }else{
        *verificar = false;
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
 * @param verificar Auxiliar para verificar se executou corretamente
 * @return Efeito* Apontador para o início da lista já atualizada
 */
Efeito* InserirEfeito(Efeito* head, Efeito* novo, Dimensao* matriz, bool* verificar){
    if(head == NULL){
        *verificar = false;
        return novo;
    }
    if(novo == NULL){
        *verificar = false;
        return head;
    }
    if(novo->l <0 || novo->c < 0){
        *verificar = false;
        return head; // Garante que os Efeitos não tenham valores negativos
    }

    if(novo->l >= matriz->l){
        matriz->l = novo->l +1;
    }

    if(novo->c >= matriz->c){
        matriz->c = novo->c +1;
    }

    Efeito* aux= head;
    Efeito* aux2= aux;

    while((aux->next != NULL) && (aux->l < novo->l || (aux->l == novo->l && aux->c < novo->c))){
        aux2 = aux;
        aux = aux->next;
    }

    if(aux == aux2){
        novo->next = head;
        head=novo;
        *verificar = true;
        return head;
    }

    if(aux->next == NULL){
        aux->next = novo;
        *verificar = true;
        return head;
    }

    aux2->next = novo;
    novo->next = aux;
    *verificar = true;
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
 * @param verificar Auxiliar para verificar se executou corretamente
 * @return * Efeito* Apontador para o início da lista ligada dos Efeitos já atualizada. 
 */
Efeito* DescubrirEfeito(Antena* inicio, Dimensao* matriz, bool* verificar){

    Efeito* head = NULL;
    Efeito* efeito1;
    Efeito* efeito2;
    bool sucesso;
    *verificar = false;

    for(Antena* aux = inicio; aux != NULL; aux = aux->next){
        for(Antena* aux2 = aux->next; aux2 != NULL ; aux2 = aux2->next){
            if(aux->frequencia == aux2->frequencia){
                int difColuna = aux2->c - aux->c;
                int difLinha = aux2->l - aux->l;
                

                if((abs(difColuna) == 2 || abs(difColuna) == 1) && difLinha == 0){ // Caso estejam na mesma linha
                    efeito1 = CriarEfeito(aux->l, aux->c - difColuna, &sucesso); 
                    head = InserirEfeito(head, efeito1, matriz, &sucesso);                                        
                    efeito2 = CriarEfeito(aux2->l, aux2->c + difColuna, &sucesso);
                    head = InserirEfeito(head, efeito2, matriz,&sucesso);
                    *verificar = true;
                }

                if((abs(difLinha) == 2 || abs(difLinha) == 1) && difColuna == 0){ // Caso estejam na mesma coluna
                    efeito1 = CriarEfeito(aux->l - difLinha, aux->c, &sucesso);                        
                    head = InserirEfeito(head, efeito1, matriz, &sucesso );
                    efeito2 = CriarEfeito(aux2->l + difLinha, aux2->c, &sucesso);
                    head = InserirEfeito(head, efeito2, matriz, &sucesso);
                    *verificar = true;
                }
                if((abs(difColuna) == 2 || abs(difColuna) == 1 ) && (abs(difLinha) == 2 || abs(difLinha) == 1)){ // Caso estejam na Vertical
                    efeito1 = CriarEfeito(aux->l -difLinha, aux->c - difColuna, &sucesso); 
                    head = InserirEfeito(head, efeito1, matriz, &sucesso);
                    efeito2 = CriarEfeito(aux2->l + difLinha, aux2->c + difColuna, &sucesso);
                    head= InserirEfeito(head, efeito2, matriz, &sucesso);
                    *verificar = true;
                }
            }
        }
    }
    return head;

}


/**
 * @brief Função para destruir a Lista dos Efeitos
 * 
 * @param head Apontador para o início da lista dos Efeitos
 * @param verificar Auxiliar para verificar se executou corretamente
 * @return Efeito* Apontador para o início da lista dos Efeitos mas já vazia
 */
Efeito* DestroiListaEfei(Efeito* head, bool* verificar){
    Efeito* aux;
    *verificar = false;
    while(head != NULL){
        aux = head;
        head = head->next;
        free(aux);
        *verificar = true;
    }
    return head;

}

#pragma endregion


#pragma region Ficheiros

/**
 * @brief Função para ler de um ficeheiro externo '.txt' a matriz que contém as Antenas.
 * 
 * A função lê caracter a caracter do ficheiro, se contiver uma letra, cria uma nova Antena e insere-a na lista com a sua localização da matriz.
 * 
 * @param Ficheiro Ficheiro que contém a matriz
 * @param verificar Auxiliar para verificar se executou corretamente
 * @return Antena* Apontador para o início da lista já atualizada
 */
Antena* CarregarDoFicheiro(char* Ficheiro, Dimensao* matriz, bool* verificar){
    bool sucesso;
    FILE* ficheiro=fopen(Ficheiro, "r");
    if(ficheiro == NULL){
        *verificar = false;
        return NULL;
    }

    Antena* inicio = NULL;
    int l=0;
    int c=0; 
    int max_colunas=0;                                       
    char caracter;

    while((caracter = fgetc(ficheiro)) != EOF){
        if (caracter >= 'A' && caracter <= 'Z'){
            Antena* nova = CriarAntena(l, c, caracter, &sucesso); 
            inicio= InserirAntena(inicio, nova, matriz, &sucesso);
            c++;
        }
        else if(caracter== '.'){
            c++;
        }

        else if(caracter=='\n'){
            if(c > max_colunas){
                max_colunas = c; 
            }

            l++;
            c=0;
        }
    }

    matriz->c = max_colunas;
    matriz->l = l;

    fclose(ficheiro);
    *verificar = true;
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
Antena* LerAntenasBin (char* Ficheiro, Dimensao* matriz, bool * verificar){
    bool sucesso;
    FILE* ficheiro = fopen(Ficheiro, "rb");
    if(ficheiro == NULL){
        *verificar = false;
        return NULL;
    }

    AntenaFicheiro antenaFich;
    Antena* aux;
    Antena* inicio = NULL;

    while(fread(&antenaFich, sizeof(antenaFich), 1, ficheiro)){
        aux = CriarAntena(antenaFich.l, antenaFich.c, antenaFich.frequencia,&sucesso);
        inicio = InserirAntena(inicio, aux, matriz,&sucesso);
    }
    fclose(ficheiro);
    *verificar = true;
    return inicio;
}
#pragma endregion

