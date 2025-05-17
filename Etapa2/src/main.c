/**
 * @file main.c
 * @author Rafael Costa (a31524@alunos.ipca.pt)
 * @brief 
 * @version 1.0
 * @date 2025-05-13
 * 
 * @copyright Copyright (c) 2025
 * 
 */

#include <stdio.h>
#include <stdbool.h>
#include "grafos.h"
#include "ecra.h"

int main(){
    bool verificar;
    Antena* inicio = NULL;
    Antena* head= NULL;
    AntenasVisitadas* visitadas;

    inicio = CarregarFicheiro("matriz.txt", &verificar);
    if(verificar == true){
        printf("Carregado do ficehrio!!\n");
    }else{
        printf("Erro ao carregar do ficherio\n");
    }

    verificar = CalcularAdj(inicio);
    if(verificar == true){
        printf("Adjacencias calculadas com sucesso!\n");
    }else{
        printf("Erro ao calcualr adjacencias\n");
    }

    ImprimirAdjacencias(inicio);

    inicio = RemoverAntena(inicio, 3, 2, &verificar);
    if(verificar == true){
        printf("Removido com sucesso!\n");
    }else{
        printf("Erro ao remover!\n");
    }

    verificar = EliminarAllAdj(inicio);
    if(verificar){
        printf("Todas as adjacencias destruidas!\n");
    }else {
        printf("Erro ao destruir adjacencias!\n");
    }

    verificar = CalcularAdj(inicio);
    if(verificar == true){
        printf("Adjacencias calculadas com sucesso!\n");
    }else{
        printf("Erro ao calcualr adjacencias\n");
    }

    ImprimirAdjacencias(inicio);

    verificar = GuardarFicheiroBin(inicio, "matriz.bin");
    if(verificar){
        printf("Guardado com sucesso!\n");
    }else {
        printf("Erro ao guardar\n");
    }




    head = CarregarFicheiroBin("matriz.bin", &verificar);
     if(verificar){
        printf("Carregado com sucesso!!\n");
    }else {
        printf("Erro ao carregar!\n");
    }

    ImprimirAdjacencias(head);


printf("Travessia através do vertice (3,0)\n");
    visitadas = IniciarTravProfu(inicio, 3,0);
    if(visitadas == NULL){
        printf("Erro!!!");
    }else{
        ImprimirVisitadas(visitadas);
    }

printf("Travessia Completa!\n");
visitadas = NULL;

visitadas = TravessiaCompleta(head);
    if(visitadas == NULL){
        printf("Erro!!!");
    }else{
        ImprimirVisitadas(visitadas);
    }



}