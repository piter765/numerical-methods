#include <iostream>
#include <cmath>
using namespace std;

double f1(double x, double y) {
	return pow(x, 2) + y;
}
double f2(double x, double y) {
	return x + y;
}

double euler( double y0, double x, int N, double(*f)(double, double)) { //double a, double b
	cout << "Warunek poczatkowy: " << "y0= " << y0 << endl;
	double h = (x - 0) / N;
	double* arrayOfX = new double[N+1];
	arrayOfX[0] = 0;
	double* arrayOfY = new double[N + 1];
	arrayOfY[0] = y0;
	for (int i = 0; i < N; i++) {
		//cout << "Krok obliczen: " << i + 1 << endl;
		arrayOfX[i + 1] = arrayOfX[i] + h;
		arrayOfY[i + 1] = arrayOfY[i] + h * f(arrayOfX[i], arrayOfY[i]);
		//cout << "x1= " << arrayOfX[i + 1] << endl;
		//cout << "y1= " << arrayOfY[i + 1] << endl;
	}
	delete[] arrayOfX, arrayOfY;
	return arrayOfY[N];
 }
//0.707
double rk2pomocnicza(double x, double y0, double h, int N, double(*f)(double, double)) {
		double k1 = f(x, y0);
		double k2 = f(x + h, y0 + h * k1);
		return 0.5 * (k1 + k2);
}
double RK2(double y0, double x, double h, int N, double(*f)(double, double)) {
	double* arrayOfX = new double[N + 1];
	arrayOfX[0] = 0;
	double* arrayOfY = new double[N + 1];
	arrayOfY[0] = y0;


	for (int i = 0; i < N; i++) {
		//cout << "Krok obliczen: " << i + 1 << endl;
		arrayOfX[i + 1] = arrayOfX[i] + h;
		arrayOfY[i + 1] = arrayOfY[i] + h * rk2pomocnicza(arrayOfX[i], arrayOfY[i],h, N, f);
		//cout << "x1= " << arrayOfX[i + 1] << endl;
		//cout << "y1= " << arrayOfY[i + 1] << endl;
	}

	delete[] arrayOfX, arrayOfY;
	return arrayOfY[N];
}
double rk4pomocnicza(double x, double y0, double h, double(*f)(double,double), int N) {
	double k1 = f(x, y0);
	double k2 = f(x + 0.5*h, y0 + 0.5*h * k1);
	double k3 = f(x + 0.5*h, y0 + 0.5*h* k2);
	double k4 = f(x + h, y0 + h * k3);
	return  (k1 + 2*k2 + 2 * k3 + k4)/6;
}
double RK4(double y0, double x, double h, int N, double(*f)(double, double)) {
	double* arrayOfX = new double[N + 1];
	arrayOfX[0] = 0;
	double* arrayOfY = new double[N + 1];
	arrayOfY[0] = y0;


	for (int i = 0; i < N; i++) {
		//cout << "Krok obliczen: " << i + 1 << endl;
		arrayOfX[i + 1] = arrayOfX[i] + h;
		arrayOfY[i + 1] = arrayOfY[i] + h * rk4pomocnicza(arrayOfX[i], arrayOfY[i], h, f, N);
		//cout << "x1= " << arrayOfX[i + 1] << endl;
		//cout << "y1= " << arrayOfY[i + 1] << endl;
	}

	delete[] arrayOfX, arrayOfY;
	return arrayOfY[N];
}

int main() {
	double y0 = 0.1; double x = 1; double a = 0; double b = 0.3; int N = 10;
	double h = (x - 0) / N;
	cout << "Dla x^2 + y: " << endl;
	cout << "Wynik z eulera: " << euler(y0, x, N, f1) << endl;
	cout << "Wynik z RK2: " << RK2(y0, x, h,N, f1) << endl;
	cout << "Wynik z RK4: " << RK4(y0, x, h, N, f1) << endl;

	cout << "Dla x + y: " << endl;

	cout << "Wynik z eulera: " << euler(y0, x, N, f2) << endl;
	cout << "Wynik z RK2: " << RK2(y0, x, h, N, f2) << endl;
	cout << "Wynik z RK4: " << RK4(y0, x, h, N,f2) << endl;

}