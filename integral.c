#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <math.h>

#define PI 3.14159265

double f1(double x){
	x=5;
	return x;
}

double f2(double x){
	x=sin(2*x)+cos(5*x);
	return x;
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

int* vetor=(int*)malloc(sizeof(int)*numeroThreads);//alocando vetor com o numeros de trapezios que cada thread vai calcular
b=b*PI;


for(int i=0; i<numeroThreads; i++){ //preenchendo vetor, indice=numero da thread, conteudo=numero de trapezios
	vetor[i]=i;
}

for(int i=0; i<numeroThreads; i++){ //imprimindo vetor, indice=numero da thread, conteudo=numero de trapezios
	printf("Thread %d = %d\n", i+1, vetor[i]);
}

if(funcao==1){
	double h=(b-a)/n;
	double area_total=(f2(a)+f2(b))/2;
	for(int i=1; i<n; i++){
		int x_i=a+i*h;
		area_total+=f2(x_i);
	}
area_total=h*area_total;
printf("area = %f\n", area_total);
}

if(funcao==2){
	double h=(b-a)/n;
	double area_total=(f2(a)+f2(b))/2;
	for(int i=1; i<n; i++){
		int x_i=a+i*h;
		area_total+=f2(x_i);
	}
area_total=h*area_total;
printf("area = %f\n", area_total);
}

printf("cos PI = %.2e\n", cos(PI));
printf("sen PI = %.2e\n", sin(PI));
printf("cos 2PI = %.2e\n", cos(2*PI));
printf("sen 2PI = %.2e\n", sin(2*PI));
printf("cos PI/2 = %.2e\n", cos(PI/2));
printf("sen PI/2 = %.2e\n", sin(PI/2));

return 0;
}