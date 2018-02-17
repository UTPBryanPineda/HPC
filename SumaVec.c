#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void csv(float *vec,char nombre[], int tam){

	FILE *fp;
	fp = fopen (nombre,"w");
    int i=0;
    
	for(i = 0; i < tam; i++){
		  char array[10];
		  sprintf(array, "%f", vec[i]);
		  fputs(array, fp);
		  fputs(";", fp);
	}
	fclose(fp);

}

int main(){

	int tam;
	float * vector1;
	float * vector2;
	float * suma;
    int i;
	float a = 1.0;
 
	vector1 = (float*) malloc (tam*sizeof(float));
	vector2 = (float*) malloc (tam*sizeof(float));
    suma    = (float*) malloc (tam*sizeof(float));

	printf("Ingrese el tamaño de los vectores:\n");
	scanf("%d",&tam);
	
	for(i = 0; i < tam; i++){
		float num = ((float)rand()/(float)(RAND_MAX) * a);
		vector1[i] = num;
	}

	for(i = 0; i < tam; i++){
		float num = ((float)rand()/(float)(RAND_MAX) * a);
		vector2[i] = num;
	}

	for(i = 0; i < tam; i++){
		suma[i] = vector1[i] + vector2[i];
	}
 
    csv(vector1,"vector 1.csv", tam);
	csv(vector2,"vector 2.csv", tam);
	csv(suma,"resultado.csv", tam);

	free(vector1);
	free(vector2);
	free(suma);
	return 0;

}
