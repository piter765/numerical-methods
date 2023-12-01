#include <iostream>
#include <fstream>
#include <cmath>
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

double* macXWek(double** A, double* b, int size)
{
    double* wynik = new double[size];
    for (int i = 0; i < size; i++) {
        wynik[i] = 0.0;
        for (int j = 0; j < size; j++) {
            wynik[i] += A[i][j] * b[j];
        }
    }
    return wynik;
}
double* dodanieWektorow(double* A, double* b, int size)
{
    double* wynik = new double[size];
    for (int i = 0; i < size; i++) {
        wynik[i] = -A[i] + b[i];
    }
    return wynik;
}
double** mnozMacKw(double** A, double** B, int n)
{
    double** wynik = new double* [n];
    for (int i = 0; i < n; i++) {
        wynik[i] = new double[n];
        for (int j = 0; j < n; j++) {
            double suma = 0.0;
            for (int k = 0; k < n; k++) {
                suma += A[i][k] * B[k][j];
            }
            wynik[i][j] = suma;
        }
    }
    return wynik;
}




void metodaJacobiego(int size, double** A) {

    double** L = new double* [size];
    double** U = new double* [size];
    double** D = new double* [size];
    double** sumaLU = new double* [size];
    for (int i = 0; i < size; i++) {
        L[i] = new double[size];
        U[i] = new double[size];
        D[i] = new double[size];
        sumaLU[i] = new double[size];
    }
    //wyzerowanie obu macierzy L i U
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            L[i][j] = 0;
            U[i][j] = 0;
            D[i][j] = 0;
            sumaLU[i][j] = 0;
        }
    }
    double suma;
    for (int i = 1; i <= size; i++) {
        for (int j = 1; j <= size; j++) {
            if (i < j) {
                U[i - 1][j - 1] = A[i - 1][j - 1];
            }
            else if (i == j) {
                D[i - 1][j - 1] = A[i - 1][j - 1];
            }
            else {
                L[i - 1][j - 1] = A[i - 1][j - 1];
            }

        }
    }
    cout << " L:  " << endl;
    showArray(L, size);
    cout << " U:  " << endl;
    showArray(U, size);
    cout << " D: " << endl;
    showArray(D, size);

    //suma L + U
    
   for (int i = 0; i < size; i++) {
        for (int j = 0; j <size; j++) {
            sumaLU[i][j] = L[i][j] + U[i][j];
        }
    }
   cout << " L + U: " << endl;
   showArray(sumaLU, size);
   bool czyDominujaca1 = true;
   bool czyDominujaca2 = false;
   suma = 0;
   for (int i = 0; i < size; i++) {
       for (int j = 0; j < size; j++) {
           suma = 0;
           if (i != j) {
               suma += abs(A[i][j]);
           }
           if (abs(A[i][i]) < suma) {
              czyDominujaca1 = false;
           }
           if (abs(A[i][i]) > suma) {
              czyDominujaca2 = true;
           }

       }
   }
   if (czyDominujaca1 && czyDominujaca2) {
       cout << "Macierz jest slabo dominujaca" << endl;
   }
   else {
       cout << "Macierz nie jest slabo dominujaca" << endl;
   }
   
   cout << endl;
   cout << "Macierz diagonalna odwrotna: " << endl;
   for (int i = 0; i < size; i++) {
       for (int j = 0; j < size; j++) {
           if (i == j) {
               D[i][j] = pow(D[i][j], -1);
           }
       }
   }
   cout << "Diagonalna odwrotna " << endl;
   showArray(D, size);

   // D^1*L+U
   double** DxLU = mnozMacKw(D, sumaLU, size);
   // D^1*b
   double* b = new double[size];
   for (int i = 0; i < size; i++) {
       b[i] = A[i][size];
   }
   // Dxb / D^1*b
   double* Dxb = macXWek(D, b, size);
   // wektor X
   double* X = new double[size];
   for (int i = 0; i < size; i++) {
       X[i] = 0.0;
   }

   /* for (int i = 1; i <= 5; i++) {
        double* DLUX = macXWek(DxLU, X, size);
        double* newX = dodanieWektorow(DLUX, Dxb, size);
        X = newX;
    }
    for (int i = 0; i < size; i++) {
        cout<<"x("<<i<<"):"<<X[i]<<endl;
    }*/

   //
   double blad = 0.01;
   int k = 1;
   double roznica;
   bool f = false;
   while (k) {
       double* dlux = macXWek(DxLU, X, size);
       double* newX = dodanieWektorow(dlux, Dxb, size);

       cout<<"Iteracja "<<k<<endl;
       cout<<"Tolerancja "<<blad<<endl;
           int s = 0;
           for (int i = 0; i < size; i++) {
               roznica = abs(newX[i] - X[i]);
               cout<<"Blad dla x"<<i<<": "<<roznica<<"\n";
               if (roznica < blad) {
                   s++;
                   cout << "blad\n";
               }
           }
           if (k == 6) {
               f = true;
           }
           if (s == size) {
               f = true;
           }
       if (f) break;
       X = newX;
       k++;
   } 
   cout << endl;
   std::cout << "Wynik:\n";
   for (int i = 0; i < size; i++) {
       std::cout<<"x"<<i<<": "<< X[i]<<"\n";
   }
}

int main() {

    std::ifstream myfile("MN-8.txt", std::ios_base::in);

    int size = 0;

    myfile >> size;

    double** A = new double* [size];
    for (int i = 0; i < size; i++) {
        A[i] = new double[size + 1];
    }

    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size + 1; j++) {
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
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size+1; j++) {
            std::cout << A[i][j] << "\t";
        }
        std::cout << "\n";
    }
    std::cout << endl;
    metodaJacobiego(size, A);
    
}