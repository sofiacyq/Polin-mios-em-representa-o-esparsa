/* a tabela de nomes servira para auxiliar nossa main a fazer seu trabalho direitinho, ela guarda o "nome"
dos polinomios, podemos pensar como se fosse uma tabela de funcionarios, assim nosso programa principal pode juntar 
tudo que ja fizemos e executar certinho, ele vai saber quantas "marias, "joaos", tem, ajudando e tendo um parametro para
o nosso comandospoli.c trabalhar */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "tabela.h"



void Cria_tabela(Tabela *tab){
   tab -> capa = CAPACIDADEINI;
   tab -> quant = 0;

   //alocando a nossa tabela
   tab -> entra = (Tab_entrada*)malloc(sizeof(Tab_entrada)*CAPACIDADEINI);

   /* e se caso a alocacao falhar infelizmente nao temos muito o que fazer temos somente
    que garantir que o programa continue tendo os campos de meneira consistentes */
    
    if(tab -> entra == NULL){
        tab -> capa = 0;

    }
}

/* vamo fazer uma funcao auxilia para que conseguir achar o indice do nome do polinomio na tabela, e se caso
nao existir deve retornar -1, utilizamos exatamente o static para que essa funcao so exista aqui dentro, ela 
vai servir para a gente aqui somente */

static int tab_acha_indi(Tabela *tab, char *nome){
    for(int i = 0; i < tab -> quant; i++){
        if(strcmp(tab -> entra[i].Name, nome) == 0){//Name e da nossa struct nome e da funcao
            return i;
        }
    }

    return -1;
}

Polinomio *busca_tab(Tabela *tab, char *nome){//funcao para buscar o polinomio na tabela
    int indi = tab_acha_indi(tab, nome);

    if(indi == -1){//nome nao encontrado
        return NULL;
    }

    return tab -> entra[indi].poli;
}

void def_tab(Tabela *tab, char *nome, Polinomio *poli){
    int indi = tab_acha_indi(tab, nome);

    /* aqui temos 2 diferentes caso para tratar, caso 1: caso o nosso polinomio ja exista, caso 2: caso o nome seja novo
    caso o nome ja exista vamos trocar o ponteiro e liberamos aquele polinomio antigo, e no caso 2 vamos primeiramente garantir 
    que tenha espaco para ele e depois colocmos na tabele */

    //caso 1
    if(indi != -1){
        liberapoli(tab -> entra[indi].poli);
        tab -> entra[indi].poli = poli;
    }

    //caso 2
    if(tab -> quant == tab -> capa){
        int Ncapa = tab -> capa * 2;
        Tab_entrada *Narray = (Tab_entrada*)realloc(tab -> entra,  sizeof(Tab_entrada) * Ncapa);

        if(Narray == NULL){//sem memoria
            printf("erro na alocacao");
            return;
        }

        tab -> entra = Narray;
        tab -> capa = Ncapa;
    }

    //inserindo
    strncpy(tab -> entra[tab -> quant].Name, nome, TAM - 1);
    tab -> entra[tab -> quant].Name[TAM - 1] = '\0';
    tab -> entra[tab -> quant].poli = poli;
    tab -> quant ++;
}

void libera_Nometab(Tabela *tab, char *nome){
    int indi = tab_acha_indi(tab, nome);

    //nome nao existe
    if(indi == -1){
        return;
    }

    //liberando o polinomio associado
    liberapoli(tab -> entra[indi].poli);

    /* como na busca a gente nunca procura por indice, ou seja, e bem lento procura nome por nome
    a forma mais rapida e trocar a ultima entrada por essa que queremos remover e remover, isso tira
    a dificuldade de ter liberar e ainda mover todo mundo da lista para outro indice */

    tab -> entra[indi] = tab -> entra[tab -> quant -1];
    tab -> quant --;
}

void liberatab(Tabela *tab){
    //funcao para liberar toda a tabela, todos os nomes que ainda estao nela
    for(int i = 0; i < tab -> quant; i++){
        liberapoli(tab -> entra[i].poli);
    }

    //liberando o array
    free(tab -> entra);
    tab -> entra = NULL;
    tab -> capa = 0;
    tab -> quant =0;

}