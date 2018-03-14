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



//#pragma omp parallel private(*vec1,*vec2, size)
float *sumvect(float *vec1, float *vec2, int size)
{
    float *result = malloc(sizeof(float) * size);
    int i;
   #pragma omp parallel for
    for (i=0; i < size; i++)
    {
        result[i] = vec1[i] + vec2[i];
    }
    return result;
}


void vectorcom(float *vec, int size)
{
    float a = 5.0;
    int i;
    //#pragma omp parallel for
    for (i=0; i < size; i++)
    {
        vec[i] = ((float)rand() / (float)(RAND_MAX)) * a;
    }
}

void vectorcsv(float *vector, int size, char *fileName)
{
    FILE *f = fopen(fileName, "w");
    int i;
   // #pragma omp parallel for	
    for (i=0; i < size; i++)
    {
        fprintf(f, "%f,", vector[i]);
    }

    long currentPos = ftell(f);
    fseek(f, currentPos - 1, SEEK_SET);
    fprintf(f, "\n");
    
    fclose(f);
}

int main()
{

int nthreads, tid;

double prometiempo;
double tiempoactual = 0;
int size;
  printf("Inserte el tama�o del vector: ");
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
//#pragma omp parallel for
for (r=0; r<=100;r++){


//medicion de tiempo
struct timeval t_ini, t_fin;
  double secs;
  gettimeofday(&t_ini, NULL);
    

    srand(time(NULL));

    float *vec1 = malloc(sizeof(float) * size);
    float *vec2 = malloc(sizeof(float) * size);
    vectorcom(vec1, size);
    vectorcom(vec2, size);
    float *result = sumvect(vec1, vec2, size);

   // #pragma omp parallel shared(vec1,vec2,size) 
    vectorcsv(vec1, size, "vector1.csv");
    vectorcsv(vec2, size, "vector2.csv");
    vectorcsv(result, size, "resultado suma vectores.csv");
    
   
    gettimeofday(&t_fin, NULL);
  secs = timeval_diff(&t_fin, &t_ini);
  printf("%.16g milliseconds\n", secs * 1000.0);
    
  tiempoactual = tiempoactual + secs;
    
  }
  prometiempo = tiempoactual / 100;
  
  printf("%.16g milliseconds promedio de tiempo\n",prometiempo * 1000.0);

}


