#ifndef TP_JUEGODEPALABRAS_REPOSITORIO_H
#define TP_JUEGODEPALABRAS_REPOSITORIO_H

#include <random>
#include <algorithm>

struct RepositorioGrande {
    // Crea un repositorio con muchas 'a'
    static Repositorio repositorioAB(){
        vector<Letra> res(2000, 'a');

        for (Nat i = 0; i < 1000; i ++) {
            res[2*i] = 'a';
            res[2*i + 1] = 'b';
        }

        return Repositorio(res.begin(), res.end());
    }

    // Crea un repositorio grande de aprox 15000 fichas
    static Repositorio repositorioGrande() {
        vector<Letra> res(0);
        res.reserve(15000);

        // 1 punto
        res.insert(res.end(), 12, 'e');
        res.insert(res.end(), 9, 'a');
        res.insert(res.end(), 9, 'i');
        res.insert(res.end(), 8, 'o');
        res.insert(res.end(), 6, 'n');
        res.insert(res.end(), 6, 'r');
        res.insert(res.end(), 6, 't');
        res.insert(res.end(), 4, 'l');
        res.insert(res.end(), 4, 's');
        res.insert(res.end(), 4, 'u');
        // 2 puntos
        res.insert(res.end(), 4, 'd');
        res.insert(res.end(), 3, 'g');
        // 3 puntos
        res.insert(res.end(), 2, 'b');
        res.insert(res.end(), 2, 'c');
        res.insert(res.end(), 2, 'm');
        res.insert(res.end(), 2, 'p');
        // 4 puntos
        res.insert(res.end(), 2, 'f');
        res.insert(res.end(), 2, 'h');
        res.insert(res.end(), 2, 'v');
        res.insert(res.end(), 2, 'w');
        res.insert(res.end(), 2, 'y');
        // 5 puntos
        res.insert(res.end(), 1, 'k');
        // 8 puntos
        res.insert(res.end(), 1, 'j');
        res.insert(res.end(), 1, 'x');
        // 10 puntos
        res.insert(res.end(), 1, 'q');
        res.insert(res.end(), 1, 'z');

        for (int i = 150; i > 0; i--){
            res.insert(res.end(), res.begin(), res.begin() + 98);
        }

        return std::move(Repositorio(res.begin(), res.end()));
    }

    // Crea un repositorio chico, de 100 fichas aprox
    static Repositorio repositorioChico() {
        vector<Letra> res(0);
        // 1 punto
        res.insert(res.end(), 12, 'e');
        res.insert(res.end(), 9, 'a');
        res.insert(res.end(), 9, 'i');
        res.insert(res.end(), 8, 'o');
        res.insert(res.end(), 6, 'n');
        res.insert(res.end(), 6, 'r');
        res.insert(res.end(), 6, 't');
        res.insert(res.end(), 4, 'l');
        res.insert(res.end(), 4, 's');
        res.insert(res.end(), 4, 'u');
        // 2 puntos
        res.insert(res.end(), 4, 'd');
        res.insert(res.end(), 3, 'g');
        // 3 puntos
        res.insert(res.end(), 2, 'b');
        res.insert(res.end(), 2, 'c');
        res.insert(res.end(), 2, 'm');
        res.insert(res.end(), 2, 'p');
        // 4 puntos
        res.insert(res.end(), 2, 'f');
        res.insert(res.end(), 2, 'h');
        res.insert(res.end(), 2, 'v');
        res.insert(res.end(), 2, 'w');
        res.insert(res.end(), 2, 'y');
        // 5 puntos
        res.insert(res.end(), 1, 'k');
        // 8 puntos
        res.insert(res.end(), 1, 'j');
        res.insert(res.end(), 1, 'x');
        // 10 puntos
        res.insert(res.end(), 1, 'q');
        res.insert(res.end(), 1, 'z');

        return Repositorio(res.begin(), res.end());
    }
};


#endif //TP_JUEGODEPALABRAS_REPOSITORIO_H
