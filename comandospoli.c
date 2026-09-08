#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "tadelista.h"
#include "tabela.h"

#define TAM2 64

/* comecamos com uma funcao auxiliar para que assim todos os comandos que exigem 
um polinomio ja existente, assim realiza a busca e se caso nao existir sera avisado, sera
usado na funcoes que pedem o polinomio assim como esta no enunciado do trabalho A e B devem existir */

Polinomio *busca_erro(Tabela *tab, char *nome){
    Polinomio *poli = busca_tab(tab, nome);

    if(poli == NULL){
        fprintf(stderr, "cuidado, polinomio indefinido, tente com polinomio existente\n");
        return NULL;
    }

    return poli;
}

//agora sim nossa funcao principal que vai ler os comandos de entrada
int main(void){
    Tabela tab;
    Cria_tabela(&tab);
    char comando[TAM2];

/* como todas as especificacoes dos comandos estao no enunciado nao comentarei o que cada um faz, 
por isso essa parte do codigo tera uma quantidade menor de comentarios, ja que so chamaremos as funcoes ja criadas 
no tadelista.c e tabela.c, la ja tem as explicacoes */
    while(scanf(" %63s", comando) == 1){

        if(strcmp(comando, "FIM") == 0){//quando fazemos a comparacao com o funcao da biblioteca string ela retorna 0 se as palavras forem exatamente iguais
            break;
        }

        else if(strcmp(comando, "DEF") == 0){
            char nome[TAM];
            int j;

            scanf("%32s %d", nome, &j);

            Polinomio *Novo = criapolinomio();
            for(int i = 0; i < j; i++){
                long long coef, Grau;
                scanf("%lld %lld", &coef, &Grau);
                inserepoli(Novo, coef, Grau);
            }
            //como dito def pode redefir e definir nomes, entao chamamos a funcao criada na tabela para liberar caso o nome ja exista
            def_tab(&tab, nome, Novo);
        }
        
        else if(strcmp(comando, "SOMA") == 0){
            char nA[TAM], nB[TAM], nresp[TAM];
            scanf("%32s %32s %32s", nA, nB, nresp);

            Polinomio *A = busca_erro(&tab, nA);
            Polinomio *B = busca_erro(&tab, nB);

            Polinomio *resp =  soma(A, B);

            def_tab(&tab, nresp, resp);
        }

        else if(strcmp(comando, "PROD") == 0){
            char nA[TAM], nB[TAM], nresp[TAM];
            scanf("%32s %32s %32s", nA, nB, nresp);

            Polinomio *A = busca_erro(&tab, nA);
            Polinomio *B = busca_erro(&tab, nB);

            Polinomio *resp = multiplica(A, B);

            def_tab(&tab, nresp, resp);
        }

        else if(strcmp(comando, "ADD") == 0){
            char Nome[TAM];
            long long coef, Grau;

            scanf("%32s %lld %lld", Nome, &coef, &Grau);

            Polinomio *A = busca_erro(&tab, Nome);
            inserepoli(A, coef, Grau);
        }

        else if(strcmp(comando, "ESCALA") == 0){
            char Nome[TAM];
            long long c;

            scanf("%32s %lld", Nome, &c);
            
            Polinomio *A = busca_erro(&tab, Nome);
            escala(A, c);
        }

        else if(strcmp(comando,"REMOVE") == 0){
            char Nome[TAM];
            long long grau;

            scanf("%32s %lld", Nome, &grau);

            Polinomio *A = busca_erro(&tab, Nome);

            removepoli(A, grau);
        }

        else if(strcmp(comando, "REMOVEMENOR") == 0){
            char Nome[TAM];

            scanf("%32s", Nome);

            Polinomio *A = busca_erro(&tab, Nome);

            removemenor(A);
        }

        else if(strcmp(comando, "LIBERA") == 0){
            char Nome[TAM];

            scanf("%32s", Nome);

            busca_erro(&tab, Nome);

            libera_Nometab(&tab, Nome);
        }

        //os que exigem impressao
        else if(strcmp(comando, "COEF") == 0){
            char Nome[TAM];
            long long Grau;

            scanf("%32s %lld", Nome, &Grau);

            Polinomio *A = busca_erro(&tab, Nome);
            printf("%lld", coeficiente(A, Grau));
        }

        else if(strcmp(comando, "GRAU") == 0){
            char Nome[TAM];

            scanf("%32s", Nome);

            Polinomio *A = busca_erro(&tab, Nome);
            printf("%lld", graumax(A));
        }

        else if(strcmp(comando, "IMPRIME") == 0){
            char Nome[TAM];
            scanf("%32s", Nome);

            Polinomio *A = busca_erro(&tab, Nome);
            imprime_poli(A);
        }

        else if(strcmp(comando, "IMPRIMEINV") == 0){
            char Nome[TAM];
            scanf("%32s", Nome);

            Polinomio *A = busca_erro(&tab, Nome);
            imprime_inverso(A);
        }
    }//acabou, "educamos" cada um dos comandos

    //vamos liberar a tabela inteira

    liberatab(&tab);
    return 0;
}
