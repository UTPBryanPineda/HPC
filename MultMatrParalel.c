#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>
#include <omp.h>

/* retorna "a - b" en segundos */
//medicion de tiempo
double timeval_diff(struct timeval *a, struct timeval *b)
{
  return
    (double)(a->tv_sec + (double)a->tv_usec/1000000) -
    (double)(b->tv_sec + (double)b->tv_usec/1000000);
}



float **multmat(float **m1, float **m2, int size){
    float **result = (float **)malloc(size * sizeof(float *));
    int i, j, k;
//#pragma omp parallel for
    for (i = 0; i < size; ++i){
        result[i] = (float *)malloc(size * sizeof(float));
    }
  // #pragma omp parallel for         
    for(i = 0; i < size; ++i){
//#pragma omp parallel for
        for(j = 0; j < size; ++j){
            float temp = 0;
//#pragma omp parallel for
            for(k = 0; k < size; ++k){
                temp += m1[i][k] * m2[k][j];
            }
            result[i][j] = temp;
        }
    }
    return result;
}

//#pragma omp parallel private(*mat,size)
void matriz(float **mat, int size){
    float a = 5.0;
    int i,j;
//#pragma omp parallel for
    for (i=0; i < size; ++i){
//#pragma omp parallel for
        for (j=0; j < size; ++j){
            mat[i][j] = ((float)rand() / (float)(RAND_MAX)) * a;
        }
    }
}

//#pragma omp parallel private(*matriz,*filename, size)
void matrizcsv(float **matriz, int size, char *fileName)
{
    FILE *f = fopen(fileName, "w");
    int i,j;
//#pragma omp parallel for
    for (i = 0; i < size; ++i){
//#pragma omp parallel for
        for (j = 0; j < size; ++j){
            fprintf(f, "%f,", matriz[i][j]);
        }
        long currentPos = ftell(f);
        fseek(f, currentPos - 1, SEEK_SET);
        fprintf(f, "\n");
    }

    fclose(f);
}

int main()
{

int nthreads, tid;
double prometiempo;
double tiempoactual = 0;

int size;
printf("Inserte el tama�o de las Matrices: ");
scanf("%d", &size);


#pragma omp parallel shared(nthreads) private(tid)
  {
  tid = omp_get_thread_num();
  if (tid == 0)
    {
    nthreads = omp_get_num_threads();
    printf("Number of threads = %d\n", nthreads);
    }
  printf("Thread %d starting...\n",tid);
}



  //repetidor
int r;
#pragma omp parallel for
for (r=0; r<=10;r++){

//medicion de tiempo
struct timeval t_ini, t_fin;
  double secs;
  gettimeofday(&t_ini, NULL);
    

    srand(time(NULL));
 
    float **matriz1 = (float **)malloc(size * sizeof(float *));
    int i;
//#pragma omp parallel for
    for (i = 0; i < size; ++i){
        matriz1[i] = (float *)malloc(size * sizeof(float));
    }
    
    float **matriz2 = (float **)malloc(size * sizeof(float *));
//#pragma omp parallel for
    for (i = 0; i < size; ++i){
        matriz2[i] = (float *)malloc(size * sizeof(float));
    }
    
    matriz(matriz1, size);
    matriz(matriz2, size);
    
    float **matrizresult = multmat(matriz1, matriz2, size);
    
    matrizcsv(matriz1, size, "matriz1.csv");
    matrizcsv(matriz2, size, "matriz2.csv");
    matrizcsv(matrizresult, size, "resultado multiciplacion matrices.csv");

  gettimeofday(&t_fin, NULL);
  secs = timeval_diff(&t_fin, &t_ini);
  printf("%.16g milliseconds\n", secs * 1000.0);
    
  tiempoactual = tiempoactual + secs;
    
  }
  prometiempo = tiempoactual / 100;
  
  printf("%.16g milliseconds promedio de tiempo\n",prometiempo * 1000.0);
}
