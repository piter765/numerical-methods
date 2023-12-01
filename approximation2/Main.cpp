#include <iostream>
#include <cmath>
using namespace std;

int factorial(unsigned int n) {
    if (n == 0)
        return 1;
    else
        return n * factorial(n - 1);
}


double dwumianNewtona3(int n, int k) {
    return factorial(n) / (factorial(k) * factorial(n - k));
}


double wielomianCzynnikowy(double x, int n) {
    double wynik = 1;
    for (int j = 0; j <= n - 1; j++) {
        wynik *= (x - j);
    }
    return wynik;
}

double Fk(int k, double q, int n) {
    double wynik = 0;
    if (q == 0) return 1;
    for (int s = 0; s <= k; s++) {
        wynik += pow(-1, s) * dwumianNewtona3(k, s) * dwumianNewtona3(k + s, s) * wielomianCzynnikowy(q,s)/ wielomianCzynnikowy(n,s);
    }
    return wynik;
}

double ck(int n , int k) {
    double wynik = 0;
    for( int i = 0; i <= n; i++) {
        wynik += pow(Fk(k, i, n), 2);
   }
    return wynik;
}
double sk(int n, int k, double** wezly) {
    double wynik = 0;
    for (int i = 0; i <= n; i++) {
        wynik += wezly[i][1]* Fk(k, i, n);
    }  
    return wynik;
}


void aproksymacja2() {

    //(1, 2), (2, 4), (3, 3), (4, 5), (5, 6), (6, 9), (7, 11), (8, 11)
    int n= 8; //liczba wezlow

    double wezly[][2] = { {1, 2}, {2, 4}, {3, 3}, {4, 5}, {5, 6}, {6, 9}, {7, 11}, {8, 11} };
    double** wezlyy = new double* [8];
    for (int i = 0; i < 8; i++) {
        wezlyy[i] = new double[2];
    }
    for (int i = 0; i < 8; i++) {
        wezlyy[i][0] = wezly[i][0];
        wezlyy[i][1] = wezly[i][1];
    }
    /*for (int i = 0; i < n; i++) {
        for (int j = 0; j < 2; j++) {
            cout << wezlyy[i][j] << " ";
        }
        cout << endl;
    }*/
    int waga = 1;
    int m = 2; //stopien wielomianu
    double x = 0; // podany x przez uzytkownika
    double h = wezly[1][0] - wezly[0][0];


    cout << "Liczba wezlow: " << n << endl;
    cout << "Wspolczynniki:" << endl;
    for (int k = 0; k <= m; k++) {
        cout << "ck" << k << ": " << ck(n - 1, k) << endl;
        cout << "sk" << k << ": " << sk(n - 1, k, wezlyy) << endl;
    }
    cout << " Wyniki: " << endl;
 
    for (int i = 0; i < n; i++) {    //wzor piaty
        double q = (wezly[i][0] - wezly[0][0]) / h;
        double ym = 0;
        for (int k = 0; k <= m; k++) {
            ym += sk(n-1, k, wezlyy) / ck(n-1, k) * Fk(k, q, n-1);
        }
        cout << " wynik dla x= " << wezly[i][0] << " i y=" << wezly[0][i] << " to " << ym << endl;
    }
    cout << "Podaj x: (9 by wyjsc)  ";
    while (cin >> x) {
        if (x == 9) break;
        double q = (x - wezly[0][0]) / h;
        double ym = 0;
        for (int k = 0; k <= m; k++) {
            ym += sk(n - 1, k, wezlyy) / ck(n - 1, k) * Fk(k, q, n - 1);
        }
        cout << "wynik dla x=" << x << " " << ym << endl;
        cout << "Podaj x: (9 by wyjsc)  ";
    }

}

int main() {
    aproksymacja2();
}