#include <iostream>
#include <fstream>

using namespace std;

void wielomian_interpolacyjny_newtona(double x, double wezly[], double wartosci_funkcji[], int liczba_wezlow);


int main() {
    double x = 0;
    cout << "Podaj punkt: ";
    cin >> x;

    std::ifstream myfile("MN-2-p2.txt", std::ios_base::in);

    int liczba_wezlow;

    myfile >> liczba_wezlow;

    double* wezly = new  double[liczba_wezlow];
    double* wartosci_funkcji = new double[liczba_wezlow];

    for (int i = 0; i < liczba_wezlow; i++) {
        myfile >> wezly[i];
        myfile >> wartosci_funkcji[i];
    }

    myfile.close();

    wielomian_interpolacyjny_newtona(x, wezly, wartosci_funkcji, liczba_wezlow);
    delete[] wezly;
    delete[] wartosci_funkcji;


}


void wielomian_interpolacyjny_newtona(double x, double wezly[], double wartosci_funkcji[], int n) {

    double W = wartosci_funkcji[0] * 1;

   
    double pk = 1;
    for (int k = 1; k < n; k++) {

        pk = 1;

        //liczymy pk dla poszczegolnych wezlow
        for (int i = 0; i <= k - 1; i++) {

            pk *= x - wezly[i];
        }


        //iloczyn z mianownika do bk
        double mianbk, bk = 0;
        for (int i = 0; i <= k; i++) {
            mianbk = 1;
            for (int j = 0; j <= k; j++) {
                if (j != i) {
                    mianbk *= wezly[i] - wezly[j];
                }
            }
            //liczymy bk
            bk += wartosci_funkcji[i] / mianbk;
        }
        W += pk * bk;
        cout << "Wspolczynniki wielomianu " << bk << endl;
    }


    //wielomian interpolacyjny


    cout << "Liczba wezlow: " << n << endl;
    for (int i = 0; i < n; i++) {
        cout << "wezel " << wezly[i] << ", " << "wartosc funkcji: " << wartosci_funkcji[i] << endl;
    }
    cout << "Punkt w ktorym liczymy wartosc wielomianu: " << x << endl;
    cout << " Wartosc wielomianu newtona w danym punkcie: " << W << endl;

}