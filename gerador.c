#include <stdio.h> 
#include <stdlib.h>
#include <time.h>

//Definições iniciais com os parâmetros oferecidos na descrição do trabalho
#define DEF_INICIAL 50000
#define GRAUS_maximo 500000
#define escala 20000

int main(void){
	srand(time(NULL)); //inicializa semente aleatória

	int *grausA = geradordosgraus(GRAUS_maximo);
	geradordepolinomio('A', grausA);
	free(grausA);
	//Gerou-se, aqui, graus para o primeiro polinômio

	for(int i=0; i<escala; i++){
		printf("%.4f\n", geradordeescala());
	}

	int *grausB = geradordosgraus(GRAUS_maximo);
	geradordepolinomio('B', grausB);
	free(grausB);

	printf("IMPRIME A\n");
	printf("GRAU A\n");
	printf("IMPRIME B\n");
	printf("GRAU B\n");
	printf("SOMA A B R\n");

}
//Função para gerar vetor e embaralhar seus elementos
int *geradordosgraus(int mval){ //a função recebe o valor máximo, que delimita o tamanho do sorteio
	int *vetor = (int*) malloc((mval + 1) * sizeof(int)); //mval + 1 para não dar buffer overflow

	if(!vetor){ return (NULL); }//verificação da alocação do vetor

	for(int i=0; i<=mval; i++){
		vetor[i] = i;  //inicialização do vetor com números ordenados
	}

	//laço de repetição para embaralhar os elementos do vetor
	for(int i=mval; i>0; i--){
		int j=rand() % (i+1);
		int aux = vetor[i];
		vetor[i] = vetor[j];
		vetor[j] = aux;
	}

	return (vetor);
}

//Função para gerar o coeficiente dentro das especificações do trabalho
double geradordocoeficiente(void){
	double coeficiente = ((double)rand()/RAND_MAX) * 2000.0 - 1000.0;
	return(coeficiente);
}

//Função para gerar o fator c de escala entre [-1, 1], para que c!=0
double geradordeescala(void){
	double c = 0.0;
	while(c == 0.0){
		c = ((double)rand()/RAND_MAX) * 2.0 - 1.0;
	}
	return(c);
}

//Função auxiliar que imprime um polinômio no formato pedido
void geradordepolinomio(char a, int *graus){
	printf("DEF %c %d\n", a, DEF_INICIAL);
	for(int i=0; i<DEF_INICIAL; i++){
		printf("%d %.2f\n", graus[i], geradordocoeficiente());
	}
}