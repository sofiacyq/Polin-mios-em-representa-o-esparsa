#include "tadelista.h"
#include <stdio.h>
#include <stdlib.h>

/* criando o espaço para o nosso polinomio, assim primeiramente ele começa como um polinomio vazio
 no final temos um endereço de onde vai ficar esse espaço */
Polinomio *criapolinomio(void){
    Polinomio *poli;
    poli = (Polinomio*)malloc(sizeof(Polinomio));

    if(poli == NULL){
        return NULL;
    }

    poli -> inicio = NULL;

    return poli;

}

void inserepoli(Polinomio *poli, long long coef, long long Grau){//para nao confundir a variavel grau do no tad é com g minusculo e da tadelista.c e maiusculo
    No *novoN; //criando um novo no
    novoN = (No*)malloc(sizeof(No)); //alocando ele

    if(coef == 0){//se o coeficiente for 0, nao faça nada
        return;
    }

    if(novoN == NULL){//caso de erro na alocacao
        return;
    }

    //agora vamos pegar em informar o nosso novo no
    novoN -> termo.coeficiente = coef; 
    novoN -> termo.grau = Grau;
    novoN -> prox = NULL;

    /* como nossa lista esta ordenada de forma decrescente, precisamos tratar algumas possibilidades iguais as ja vistas em sala,
    1-caso tenhamos um lista vazia(obs:lista vazia!=lista nula), 2-caso o termo precise ser inserido no começo, 3-quando precisamos inserir no meio/fim, ou seja,
    precisamos achar onde inserir */
    
    //caso 1, lista vazia
    if(poli -> inicio == NULL){
        poli -> inicio = novoN;
        return;
    }
    /* o que aconteceu? perguntamos se o inicio do primeiro no e vazio, se isso ocorrer, vamos pegar o novo no criado e esse passara a ser o primeiro no */

    // caso 2, insercao no inicio
    if(Grau > poli->inicio->termo.grau){ //se o Grau for maior que grau  do primeiro termo da lista
        novoN -> prox = poli -> inicio; //o proximo termo passa a ser aquele que estava no inicio da lista
        poli -> inicio = novoN; //o novo termo passa ser o primeiro da lista
        return; 
    }

    //caso 3, procuramos onde inserir
    No *atual;
    No *anterior;
    atual = poli -> inicio;
    anterior = NULL;

    /* enquanto a lista nao estiver nula e o grau do polinomio que quero inserir é menor que da minha lista */
    while(atual != NULL && atual -> termo.grau > Grau){ 
        anterior = atual; 
        atual = atual -> prox;

    }

    //e se caso o polinomio inserido tem o mesmo grau que o um que ja existe na lista, entao devemos somar os coeficientes, como pedido no enunciado
    if(atual != NULL && atual -> termo.grau == Grau){
        atual -> termo.coeficiente += coef; 
        free(novoN); //nao vamos mais usar o novo no nesse caso
    
        //e se a soma der zero?
        if(atual -> termo.coeficiente == 0){
            if(anterior == NULL){
                poli->inicio = atual->prox;
            }
            else{
                 anterior->prox = atual->prox;
            }

            free(atual);

        }
         
        return;

    }

    //agora sim, caso contrario nao exista grau igual entao vamos inserir o novo no, ele deve estar entre o anterior e o atual

    novoN -> prox = atual;
    if(anterior == NULL){
        poli -> inicio = novoN;
    }
    else{
        anterior -> prox = novoN;
    }

}

//funcao para remover um termo
void removepoli(Polinomio *poli, long long Grau){
    if(poli == NULL || poli -> inicio == NULL){ //se o polinomio e nulo ou a lista estiver vazia nao fazemos nada
        return;
    }
    //primeiro vamos procurar o termo dentro da nossa lista, fazendo da mesma maneira do caso 3 da funcao anterior
    No *atual;
    No *anterior;
    atual = poli -> inicio;
    anterior = NULL;

    while(atual != NULL && atual -> termo.grau > Grau){ 
        anterior = atual; 
        atual = atual -> prox;
    }

    //e se caso nao bater nenhum grau? quer dizer que o termo nao existe dentro da lista entao, ou se a lista chegar no fim, nao fazemos nada
    if(atual == NULL || atual -> termo.grau != Grau){
        return;
    }

    //se nao for o caso entao vamos remover o no que queremos 
    if(anterior == NULL){
        poli -> inicio = atual -> prox;
    }
    else {
        anterior -> prox = atual -> prox;
    }

    free(atual);

}

