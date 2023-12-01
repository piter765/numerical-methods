#include <iostream>
#include <fstream>

using namespace std;

void showArray(double** arr, int size) {
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            std::cout << arr[i][j] << "\t";
        }
        std::cout << "\n";
    }
    std::cout << endl;
}

void doolittle(double** A, int size) {
    double** L = new double* [size];
    double** U = new double* [size];
    for (int i = 0; i < size; i++) {
        L[i] = new double[size];
        U[i] = new double[size];
    }
    //wyzerowanie obu macierzy L i U
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            L[i][j] = 0;
            U[i][j] = 0;
            if (i == j) L[i][j] = 1;
        }
    }
    double suma;
    for (int i = 1; i <= size; i++) {
        for (int j = 1; j <= size; j++) { 
            suma = 0.0;
            for (int k = 1; k <= i - 1; k++) {
                suma += L[i-1][k-1] * U[k-1][j-1];
            }
            if (i <= j) {
                U[i-1][j-1] = A[i-1][j-1] - suma;
            }
            else {
                L[i-1][j-1] = 1 / U[j-1][j-1] * (A[i-1][j-1] - suma);
            }
            
        }
    }
    std::cout << "Macierz U: " << endl;
    showArray(U, size);
    std::cout << "Macierz L: " << endl;
    showArray(L, size);

    //wektor Y
    double* Y = new double[size];

    Y[0] = A[0][size];
    for (int i = 1; i < size; i++) {
        suma = 0;
        for (int j = 0; j <= i - 1; j++) {
            suma += L[i][j] * Y[j];
        }
        Y[i] = A[i][size] - suma;
    }
    std::cout << "Wektor Y:" << endl;
    for (int i = 0; i < size; i++) {
        std::cout << Y[i] << "  ";
    }
    std::cout << endl;

    //Wynik
    double* X = new double[size];

    X[size-1] = Y[size-1] / U[size-1][size-1];
    for (int i = size - 2; i >= 0; i--) {
        suma = 0;
        for (int j = i + 1; j < size; j++) {
            suma += U[i][j] * X[j];
        }

        X[i] = (1 / U[i][i]) * (Y[i] - suma);
    }


    std::cout << "Wynik:" << endl;
    for (int i = 0; i < size; i++) {
        std::cout << "x: " << X[i] << endl;
    }

    for (int i = 0; i < size; i++) {
        delete[] A[i];
        delete[] L[i];
        delete[] U[i];
    }
    delete[] A;
    delete[] L;
    delete[] U;
    

}




int main() {
    std::ifstream myfile("RURL_dane2.txt", std::ios_base::in);

    int size = 0;

    myfile >> size;

    double** A = new double* [size];
    for (int i = 0; i < size; i++) {
        A[i] = new double[size+1];
    }


    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size+1; j++) {
            myfile >> A[i][j];
            if (i == j && A[i][j] == 0) {
                cout << "0 na przekatnej" << endl;
                myfile.close();
                return 0;
            }
        }
    }
    myfile.close();
    //wypisanie macierzy
    cout << "Macierz A: " << endl;
    showArray(A, size);
    doolittle(A, size);
}