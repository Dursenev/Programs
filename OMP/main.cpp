

#include <iostream>
#include <omp.h>
#include <cmath>
#include<ctime>
#define M_Size 3

void PrintM(int **A){
    for(int i = 0;i < M_Size;i++){
        for(int j = 0;j < M_Size;j++){
            std :: cout << A[i][j] << "  ";
        }
        std :: cout << "\n";
    }
}

void PrintM(int **A, int**B){
    for(int i = 0;i < M_Size;i++){
        for(int j = 0;j < M_Size;j++){
            std :: cout << A[i][j] << "  ";
        }
		std::cout<<"\t";
		for(int j = 0;j < M_Size;j++){
            std :: cout << B[i][j] << "  ";
        }
        std :: cout << "\n";
    }
}
int **alloc_2d_int(int N) 
{
    int *data = (int *)malloc(N*N*sizeof(int));
    int **array= (int **)malloc(N*sizeof(int*));
    //int** array = new int*[N];
    for (int i=0; i<N; i++)
        array[i] = &(data[N*i]);
        //array[i] = new int[i];

    return array;
}
void free_mem(int **A)//Осбождает память
{
	free(A[0]);
	free(A);	
}
void FillM(int **A){
	for(int i = 0;i < M_Size;i++){
		for(int j = 0;j < M_Size;j++){
			A[i][j] = rand()%5;
		}
	}
}
void zeros(int **B){
	for(int i = 0;i < M_Size;i++){
		for(int j = 0;j < M_Size;j++){
			B[i][j] = 0;
		}
	}
}
int main(){
    omp_set_num_threads(omp_get_num_procs());
	double time;
	int N = M_Size;
	int **A = alloc_2d_int(N);
	int **B = alloc_2d_int(N);
	int **C = alloc_2d_int(N);
	int **AT =alloc_2d_int(N);
	int **B2 =alloc_2d_int(N);
	int **F = alloc_2d_int(N);
	FillM(A);
	FillM(B);
	FillM(C);
	
	
    std :: cout << "Size = " << N << "x" << N << "\n";
    unsigned int start_time = clock();
	#pragma omp parallel for
    for(int i = 0; i < N;i++)
    {
		for(int j = 0; j < N;j++)
		{
			AT[i][j]=A[j][i];
		}
   }
   #pragma omp parallel for
	for(int i=0;i<N;i++)
	{
	#pragma omp parallel for
	for(int j=0;j<N;j++)
	{
	B2[i][j]=0;
	#pragma omp parallel for
	for(int k=0;k<N;k++)
	B2[i][j]+=B[i][k]*B[k][j];
	}
}
	#pragma omp parallel for
	for(int i = 0; i < N;i++)
	{
	#pragma omp parallel for
		for(int j = 0; j < N;j++)
		{
			F[i][j] += C[i][j]+AT[i][j]+B2[i][j];
		}
	}
	unsigned int end_time = clock();
	unsigned int search_time = end_time-start_time;
	std::cout << "Time = " << search_time; 
		std :: cout << "A:\t\tA^T:\n";
		PrintM(A,AT);
		std :: cout << "B:\t\tB^2:\n";
		PrintM(B,B2);
		std :: cout << "C:\n";
		PrintM(C);
		std :: cout << "F = AT+B2 + c:\n";
		PrintM(F);

	free_mem(A);
	free_mem(B);
	free_mem(AT);
	free_mem(B2);	
	free_mem(F);
	return 0;
}
