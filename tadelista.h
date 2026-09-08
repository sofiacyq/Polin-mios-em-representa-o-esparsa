#ifndef TADELISTA_H
#define TADELISTA_H

//construcao da struct para o polinomio
typedef struct{
    long long coeficiente;
    long long grau;
}Termo;

//construcao da struct do no
typedef struct No{
    Termo termo;
    struct No *prox;
}No;

typedef struct{
    No *inicio;
}Polinomio;

//parametros das nossas funcoes criadas no tadelista.c
Polinomio *criapolinomio(void);
void inserepoli(Polinomio *poli, long long coef, long long Grau);
void removepoli(Polinomio *poli, long long Grau);
void removemenor(Polinomio *poli);
void liberapoli(Polinomio *poli);
long long coeficiente(Polinomio *poli, long long Grau);
long long graumax(Polinomio *poli);
Polinomio *soma(Polinomio *A, Polinomio *B);
Polinomio *multiplica(Polinomio *A, Polinomio *B);
void escala(Polinomio *poli, long long C);
void impriprime_poli(Polinomio *poli);
void imprime_inverso(Polinomio *poli);
#endif

/*Termo!=polinomio, termo representa apenas cada um dos termos da nossa expressao, e polinomio sim representa a nossa expressao
ou seja, termopoli= 5x^2, polinomio = 5*x^2 + 3*x^1 e etc... bem obivio, mas so lembrando*/
