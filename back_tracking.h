#ifndef TP1_2_PROBL_MOCHILA_H
#define TP1_2_PROBL_MOCHILA_H

#include "terminologia.h"

using namespace std;

pair<Benef, Conj_ind> back_tracking_base(pair<Costo, Benef>* conj, int fin, uint w_rest, uint& cant_nodos_visitados);
//pair<Benef, Conj_ind> back_tracking1(pair<Costo, Benef>* conj, pair<Costo, Benef>* resuls_parcs, int fin, Costo w_rest, Benef benef_acumul, uint& cant_podas, uint& cant_nodos_visitados);
pair<Benef, Conj_ind> back_tracking1(pair<Costo, Benef>* conj, pair<Costo, Benef>* resuls_parcs, int fin, Costo w_rest, Benef benef_acumul);
//pair<Benef, Conj_ind> back_tracking2(pair<Costo, Benef>* conj, int fin, uint w_rest, uint& cant_podas, uint& cant_nodos_visitados);
pair<Benef, Conj_ind> back_tracking2(pair<Costo, Benef>* conj, int fin, uint w_rest);
//void recursionBT2(pair<Costo, Benef>* conj, int fin, uint w_rest, Benef& benef_acumul, Benef& benef_max, Conj_ind& conj_acumul, Conj_ind& conj_max, uint& cant_podas, uint& cant_nodos_visitados);
void recursionBT2(pair<Costo, Benef>* conj, int fin, uint w_rest, Benef& benef_acumul, Benef& benef_max, Conj_ind& conj_acumul, Conj_ind& conj_max);
pair<Benef, int> cota_super(pair<Costo, Benef>* conj, int fin, uint w_rest);
bool menor_proporcionalmente(pair<Costo, Benef> a, pair<Costo, Benef> b);
pair<Costo, Benef>* copiar_conj(pair<Costo, Benef>* conj, uint n);

#endif //TP1_2_PROBL_MOCHILA_H
