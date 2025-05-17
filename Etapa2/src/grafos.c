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
    aux->visitado = false;
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

 /**
  * @brief Função para remover Antena da lista dos vertices
  * 
  * Verifica se a lista dos vertices não está vazio.
  * Com a ajuda de dois auxiliares, encontra a posição onde está a antena a romver.
  * Elimina todas as adjacencias desse vertice.
  * Por fim remove a Antena.
  * 
  * @param inicio Apontador para a lista dos vertices
  * @param l Linha da Antena a remover
  * @param c Coluna da Antena a remover
  * @param verificar Auxiliar para verificar se executou corretamente
  * @return Antena* Lista dos vertices sem a Antena já.
  */
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

    // Se entrar aqui é porque tem antena e etá na posiçao de aux
    Adjacencia* auxAdj= aux->Adj;  
    Adjacencia* aux2Adj = auxAdj;

    while(auxAdj != NULL){ //Eliminar adjacencias do vertice
        aux2Adj = auxAdj;
        auxAdj = auxAdj->next;
        free(aux2Adj);
    }

    if(aux == aux2){
        inicio= aux->next;   // Eliminar o vertice caso esteja no incio
        free(aux);
        *verificar = true;
        return inicio;
    }

    aux2->next = aux->next;
    free (aux);                //Elinar o vertice 
    *verificar = true;
    return inicio;
 }

 /**
  * @brief Função que romove todos os vertices (Antenas)
  * 
  * A função percorre toda a lista das antenas e invoca a função RemoverAntena, que remove a antena escolhida.
  * 
  * @param inicio Apontador para o inicio da lista dos vértices
  * @return Antena* Apontador para o inicio da lista dos vertices, a NULL, porque removeu todas as antenas
  */
 Antena* RemoveTodasAntenas(Antena* inicio){
    Antena* aux = inicio;
    bool verificar;

    while(inicio != NULL){
        int l = aux->l;
        int c = aux->c;
        inicio = RemoverAntena(inicio, l,c, &verificar);  // devolve o incio da lista sem a Antena
    }
    return NULL;
 }

 #pragma endregion

 #pragma region Adjacencias


/**
 * @brief Cria uma nova adjacencia para uma antena, com base nas coordenadas fornecidas
 * 
 * A função aloca memória para uma noca estrutura do tipo Adjacencia,
 * preenchendo as coordenadas com os dados fornecidos.
 * Os apontadores são inicializados como NULL.
 * 
 * @param l Linha da adjacencia a adicionar
 * @param c Linha da coluna a adicionar
 * @param verificar Auxiliar para verificar se executou corretamente
 * @return Adjacencia* Apontador para a adjacencia criada
 */
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

 /**
  * @brief Função insere a adjacencia no vertice pretendido
  * 
  * Função verifica se o vertice e a adjacencia a inserir são validos.
  * Após verifica se a adjacencia já existe.
  * Por ultimo insere a adjacencia no vertice pretendido.
  * 
  * @param vertice Apontador para o vertice que deseja inserir a adjacencia.
  * @param nova Apontador para a adjacencia que deseja inserir.
  * @return true se adicionar a adjacencia com sucesso
  * @return false se ocorrer algum erro na inserção
  */
bool InsereAdj (Antena* vertice, Adjacencia* nova){
    if (vertice == NULL) return false;
    if(nova == NULL) return false;

    
    Adjacencia* aux = vertice->Adj;                   
    while(aux != NULL){
        if(aux->l == nova->l && aux->c == nova->c)return false;   // verificar se ja existe a adjacencia nesse vertice
        aux = aux->next;
    }

    if(vertice->Adj == NULL){      // Insere a adjacencia no inicio, caso nao haja nenhuma para esse vertice
        vertice->Adj = nova;
    }else{
        aux = vertice->Adj;
        while(aux->next != NULL){  // Caso ja haja adjacencias nesse vertice, percorre-as até ao fm e insere no fim.
            aux = aux->next;
        }
        aux->next = nova;
    }
    return true;
}