void removemenor(Polinomio *poli){
    //novamente se a lista estiver vazia ou polinomio nulo nao fazemos
    if(poli == NULL || poli -> inicio == NULL){
        return;
    }

    No *atual;
    No *anterior;
    atual = poli -> inicio;
    anterior = NULL;

    /* ja que estamos ordenando a nossa lista em ordem decrescente, o nosso menor grau sempre vai estar
     no ultimo no da lista, entao vamo procurar o ultimo no dessa lista */
    
     while(atual -> prox != NULL){
        anterior = atual;
        atual  = atual -> prox;
    }

    //se haver apenas um termo na lista assim que removermos ele essa vira uma lista vazia
    if(anterior == NULL){
        poli -> inicio = NULL;
    }
    
    //se nao for o caso entao removemos o ultimo termo normalmente
    else{
        anterior -> prox = NULL;
    }

    free(atual);
}

void liberapoli(Polinomio *poli){
    //novamente se o ponteiro do polinomio for nulo nao temos o que fazer, vamos verificar isso
    if(poli == NULL){
        return;
    }

    No *atual;
    No *proximo; //para nao confundir prox é do nosso tadelista.h, aqui nessa funcao vamo usar por extenso
    atual = poli -> inicio;

    while(atual != NULL){//enquanto nossa lista nao for ate o final
        proximo = atual -> prox; //vamos guardar o proximo antes de liberar o atual, para nao ocorrer divergencia de ref

        free(atual);
        atual = proximo;
    }

    //no final de tudo isso, devemos liberar tambem a struct do polinomio
    free(poli);
}

long long coeficiente(Polinomio *poli, long long Grau){
    /* verificando se é um polinomio nulo ou uma lista vazia, 
    como pedido em um dos criterios de tratamento, nessa condiçoes deve-se retornar 0 */
    if(poli == NULL || poli -> inicio == NULL){
        return 0;
    }

    No *atual;
    atual = poli -> inicio;

    //vamos procurar o polinomio que queremos, da mesma maneira ja feita
    while(atual != NULL && atual -> termo.grau > Grau){
        atual = atual -> prox;
    }

    //assim que achamos o nosso termo vamos devolver seu coeficiente, mas precisamos checar se esta correto o nosso termo achado
    if(atual != NULL && atual -> termo.grau == Grau){
        return atual -> termo.coeficiente;
    }

    //caso isso nao aconteca por motivos de nao achar ou a lista chegou no final devolvemos 0
    return 0;
}

long long graumax(Polinomio *poli){
    /* verificao padrao,  como um dos tratamentos pedidos se nosso 
    polinomio for nulo ou lista vazia a funcao deve retornar -1 */
    if(poli == NULL || poli -> inicio == NULL){
        return -1;
    }

    /* como a lista esta ordenada de maneira decrescente o nosso grau maximo 
    da expressao vai estar sempre no inicio da nossa lista */
   return poli -> inicio -> termo.grau;
}

Polinomio *soma(Polinomio *A, Polinomio *B){
    Polinomio *Resultado;
    Resultado = criapolinomio();
    
    //verificacao, se acontecer alguma coisa na alocacao desse novo polinomio saberemos atraves dessa verificacao que retornara o NULL
    if(Resultado == NULL){
        return NULL;    
    }

    //inserindo os termo de A
    No *atual;
    //verificacao para o codigo nao "quebrar" caso seja passado um polinomio nulo e fique tentando acessar A, vamos fazer o mesmo com B
    if(A != NULL){
        atual = A -> inicio;
    }
    else{
        atual = NULL;
    }
    
    while(atual != NULL){
        //vamos chamar a nossa funcao ja criada, a insere, ela vai inserindo cada um dos termos da expressao de A
        inserepoli(Resultado, atual -> termo.coeficiente, atual -> termo.grau);
        atual =  atual -> prox;
    }

    /* a soma dos polinomios so ocorre se tivermos termos com o mesmo expoente, portanto, usamos a funcao ja criada
    para fazer esse papel, ja que dentro dela ja esta implementado o papel de tratamento de casos desse tipo, ou seja,
    somente os termos de mesmo grau sao somados os coeficientes, de resto mantemos normamente */

    //fazendo o mesmo de A, que ja vai somar automaticamente

    if(B != NULL){
        atual = B -> inicio;
    }
    else{
        atual = NULL;
    }

    while(atual != NULL){
        inserepoli(Resultado, atual -> termo.coeficiente, atual -> termo.grau);
        atual = atual -> prox;
    }

    return Resultado;

}

