#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <math.h>

#define PI 3.14159265

double f1(double x){
	double resultado=5;
	return resultado;
}

double f2(double x){
	double resultado;
	resultado=sin(2*x)+cos(5*x);
	return resultado;
}

int main(){

int n, numeroThreads, funcao;
double a, b;

printf("Digite quantidade de trapezios\n");
scanf("%d", &n);
printf("Digite quantidade de threads\n");
scanf("%d", &numeroThreads);
printf("Digite o limite a\n");
scanf("%le", &a);
printf("Digite o limite b\n");
scanf("%le", &b);
printf("Digite 1 para funcao 1; 2 para funcao 2\n");
scanf("%d", &funcao);

int aux=n;
int contador=0;

int* vetor=(int*)malloc(sizeof(int)*numeroThreads);//alocando vetor com o numeros de trapezios que cada thread vai calcular

/*
for(int i=0; i<numeroThreads; i++){ //preenchendo vetor, indice=numero da thread, conteudo=numero de trapezios
	vetor[i]=i;
}*/

do{
	vetor[contador]+=1;
	if(contador==numeroThreads-1){
		contador=0;
	}else{
		contador++;
	}
	aux--;
}while(aux>0);

for(int i=0; i<numeroThreads; i++){ //imprimindo vetor, indice=numero da thread, conteudo=numero de trapezios
	printf("Thread %d = %d trapezios\n", i+1, vetor[i]);
}

//======================FUNCAO 1: CONSTANTE (SEM THREAD)=================

if(funcao==1){ //Solucao 1
	double h=(b-a)/n;
	double area_total=((f1(a)+f1(a+h))*h)/2;
	for(int i=1; i<n; i++){
		double x_i=a+i*h;
		area_total+=((f1(x_i)+f1(x_i+h))*h)/2;
	}
printf("Solucao 1, funcao 1 (constante): area = %.2e\n", area_total);
}

if(funcao==1){ //Solucao 2
	double h=(b-a)/n;
	double area_total=(f1(a)+f1(b))/2;
	for(int i=1; i<n; i++){
		double x_i=a+i*h;
		area_total+=f1(x_i);
	}
area_total=h*area_total;
printf("Solucao 2, funcao 1 (constante): area = %.2e\n", area_total);
}
//====================================FIM=================================


//===============FUNCAO 2: f(x)=f(x)=sen(2x)+cos(5x) (SEM THREAD)==========

if(funcao==2){ //Solucao 1
	b=b*PI;
	double h=(b-a)/n;
	double area_total=((f2(a)+f2(a+h))*h)/2;
	for(int i=1; i<n; i++){
		double x_i=a+i*h;
		area_total+=((f2(x_i)+f2(x_i+h))*h)/2;
	}
printf("Solucao 1, funcao 2 f(x)=sen(2x)+cos(5x): area = %.2e\n", area_total);
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
printf("Solucao 2, funcao 2 f(x)=sen(2x)+cos(5x): area = %.2e\n", area_total);
}
//====================================FIM=================================

/*
printf("cos PI = %.2e\n", cos(PI));
printf("sen PI = %.2e\n", sin(PI));
printf("cos 2PI = %.2e\n", cos(2*PI));
printf("sen 2PI = %.2e\n", sin(2*PI));
printf("cos PI/2 = %.2e\n", cos(PI/2));
printf("sen PI/2 = %.2e\n", sin(PI/2));*/

free(vetor);

return 0;
}