#include "back_tracking.h"
#include <iostream>
#define weight int
#define profit int
#define pedido pair<weight, profit>

using namespace std;

int main() {
    int n;
    int w;
    cin >> n;
    cin >> w;
    vector<pedido> S(n);
    for(int i = 0; i<n; i++) {
        cin >> S[i].first;
        cin >> S[i].second;
    }/* COMPLETAR */


    //cout << result;
    return 0;
}