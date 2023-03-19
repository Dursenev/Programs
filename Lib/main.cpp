#include "library.h"
#include <iostream>
#include <cmath>
#include <stdlib.h>
using namespace std;

int main()
{
double eps, ** a, * b, * x, * p, *x1;
	int n, i, j;
	cout << "razmer matr: ";
	cin >> n;
	cout << "Eps: ";
	cin >> eps;
	cout << "matr A: ";
	a = new double* [n];
		for (int i = 0; i < n; i++)
		{
			a[i] = new double[n];
		}
		for (i = 0; i < n; i++)
			for (j = 0; j < n; j++)
			{
				cout << "A[" << i << "][" << j << "] = ";
				cin >> a[i][j];
			}
		cout << "A: " << endl;
		for (i = 0; i < n; i++)
		{
			for (j = 0; j < n; j++)
				cout << a[i][j] << " ";
			cout << endl;
		}
		cout << "svobodnii chleni: " << endl;
		b = new double[n];
		x = new double[n];
		p = new double[n];
		for (i = 0; i < n; i++)
		{
			cout << "B[" << i + 1 << "] = ";
			cin >> b[i];
		}

		cout << endl;
		cout << "method Zeldel: \n" ;
		Zeidal(a,b,x,p,eps,n);
		cout << endl;
		cout << "method simple iteration: \n" ;
		x1 = new double[n];
		x1 = iter(a, b, n);

		for (int i = 0; i < n; i++)
		{
			cout <<"X"<< i+1<<"= " << x1[i] << "\t";
		}
		cout << endl;
		return 0;
}
