#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <math.h>

#define PI 3.14159265

int n, numeroThreads, funcao, status;
double a, b;
void *thread_return;
int* vetor;
double* resultados;

double f1(double x){
	double resultado=5;
	return resultado;
}

double f2(double x){
	double resultado;
	resultado=sin(2*x)+cos(5*x);
	return resultado;
}

void* constante(void* tid){
	double a_local=a;
	double h=(b-a)/n;
	if(tid>0){//calculando a_local
		for(int i=0; i<(int)(size_t)tid; i++){
			a_local=a_local+(h*vetor[(int)(size_t)tid]);
		}
	}
	double area_total=((f1(a_local)+f1(a_local+h))*h)/2;
	for(int i=1; i<vetor[(int)(size_t)tid]; i++){
		double x_i=a_local+i*h;
		area_total+=((f1(x_i)+f1(x_i+h))*h)/2;
	}
	resultados[(int)(size_t)tid]=area_total;
	printf("Thread %d executada e calculou area= %le\n", (int)(size_t)tid, area_total);
	pthread_exit(NULL);
}

void* trigonometrica(void* tid){
	//b=b*PI; valor de b já foi alterado na resolução sem thread
	double a_local=a;
	double h=(b-a)/n;
	if(tid>0){//calculando a_local
		for(int i=0; i<(int)(size_t)tid; i++){
			a_local=a_local+(h*vetor[(int)(size_t)tid]);
		}
	}
	double area_total=((f2(a_local)+f2(a_local+h))*h)/2;
	for(int i=1; i<vetor[(int)(size_t)tid]; i++){
		double x_i=a_local+i*h;
		area_total+=((f2(x_i)+f2(x_i+h))*h)/2;
	}
	resultados[(int)(size_t)tid]=area_total;
	printf("Thread %d executada e calculou area= %le\n", (int)(size_t)tid, area_total);
	pthread_exit(NULL);
}

int main(){

printf("Digite quantidade de trapezios\n");
scanf("%d", &n);
printf("Digite quantidade de threads\n");
scanf("%d", &numeroThreads);
printf("Digite o limite a\n");
scanf("%le", &a);
printf("Digite o limite b\n");
scanf("%le", &b);
printf("Digite 1 para funcao constante; 2 para funcao sen(2x)+cos(5x)\n");
scanf("%d", &funcao);
printf("\n");

pthread_t threads[numeroThreads]; //vetor de threads
resultados=(double*)malloc(sizeof(double)*numeroThreads); //vetor que guarda o resultado de cada thread

vetor=(int*)malloc(sizeof(int)*numeroThreads);//alocando vetor com o numeros de trapezios que cada thread vai calcular

int aux=n;
int contador=0;
do{ //distribuição dos trapezios por thread, indice=numero da thread, conteudo=numero de trapezios
	vetor[contador]+=1;
	if(contador==numeroThreads-1){
		contador=0;
	}else{
		contador++;
	}
	aux--;
}while(aux>0);

for(int i=0; i<numeroThreads; i++){ //imprimindo vetor, indice=numero da thread, conteudo=numero de trapezios
	printf("Thread %d = %d trapezios\n", i, vetor[i]);
}
printf("\n");

//======================FUNCAO 1: CONSTANTE (SEM THREAD)=================

printf("Resultados sem uso de threads\n");

if(funcao==1){ //Solucao 1
	double h=(b-a)/n;
	double area_total=((f1(a)+f1(a+h))*h)/2;
	for(int i=1; i<n; i++){
		double x_i=a+i*h;
		area_total+=((f1(x_i)+f1(x_i+h))*h)/2;
	}
printf("Solucao 1, funcao 1: (constante): area = %.2e\n", area_total);
}

if(funcao==1){ //Solucao 2
	double h=(b-a)/n;
	double area_total=(f1(a)+f1(b))/2;
	for(int i=1; i<n; i++){
		double x_i=a+i*h;
		area_total+=f1(x_i);
	}
area_total=h*area_total;
printf("Solucao 2, funcao 1: (constante): area = %.2e\n", area_total);
}
//====================================FIM=================================


//===============FUNCAO 2: f(x)=sen(2x)+cos(5x) (SEM THREAD)==========

if(funcao==2){ //Solucao 1
	b=b*PI;
	double h=(b-a)/n;
	double area_total=((f2(a)+f2(a+h))*h)/2;
	for(int i=1; i<n; i++){
		double x_i=a+i*h;
		area_total+=((f2(x_i)+f2(x_i+h))*h)/2;
	}
printf("Solucao 1, funcao 2: f(x)=sen(2x)+cos(5x): area = %.2e\n", area_total);
}

if(funcao==2){ //Solucao 2
	//b=b*PI; valor de b já foi alterado na Solucao 1
	double h=(b-a)/n;
	double area_total=(f2(a)+f2(b))/2;
	for(int i=1; i<n; i++){
		double x_i=a+i*h;
		area_total+=f2(x_i);
	}
area_total=h*area_total;
printf("Solucao 2, funcao 2: f(x)=sen(2x)+cos(5x): area = %.2e\n", area_total);
}
printf("\n");
//====================================FIM=================================

if(funcao==1){
	for(int i=0; i<numeroThreads; i++){
		status=pthread_create(&threads[i], NULL, constante, (void*)(size_t)i);
	}
}

if(funcao==2){
	for(int i=0; i<numeroThreads; i++){
		status=pthread_create(&threads[i], NULL, trigonometrica, (void*)(size_t)i);
	}
}

for(int i=0; i<numeroThreads; i++){ //aguardando fim das threads
	pthread_join(threads[i], &thread_return);
}

double resultado_final=0;
for(int i=0; i<numeroThreads; i++){ //soma dos resultados calculados pelas threads
	resultado_final=resultado_final+resultados[i];
}

printf("\n");
printf("Resultados com uso de threads\n");

if(funcao==1){
printf("Area da função 1 (constante) = %.2e\n", resultado_final);
printf("\n");
}
if(funcao==2){
printf("Area da função 2 f(x)=sen(2x)+cos(5x) = %.2e\n", resultado_final);
printf("\n");	
}

for(int i=0; i<numeroThreads; i++){
	printf("valor do vetor resultados na posicao %d = %le\n", i, resultados[i]);
}

free(vetor);
free(resultados);

return 0;
}