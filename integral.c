#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char *argv[]){

if(argc<5){
	printf("Falta parametro: /.<prog> <n> <a> <b> <threads>\n");
	return 0;
}

int n, a, b, numeroThreads;
double h=(b-a)/n;

n=atoi(argv[1]);
a=atoi(argv[2]);
b=atoi(argv[3]);
numeroThreads=atoi(argv[4]);

printf("n=%d a=%d b=%d threads=%d\n", n, a, b, numeroThreads);

int* vetor=(int*)malloc(sizeof(int)*numeroThreads);

for(int i=0; i<numeroThreads; i++){ //preenchendo vetor
	vetor[i]=i;
}

for(int i=0; i<numeroThreads; i++){ //imprimindo vetor
	printf("Thread %d = %d\n", i+1, vetor[i]);
}

return 0;
}