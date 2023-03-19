#include "library.h"
#include <iostream>
#include <cmath>

using namespace std;

bool converge(double *xk, double *xkp, int n, double eps)
{
	double norm = 0;
	for (int i = 0; i < n; i++)
		norm += (xk[i] - xkp[i]) * (xk[i] - xkp[i]);
	return (sqrt(norm) < eps);
}

double okr(double x, double eps)
{
	int i = 0;
	double neweps = eps;
	while (neweps < 1)
	{
		i++;
		neweps *= 10;
	}
	int okr = pow(double(10), i);
	x = int(x * okr + 0.5) / double(okr);

	return x;
}

bool diagonal(double **a, int n)
{
	int i, j, k = 1;
	double sum;
	for (i = 0; i < n; i++) {
		sum = 0;
		for (j = 0; j < n; j++) sum += abs(a[i][j]);
		sum -= abs(a[i][i]);
		if (sum > abs(a[i][i]))
		{
			k = 0;
			cout << a[i][i] << " < " << sum << endl;
		}
		else
		{
			cout << a[i][i] << " > " << sum << endl;
		}


	}

	return (k == 1);

}

void Zeidal(double** a, double* b, double* x, double* p, double eps, int n)
{
	cout << "Diagonalnie preobrazovania: " << endl;
	if (diagonal(a, n)) {
		do
		{
			for (int i = 0; i < n; i++)
				p[i] = x[i];
			for (int i = 0; i < n; i++)
			{
				double var = 0;
				for (int j = 0; j < n; j++)
					if (j != i) var += (a[i][j] * x[j]);

				x[i] = (b[i] - var) / a[i][i];
			}

		} while (!converge(x, p, n, eps));



		cout << "Reshenie sistemi:"  << endl;
		for (int i = 0; i < n; i++) cout << "x" << i << " = " << okr(x[i], eps) << "" << endl;
	}
	else {
		cout << "Ne vipolnyaetsya preobrazovanie" << endl;
	}
}
double* iter(double** a, double* y, int n)
{
	double* res = new double[n];
	int i, j;


	for (i = 0; i < n; i++)
	{
		res[i] = y[i] / a[i][i];
	}

	double eps = 0.1;
	double* Xn = new double[n];

	do {
		for (i = 0; i < n; i++) {
			Xn[i] = y[i] / a[i][i];
			for (j = 0; j < n; j++) {
				if (i == j)
					continue;
				else {
					Xn[i] -= a[i][j] / a[i][i] * res[j];
				}
			}
		}

		bool flag = true;
		for (i = 0; i < n - 1; i++) {
			if (abs(Xn[i] - res[i]) > eps) {
				flag = false;
				break;
			}
		}

		for (i = 0; i < n; i++) {
			res[i] = Xn[i];
		}

		if (flag)
			break;
	} while (1);

	return res;
}
