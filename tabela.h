#include <stdio.h>
#include <stdlib.h>
#include "tadelista.h"

#ifndef TABELA_H
#define TABELA_H

#define CAPACIDADEINI 64 //capacidade inicial e por acaso precisar de espaco ela cresce
#define TAM 33 
/*Como escrito na tabela de limites la no enunciado, o tamanho max de um polinomio e
de 32 caracteres, colocamos aqui 33 por causa do \0 */

//struct de associacao dos nomes de um polinomio
typedef struct{
    char Name[TAM];
    Polinomio *poli; 
}Tab_entrada;

//a tabela que vai ser um array 
typedef struct{
    Tab_entrada *entra;
    int capa; //aqui e a capacidade da tabela, ou seja, o tamanho atual do array    
    int quant; //quantidade de nomes definidos dentro da tabela
}Tabela;

//mesma coisa de polilista.h, aqui tambem vamos colocar as  funcoes que vao ser criadas no tabela.c
void Cria_tabela(Tabela *tab);
Polinomio *busca_tab(Tabela *tab, char *nome);
void def_tab(Tabela *tab, char *nome, Polinomio *poli);
void libera_Nometab(Tabela *tab, char *nome);
void liberatab(Tabela *tab);


#endif



