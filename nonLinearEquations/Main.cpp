#include <iostream>
#include <cmath>
using namespace std;


double f1(double x) {
	return (-1 * pow(x, 3) + 10 * x + 5);
}
double f1prim(double x) {
	return -3 * pow(x, 2) + 10;
}

double f2(double x) {
	return -5 * pow(x, 3) + 9 * x + 4;
}
double f2prim(double x) {
	return -15 * x * x + 9;
}

double f3(double x) {
	return -6 * pow(x, 3) + 3 * x + 6;
}
double f3prim(double x) {
	return -18 * x * x + 3;
}
void metoda_stycznych(double x0,int N, double(*f)(double), double (*fprim)(double)) {

	double* arrayOfX = new double[N+1];
	arrayOfX[0] = x0;
	/*double* arrayOfY = new double[a - b + 1];
	arrayOfY[0] = y0;*/
	for (int i = 0; i < N; i++) {
		arrayOfX[i + 1] = arrayOfX[i] - (f(arrayOfX[i]) / fprim(arrayOfX[i]));
		cout << arrayOfX[i + 1] << endl;
	}
	delete[]arrayOfX;

}
void metoda_siecznych(double x0, int N, double(*f)(double)) {
	double xkminusOne = x0 - 0.1;
	double* arrayOfX = new double[N + 2];
	arrayOfX[0] = xkminusOne;
	arrayOfX[1] = x0;
	/*double* arrayOfY = new double[a - b + 1];
	arrayOfY[0] = y0;*/
	for (int i = 2; i < N+2; i++) {
		arrayOfX[i] = arrayOfX[i-1] - f(arrayOfX[i-1]) * (arrayOfX[i-1] - arrayOfX[i-2]) / (f(arrayOfX[i-1])-f(arrayOfX[i - 2]));
		//cout << "wartosc funkcji dla iteracji numer " << i << ":" << f(arrayOfX[i]) << endl;
		cout << arrayOfX[i] << endl;
	}

}

int main() {
	cout << "-1 x^3 + 10 * x + 5: " << endl;
	metoda_stycznych(6, 5, f1, f1prim);
	cout << endl;
	metoda_siecznych(6, 5, f1);
	cout << endl;

	cout << "-5 x^3 + 9 * x + 4: " << endl;
	metoda_stycznych(2, 5, f2, f2prim);
	cout << endl;
	metoda_siecznych(2, 5, f2);
	cout << endl;

	cout << "-6 x^3 + 3 * x + 6: " << endl;
	metoda_stycznych(2, 5, f3, f3prim);
	cout << endl;
	metoda_siecznych(2, 5, f3);
	cout << endl;
}