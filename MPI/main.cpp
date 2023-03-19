#include <cstdio>
#include <mpi.h>
#include <cmath>

using namespace std;

double f(double x)
{ 
	return 2*x*x-sqrt(x+2);
}

double g(double x)
{
	return 7*x*x-3*sqrt(x);
}

int main(int argc, char *argv[])
{
	int r, p,i,n=1000000000;
	double sum=0,sum1=0,sum2=0,h1,h2,t,a=-2.0,b=4.0,c = 0.0, d = 3.0;
	
	MPI_Status st;
	MPI_Init(&argc,&argv);
	MPI_Comm_rank(MPI_COMM_WORLD,&r);
	MPI_Comm_size(MPI_COMM_WORLD,&p);
	if (r==0) 
		t=MPI_Wtime();
	MPI_Barrier(MPI_COMM_WORLD);

	
	h1=(b-a)/n;
	for(i=r;i<=n;i+=p)
		sum1+=f(a+(i+0.5)*h1);
	sum1*=h1;
	
	
	
	h2=(d-c)/n;
	for(i=r;i<=n;i+=p)
		sum2+=g(c+(i+0.5)*h2);
	sum2*=h2;
	
	
	if (r!=0)
	{	
		MPI_Send(&sum1,1,MPI_DOUBLE,0,0,MPI_COMM_WORLD);
		MPI_Send(&sum2,1,MPI_DOUBLE,0,1,MPI_COMM_WORLD);
	}
	if (r==0)
	{
		double s;
		for(i=1;i<p;i++)
		{
			if(i>=p)
				break;
			MPI_Recv(&s,1,MPI_DOUBLE,i,0,MPI_COMM_WORLD,&st);
			sum1+=s;
			MPI_Recv(&s,1,MPI_DOUBLE,i,1,MPI_COMM_WORLD,&st);
			sum2+=s;
		}
		t=MPI_Wtime()-t;
		printf("Значение интеграла=%lf,\n время счёта=%f\n",sum1+sum2, t);
	}
	MPI_Finalize();
	
	return 0;
}
