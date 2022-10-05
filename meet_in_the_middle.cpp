//
// Created by nahuel on 3/04/19.
//

#include "meet_in_the_middle.h"

bool comparador_costo(const CBySub& a, const CBySub& b){return a.costo < b.costo;}
//bool comparador_costo_inverso(const CBySub& a, const CBySub& b){return a.costo > b.costo;}

void dar_subconjuntos(pair<Costo, Benef> *conj, int prin, int fin, vector<CBySub> &subconjuntos, Costo w_max){
    subconjuntos.push_back({0,0,CONJ_VACIO});
    for(int i = prin; i < fin; ++i){
        size_t n = subconjuntos.size();
        for(size_t j = 0; j < n; ++j){
            if(subconjuntos[j].costo + conj[i].first <= w_max){ //Si puedo agregar el elemento x_i al subconjunto s_j...
                CBySub nuevo_subconj = {subconjuntos[j].costo + conj[i].first, subconjuntos[j].benef + conj[i].second, subconjuntos[j].conj}; //aumento el costo y el beneficio del subconjunto y...
                nuevo_subconj.conj.push_back(i); //le agrego el índice "i" al nuevo conjunto de índices.
                subconjuntos.push_back(nuevo_subconj);
            }
        }
    }
}

pair<Benef, Conj_ind> meet_in(pair<Costo, Benef>* conj, int fin, uint w_max){
    int mitad = fin/2;
    Benef benef_max = 0;
    Conj_ind conj_max = CONJ_VACIO;
    vector<CBySub> subconjs_prim_mitad;
    vector<CBySub> subconjs_segu_mitad;
    dar_subconjuntos(conj, 0, mitad, subconjs_prim_mitad, w_max);
    dar_subconjuntos(conj, mitad, fin, subconjs_segu_mitad, w_max);
    sort(subconjs_prim_mitad.begin(), subconjs_prim_mitad.end(), comparador_costo);
    sort(subconjs_segu_mitad.begin(), subconjs_segu_mitad.end(), comparador_costo);
    int i_res = 0;
    int j = 0; //"j" es el índice para los subconjuntos de la 2º mitad.
    int j_max = 0;
    int j_res = 0;
    Benef benef_max_segu = 0;
    for(int i = subconjs_prim_mitad.size()-1; i >= 0; --i){ //"i" es el índice para los subconjuntos de la 1º mitad.
        while(j < subconjs_segu_mitad.size() && subconjs_prim_mitad[i].costo + subconjs_segu_mitad[j].costo <= w_max){
            if(subconjs_segu_mitad[j].benef > benef_max_segu) {
                benef_max_segu = subconjs_segu_mitad[j].benef;
                j_max = j;
            }
            ++j;
        }
        if(subconjs_prim_mitad[i].benef + benef_max_segu > benef_max){
            benef_max = subconjs_prim_mitad[i].benef + benef_max_segu;
            i_res = i;
            j_res = j_max;
        }
    }
    Conj_ind res;
    res.splice(res.end(), subconjs_prim_mitad[i_res].conj, subconjs_prim_mitad[i_res].conj.begin(), subconjs_prim_mitad[i_res].conj.end());
    res.splice(res.end(), subconjs_segu_mitad[j_res].conj, subconjs_segu_mitad[j_res].conj.begin(), subconjs_segu_mitad[j_res].conj.end());
    return {benef_max, res};
}
//{}