Polinomio *multiplica(Polinomio *A, Polinomio *B){
    Polinomio *Resultado;
    Resultado = criapolinomio();
    //verificando assim como na soma
    if(Resultado == NULL){
        return NULL;
    }
    
    //Como funciona a multiplicacao? precisamos multiplicar os coeficientes e somar os expoentes
    
    No *TerA;
    //verificacao de protecao assim como na soma
    if(A != NULL){
        TerA = A -> inicio;
    }
    else{
        TerA = NULL;
    }
    
    while(TerA != NULL){

        No *TerB;
        //verificacao
        if(B != NULL){
            TerB = B -> inicio;
        }
        else{
            TerB = NULL;
        }

        while(TerB != NULL){
            long long NovoCoef;//multiplicando os coeficientes
            long long NovoGrau;//somando os graus

            NovoCoef = TerA -> termo.coeficiente * TerB -> termo.coeficiente;
            NovoGrau = TerA -> termo.grau + TerB -> termo.grau;

            /*o insere ja cuida de todos os caso, soma os graus iguais e exclui os que se zeram, por isso vamos chamar ele aqui
            como ja foi implementado nao precisamos fazer isso na mao, mesma coisa na soma*/
            inserepoli(Resultado, NovoCoef, NovoGrau);
            
            TerB = TerB -> prox;
        }

        TerA = TerA -> prox;
    }

    return Resultado;

}

void escala(Polinomio *poli, long long C){
    //verificando se o polinomio é nulo, como sempre nao temos o que fazer
    if(poli == NULL){
        return;
    }

    /* dentro dos casos de tratamento na escala precisamos tratar caso o c = 0, tudo multiplicado por 0 é zero
    dessa maneira os coeficientes zeram, e nao podemos deixar assim, por isso é preciso tratar a lista vazia
    ja que nosso polinomio se anula, ou seja, liberar a lista */
    if(C == 0){
        No *atual;
        No *proximo;
        atual = poli -> inicio;
        //liberando assim como em liberapoli
        while(atual != NULL){
            proximo = atual -> prox;

            free(atual);
            atual = proximo;
        }
        
        poli -> inicio = NULL;
        return;
    }

    //em casos normais vamos percorrer toda a lista e multiplicar os coeficentes por c
    No *atual;
    atual = poli -> inicio;

    while(atual != NULL){
        atual -> termo.coeficiente *= C;
        atual = atual -> prox;
    }
}

void imprime_poli(Polinomio *poli){
    //verificando
    if(poli == NULL || poli -> inicio == NULL){
        printf("0\n");
        return;
    }

    //casos normais
    No *atual;
    int prim = 1; // variavel para controle de espacos
    atual = poli -> inicio;

    while(atual != NULL){
        if(!prim){
            printf(" ");
        }
        /* vamos utilizar o not aqui para controlar o espaço, nao queremos que tenha um espaço antes do primeiro termo
        assim com a porta logica os valores sao invertidos, se e 1/verdadeiro vira 0/falso, assim podemos pensar, se for 
        o primeiro termo nao imprima o espaco */
     
        printf("%.2f*x^%d", atual -> termo.coeficiente, atual -> termo.grau);
        prim = 0;
        atual = atual -> prox;

        /* entao, se for o primeiro termo ele nao vai imprimir o espaço, e vai cair direto na impressao do termo
        imprime e logo apos ja passamos para o proximo termo, que ai sim cai no if e imprime o espaço antes de 
        imprimir o termo da nossa expressao, vale resaltar que essa maneira incluida por nos foi uma maneira de colocar
        os espacos como pedido no enunciado, mas por uma pura questao de estetica pesquisamos uma maneira para nao 
        ficar o espaco antes do termo 1, por que achamos feio */
    }

    printf("\n");
}

void imprime_inverso(Polinomio *poli){
    //verificacao como no caso de impressao canonica
    if(poli == NULL || poli -> inicio == NULL){
        printf("0\n");
        return;
    }
    
    //na impressao invertida precisamos inverter nossa lista e colocala em ordem crescente
    No *atual;
    No *anterior;
    No *proximo;
    atual = poli -> inicio;
    anterior = NULL;

    //percorrendo a lista para fazer a inversao
    while(atual != NULL){
        proximo = atual -> prox; //vamo guardar o  proximo antes de mexer em algo
        atual -> prox = anterior;//invertendo 
        anterior = atual;
        atual = proximo;
    }

    poli -> inicio = anterior; //o inicio agora tem o ultimo termo da antiga lista, ou seja, a lista começa com o termo de menor grau

    //agora podemos imprimir
    atual = poli -> inicio;
    int prim = 1;

    while(atual != NULL){
        //fazendo o mesmo esquema da impressao na ordem canonica 
        if(!prim){
            printf(" ");
        }

        printf("%.2f*x^%d", atual -> termo.coeficiente, atual -> termo.grau);
        prim = 0;
        atual = atual -> prox;
    }

    printf("\n");

    /*mas precisamos voltar nossa lista para ordem normal, para que nao exista divergencias na chamada de outras funcoes,
    fazemos a mesma manipulacao que ja fizemos, exatamente como fizemos para inverter a forma original, como se anulassemos ela
    podemos pensar assim como numa expressao matematica*/

    atual = poli -> inicio;
    anterior = NULL;

    while(atual != NULL){
        proximo = atual -> prox;
        atual -> prox = anterior;
        anterior = atual;
        atual = proximo;
    }

    poli -> inicio = anterior; //agora sim temos nossa lista no formato original 

}
