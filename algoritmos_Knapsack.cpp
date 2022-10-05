#include <vector>
#include <list>
#include <algorithm>
#include <iostream>
#include <fstream>
#include <string>
#include <chrono>
#include <sstream>

#define weight int
#define profit int
#define pedido pair<weight, profit>

using namespace std;

/**
 * Método recursivo a Fuerza Bruta dónde agregamos al pedido y no lo agregamos en cada llamado recursivo y hecho eso,
 * continuamos con el pedido directamente posterior.
 * @param S Vector Conjunto de pedidos, donde un pedido es un par con su peso y su beneficio.
 * @param w
 * @param pedido
 * @return
 */
int knapsack_Bruto(const vector<pedido>& S, int w, int pedido_i) {
    int result;
    int n = S.size();
    //Caso base
    if(n == pedido_i) {
        result = w >= 0? 0 : -1;
        return result;
    }

    int sol_agregando = knapsack_Bruto(S, w-S[pedido_i].first,pedido_i + 1);
    int sol_sin_agregar = knapsack_Bruto(S, w, pedido_i + 1);

    if (sol_agregando == -1) {
        result = sol_sin_agregar;
    } else if (sol_sin_agregar == -1) {
        result = S[pedido_i].second + sol_agregando;
    } else {
        result = max(S[pedido_i].second + sol_agregando, sol_sin_agregar);
    }

    return result;
}
/**
 * Programacion dinámica del problema de la mochila muy similar al matricial a continuacion, pero donde usamos 2 vectores
 * para usar menos memoria.
 * @param S
 * @param w
 * @return
 */
int knapsack_PD_Bottom_Up(const vector<pedido>& S, int w) {
    int n = S.size();
    vector<int> memoization1(w + 1, 0); //memoization1 inicializados en 0 porque para i=0 no hay pedidos
                                        // asique la solución es no meter ninguno.
    vector<int> memoization2(w + 1, 0);
    for (int i = 1; i < n + 1; i++) { //Teniendo los pedidos hasta i exclusive
        for (int j = 0; j < w + 1; j++) { //Teniendo una mochila de capacidad j
            memoization2[j] = j >= S[i - 1].first ? max(memoization1[j - S[i - 1].first] + S[i - 1].second,
                                                        memoization1[j]) : memoization1[j];
        }
        memoization1.swap(memoization2);
    }
    return memoization1[w];
}


/**
 * Programacion dinámica del problema de la mochila donde M[i][j] denota la subsolución de calcular el problema original
 * con los respectivos pesos y beneficios, pero solo habilitando los pedidos hasta el i-ésimo EXCLUSIVE, y con peso
 * máximo j.
 * @param S
 * @param w
 * @return
 */
 /* CODIGO NO USADO */
int knapsack_PD_Bottom_Up_matricial(const vector<pedido>& S, int w) {
    int n = S.size();
    vector<vector<int> > memoization(n+1,vector<int>(w+1,0)); //memoization[i][j]==0 para i=0 ya que no hay pedidos asique la solución es no meter ninguno.
    for(int i = 1; i < n+1; i++){
        for(int j = 0; j < w+1; j++) {
            memoization[i][j] = j >= S[i-1].first ? max(memoization[i-1][j - S[i-1].first] + S[i-1].second,
                    memoization[i-1][j]) : memoization[i-1][j];
        }
    }
    return memoization[n][w];
}