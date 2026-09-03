#ifndef LISTA_H
#define LISTA_H

//construcao da struct para o polinomio
typedef struct{
    long long coeficente;
    long long grau;
}Termopoli;

//construcao da struct do no
typedef struct No{
    Termopoli termo;
    struct No *prox;
}No;

typedef struct{
    No *inicio;
}Polinomio;

/*termopoli!=polinomio, termopoli representa apenas cada um dos termos da nossa expressao, e polinomio sim representa a nossa expressao
ou seja, termopoli= 5x^2, polinomio = 5*x^2 + 3*x^1 e etc...*/
