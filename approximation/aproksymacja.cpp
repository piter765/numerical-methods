#include <iostream>
#include <fstream>
#include <cmath>
using namespace std;

double fi(double &x, double k) {
    return pow(x, k);
}


void aproksymacja() {

    //(1, 2), (2, 4), (3, 3), (4, 5), (5, 6), (6, 9), (7, 11), (8, 11)
    int size = 8; //m
    double wezly[][2] = { {1, 2}, {2, 4}, {3, 3}, {4, 5}, {5, 6}, {6, 9}, {7, 11}, {8, 11} };
    int waga = 1;
    int n = 3; //stopien wielomianu

    //macierz rozszerzona wiec n+1
    double** gF = new double* [n];
    for (int i = 0; i < n; i++) {
        gF[i] = new double[n+1];
    }
    for (int k = 0; k < n; k++) {
        for (int j = 0; j < n+1; j++) {
            gF[k][j] = 0;
        }
    }
    for (int k = 0; k < n; k++) {
        for (int j = 0; j < n+1; j++) {
            for (int i = 0; i <= size-1; i++) { // size - 1 = m
                //wezly[i][0] - x
                //wezly[i][1] - y
                if( j != n)
                    gF[k][j] += fi(wezly[i][0], k) * fi(wezly[i][0], j) * waga;   
                else if (j == n) {
                    gF[k][j] += fi(wezly[i][0], k) * wezly[i][1] * waga;
                }
            }
        }
       
    }
    cout << "Liczba wezlow: " << size << endl;

    //wypisanie macierzy gF
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n+1; j++) {
            if (j != n) {
                cout << "g" << i << j << ": " << gF[i][j] << "  ";
            }
            else if (j == n) {
                cout << "F" << i << ": " << gF[i][j] << "  ";
            }
        }
        cout << "\n";
    }
    
    //metoda Gaussa 
    size = n;
    double m = 0; int k = 0;
    for (int i = 0; i < size; i++) {

        for (int z = i; z < size - 1; z++) {

            if (gF[i][i] != 0) {
                m = gF[z + 1][i] / gF[i][i];

                for (int j = i; j < size + 1; j++) {

                    gF[z + 1][j] -= gF[i][j] * m;

                }
            }
            else {
                cout << "0 na przekatnej " << endl;
                break;
            }
        }

    }
    cout << endl;
    double x = 0.0, suma = 0.0;
    double* tabx = new double[n]; // tu zmienilem z size - 1 na size
    tabx[size - 1] = gF[size - 1][size] / gF[size - 1][size - 1];
    for (int i = size - 2; i >= 0; i--) {
        suma = 0;
        for (int j = i + 1; j < size; j++) {
            suma += gF[i][j] * tabx[j];
        }
        tabx[i] = (gF[i][size] - suma) / gF[i][i];

    }
    for (int i = 0; i < size; i++) {
        cout << "Wartosci wspolczynnikow: a" << i << "=" << tabx[i] << endl;
    }
    double* wyniki = new double[size];
    
    cout << "wyniki funkcji w punktach: " << endl;
    for (int i = 0; i < 8; i++) {
        wyniki[i] = 0; 
        for (int j = 0; j < n; j++) {
            wyniki[i] += tabx[j] * fi(wezly[i][0], j);
        }
        cout << "wynik dla x" << wezly[i][0] << ": " << wyniki[i] << endl;
    }
    delete[] tabx;
    for (int i = 0; i < n; i++) {
        delete[] gF[i];
    }
    delete[] gF;
    delete[] wyniki;
}

int main() {
    aproksymacja();

    
}