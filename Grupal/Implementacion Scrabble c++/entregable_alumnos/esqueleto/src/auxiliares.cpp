#include "auxiliares.h"

ConjTrie pasarATrie(set<vector<Letra>> s){
    ConjTrie trie = ConjTrie();
    trie.agregarPalabras(s);
    return trie;
}

vector<Nat> convertirVector(map<Letra,Nat> map){
    vector<Nat> vector(TAMANIO_ALFABETO,1);
    for(pair<Letra, Nat> p:map){
        vector[ord(p.first)]=p.second;
    }
    return vector;
}

queue<Letra> proximosN(queue<Letra> &c, Nat cantFichas){
    queue<Letra> res;
    for(int i=0; i<cantFichas; i++){
        res.push(c.front());
        c.pop();
    }
    return res;
}

multiset<Letra> colaAMultiset(queue<Letra> c){
    multiset<Letra> mul;
    while(!c.empty()){
        mul.insert(c.front());
        c.pop();
    }
    return mul;
}

queue<Letra> pasarAQueue(list<Letra> mylist){
    queue<Letra> res;
    for (std::list<Letra>::iterator it=mylist.begin(); it != mylist.end(); ++it){
        res.push(*it);
    }
    return res;
}

std::list<Notificacion> pasarALista(queue<Notificacion> cola){
    std::list<Notificacion> res;
    while(!cola.empty()){
        res.push_back(cola.front());
        cola.pop();
    }
    return res;
}