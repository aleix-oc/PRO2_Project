/** @file Proceso.cc
    @brief Implementacion de la clase Proceso
*/
#include "Proceso.hh"

Proceso::Proceso() {
    nom = -1;
    memo = 0;
    tej = 0;
}

Proceso::Proceso(int n, int m, int t) {
    nom = n;
    memo = m;
    tej = t;
}

int Proceso::con_nom() const {
    return nom;
}

int Proceso::con_memo() const {
    return memo;
}

int Proceso::con_tej() const {
    return tej;
}

void Proceso::modify_tej(int t) {
    //Nomes s'utilitza quan sabem que el proces no sera eliminat
    tej -= t;
}

void Proceso::out_proces() const {
    cout << nom << " " << memo << " " << tej << '\n';
}
