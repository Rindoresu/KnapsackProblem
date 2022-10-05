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
    //std::cout << "sizeof(uint) = " << sizeof(uint) << std::endl;
    pair<Costo, Benef> C[3] = {{80, 40}, {70, 50}, {60, 45}};
    pair<Costo, Benef> C0[3] = {{20, 50}, {20, 45}, {80, 40}};
    pair<Costo, Benef> C1[5];
    for(int i = 1; i <= 5; ++i)
        C1[5-i] = {i,i};
    pair<Costo, Benef> C2[5] = {{20,43}, {12,23}, {35,20}, {32,65}, {47, 93}};
    pair<Costo, Benef> Crand[30];
    for(uint i = 0; i < 30; ++i)
        Crand[i] = {rand() % 100 + 1, rand() % 100 +1};
    pair<Costo, Benef> CrandCmB[30];
    for (auto &e : CrandCmB) {
        Costo c = rand() % 100 + 1;
        e = {c, c + (rand() % 100)};
    }
    pair<Costo, Benef> Crand0p5_1p5[30];
    for(pair<Costo, Benef>& e : Crand0p5_1p5){
        Costo c = rand() % 100 + 1;
        e = {c, c/2 + (rand() % c)};
    }
    pair<Costo, Benef> resuls_parcs[30];
    pair<Costo, Benef>* conj;
    pair<Costo, Benef>* conj_ord;
    vector<pair<Costo, Benef> > vec_ord;
    uint n;
    Costo w_max;
    uint cant_nodos_visitados = 0;
    uint cant_nodos_visitados_base = 0;
    uint cant_podas = 0;
    pair<Benef, Conj_ind> res;
    Conj_ind S_base;
    Conj_ind S_1;
    Conj_ind S_2;
    Conj_ind S_m;
    pair<Costo, Benef> chequeo_subconjuntos1;
    pair<Costo, Benef> chequeo_subconjuntos2;

    /* Pruebas con casos chicos de las funciones de back tracking:
    conj = C;
    n = 3;
    w_max = 100;
    inicializar_resuls_parcs(resuls_parcs, n);
    res = back_tracking_base(conj, n, w_max, cant_nodos_visitados_base);
    S_base = res.second;
    std::cout << " :Base: benef = " << res.first << std::endl;
    res = back_tracking1(conj, resuls_parcs, n, w_max, 0, cant_podas, cant_nodos_visitados);
    S_1 = res.second;
    std::cout << "  BT1:  benef = " << res.first << "; #podas = " << cant_podas << "; #nodos ahorrados = " << cant_nodos_visitados_base - cant_nodos_visitados << std::endl;
    cant_podas = 0;
    cant_nodos_visitados = 0;
    res = back_tracking2(conj, n, w_max, cant_podas, cant_nodos_visitados);
    S_2 = res.second;
    vec_ord = vector<pair<Costo, Benef> >(conj, conj + n);
    sort(vec_ord.begin(), vec_ord.end(), menor_proporcionalmente);
    std::cout << "  BT2:  benef = " << res.first << "; #podas = " << cant_podas << "; #nodos ahorrados = " << cant_nodos_visitados_base - cant_nodos_visitados << std::endl;
    res = meet_in(conj, n, w_max);
    std::cout << " meet:  benef = " << res.first << std::endl;
    S_m = res.second;
    cant_podas = 0;
    cant_nodos_visitados = 0;
    cant_nodos_visitados_base = 0;

    conj = C0;
    n = 3;
    w_max = 100;
    inicializar_resuls_parcs(resuls_parcs, n);
    res = back_tracking1(conj, resuls_parcs, n, w_max, 0, cant_podas, cant_nodos_visitados);
    std::cout << "0:Base: benef = " << res.first << std::endl;
    S_base = res.second;
    res = back_tracking_base(conj, n, w_max, cant_nodos_visitados_base);
    std::cout << "  BT1:  benef = " << res.first << "; #podas = " << cant_podas << "; #nodos ahorrados = " << cant_nodos_visitados_base - cant_nodos_visitados << std::endl;
    S_1 = res.second;
    cant_podas = 0;
    cant_nodos_visitados = 0;
    res = back_tracking2(conj, n, w_max, cant_podas, cant_nodos_visitados);
    std::cout << "  BT2:  benef = " << res.first << "; #podas = " << cant_podas << "; #nodos ahorrados = " << cant_nodos_visitados_base - cant_nodos_visitados << std::endl;
    S_2 = res.second;
    vec_ord = vector<pair<Costo, Benef> >(conj, conj + n);
    sort(vec_ord.begin(), vec_ord.end(), menor_proporcionalmente);
    res = meet_in(conj, n, w_max);
    std::cout << " meet:  benef = " << res.first << std::endl;
    S_m = res.second;
    cant_podas = 0;
    cant_nodos_visitados = 0;
    cant_nodos_visitados_base = 0;

    conj = C1;
    n = 5;
    w_max = 10;
    inicializar_resuls_parcs(resuls_parcs, n);
    res = back_tracking_base(conj, n, w_max, cant_nodos_visitados_base);
    std::cout << "1:Base: benef = " << res.first << std::endl;
    S_base = res.second;
    res = back_tracking1(conj, resuls_parcs, n, w_max, 0, cant_podas, cant_nodos_visitados);
    std::cout << "  BT1:  benef = " << res.first << "; #podas = " << cant_podas << "; #nodos ahorrados = " << cant_nodos_visitados_base - cant_nodos_visitados << std::endl;
    S_1 = res.second;
    cant_podas = 0;
    cant_nodos_visitados = 0;
    res = back_tracking2(conj, n, w_max, cant_podas, cant_nodos_visitados);
    std::cout << "  BT2:  benef = " << res.first << "; #podas = " << cant_podas << "; #nodos ahorrados = " << cant_nodos_visitados_base - cant_nodos_visitados << std::endl;
    S_2 = res.second;
    vec_ord = vector<pair<Costo, Benef> >(conj, conj + n);
    sort(vec_ord.begin(), vec_ord.end(), menor_proporcionalmente);
    res = meet_in(conj, n, w_max);
    std::cout << " meet:  benef = " << res.first << std::endl;
    S_m = res.second;
    cant_podas = 0;
    cant_nodos_visitados = 0;
    cant_nodos_visitados_base = 0;

    conj = C2;
    n = 5;
    w_max = 10;
    inicializar_resuls_parcs(resuls_parcs, n);
    res = back_tracking_base(conj, n, w_max, cant_nodos_visitados_base);
    std::cout << "2:Base: benef = " << res.first << std::endl;
    S_base = res.second;
    res = back_tracking1(conj, resuls_parcs, n, w_max, 0, cant_podas, cant_nodos_visitados);
    std::cout << "  BT1:  benef = " << res.first << "; #podas = " << cant_podas << "; #nodos ahorrados = " << cant_nodos_visitados_base - cant_nodos_visitados << std::endl;
    S_1 = res.second;
    cant_podas = 0;
    cant_nodos_visitados = 0;
    res = back_tracking2(conj, n, w_max, cant_podas, cant_nodos_visitados);
    std::cout << "  BT2:  benef = " << res.first << "; #podas = " << cant_podas << "; #nodos ahorrados = " << cant_nodos_visitados_base - cant_nodos_visitados << std::endl;
    S_2 = res.second;
    vec_ord = vector<pair<Costo, Benef> >(conj, conj + n);
    sort(vec_ord.begin(), vec_ord.end(), menor_proporcionalmente);
    res = meet_in(conj, n, w_max);
    std::cout << " meet:  benef = " << res.first << std::endl;
    S_m = res.second;
    cant_podas = 0;
    cant_nodos_visitados = 0;
    cant_nodos_visitados_base = 0;*/

    /* Pruebas de las funciones de "back tracking" y "meet in the middle" con costos y beneficios aleatorios:
    conj = Crand;
    n = 30;
    Costo costo_total = costo_total_hasta(conj, n);
    w_max = costo_total/4;
    inicializar_resuls_parcs(resuls_parcs, n);
    conj_ord = copiar_conj(conj, n);
    res = back_tracking_base(conj, n, w_max, cant_nodos_visitados_base);
    std::cout << "Rand1:Base: benef = " << res.first << std::endl;
    S_base = res.second;
    res = back_tracking1(conj, resuls_parcs, n, w_max, 0, cant_podas, cant_nodos_visitados);
    std::cout << "      BT1:  benef = " << res.first << "; #podas = " << cant_podas << "; % de nodos visitados = %" << (100.0*cant_nodos_visitados)/cant_nodos_visitados_base << std::endl;
    S_1 = res.second;
    cant_podas = 0;
    cant_nodos_visitados = 0;
    vec_ord = vector<pair<Costo, Benef> >(conj, conj + n);
    sort(vec_ord.begin(), vec_ord.end(), menor_proporcionalmente);
    res = back_tracking2(conj_ord, n, w_max, cant_podas, cant_nodos_visitados);
    std::cout << "      BT2:  benef = " << res.first << "; #podas = " << cant_podas << "; % de nodos visitados = %" << (100.0*cant_nodos_visitados)/cant_nodos_visitados_base << std::endl;
    S_2 = res.second;
    res = meet_in(conj, n, w_max);
    std::cout << "     meet:  benef = " << res.first << std::endl;
    S_m = res.second;
    chequeo_subconjuntos1 = {0, 0};
    for(auto it = S_m.begin(); it != S_m.end(); ++it){
        chequeo_subconjuntos1.first += conj[*it].first;
        chequeo_subconjuntos1.second += conj[*it].second;
    }
    chequeo_subconjuntos2 = {0, 0};
    for(auto it = S_2.begin(); it != S_2.end(); ++it){
        chequeo_subconjuntos2.first += conj_ord[*it].first;
        chequeo_subconjuntos2.second += conj_ord[*it].second;
    }
    cant_podas = 0;
    cant_nodos_visitados = 0;
    cant_nodos_visitados_base = 0;

    w_max = costo_total/3;
    inicializar_resuls_parcs(resuls_parcs, n);
    res = back_tracking_base(conj, n, w_max, cant_nodos_visitados_base);
    std::cout << "Rand2:Base: benef = " << res.first << std::endl;
    S_base = res.second;
    res = back_tracking1(conj, resuls_parcs, n, w_max, 0, cant_podas, cant_nodos_visitados);
    std::cout << "      BT1:  benef = " << res.first << "; #podas = " << cant_podas << "; % de nodos visitados = %" << (100.0*cant_nodos_visitados)/cant_nodos_visitados_base << std::endl;
    S_1 = res.second;
    cant_podas = 0;
    cant_nodos_visitados = 0;
    vec_ord = vector<pair<Costo, Benef> >(conj, conj + n);
    sort(vec_ord.begin(), vec_ord.end(), menor_proporcionalmente);
    res = back_tracking2(conj_ord, n, w_max, cant_podas, cant_nodos_visitados);
    std::cout << "      BT2:  benef = " << res.first << "; #podas = " << cant_podas << "; % de nodos visitados = %" << (100.0*cant_nodos_visitados)/cant_nodos_visitados_base << std::endl;
    S_2 = res.second;
    res = meet_in(conj, n, w_max);
    std::cout << "     meet:  benef = " << res.first << std::endl;
    S_m = res.second;
    chequeo_subconjuntos1 = {0, 0};
    for(auto it = S_m.begin(); it != S_m.end(); ++it){
        chequeo_subconjuntos1.first += conj[*it].first;
        chequeo_subconjuntos1.second += conj[*it].second;
    }
    chequeo_subconjuntos2 = {0, 0};
    for(auto it = S_2.begin(); it != S_2.end(); ++it){
        chequeo_subconjuntos2.first += conj_ord[*it].first;
        chequeo_subconjuntos2.second += conj_ord[*it].second;
    }
    cant_podas = 0;
    cant_nodos_visitados = 0;
    cant_nodos_visitados_base = 0;
    delete conj_ord;*/

    /* Pruebas de las funciones de "back tracking" y "meet in the middle" con costos = rand(100) y beneficios = costo + rand(100):
    conj = CrandCmB;
    n = 30;
    costo_total = costo_total_hasta(conj, n);
    w_max = costo_total/4;
    inicializar_resuls_parcs(resuls_parcs, n);
    conj_ord = copiar_conj(conj, n);
    res = back_tracking_base(conj, n, w_max, cant_nodos_visitados_base);
    std::cout << "RandCnB /4:Base: benef = " << res.first << std::endl;
    S_base = res.second;
    res = back_tracking1(conj, resuls_parcs, n, w_max, 0, cant_podas, cant_nodos_visitados);
    std::cout << "           BT1:  benef = " << res.first << "; #podas = " << cant_podas << "; % de nodos visitados = %" << (100.0*cant_nodos_visitados)/cant_nodos_visitados_base << std::endl;
    S_1 = res.second;
    cant_podas = 0;
    cant_nodos_visitados = 0;
    vec_ord = vector<pair<Costo, Benef> >(conj, conj + n);
    sort(vec_ord.begin(), vec_ord.end(), menor_proporcionalmente);
    res = back_tracking2(conj_ord, n, w_max, cant_podas, cant_nodos_visitados);
    std::cout << "           BT2:  benef = " << res.first << "; #podas = " << cant_podas << "; % de nodos visitados = %" << (100.0*cant_nodos_visitados)/cant_nodos_visitados_base << std::endl;
    S_2 = res.second;
    res = meet_in(conj, n, w_max);
    std::cout << "          meet:  benef = " << res.first << std::endl;
    S_m = res.second;
    chequeo_subconjuntos1 = {0, 0};
    for(auto it = S_m.begin(); it != S_m.end(); ++it){
        chequeo_subconjuntos1.first += conj[*it].first;
        chequeo_subconjuntos1.second += conj[*it].second;
    }
    chequeo_subconjuntos2 = {0, 0};
    for(auto it = S_2.begin(); it != S_2.end(); ++it){
        chequeo_subconjuntos2.first += conj_ord[*it].first;
        chequeo_subconjuntos2.second += conj_ord[*it].second;
    }
    cant_podas = 0;
    cant_nodos_visitados = 0;
    cant_nodos_visitados_base = 0;

    w_max = costo_total/3;
    inicializar_resuls_parcs(resuls_parcs, n);
    res = back_tracking_base(conj, n, w_max, cant_nodos_visitados_base);
    std::cout << "RandCnB /3:Base: benef = " << res.first << std::endl;
    S_base = res.second;
    res = back_tracking1(conj, resuls_parcs, n, w_max, 0, cant_podas, cant_nodos_visitados);
    std::cout << "           BT1:  benef = " << res.first << "; #podas = " << cant_podas << "; % de nodos visitados = %" << (100.0*cant_nodos_visitados)/cant_nodos_visitados_base << std::endl;
    S_1 = res.second;
    cant_podas = 0;
    cant_nodos_visitados = 0;
    vec_ord = vector<pair<Costo, Benef> >(conj, conj + n);
    sort(vec_ord.begin(), vec_ord.end(), menor_proporcionalmente);
    res = back_tracking2(conj_ord, n, w_max, cant_podas, cant_nodos_visitados);
    std::cout << "           BT2:  benef = " << res.first << "; #podas = " << cant_podas << "; % de nodos visitados = %" << (100.0*cant_nodos_visitados)/cant_nodos_visitados_base << std::endl;
    S_2 = res.second;
    res = meet_in(conj, n, w_max);
    std::cout << "          meet:  benef = " << res.first << std::endl;
    S_m = res.second;
    chequeo_subconjuntos1 = {0, 0};
    for(auto it = S_m.begin(); it != S_m.end(); ++it){
        chequeo_subconjuntos1.first += conj[*it].first;
        chequeo_subconjuntos1.second += conj[*it].second;
    }
    chequeo_subconjuntos2 = {0, 0};
    for(auto it = S_2.begin(); it != S_2.end(); ++it){
        chequeo_subconjuntos2.first += conj_ord[*it].first;
        chequeo_subconjuntos2.second += conj_ord[*it].second;
    }
    cant_podas = 0;
    cant_nodos_visitados = 0;
    cant_nodos_visitados_base = 0;
    delete conj_ord;*/

    /* Pruebas de las funciones de "back tracking" y "meet in the middle" con costos = rand(100) y beneficios costo/2 + rand(costo):
    conj = Crand0p5_1p5;
    n = 30;
    costo_total = costo_total_hasta(conj, n);
    w_max = costo_total/4;
    inicializar_resuls_parcs(resuls_parcs, n);
    conj_ord = copiar_conj(conj, n);
    res = back_tracking_base(conj, n, w_max, cant_nodos_visitados_base);
    std::cout << "Crand0p5_1p5 /4:Base: benef = " << res.first << std::endl;
    S_base = res.second;
    res = back_tracking1(conj, resuls_parcs, n, w_max, 0, cant_podas, cant_nodos_visitados);
    std::cout << "                BT1:  benef = " << res.first << "; #podas = " << cant_podas << "; % de nodos visitados = %" << (100.0*cant_nodos_visitados)/cant_nodos_visitados_base << std::endl;
    S_1 = res.second;
    cant_podas = 0;
    cant_nodos_visitados = 0;
    vec_ord = vector<pair<Costo, Benef> >(conj, conj + n);
    sort(vec_ord.begin(), vec_ord.end(), menor_proporcionalmente);
    res = back_tracking2(conj_ord, n, w_max, cant_podas, cant_nodos_visitados);
    std::cout << "                BT2:  benef = " << res.first << "; #podas = " << cant_podas << "; % de nodos visitados = %" << (100.0*cant_nodos_visitados)/cant_nodos_visitados_base << std::endl;
    S_2 = res.second;
    res = meet_in(conj, n, w_max);
    std::cout << "               meet:  benef = " << res.first << std::endl;
    S_m = res.second;
    chequeo_subconjuntos1 = {0, 0};
    for(auto it = S_m.begin(); it != S_m.end(); ++it){
        chequeo_subconjuntos1.first += conj[*it].first;
        chequeo_subconjuntos1.second += conj[*it].second;
    }
    chequeo_subconjuntos2 = {0, 0};
    for(auto it = S_2.begin(); it != S_2.end(); ++it){
        chequeo_subconjuntos2.first += conj_ord[*it].first;
        chequeo_subconjuntos2.second += conj_ord[*it].second;
    }
    cant_podas = 0;
    cant_nodos_visitados = 0;
    cant_nodos_visitados_base = 0;

    w_max = costo_total/3;
    inicializar_resuls_parcs(resuls_parcs, n);
    res = back_tracking_base(conj, n, w_max, cant_nodos_visitados_base);
    std::cout << "Rand0p5_1p5 /3:Base: benef = " << res.first << std::endl;
    S_base = res.second;
    res = back_tracking1(conj, resuls_parcs, n, w_max, 0, cant_podas, cant_nodos_visitados);
    std::cout << "               BT1:  benef = " << res.first << "; #podas = " << cant_podas << "; % de nodos visitados = %" << (100.0*cant_nodos_visitados)/cant_nodos_visitados_base << std::endl;
    S_1 = res.second;
    cant_podas = 0;
    cant_nodos_visitados = 0;
    vec_ord = vector<pair<Costo, Benef> >(conj, conj + n);
    sort(vec_ord.begin(), vec_ord.end(), menor_proporcionalmente);
    res = back_tracking2(conj_ord, n, w_max, cant_podas, cant_nodos_visitados);
    std::cout << "               BT2:  benef = " << res.first << "; #podas = " << cant_podas << "; % de nodos visitados = %" << (100.0*cant_nodos_visitados)/cant_nodos_visitados_base << std::endl;
    S_2 = res.second;
    res = meet_in(conj, n, w_max);
    std::cout << "              meet:  benef = " << res.first << std::endl;
    S_m = res.second;
    chequeo_subconjuntos1 = {0, 0};
    for(auto it = S_m.begin(); it != S_m.end(); ++it){
        chequeo_subconjuntos1.first += conj[*it].first;
        chequeo_subconjuntos1.second += conj[*it].second;
    }
    chequeo_subconjuntos2 = {0, 0};
    for(auto it = S_2.begin(); it != S_2.end(); ++it){
        chequeo_subconjuntos2.first += conj_ord[*it].first;
        chequeo_subconjuntos2.second += conj_ord[*it].second;
    }
    cant_podas = 0;
    cant_nodos_visitados = 0;
    cant_nodos_visitados_base = 0;
    delete conj_ord;*/

    /* Pruebo las funciones "cota_super" y "menor_proporcionalmente":*/
    Benef a = cota_super(C1, 5, 8).first;
    cout << a << endl;
    C1[1] = {7,7};
    a = cota_super(C1, 5, 8).first;
    cout << a << endl;
    C1[1] = {7,8};
    a = cota_super(C1, 5, 8).first;
    cout << a << endl;

    sort(C, C+3, menor_proporcionalmente);
    sort(C0, C0+3, menor_proporcionalmente);
    sort(C1, C1+5, menor_proporcionalmente);
    sort(C2, C2+5, menor_proporcionalmente);
    sort(Crand, Crand+30, menor_proporcionalmente);
    
    pair<Costo, Benef> C_con_algun_costo_0[7] = {{1, 4}, {2, 4}, {0, 4}, {3, 4}, {5, 5}, {0, 2}, {7, 14}};
    sort(C_con_algun_costo_0, C_con_algun_costo_0+7, menor_proporcionalmente);

    /* Prueba de "fuerza bruta":
    conj = Crand;
    n = 15;
    vector<pedido> S(Crand, Crand+n);
    w_max = costo_total_hasta(Crand, n)/4;
    inicializar_resuls_parcs(resuls_parcs, n);
    int res_bruto = knapsack_Bruto(S, w_max, 0);
    std::cout << "Rand/2:Bruto: benef = " << res_bruto << std::endl;
    res = back_tracking1(Crand, resuls_parcs, n, w_max, 0, cant_podas, cant_nodos_visitados);
    std::cout << "       BT1:   benef = " << res.first << std::endl;
    cant_podas = 0;
    cant_nodos_visitados = 0;
    res = back_tracking2(conj, n, w_max, cant_podas, cant_nodos_visitados);
    std::cout << "       BT2:   benef = " << res.first << std::endl;
    cant_podas = 0;
    cant_nodos_visitados = 0;
    cant_nodos_visitados_base = 0;*/

    /* Pruebo la funcion "dar_subconjuntos":
    vector<CBySub> subconjs;
    dar_subconjuntos(C, 0, 3, subconjs, 100);
    subconjs = vector<CBySub>();
    dar_subconjuntos(C0, 0, 3, subconjs, 100);
    subconjs = vector<CBySub>();
    dar_subconjuntos(C1, 0, 5, subconjs, 10);
    subconjs = vector<CBySub>();
    dar_subconjuntos(C2, 0, 5, subconjs, 10);
    subconjs = vector<CBySub>();
    dar_subconjuntos(Crand, 0, 5, subconjs, 120);
    subconjs = vector<CBySub>();*/

    return 0;
}