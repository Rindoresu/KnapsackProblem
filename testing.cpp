#include <iostream>
#include <cstdlib>
#include "back_tracking.h"
#include "algoritmos_Knapsack.cpp"
#include "meet_in_the_middle.h"

using namespace std;

void inicializar_resuls_parcs(pair<Costo, Benef>* resuls_parcs, uint hasta){
    for(uint i = 0; i < hasta; ++i)
        resuls_parcs[i] = {0, 0};
}
Costo costo_total_hasta(pair<Costo, Benef>* conj, int hasta){
    Costo total = 0;
    for(int i = 0; i < hasta; ++i)
        total += conj[i].first;
    return total;
}

int main() {
    int n = 30;
    pair<Costo, Benef> conj[n];
    for (int i = 0; i < n-1; i++) {
        conj[i] = {1, 1};
    }
    conj[n-1] = {31, 30};
    int fin = n;
    uint w_rest = 31;
    uint cant_podas = 0;
    uint cant_nodos_visitados = 0;

    pair<Benef, Conj_ind> res = back_tracking2(conj, fin, w_rest, cant_podas, cant_nodos_visitados);
    //std::cout << "      BT2:  benef = " << res.first << "; #podas = " << cant_podas << "; % de nodos visitados = %" << (100.0*cant_nodos_visitados)/cant_nodos_visitados_base << std::endl;
    cout << "      BT2:  benef = " << res.first << "; #podas = " << cant_podas << "; % de nodos visitados = %";
    return 0;
}