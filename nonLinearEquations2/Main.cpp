#include <iostream>
#include <cmath>

using namespace std;

double f1(double x) {
	return cos(pow(x, 3) - 2 * x);
}
double f2(double x) {
	return -5 * pow(x, 3) + 9 * x + 4;
}


double f3(double x) {
	return -6 * pow(x, 3) + 3 * x + 6;
}


void bisekcja(double a, double b,double e, double(*f)(double)) {
	double a1 = a;
	double b1 = b;
	int i = 1;
	for (;;) {
		double x0 = (a1 + b1) / 2;
		cout << i << ".\t" << a1 << "\t" << b1 <<"\t" << f(a1) << "\t" << f(b1) << "\t" << x0 << "\t" << f(x0) << "\t" << f(a1) * f(x0) << endl;
		if (abs(f(x0)) < e) {
			cout << "f mniejsze od epsilon\n";
			break;
		}
		else {
			if (f(a1) * f(x0) < 0) {
				b1 = x0;
				i++;
			}
			else {
				a1 = x0;
				i++;
			}
		}
	}
}
void metoda_falszywej_linii(double a, double b, double e, double(*f)(double)) {
	double a1 = a;
	double b1 = b;
	int i = 1;
	for (;;) {
		double x0 = a1 - (f(a1) * (b1 - a1)) / (f(b1) - f(a1));
		cout << i << ".\t" << a1 << "\t" << b1 << "\t" << f(a1) << "\t" << f(b1) << "\t" << x0 << "\t" << f(x0) << "\t" << f(a1) * f(x0) << endl;
		if (abs(f(x0)) < e) {
			cout << "f mniejsze od epsilon\n";
			break;
		}
		else {
			if (f(x0) * f(a1) < 0) {
				b1 = x0;
				i++;
			}
			else {
				a1 = x0;
				i++;
			}
		}
	}
}
int main() {
	cout << "DLA funkcji cos cos tam" << endl;
	cout << "\ta\t" << "b\t" << "f(a)\t f(b)\t x0\t f(x0)\t f(a)*f(x0)" << endl;
	bisekcja(0, 2, 0.01, f1);

	cout << "\ta\t" << "b\t" << "f(a)\t f(b)\t x0\t f(x0)\t f(a)*f(x0)" << endl;
	metoda_falszywej_linii(0, 2, 0.01, f1);

	cout << endl;
	cout << "DLA - 5 x ^ 3 + 9 * x + 4: " << endl;
	cout << "\ta\t" << "b\t" << "f(a)\t f(b)\t x0\t f(x0)\t f(a)*f(x0)" << endl;
	bisekcja(0, 2, 0.01, f1);

	cout << "\ta\t" << "b\t" << "f(a)\t f(b)\t x0\t f(x0)\t f(a)*f(x0)" << endl;
	metoda_falszywej_linii(0, 2, 0.01, f2);

	cout << endl;
	cout << "DLA -6 x^3 + 3 * x + 6: " << endl;
	cout << "\ta\t" << "b\t" << "f(a)\t f(b)\t x0\t f(x0)\t f(a)*f(x0)" << endl;
	bisekcja(0, 2, 0.01, f1);
	cout << "\ta\t" << "b\t" << "f(a)\t f(b)\t x0\t f(x0)\t f(a)*f(x0)" << endl;
	metoda_falszywej_linii(0, 2, 0.01, f3);
}
