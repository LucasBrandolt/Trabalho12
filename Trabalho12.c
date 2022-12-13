#include <stdio.h>
#include <stdlib.h>
#include "heap.h"

//Função de criação da HEAP
HEAP* HEAP_create(int n, COMP* compara){
    HEAP* heap = malloc(sizeof(HEAP));              //Faz a alocação de memoria necessaria para o vetor
    heap->comparador = compara;                     //Define o comparador
    heap->N = n;                                    //Define o N
    heap->P = 0;                                    //Define o P
    heap->elems = malloc(n * sizeof(void *));       //Aloca memoria para o vetor
    for(int i = 0;i<n;i++){
        heap->elems[i] = NULL;                      //Define todos as posições como NULL
    }
    return heap;                                    //retorna o ponteiro heap
}

//Função de adicionar na HEAP
void HEAP_add(HEAP* vetor, void* newelem){
    if(vetor->P < vetor->N){                          //faz a verificação para saber se tem espaço no vetor
        if(vetor->P == 0){                            //Testa se o vetor esta vazio
            vetor->elems[0] = newelem;                //adiciona um novo elemento no vetor
            vetor->P++;                               //Adiciona mais um no valor de P
        }
        else{
            vetor->elems[vetor->P] = newelem;                                       //Adiciona o novo elemento na variavel P da estrutura vetor
            vetor->P++;                                                             //Adiciona mais um em P
            for(int i=vetor->P-1;i>0;i--){                                          //Serve para caminhar pelos elementos do vetor de traz para frente
                if(vetor->comparador(vetor->elems[i], vetor->elems[i/2]) == 1){     //Faz a verificação se o elemento é maior que seu pai
                    void* aux = vetor->elems[i];                                    //As proxims linhas servem para fazer a troca de posição entre pai e filho
                    vetor->elems[i] = vetor->elems[i/2];
                    vetor->elems[i/2] = aux;
                }
            }
        }
    }
}

//Função de remoção na HEAP
void* HEAP_remove(HEAP* vetor){
    void* aux = vetor->elems[0];                                            //Armazena o primeiro elemento da heap no aux
    for(int i = 0;i<vetor->P;i++){                                          //O for faz o deslocamento de todos os elementos para a esquerda
        vetor->elems[i] = vetor->elems[i+1]; 
    }
    vetor->P--;                                                             //Reduz o valor do contador P
    for(int i=vetor->P-1;i>0;i--){                                          //Percorre a HEAP de traz pra frente
        if(vetor->comparador(vetor->elems[i], vetor->elems[i/2]) == 1){     //Faz a verificação se o elemento é maior que o pai
            void* aux = vetor->elems[i];                                    //As proxims linhas servem para fazer a troca de posição entre pai e filho
            vetor->elems[i] = vetor->elems[i/2];
            vetor->elems[i/2] = aux;
        }
    }
    return aux;                     //Retorna o valor do aux
}
