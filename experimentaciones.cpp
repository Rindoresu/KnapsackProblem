#include "algoritmos_Knapsack.cpp"
#include "back_tracking.h"
#include "meet_in_the_middle.h"
#include <cstdio>
#include <string>

#define algoritmo_usado 2 // 0 == FuerzaBruta, 1 == BackTracking1, 2 == BackTracking2, 3 == MitM, 4 == PD


using namespace std;



int main() {
    //ifstream cin("./MaloBacktrackingPseudopolinomial.csv");
    int n_ini;
    int n_fin;
    cin >> n_ini;
    cin >> n_fin;
    vector<pair<int, double> > tiempos(n_fin-n_ini+1);

    for (int tam = n_ini; tam <= n_fin; tam++) {
        tiempos[tam-n_ini].first = tam;
        tiempos[tam-n_ini].second = -1;
        int n;
        int w;
        cin >> n;
        cin >> w;
        vector<pedido> S(n);
        pair<Costo, Benef> C[n];
        pair<Costo, Benef> resuls_parcs[n];
        for(int i = 0; i < n; ++i)
            resuls_parcs[i] = {0, 0};
        for(int i = 0; i<n; i++) {
            cin >> S[i].first;
            C[i].first = S[i].first;
            cin >> S[i].second;
            C[i].second = S[i].second;
        }
        if(algoritmo_usado == 3 or tam<20) { //Hago 50 repes porque tarda muy poco
            for (int repes_outliers = 0; repes_outliers<50; repes_outliers++) {
                chrono::steady_clock::time_point t0;
                chrono::steady_clock::time_point t1;
                t0 = chrono::steady_clock::now();
                switch(algoritmo_usado){
                    case 0 :
                        knapsack_Bruto(S,w,0);
                        break;
                    case 1 :
                        back_tracking1(C, resuls_parcs, n, w, 0);
                        break;
                    case 2 :
                        back_tracking2(C, n, w);
                        break;
                    case 3 :
                        meet_in(C, n, w);
                        break;
                    case 4 :
                        knapsack_PD_Bottom_Up(S,w);
                        break;
                }
                t1 = chrono::steady_clock::now();

                double delta_t = chrono::duration_cast<chrono::nanoseconds>(t1-t0).count();

                if(tiempos[tam-n_ini].second == -1 or tiempos[tam-n_ini].second > delta_t) {
                    tiempos[tam-n_ini].second = delta_t;
                }

            }
        } else if (tam<28) { // Hago 10 repes porque sino tarda mucho
            for (int repes_outliers = 0; repes_outliers<10; repes_outliers++) {
                chrono::steady_clock::time_point t0;
                chrono::steady_clock::time_point t1;
                t0 = chrono::steady_clock::now();
                switch(algoritmo_usado){
                    case 0 :
                        knapsack_Bruto(S,w,0);
                        break;
                    case 1 :
                        back_tracking1(C, resuls_parcs, n, w, 0);
                        break;
                    case 2 :
                        back_tracking2(C, n, w);
                        break;
                    case 3 :
                        meet_in(C, n, w);
                        break;
                    case 4 :
                        knapsack_PD_Bottom_Up(S,w);
                        break;
                }
                t1 = chrono::steady_clock::now();

                double delta_t = chrono::duration_cast<chrono::nanoseconds>(t1-t0).count();

                if(tiempos[tam-n_ini].second == -1 or tiempos[tam-n_ini].second > delta_t) {
                    tiempos[tam-n_ini].second = delta_t;
                }

            }
        } else { // Hago 3 repes porque tarda tanto que casi no varía
            for (int repes_outliers = 0; repes_outliers<5; repes_outliers++) {
                chrono::steady_clock::time_point t0;
                chrono::steady_clock::time_point t1;
                t0 = chrono::steady_clock::now();
                switch(algoritmo_usado){
                    case 0 :
                        knapsack_Bruto(S,w,0);
                        break;
                    case 1 :
                        back_tracking1(C, resuls_parcs, n, w, 0);
                        break;
                    case 2 :
                        back_tracking2(C, n, w);
                        break;
                    case 3 :
                        meet_in(C, n, w);
                        break;
                    case 4 :
                        knapsack_PD_Bottom_Up(S,w);
                        break;
                }
                t1 = chrono::steady_clock::now();

                double delta_t = chrono::duration_cast<chrono::nanoseconds>(t1-t0).count();

                if(tiempos[tam-n_ini].second == -1 or tiempos[tam-n_ini].second > delta_t) {
                    tiempos[tam-n_ini].second = delta_t;
                }

            }
        }
    }
    cout << "n,Tiempo" << '\n';
    for (int tam = n_ini; tam <= n_fin; tam++) {
        cout << tiempos[tam-n_ini].first << ',' << tiempos[tam-n_ini].second << '\n';
    }

    return 0;
}