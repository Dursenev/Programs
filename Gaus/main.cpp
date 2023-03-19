#include <iostream>
#include <cmath>
#include <vector>

using namespace std;

int MaxColum(vector <vector <double>>& Matr, int colum)
{
	int MaxIndex = colum;
	for (int i=colum; i < Matr.size(); i++)
	{
		if((abs(Matr[MaxIndex][colum])) < (abs(Matr[i][colum])))
			MaxIndex = i;
	}
	cout <<"В столбце "<< colum <<" максимальный по модулю элемент "<< Matr[MaxIndex][colum] <<endl;
	return MaxIndex;
}

void Gauss(vector <vector <double>>& Matr, vector <double>& F)
{
	double zero = 0.0000000000001;
	bool flag = true;
	int MaxIndex;
	double Max;
	double denominator;
	
	for (int i=0; i<Matr.size(); i++)
	{
		MaxIndex = MaxColum(Matr, i);
		Max = Matr[MaxIndex][i];
		if(abs(Max) < zero)
		{
			cout << "Матрица вырожденная." << endl;
			flag = false;
			break;
		}
		else if(Max != i)
		{
			for (int k=0; k<Matr.size(); k++)
			{
				swap(Matr[i][k], Matr[MaxIndex][k]);
				Matr[i][k]/=Max;
			}	
			swap(F[i], F[MaxIndex]);
			F[i]/=Max;
		}
		else 
		{
			for (int k=0; k<Matr.size(); k++)
			{
				Matr[i][k]/=Max;
			}	
			F[i]/=Max;
		}
		if (flag)
		{
			for (int j = 0; j < Matr.size(); j++) 
			{
                		if (j != i) 
                		{
                    			denominator = Matr[j][i];
                    			for (int k = i; k < Matr.size(); k++) 
                    			{
                       				 Matr[j][k] -= Matr[i][k] * denominator;
                    			}
                    			F[j] -= F[i] * denominator;
                		}		
            		}
		}
	}
}

int main()
{
int size;
cout << "Введите размерность матрицы (N x N): ";
cin >> size;
vector <vector <double>> Matr(size, vector<double>(size));
vector <double> F (size);
for(int i=0; i<Matr.size(); i++)
{
	for(int j=0; j<Matr.size(); j++)
	{
	cout <<"Matr ["<< i <<"]["<< j <<"] = ";
	cin >> Matr[i][j];
	}
}
for (int i =0; i< F.size(); i++)
{
	cout <<"F ["<< i << "] = ";
	cin >> F[i];
}
Gauss(Matr,F);
for(int i=0; i<Matr.size(); i++)
{
	for(int j=0; j<Matr.size(); j++)
		cout<< Matr[i][j]<< "\t";
	cout <<"| "<<F[i] << endl;
}

return 0;
}
//4 3 2 5 6 7 8 9 0 6 5 4
