//
// Created by nahuel on 5/04/19.
//

#ifndef TP1_2_TERMINOLOGIA_H
#define TP1_2_TERMINOLOGIA_H

#include <list>
#include <utility>
#include <vector>
#include <limits.h>
#include <math.h>
#include <algorithm>

typedef unsigned int uint;
typedef unsigned int Costo;
typedef unsigned int Benef;
typedef std::list<int> Conj_ind;

struct CBySub{
    Costo costo;
    Benef benef;
    Conj_ind conj;
};

#define CONJ_VACIO list<int>()

#endif //TP1_2_TERMINOLOGIA_H
