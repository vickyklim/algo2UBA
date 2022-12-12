//
// Created by clinux01 on 18/11/22.
//

#ifndef TP_JUEGODEPALABRAS_AUXILIARES_H
#define TP_JUEGODEPALABRAS_AUXILIARES_H

#include "ConjTrie.h"
#include <queue>
#include "Notificacion.h"

ConjTrie pasarATrie(set<vector<Letra>> s);

vector<Nat> convertirVector(map<Letra,Nat> map);

queue<Letra> proximosN(queue<Letra> &c, Nat cantFichas);

multiset<Letra> colaAMultiset(queue<Letra> c);

queue<Letra> pasarAQueue(list<Letra> mylist);

std::list<Notificacion> pasarALista(queue<Notificacion> cola);



#endif //TP_JUEGODEPALABRAS_AUXILIARES_H
