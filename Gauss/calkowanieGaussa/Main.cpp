#include <iostream>
#include <cmath>
#include <fstream>
using namespace std;


//tablice do gaussa
double tab2[] = {1.0, 1.0};
double tab3[] = { 5.0/9.0,8.0/9.0,5.0/9.0};
double tab4[] = { 1.0/36.*(18.-sqrt(30.)),
                       1./36.*(18.+sqrt(30.)),
                       1./36.*(18.+sqrt(30.)),
                       1./36.*(18.-sqrt(30.)) };

double tabx2[] = {-sqrt(3.)/3.,sqrt(3.)/3.};
double tabx3[] = {-sqrt(3./5.), 0.,sqrt(3./5.)};
double tabx4[] = {-1./35.*(sqrt(525.+70.*sqrt(30.))),
                -1./35.*(sqrt(525.-70.*sqrt(30.))),
                1./35.*(sqrt(525.-70.*sqrt(30.))),
                1./35.*(sqrt(525.+70.*sqrt(30.))) };

void gauss_lagendre(double a, double b, int n, double(*f)(double)) {
    double wynik = 0.0;
    double t = 0.0;
    if (n == 2) {
        for (int i = 0; i < n; i++) {
            t = (a + b) / 2. + (b - a) / 2. * tabx2[i];
            wynik += tab2[i] * f(t);
        }
    }
    else if (n == 3) {
        for (int i = 0; i < n; i++) {
            t = (a + b) / 2. + (b - a) / 2. * tabx3[i];
            wynik += tab3[i] * f(t);
        }
    }
    else if (n == 4) {
        for (int i = 0; i < n; i++) {
            t = (a + b) / 2. + (b - a) / 2. * tabx4[i];
            wynik += tab4[i] * f(t);
        }
    }
    wynik *= (b - a) / 2.;
    cout << "Metoda Gaussa " << wynik << endl;

}

double metoda_prostokatow(double a, double b, int n, double (*f)(double));
double metoda_trapezow(double a, double b, int n, double (*f)(double));
double metoda_simpsona(double a, double b, int n, double (*f)(double));

double wielomian(double x) {
    return (pow(x, 2) + 2 * x + 5);
}


int main() {






    double a = 0.5;
    double b = 2.5;
    int n = 4;
    cout << "sin" << endl;
    cout << "Wzor calkowanej funkcji: sin(x)" << endl;
    cout << "Przedzial calkowania <" << a << "," << b << ">" << endl;
    cout << "Liczba przedzialow " << n << endl;
    cout << " Metoda prostokatow " << metoda_prostokatow(0.5, 2.5, 4, sin) << endl;
    cout << "Metoda trapezow " << metoda_trapezow(0.5, 2.5, 4, sin) << endl;
    cout << "Metoda simpsona " << metoda_simpsona(0.5, 2.5, 4, sin) << endl;
    gauss_lagendre(0.5, 2.5, 3, sin);

    b = 5;
    cout << "Wielomian" << endl;
    cout << "Wzor calkowanej funkcji: x^2 + 2x + 5" << endl;
    cout << "Przedzial calkowania <" << a << "," << b << ">" << endl;
    cout << "Liczba przedzialow " << n << endl;
    cout << " Metoda prostokatow " << metoda_prostokatow(a, b, 4, wielomian) << endl;
    cout << "Metoda trapezow " << metoda_trapezow(a, b, 4, wielomian) << endl;
    cout << "Metoda simpsona " << metoda_simpsona(a, b, 4, wielomian) << endl;
    gauss_lagendre(0.5, 5.0, 3, wielomian);

    b = 5;
    cout << "exp" << endl;
    cout << "Wzor calkowanej funkcji: exp(x)" << endl;
    cout << "Przedzial calkowania <" << a << "," << b << ">" << endl;
    cout << "Liczba przedzialow " << n << endl;
    cout << " Metoda prostokatow " << metoda_prostokatow(a, b, 4, exp) << endl;
    cout << "Metoda trapezow " << metoda_trapezow(a, b, 4, exp) << endl;
    cout << "Metoda simpsona " << metoda_simpsona(a, b, 4, exp) << endl;
    gauss_lagendre(0.5, 5.0, 3, exp);
    //czesc zadania drugiego

    /*std::fstream myfile("wynikiSin.txt", std::ios_base::out);
    int n = 1;
    double wynik;
    for (int i = 0; i < 20; i++) {
    myfile << n;
    n++;
    wynik = metoda_prostokatow(0.5, 2.5, n, sin);
    myfile << wynik;
    wynik = metoda_trapezow(0.5, 2.5, n, sin);
    myfile << wynik;
    wynik = metoda_simpsona(0.5, 2.5, n, sin);
    myfile << wynik;
    }*/



}

double metoda_prostokatow(double a, double b, int n, double (*f)(double)) {
    double s = (b - a) / n;
    double* h = new double[n];
    double hAll = 0;
    for (int i = 0; i < n; i++) {
        double funcArg = a + s * i + s / 2;
        h[i - 1] = f(funcArg);
        hAll += h[i - 1];
    }

    double result = s * hAll;

    return result;
}
double metoda_trapezow(double a, double b, int n, double (*f)(double)) {
    double s = (b - a) / n;
    double result = 0;
    for (int i = 0; i < n; i++) {
        result += ((a + s * (i + 1) - (a + s * i)) / 2.0) * (f(a + s * i) + f(a + s * (i + 1)));
    }
    return result;
}
double metoda_simpsona(double a, double b, int n, double (*f)(double)) {
    double result = 0;
    double s = (b - a) / n;
    for (int i = 0; i < n; i++) {
        result += (((a + s * (i + 1)) - (a + s * i)) / 6) * (f(a + s * i) + 4 * f((a + s * (i + 1) + a + s * i) / 2) + f(a + s * (i + 1)));
    }

    return result;
}