/**
 * @brief A função calcula todas as adjacencias
 * 
 * Através de dois ciclos, a função comprara todas as antenas com todas.
 * Caso a frequencia seja igual, e as antenas sejam diferentes, a adjacencia é criada e inserida.
 * 
 * @param inicio Apontador para o inicio da lista das Antenas
 * @return true Caso calcule todas as adjacencias com sucesso
 * @return false Caso haja um erro no calculo das adjacencias
 */
bool CalcularAdj (Antena* inicio){
    bool sucesso;

    for(Antena* aux = inicio ; aux != NULL ; aux = aux->next){            
        for(Antena* aux2 = inicio ; aux2 != NULL ; aux2 = aux2->next){   // Comparar todas as atenas com todas(começando sempre o aux2 do inicio)
            if(aux->frequencia == aux2->frequencia){      //Quando a frequencia for igual
                if(aux != aux2){                          // e nao forem a mesma antena  
                    Adjacencia* nova = CriarAdj(aux2->l, aux2->c, &sucesso);
                    if(sucesso == false)return false;
                    sucesso = InsereAdj(aux, nova);
                    if(sucesso == false)return false;
                }
            }
        }
    }
    return true;
}

/**
 * @brief Função elimina todas as Adjacencias
 * 
 * A função percorre todos os vertices e para cada vertice elimina todas as suas adjacencias.
 * 
 * @param inicio Apontador para o inicio da lista das Antenas
 * @return true Caso Remova todas com sucesso
 * @return false Caso haja algum erro a devolver
 */
bool EliminarAllAdj (Antena* inicio){
    for(Antena* vertice = inicio; vertice != NULL ; vertice = vertice->next){
        Adjacencia* aux = vertice->Adj;
        Adjacencia* aux2 = aux;

        while(aux != NULL){
            aux2=aux;
            aux=aux->next;
            free(aux2);
        }
        vertice->Adj = NULL;
    }
    return true;
}


 #pragma endregion

 #pragma region Ficheiro

 /**
  * @brief Carrega de um ficheiro.txt todos os vertices do grafo.
  * 
  * A função lê um ficheiro caracter a caracter, onde tiver uma letra, a mesma é inserida na lista das Antenas
  * com a respetiva coordenada, linha e coluna.
  * 
  * @param Ficheiro Ficheiro.txt que contem a matriz
  * @param verificar Auxiliar para verificar se executou corretamente
  * @return Antena* Apontador para o inicio da lista das Antenas
  */
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

 while ((caracter = fgetc(ficheiro)) != EOF){
    if(caracter >= 'A' && caracter <= 'Z'){
        Antena* nova = CriarAntena(caracter, l, c, &sucesso);
        if(sucesso == false){
            fclose(ficheiro);
            return NULL;
        }
        
        inicio = InserirAntena(inicio, nova, &sucesso);
         if(sucesso == false){
            fclose(ficheiro);
            return NULL;
        }

        c++;
    }else if( caracter == '.'){
        c++;
    }else if(caracter == '\n'){
        c=0;
        l++;
    }
  }
  fclose(ficheiro);
  *verificar= true;
  return inicio;
 }



 /**
  * @brief Guarda o grafo de antenas num ficheiro binário.
  * 
  * Esta função percorre a lista ligada de antenas e escreve, em formato binário, todos os vértices (antenas)
  * e suas respetivas adjacências num ficheiro especificado. Cada antena é identificada pelas suas coordenadas
  * (linha e coluna) e pela sua frequência (caracter). Para cada antena, também são guardadas as coordenadas
  * das antenas adjacentes.
  *
  * O formato do ficheiro binário é o seguinte:
  * - int: número total de antenas (vértices)
  * Para cada antena:
  *   - int: linha
  *   - int: coluna
  *   - char: frequência
  *   - int: número de adjacências
  *   - Para cada adjacência:
  *       - int: linha da antena adjacente
  *       - int: coluna da antena adjacente
  * 
  * @param inicio  Ponteiro para o início da lista de antenas.
  * @param NomeFicheiro Ficheiro binario onde será guardado
  * @return true se o ficheiro foi guardado com sucesso
  * @return false se ocorreu erro
  */
