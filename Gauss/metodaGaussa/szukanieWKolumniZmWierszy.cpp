//#include <iostream>
//#include <fstream>
//
//using namespace std;
//int main() {
//
//
//    std::ifstream myfile("MN-6-2.txt", std::ios_base::in);
//
//    int size = 0;
//
//    myfile >> size;
//
//    double** M = new double* [size];
//    for (int i = 0; i < size; i++) {
//        M[i] = new double[size + 1];
//    }
//
//
//    for (int i = 0; i < size; i++) {
//        for (int j = 0; j < size + 1; j++) {
//            myfile >> M[i][j];
//        }
//    }
//    //wypisanie macierzy
//    for (int i = 0; i < size; i++) {
//        for (int j = 0; j < size + 1; j++) {
//            cout << M[i][j] << "\t";
//        }
//        cout << "\n";
//    }
//    cout << endl;
//    myfile.close();
//
//    double m = 0; int k = 0;
//    double* temp = new double[size + 1];
//    
//    cout << endl;
//    for (int i = 0; i < size; i++) {
//
//        int maxIndex = i;
//        //szukanie najwyzeszej wartosci w pierwszej kolumnie
//        for (int k = i+1; k < size; k++) {
//            if (abs(M[k][i]) > abs(M[i][maxIndex])) {
//                maxIndex = k;
//            }
//        }
//        //zamiana wierszy
//        for (int p = 0; p < size + 1; p++) {
//            temp[p] = M[i][p];
//            M[i][p] = M[maxIndex][p];
//            M[maxIndex][p] = temp[p];
//        }
//        //wypisanie macierzy
//        /*cout << "wiersz " << endl;
//        for (int i = 0; i < size; i++) {
//            for (int j = 0; j < size + 1; j++) {
//                cout << M[i][j] << "\t";
//            }
//            cout << "\n";
//        }*/
//        cout << endl;
//        //postepowanie proste
//        for (int z = i; z < size - 1; z++) {
//            if (M[i][i] != 0) {
//                m = M[z + 1][i] / M[i][i];
//
//                for (int j = i; j < size + 1; j++) {
//
//                    M[z + 1][j] -= M[i][j] * m;
//
//                }
//            }
//            else {
//                cout << "0 na przekatnej " << endl;
//                break;
//            }
//        }
//
//    }
//    //wypisanie macierzy
//    for (int i = 0; i < size; i++) {
//        for (int j = 0; j < size + 1; j++) {
//            cout << M[i][j] << "\t";
//        }
//        cout << "\n";
//    }
//    cout << endl;
//    //postepowanie odwrotne
//    double x = 0.0, suma = 0.0;
//    double* tabx = new double[size - 1];
//    tabx[size - 1] = M[size - 1][size] / M[size - 1][size - 1];
//    for (int i = size - 2; i >= 0; i--) {
//        suma = 0;
//        for (int j = i + 1; j < size; j++) {
//            suma += M[i][j] * tabx[j];
//        }
//        tabx[i] = (M[i][size] - suma) / M[i][i];
//
//    }
//
//    for (int i = size - 1; i >= 0; i--) {
//        cout << "Rozwiazanie ukladu rownan: x" << i << "=" << tabx[i] << endl;
//    }
//    delete[] temp;
//}
