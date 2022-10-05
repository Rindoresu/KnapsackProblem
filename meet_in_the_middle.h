//
// Created by nahuel on 3/04/19.
//

#ifndef TP1_2_MEET_IN_THE_MIDDLE_H
#define TP1_2_MEET_IN_THE_MIDDLE_H

#include "terminologia.h"

using namespace std;

bool comparador_costo(const CBySub& a, const CBySub& b);
//bool comparador_costo_inverso(const CBySub& a, const CBySub& b);
void dar_subconjuntos(pair<Costo, Benef> *conj, int prin, int fin, vector<CBySub> &subconjuntos, Costo w_max);
pair<Benef, Conj_ind> meet_in(pair<Costo, Benef>* conj, int fin, uint w_max);

#endif //TP1_2_MEET_IN_THE_MIDDLE_H
