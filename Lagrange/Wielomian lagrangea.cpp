#include <iostream>
#include <fstream>

using namespace std;

void wielomian_interpolacyjny_lagrangea(double x, double wezly[], double wartosci_funkcji[], int liczba_wezlow);
void zad2();

int main() {
    double x = 0;
    cout << "Podaj punkt: ";
    cin >> x;

    std::ifstream myfile("wezly.txt", std::ios_base::in);

    int liczba_wezlow;

    myfile >> liczba_wezlow;

    double* wezly = new  double[liczba_wezlow];
    double* wartosci_funkcji = new double[liczba_wezlow];

    for (int i = 0; i < liczba_wezlow; i++) {
        myfile >> wezly[i];
        myfile >> wartosci_funkcji[i];
    }

    myfile.close();

    wielomian_interpolacyjny_lagrangea(x, wezly, wartosci_funkcji, liczba_wezlow); //zad1
    delete[] wezly;
    delete[] wartosci_funkcji;
    zad2(); //zad2
    
}

void wielomian_interpolacyjny_lagrangea(double x, double wezly[], double wartosci_funkcji[], int liczba_wezlow) {

   

    double* l = new double[liczba_wezlow];
    double l_wynik = 0;
    // l - wielomian chyba
    
    for (int i = 0; i < liczba_wezlow; i++) {
        l[i] = 1;
        for (int j = 0; j < liczba_wezlow; j++) {
            if (i != j) {
                l[i] *= ((x - wezly[j]) / (wezly[i] - wezly[j]));
            }
        }
    }
    for (int i = 0; i < liczba_wezlow; i++) {
        l_wynik += l[i] * wartosci_funkcji[i];
    }


    cout << "Liczba wezlow: " << liczba_wezlow << endl;
    for (int i = 0; i < liczba_wezlow; i++) {
        cout << "wezel " << wezly[i] << ", " << "wartosc funkcji: " << wartosci_funkcji[i] << endl;
    }
    cout << "Punkt w ktorym liczymy wartosc wielomianu: " << x << endl;
    cout << " Wartosc wielomianu lagrangea w danym punkcie: " << l_wynik << endl;

    delete[] l;



}


void zad2() {
    const int SIZE = 4;
    double wezly[SIZE] = { 27.0,64.0,125.0,216.0 };
    double wartosci_funkcji[SIZE];
    for (int i = 0; i < SIZE; i++) {
        wartosci_funkcji[i] = pow(double(wezly[i]), 1.0/3.0);
    }
    double x = 50.0;
    wielomian_interpolacyjny_lagrangea(x,wezly,wartosci_funkcji,SIZE);

}