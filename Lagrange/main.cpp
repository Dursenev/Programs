#include <iostream>
#include <cmath>

using namespace std;

double Lagrange(double *X, double *Y, int n, double x)
{
    double l,L=0;
    for (int i=0; i<n; i++)
    {
        l=1;
        for(int j=0; j<n; j++)
             if (j != i)
             {
            	l *= (x-X[j])/(X[i]-X[j]);
            }
        L+=Y[i]*l;
    }
    return(L);
}

double Omega(double *X, double a, int n)
{
    double omega = 1;
    for (int i=0; i<n; i++)
    {
        omega *=(a-X[i]);
    }
    return(omega);
}

double fact(int n)
{
    double x = 1;
    for (int i = 2; i<=n; i++ )
        x*=i;
    return (x);
}

int main()
{
    double *X, *Y, a , Lg, M, err;
    int n;
    cout << "Введите количество узлов: ";
    cin >> n;
    X = new double[n+1];
    Y = new double[n+1];
    for (int i=0; i<n+1;i++)
    {
        cout <<"x["<<i<<"]= ";
        cin>>X[i];
        Y[i]=sin(X[i]);
        cout << "y["<<i<<"]= " << Y[i] << endl;
        
    }
     cout << "Введите значение точки а: ";
     cin >> a;
     Lg = Lagrange(X,Y,n+1,a);
     cout << "L(a) = " << Lg << endl;
     cout << "Введите константу для оценки погрешности M: ";
     cin >> M;
     cout << "Омега(a) равна: " << Omega(X, a, n+1) << endl;
    err = abs((M * Omega(X, a, n+1))/fact(n+1));
    cout << "Ошибка погрешности равна: " << err << endl;
    return 0;

    

}