bool GuardarFicheiroBin (Antena* inicio, char* NomeFicheiro){
    FILE* ficheiro = fopen(NomeFicheiro, "wb");
    if(ficheiro == NULL)return false;

    int totalvertices=0;

    for(Antena* aux= inicio ; aux != NULL ; aux = aux->next){
        totalvertices ++;
    }

    fwrite(&totalvertices, sizeof(int), 1, ficheiro);

    for(Antena* aux = inicio ; aux != NULL ; aux = aux->next){
        fwrite(&(aux->l), sizeof(int), 1, ficheiro);
        fwrite(&(aux->c), sizeof(int), 1, ficheiro);
        fwrite(&(aux->frequencia), sizeof(char), 1, ficheiro);

        int totalAdj=0;

        for(Adjacencia* adj = aux->Adj; adj != NULL ; adj = adj->next){
            totalAdj ++;
        }

        fwrite(&totalAdj, sizeof(int), 1, ficheiro);

        for(Adjacencia* adj = aux->Adj ; adj != NULL ; adj = adj->next){
            fwrite(&(adj->l), sizeof(int), 1, ficheiro);
            fwrite(&(adj->c), sizeof(int), 1, ficheiro);
        }
    }

    fclose(ficheiro);
    return true;
}


/**
 * @brief Carrega um grafo de antenas a partir de um ficheiro binário.
 * 
 * O ficheiro deve conter a seguinte estrutura binária:
 * - int: número total de antenas (vértices)
 * Para cada antena:
 *   - int: linha (l)
 *   - int: coluna (c)
 *   - char: frequência
 *   - int: número de adjacências
 *   - Para cada adjacência:
 *       - int: linha da antena adjacente
 *       - int: coluna da antena adjacente
 *
 * @param NomeFicheiro Ficheiro binario onde será guardado
 * @param verificar Auxiliar para verificar se executou corretamente
 * @return Antena* Apontador para o inicio da lista dos vertices
 */
Antena* CarregarFicheiroBin (char* NomeFicheiro, bool* verificar){
    *verificar = false;
    FILE* ficheiro = fopen(NomeFicheiro, "rb");
    if(ficheiro == NULL)return NULL;

    Antena* inicio = NULL;
    bool sucesso;
    int totalvertices=0;
    int totalAdj=0;
    char frequencia;
    int l, c;
    int adjL, adjC;

    fread(&totalvertices, sizeof(int), 1, ficheiro);

    for(int i=0 ; i<totalvertices; i++){
        fread(&l, sizeof(int), 1, ficheiro);
        fread(&c, sizeof(int), 1, ficheiro);
        fread(&frequencia, sizeof(char), 1, ficheiro);

        Antena* novoVert = CriarAntena(frequencia, l,c,&sucesso);
        if(sucesso == false){
            fclose(ficheiro);
            return NULL;
        }
        inicio = InserirAntena(inicio, novoVert, &sucesso);
        if(sucesso == false){
            fclose(ficheiro);
            return NULL;
        }
             
        fread(&totalAdj, sizeof(int), 1, ficheiro);

        for(int j=0 ; j<totalAdj ; j++){
            fread(&adjL, sizeof(int), 1, ficheiro);
            fread(&adjC, sizeof(int), 1, ficheiro);
            Adjacencia* novaAdj = CriarAdj(adjL, adjC, &sucesso);
            if(sucesso == false){
            fclose(ficheiro);
            return NULL;
        }
            sucesso = InsereAdj(novoVert, novaAdj);  
            if(sucesso == false){
            fclose(ficheiro);
            return NULL;
        }      
        }

    }
    fclose(ficheiro);
    *verificar = true;
    return inicio;
}



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
AntenasVisitadas* CriarVisitado (int l, int c, bool* verificar){
    *verificar=false;
    AntenasVisitadas* nova;

    nova =(AntenasVisitadas*)malloc(sizeof(AntenasVisitadas));
    if(nova == NULL)return NULL;

    nova->l = l;
    nova->c = c;
    nova->next = NULL;
    *verificar = true;
    return nova;
}

