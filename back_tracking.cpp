//
// Created by nahuel on 26/03/19.
//

#include "back_tracking.h"

#define MAX(a, b) (a >= b) ? a : b

pair<Benef, Conj_ind> back_tracking_base(pair<Costo, Benef>* conj, int fin, uint w_rest, uint& cant_nodos_visitados){
    if(fin == 0) return {0, CONJ_VACIO};
    ++cant_nodos_visitados;
    int ultim = fin-1;
    Costo& w_ultim = conj[ultim].first;
    Benef& p_ultim = conj[ultim].second;
    pair<Benef, Conj_ind> lo_uso = {0, CONJ_VACIO};
    pair<Benef, Conj_ind> no_lo_uso;
    bool entra_x_i = (w_ultim <= w_rest);
    if(entra_x_i){
        lo_uso = back_tracking_base(conj, ultim, w_rest - w_ultim, cant_nodos_visitados);
        lo_uso.first += p_ultim;
        lo_uso.second.push_back(ultim);
    }
    no_lo_uso = back_tracking_base(conj, ultim, w_rest, cant_nodos_visitados);
    return (lo_uso.first >= no_lo_uso.first) ? lo_uso : no_lo_uso;
}

//-------------------------------------------------------------------------------------------------------
//pair<Benef, Conj_ind> back_tracking1(pair<Costo, Benef> *conj, pair<Costo, Benef> *resuls_parcs, int fin, Costo w_rest, Benef benef_acumul, uint& cant_podas, uint& cant_nodos_visitados){
pair<Benef, Conj_ind> back_tracking1(pair<Costo, Benef> *conj, pair<Costo, Benef> *resuls_parcs, int fin, Costo w_rest, Benef benef_acumul){
    if(fin == 0) return {0, CONJ_VACIO};
    //++cant_nodos_visitados;
    int ultim = fin-1;
    Costo& mejor_w_hasta_i = resuls_parcs[ultim].first;
    Benef& mejor_p_hasta_i = resuls_parcs[ultim].second;
    // w_max <= C_i0 && p_acumul <= P_i0
    bool no_optimo = (w_rest <= mejor_w_hasta_i && benef_acumul <= mejor_p_hasta_i);
    Costo& w_ultim = conj[ultim].first;
    Benef& p_ultim = conj[ultim].second;
    if(no_optimo){
        //++cant_podas;
        return {0, CONJ_VACIO};
    }
    else {
        mejor_w_hasta_i = w_rest;
        mejor_p_hasta_i = benef_acumul;
    }
    pair<Benef, Conj_ind> lo_uso = {0, CONJ_VACIO};
    pair<Benef, Conj_ind> no_lo_uso;
    bool entra_x_i = (w_ultim <= w_rest);
    if(entra_x_i){
        //lo_uso = back_tracking1(conj, resuls_parcs, ultim, w_rest - w_ultim, benef_acumul + p_ultim, cant_podas, cant_nodos_visitados);
        lo_uso = back_tracking1(conj, resuls_parcs, ultim, w_rest - w_ultim, benef_acumul + p_ultim);
        lo_uso.first += p_ultim;
        lo_uso.second.push_back(ultim);
    }
    //no_lo_uso = back_tracking1(conj, resuls_parcs, ultim, w_rest, benef_acumul, cant_podas, cant_nodos_visitados);
    no_lo_uso = back_tracking1(conj, resuls_parcs, ultim, w_rest, benef_acumul);
    return (lo_uso.first >= no_lo_uso.first) ? lo_uso : no_lo_uso;
}

//-------------------------------------------------------------------------------------------------------
pair<Costo, Benef>* copiar_conj(pair<Costo, Benef>* conj, uint n){
    pair<Costo, Benef>* copia = new pair<Costo, Benef>[n];
    for(uint i = 0; i < n; ++i)
        copia[i] = conj[i];
    return copia;
}

bool menor_proporcionalmente(pair<Costo, Benef> a, pair<Costo, Benef> b){
    if(a.first)
        if(b.first)
            return (double)(a.second)/a.first < (double)(b.second)/b.first;   //Si ninguno tiene costo 0, puedo hacer la división.
        else
            return true;    //Si "b" tiene costo 0 pero "a" no, considero a "b" mayor proporsionalmente.
    else
        return false;   //Si "a" tiene costo 0 lo concidero mayor proporcionalmente (no importa si b también tiene costo 0).
}

