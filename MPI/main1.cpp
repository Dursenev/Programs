
#include "mpi.h"
#include <cmath>
#include <iostream>

using namespace std;

void vvod_matrix(double* A, int N1,int N2) {
    int i, j;
    for (i = 0; i < N1; i++) {
        for (j = 0; j < N2; j++)
            cout << A[i*N2+j] << ' ';
        cout << endl;
    }
}

int main(int argc, char *argv[])
{
	int r, p,i,j,n=500;
	double *a, *b, *h1,*c,*h2,*f,t, t1,t2;
	a=(double *)calloc(n*n,sizeof(double));
	b=(double *)calloc(n*n,sizeof(double));
	c=(double *)calloc(n*n,sizeof(double));
	b2=(double *)calloc(n*n,sizeof(double));
	h1=(double *)calloc(n*n,sizeof(double));
	h2=(double *)calloc(n*n,sizeof(double));
	f=(double *)calloc(n*n,sizeof(double));
	
	MPI_Status st;
	MPI_Init(&argc,&argv);
	MPI_Comm_rank(MPI_COMM_WORLD,&r);
	MPI_Comm_size(MPI_COMM_WORLD,&p);
	
	if (r==0)
		{
			for(i=0;i<n;i++)
				for(j=0;j<n;j++)
				{
					a[i*n+j]=rand() % 100 - 50;
					b[i*n+j]=rand() % 100 - 50;
					c[i*n+j]=rand() % 100 - 50;
					f[i*n+j]=0;
				}
		}

	MPI_Bcast(&n,1, MPI_INT, 0, MPI_COMM_WORLD);
	MPI_Bcast(a,n*n, MPI_DOUBLE, 0, MPI_COMM_WORLD);
	MPI_Bcast(b,n*n, MPI_DOUBLE, 0, MPI_COMM_WORLD);
	MPI_Bcast(c,n*n, MPI_DOUBLE, 0, MPI_COMM_WORLD);
	MPI_Bcast(h1,n*n, MPI_DOUBLE, 0, MPI_COMM_WORLD);
	MPI_Bcast(h2,n*n, MPI_DOUBLE, 0, MPI_COMM_WORLD);
	MPI_Bcast(f,n*n, MPI_DOUBLE, 0, MPI_COMM_WORLD);
	
	t1=MPI_Wtime();
	MPI_Barrier(MPI_COMM_WORLD);
	
	int kvo=n/p;
	int in=r*kvo;
	int ik;
	
	if (r==p-1) 
		ik=n;
	else 
		ik=in+kvo;
		
	int k;
	for(int i=in;i<ik;i++)
	for(int j=0;j<n;j++)
	{
	for(b2[i*n+j],h2[i*n+j]=0,k=0;k<n;k++)
	{
	b2[i*n+j]+=b[k*n+i]*b[j*n+k];
	h2[i*n+j]+=c[i*n+k]+a[i*n+k];
	}
	f[i*n+j]=b2[i*n+j]+h2[i*n+j];
	}
	for(int k=0;k<N;k++)
	B2[i][j]+=B[i][k]*B[k][j];
	
}
	for(i=in;i<ik;i++)
		for(j=0;j<n;j++)
		{
			for(h1[i*n+j]=0,h2[i*n+j]=0,k=0;k<n;k++)
			{
				h1[i*n+j]+=a[k*n+i] +b[j*n+k];
				h2[i*n+j]+=c[i*n+k];
			}
			f[i*n+j]=h1[i*n+j]+h2[i*n+j];
		}
	MPI_Barrier(MPI_COMM_WORLD);
	if (r!=0) 
	{
		MPI_Send(&in,1,MPI_INT,0,1,MPI_COMM_WORLD);
		MPI_Send(&ik,1,MPI_INT,0,2,MPI_COMM_WORLD);
		MPI_Send(h1+in*n,(ik-in)*n,MPI_DOUBLE,0,0,MPI_COMM_WORLD);
		MPI_Send(h2+in*n,(ik-in)*n,MPI_DOUBLE,0,0,MPI_COMM_WORLD);
		MPI_Send(f+in*n,(ik-in)*n,MPI_DOUBLE,0,0,MPI_COMM_WORLD);
	}
	else
	{
		int ii;
		for( ii=1;ii<p;ii++)
		{
			MPI_Recv(&in,1,MPI_INT,ii,1,MPI_COMM_WORLD,&st);
			MPI_Recv(&ik,1,MPI_INT,ii,2,MPI_COMM_WORLD,&st);
			MPI_Recv(h1+in*n,(ik-in)*n,MPI_DOUBLE,ii,0,MPI_COMM_WORLD,&st);
			MPI_Recv(h2+in*n,(ik-in)*n,MPI_DOUBLE,ii,0,MPI_COMM_WORLD,&st);
			MPI_Recv(f+in*n,(ik-in)*n,MPI_DOUBLE,ii,0,MPI_COMM_WORLD,&st);
		}	
		t2=MPI_Wtime();
		t=t2-t1;
		fo
		cout<<"Time= "<<t<<endl;

	}
	
	MPI_Finalize();
	free(a);
	free(b);
	free(c);
	free(f);
	free(h1);
	free(h2);
	
}
