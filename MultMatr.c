#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void csv(float **vec,char nombre[], int tam){

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
	float ** matriz1;
	float ** matriz2;
	float ** mult;
	int i;
	int j;
    float a = 1.0;
    
	matriz1 = (float**) malloc (tam*sizeof(float*));
	matriz2 = (float**) malloc (tam*sizeof(float*));
	mult    = (float**) malloc (tam*sizeof(float));

	printf("Ingrese el tamaño de las matrices: \n");
	scanf("%d",&tam);


	for(i = 0; i < tam; i++){
		matriz1[i] = (float*) malloc (tam*sizeof(float));
		matriz2[i] = (float*) malloc (tam*sizeof(float));
	}

	for(i = 0; i < tam; i++){
		for(j = 0; j < tam; j++){
			float num = ((float)rand()/(float)(RAND_MAX) * a);
			matriz1[i][j] = num;
		}
	}

	for(i = 0; i < tam; i++){
		for(j = 0; j < tam; j++){
			float num = ((float)rand()/(float)(RAND_MAX) * a);
			matriz2[i][j] = num;
		}
	}
	
	for(i = 0; i < tam; i++){
	   for(j = 0; j < tam; j++){
			mult[i][j] = matriz1[i][j] * matriz2[i][j];
		}
	}
		
	
	csv(matriz1,"matriz 1.csv", tam);
    csv(matriz2,"matriz 2.csv", tam);
	csv(mult,"resultado matriz.csv", tam);

	free(matriz1);
	free(matriz2);
	free(mult);
	return 0;

}