/**
 * @brief Insere uma AntenaVisitada na lista de Antenas Visitadas
 * 
 * @param inicio Apontador para o inicio da lista das antenas visitadas
 * @param nova Apontador para a antena visitada a inserir
 * @param verificar Auxiliar para verificar se executou corretamente
 * @return AntenasVisitadas* Apontador para a inicio da lista das Antenas Visitadas
 */
AntenasVisitadas* InserirVisitadas(AntenasVisitadas* inicio, AntenasVisitadas* nova, bool* verificar){
    *verificar = false;

    if(nova == NULL)return inicio;
    if(inicio == NULL){
        *verificar = true;
        return nova;  // nova passa a ser o 1º elemento de inicio
    }

    AntenasVisitadas* aux = inicio;

    while(aux->next != NULL){
        aux = aux->next;
    }

    aux->next = nova;
    *verificar = true;
    return inicio;
    
}

/**
 * @brief Função para limpar o parametro visitado das Antenas
 * 
 * @param inicio Apontador para o inicio da lista das Antenas
 * @return true Caso troque todos os parametros para false
 * @return false caso aconteça algum erro
 */
bool LimparVisitado (Antena* inicio){
    Antena* aux = inicio;

    while(aux != NULL){
        aux->visitado=false;
        aux = aux->next;
    }
    return true;
 }
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
 AntenasVisitadas* IniciarTravProfu(Antena* inicio, int l, int c){
    bool sucesso;
    sucesso = LimparVisitado(inicio);
    if(sucesso == false)return NULL;

    AntenasVisitadas* visitadas = NULL;

    for(Antena* aux = inicio ; aux != NULL ; aux = aux->next){
        if(aux->l == l && aux->c == c){
            visitadas = TravProfu(aux, inicio, visitadas);
            return visitadas;
        }
    }
    return NULL;
 }

/**
 * @brief Travessia do grafo em profundidade
 * 
 * Esta função percorre recursivamente as antenas adjacentes ainda não visitadas,
 * marcando cada antena como visitada e adicionando-a a uma lista ligada de visitadas.
 * 
 * @param vertice Apontador para um vertice
 * @param inicio Apontador para a lista das Antenas
 * @param visitadas Apontador para a lista das Antenas Visitadas
 * @return AntenasVisitadas* Apontador para uma lista que contem todas as Antenas Visitadas
 */
 AntenasVisitadas* TravProfu (Antena* vertice,Antena* inicio, AntenasVisitadas* visitadas){
    bool sucesso = false;
    if(vertice == NULL || vertice->visitado == true)return visitadas;

    vertice->visitado = true;

    AntenasVisitadas* nova=CriarVisitado(vertice->l, vertice->c, &sucesso);
    if(sucesso == true){
        visitadas = InserirVisitadas(visitadas, nova, &sucesso);
    }

    for(Adjacencia* adj = vertice->Adj ; adj != NULL ; adj = adj->next){
        for(Antena* aux = inicio ; aux != NULL ; aux = aux->next){
            if(aux->l == adj->l && aux->c == adj->c && aux->visitado ==false){
                visitadas = TravProfu(aux,inicio, visitadas);
            }
        }
    }
    return visitadas;
    
 }
 
/**
 * @brief Função que realiza a travessia completa
 * 
 * @param inicio Apontador para o inicio da lista das Antenas
 * @return AntenasVisitadas* Apontador para o inicio da listas das Antenas Visitadas
 */
 AntenasVisitadas* TravessiaCompleta(Antena* inicio){
    bool sucesso = LimparVisitado(inicio);
    if (!sucesso) return NULL;

    AntenasVisitadas* visitadas = NULL;

    for (Antena* aux = inicio; aux != NULL; aux = aux->next) {
        if (!aux->visitado) {
            visitadas = TravProfu(aux, inicio, visitadas);
        }
    }

    return visitadas;
}


#pragma endregion 