pair<Benef, int> cota_super(pair<Costo, Benef>* conj, int fin, uint w_rest){
    Costo costo_acumulado = 0;
    Benef benef_acumulado = 0;
    int i = fin - 1;
    while(i >= 0 && costo_acumulado + conj[i].first <= w_rest){
        costo_acumulado += conj[i].first;
        benef_acumulado += conj[i].second;
        --i;
    }
    if(i >= 0) { //costo_acumulado + conj[i].first > w_rest
        benef_acumulado += ceil(conj[i].second * (double) (w_rest - costo_acumulado) / (double) (conj[i].first));
        i = INT_MIN;
    }
    return {benef_acumulado, i+1};
}

//void recursionBT2(pair<Costo, Benef>* conj, int fin, uint w_rest, Benef& benef_acumul, Benef& benef_max, Conj_ind& conj_acumul, Conj_ind& conj_max, uint& cant_podas, uint& cant_nodos_visitados){
void recursionBT2(pair<Costo, Benef>* conj, int fin, uint w_rest, Benef& benef_acumul, Benef& benef_max, Conj_ind& conj_acumul, Conj_ind& conj_max){
    if(fin == 0){
        if(benef_acumul > benef_max) {
            benef_max = benef_acumul;
            conj_max = conj_acumul;
        }
        return;
    }
    //++cant_nodos_visitados;
    pair<Benef, int> cota_s = cota_super(conj, fin, w_rest);
    if(benef_acumul + cota_s.first <= benef_max){ //Si no se puede mejorar la mejor solución que se tiene...
        //++cant_podas;
        return; //Podamos.
    }else if(cota_s.second >= 0){ //i.e., se puede alcanzar la cota con los elem. desde "fin" (exclusive) hasta "cota_s.second" (inclusive).
        //++cant_podas;
        benef_max = benef_acumul + cota_s.first;
        conj_max = conj_acumul;
        for(int i = fin-1; i >= cota_s.second; --i)
            conj_max.push_back(i);
        return;
    }
    int ultim = fin-1;
    Costo& w_ultim = conj[ultim].first;
    Benef& p_ultim = conj[ultim].second;
    bool entra_x_i = (w_ultim <= w_rest);
    if(entra_x_i){
        benef_acumul += p_ultim;
        conj_acumul.push_back(ultim);
        //recursionBT2(conj, ultim, w_rest - w_ultim, benef_acumul, benef_max, conj_acumul, conj_max, cant_podas, cant_nodos_visitados); //Caso en el que USO el próximo elem.
        recursionBT2(conj, ultim, w_rest - w_ultim, benef_acumul, benef_max, conj_acumul, conj_max); //Caso en el que USO el próximo elem.
        benef_acumul -= p_ultim;
        conj_acumul.pop_back();
    }
    //recursionBT2(conj, ultim, w_rest, benef_acumul, benef_max, conj_acumul, conj_max, cant_podas, cant_nodos_visitados); //Caso en el que NO uso el próximo elem.
    recursionBT2(conj, ultim, w_rest, benef_acumul, benef_max, conj_acumul, conj_max); //Caso en el que NO uso el próximo elem.
}

//pair<Benef, Conj_ind> back_tracking2(pair<Costo, Benef>* conj, int fin, uint w_rest, uint& cant_podas, uint& cant_nodos_visitados){
pair<Benef, Conj_ind> back_tracking2(pair<Costo, Benef>* conj, int fin, uint w_rest){
    //pair<Costo, Benef>* conj_ordenado = copiar_conj(conj, fin);
    //sort(conj_ordenado, conj_ordenado + fin, menor_proporcionalmente);
    sort(conj, conj + fin, menor_proporcionalmente);
    Benef benef_acumul = 0;
    Benef benef_max = 0;
    Conj_ind conj_acumul = CONJ_VACIO;
    Conj_ind conj_max = CONJ_VACIO;
    //recursionBT2(conj_ordenado, fin, w_rest, benef_acumul, benef_max, conj_acumul, conj_max, cant_podas, cant_nodos_visitados);
    //recursionBT2(conj, fin, w_rest, benef_acumul, benef_max, conj_acumul, conj_max, cant_podas, cant_nodos_visitados);
    recursionBT2(conj, fin, w_rest, benef_acumul, benef_max, conj_acumul, conj_max);
    //delete conj_ordenado;
    return {benef_max, conj_max};
}