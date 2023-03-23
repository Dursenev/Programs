#include <iostream>
#include <mpreal.h>

using namespace mpfr;
using namespace std;

mpreal Fibonacci(mpreal number)
{
	mpreal Fib;
	Fib = (pow((1+sqrt(5))/2,number)-pow((1-sqrt(5))/2,number))/sqrt(5);
	return Fib;
}

mpreal polynom (mpreal x, mpreal y)
{
	mpreal F;
	F = 1/(pow(y,6)-3*x*pow(y,5)+5*pow(x,3)*pow(y,3)-3*pow(x,5)*y-pow(x,6));
	return F;
}

int main()
{
	mpfr_set_default_prec(256);
	cout <<"точность вычисления = "<<mpfr_get_default_prec()<<endl;
	mpreal y,x,polyn;
	cout << "Введите номер числа Фибоначчи для первого числа (45) :";
	cin >> x;
	cout << "Введите номер числа Фибоначчи для второго числа (46) :";
	cin >> y;
	polyn = polynom(Fibonacci(x),Fibonacci(y));
	cout.precision(35);
	cout << "F(x,y) = " << polyn << endl;
	return 0;
}

