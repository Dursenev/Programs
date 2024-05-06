#include <iostream>
#include <vector>
#include <cmath>
#include<iomanip>

using namespace std;

double U_0 (double x)
{
    return 0;
}

double U_l (double x)
{
    return 0;
}

double U_x(double x)
{
    return 0;
}

double f(double x, double t)
{
    return 1;
}

double sigma(double xs, double l, double h)
{
    return (24 * pow(sin((M_PI * xs) / (2 * l)), 2)) / (h * h * (5 + cos(M_PI * xs / l)));
}

vector<double> Uk_solve(double t, vector <double> x, int solve, double l, double h, vector <double> F, vector <double> D)
{
    vector <double> Uk;
    for (int k=0; k < solve; k++)
    {
        Uk.push_back(0);
        for(int s=0; s < solve; s++)
        {
            Uk[k] += D[s] * sin((M_PI * (s + 1) * x[k+1]) / l) * exp(-sigma(x[s+1], l, h) * t);
        }
        Uk[k] += F[k];
    }
    return Uk;
}



vector<double> Gaus(vector<vector<double>> Matrix, vector<double> x, int solve)
{
    float temp,s;
    int i,j,k;

    	for(j=0; j < solve - 1; j++)
	{
		for(i=j+1; i<solve; i++)
		{
			temp=Matrix[i][j] / Matrix[j][j];

			for(k=0; k < solve + 1; k++)
				Matrix[i][k] -= Matrix[j][k] * temp;
		}
	}

	for(i=solve-1; i>=0; i--)
	{
		s=0;
		for(j=i+1; j<solve; j++)
		s += Matrix[i][j]*x[j];
		x[i]=(Matrix[i][solve]-s)/Matrix[i][i];
	}

     return x;
}

vector <double> system_solve (double l, int fragment, double h, int solve, double t, vector <double> Uk)
{
    int row = solve , col = solve;
    vector<vector<double> > A, Matrix_D;
    vector<double> F, x, D;

    for (int i=0; i<=fragment; i++)
    {
        x.push_back(h * i);
    }

    for(int i = 0; i < row; i++)
    {
        F.push_back((5.0 / 6.0) * f(x[i+1] ,t) + (1.0 / 12.0) * (f(x[i] ,t) + f(x[i+2], t)));

        if(i == 0)
        {
            F[i] -= U_0(x[i+1]) * (-1 / (h * h));
        }

        if(i == row - 1)
        {
            F[i] -= U_l(x[i+1]) * (-1 / (h * h));
        }

        vector <double> Aarr;

        for(size_t j = 0; j < col; j++)
            Aarr.push_back(0);

        A.push_back(vector<double>(Aarr));
        Matrix_D.push_back(vector<double>(Aarr));
    }

    
    for (int i=0; i < row; i++)
    {
        for (int j=0; j < col; j++)
        {
            if(i == j)
            {
                A[i][j] = -2 * ( -1 / (h * h));
                continue;
            }

            if((i-1 == j)||(i+1 == j))
            {
                A[i][j] = 1 * ( -1 / (h * h));
                continue;
            }
        }
    }
        
    for (int i=0; i< row; i++)
    {
        A[i].push_back(F[i]);
    }

    F = Gaus(A,F,solve);

     for (int k=0; k < solve; k++)
    {
        D.push_back(0);
        for(int s=0; s < solve; s++)
        {
            Matrix_D[k][s] = sin((M_PI * (s + 1) * x[k+1]) / l) ;
        }
        Matrix_D[k].push_back(U_x(x[k+1]) - F[k]);
    }
    
    D = Gaus(Matrix_D,D,solve);
    Uk = Uk_solve(t, x, solve, l, h, F,D);
    
    return Uk;
}


int main()
{
    vector <double> Uk;
    double l = M_PI, T=1,timeStep = 0.1;
    int fragment = 4 ;
    double h = l / fragment;
    int solve = fragment - 1;

    for (double t=0;t<=T;t+=timeStep)
    {
        Uk = system_solve(l, fragment, h, solve, t, Uk);
        cout<< "\n t = " << t << "\n";
        for (int i=0; i<solve; i++)
        {
            cout << "U[" << (i + 1)*h << "] = " << Uk[i] << "\n";
        }
    }
    
    return 0;
}
