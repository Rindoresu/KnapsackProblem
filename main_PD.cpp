#include "algoritmos_Knapsack.cpp"

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
    }
    int result = knapsack_PD_Bottom_Up(S,w);
    cout << result;
    return 0;
}