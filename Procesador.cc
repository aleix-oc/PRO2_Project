/** @file Procesador.cc
    @brief Implementacion de la clase Procesador
*/
#include "Procesador.hh"

Procesador::Procesador() {
}

Procesador::Procesador(int n) {
    memory = n;
    huecos[n].insert(0);
    freememory = n;
}

int Procesador::con_free() const {
    return freememory;
}

int Procesador::hueco_ajustado(int m) {
    //Se usa cuando ya se sabe que hay hueco minimo para m, que existe el lowerbound
    map<int, set<int>>::const_iterator it = huecos.lower_bound(m);
    return it->first;
}

bool Procesador::hueco(int m) {
    map<int, set<int>>::const_iterator it = huecos.lower_bound(m);
    if (it == huecos.end()) return false;
    return true;
}


bool Procesador::no_tiene_procesos() const {
    return mproc.empty();
}

bool Procesador::search(int n) const {
    map<int, int>::const_iterator it = mname.find(n);
    if (it != mname.end()) return true;
    return false;
}

void Procesador::baja(int n) {
    //Gestionamos el mapa de huecos
    map<int, int>::iterator it = mname.find(n);
    map<int, Proceso>::iterator it2 = mproc.find(it->second);
    map<int, Proceso>::iterator it3 = it2;
    ++it3;
    //Miramos si el proceso esta al principio, al final o a la mitad del mapa de procesos
    if (it2 == mproc.begin()) {
        //Si es unico el proceso
        if (it3 == mproc.end()) {
            huecos.clear();
            huecos[memory].insert(0);
        }
        else {
            int x = it2->second.con_memo();
            //Si esta al principio de la memoria
            if (it2->first == 0) {
                //Si hay hueco entre el proceso actual y el de su derecha
                if (it3->first == x) huecos[x].insert(0);
                else {
                    huecos[it3->first - x].erase(x);
                    if (huecos[it3->first - x].empty()) huecos.erase(it3->first - x);
                    huecos[it3->first].insert(0);
                }
            }
            else {
                //Si hay hueco entre el proceso actual y el de su derecha
                if (it3->first == it2->first + x) {
                    huecos[it2->first].erase(0);
                    if (huecos[it2->first].empty()) huecos.erase(it2->first);
                    huecos[it3->first].insert(0);
                }
                else {
                    huecos[it2->first].erase(0);
                    if (huecos[it2->first].empty()) huecos.erase(it2->first);
                    huecos[it3->first - (it2->first + x)].erase(it2->first + x);
                    if (huecos[it3->first - (it2->first + x)].empty()) huecos.erase(it3->first - (it2->first + x));
                    huecos[it3->first].insert(0);
                }
            }
        }
    }
    else if (it3 == mproc.end()) {
        map<int, Proceso>::iterator it4 = it2;
        --it4;
        int x = it2->second.con_memo();
        int y = it4->second.con_memo();
        //Miramos si el proceso esta en el extremo final de la memoria
        if (it2->first + x == memory) {
            //Si hay hueco entre el proceso izquierdo y el actual
            if ((it4->first + y) == it2->first) {
                huecos[x].insert(it4->first + y);
            }
            else {
                huecos[it2->first - (it4->first + y)].erase(it4->first + y);
                if (huecos[it2->first - (it4->first + y)].empty()) huecos.erase(it2->first - (it4->first + y));
                huecos[(it2->first - (it4->first + y)) + x].insert(it4->first + y);
            }
        }
        else {
            //Si hay hueco entre el proceso izquierdo y el actual
            if ((it4->first + y) == it2->first) {
                huecos[memory - (it2->first + x)].erase(it2->first + x);
                if (huecos[memory - (it2->first + x)].empty()) huecos.erase(memory - (it2->first + x));
                huecos[memory - it2->first].insert(it4->first + y);
            }
            else {
                huecos[memory - (it2->first + x)].erase(it2->first + x);
                if (huecos[memory - (it2->first + x)].empty()) huecos.erase(memory - (it2->first + x));
                huecos[it2->first - (it4->first + y)].erase(it4->first + y);
                if (huecos[it2->first - (it4->first + y)].empty()) huecos.erase(it2->first - (it4->first + y));
                huecos[memory - (it4->first + y)].insert(it4->first + y);
            }
        }
    }
    else {
        map<int, Proceso>::iterator it4 = it2;
        --it4;
        int x = it2->second.con_memo();
        int y = it4->second.con_memo();
        //Si no hay huecos en izquierda-actual-derecha
        if ((it2->first == (it4->first + y)) and (it3->first == (it2->first + x))) {
            huecos[x].insert(it4->first + y);
        }
        //Si hay hueco izquierda-actual y no actual-derecha
        else if ((it2->first != (it4->first + y)) and (it3->first == (it2->first + x))) {
            huecos[it2->first - (it4->first + y)].erase(it4->first + y);
            if (huecos[it2->first - (it4->first + y)].empty()) huecos.erase(it2->first - (it4->first + y));
            huecos[(it2->first - (it4->first + y)) + x].insert(it4->first + y);
        }
        //Si no hay hueco izquierda-actual pero hay actual-derecha
        else if ((it2->first == (it4->first + y)) and (it3->first != (it2->first + x))) {
            huecos[it3->first - (it2->first + x)].erase(it2->first + x);
            if (huecos[it3->first - (it2->first + x)].empty()) huecos.erase(it3->first - (it2->first + x));
            huecos[it3->first - it2->first].insert(it2->first);
        }
        //Si hay hueco izquierda-actual y actual-derecha
        else {
            huecos[it2->first - (it4->first + y)].erase(it4->first + y);
            if (huecos[it2->first - (it4->first + y)].empty()) huecos.erase(it2->first - (it4->first + y));
            huecos[it3->first - (it2->first + x)].erase(it2->first + x);
            if (huecos[it3->first - (it2->first + x)].empty()) huecos.erase(it3->first - (it2->first + x));
            huecos[it3->first - (it4->first + y)].insert(it4->first + y);
        }
    }
}

void Procesador::borra(int n) {
    //Gestionamos 2 de los 3 mapas del procesador
    map<int, int>::iterator it = mname.find(n);
    map<int, Proceso>::iterator it2 = mproc.find(it->second);
    freememory += it2->second.con_memo();
    mname.erase(n);
    mproc.erase(it2);
}

void Procesador::adelantar(int n) {
    map<int, Proceso>::iterator it = mproc.begin();
    while (it != mproc.end()) {
        //Si el tiempo avanzado es mayor que el del proceso se elimina, si no se modifica su tiempo
        if (it->second.con_tej() <= n) {
            int name = it->second.con_nom();
            baja(name);
            freememory += it->second.con_memo();
            mname.erase(name);
            it = mproc.erase(it);
        }
        else {
            it->second.modify_tej(n);
            ++it;
        }
    }
}

void Procesador::alta(const Proceso&p) {
    //La utilizamos ya sabiendo que hay lowerbound de la memoria del proceso, que hay huecos
    map<int, set<int>>::iterator it = huecos.lower_bound(p.con_memo());
    set<int>::iterator aux = it->second.begin();
    mname.insert(make_pair(p.con_nom(), *aux));
    mproc.insert(make_pair(*aux, p));
    int m = p.con_memo();
    freememory -= m;
    //Gestionamos el mapa de huecos dependiendo de si p ocupa el hueco entero al que se mete o no
    if (it->first == m) {
        it->second.erase(aux);
        if (it->second.empty()) huecos.erase(it);
    }
    else {
        huecos[it->first - m].insert(*aux + m);
        it->second.erase(aux);
        if (it->second.empty()) huecos.erase(it);
    }
}

void Procesador::compact() {
    if (not mproc.empty()) {
        map<int, Proceso>::iterator it = mproc.begin();
        map<int, Proceso>::iterator it2 = it;
        ++it2;
        //Miramos si hay un proceso o mas de uno en la memoria
        if (it2 == mproc.end()) {
            int aux = it->second.con_nom();
            int maux = it->second.con_memo();
            //Si ya estaba al principio de la memoria no se modifica nada
            if (it->first != 0) {
                mname.erase(aux);
                mname.insert(make_pair(aux, 0));
                mproc.insert(make_pair(0,it->second));
                mproc.erase(it->first);
            }
            if(maux != memory) {
                huecos.clear();
                huecos[memory-maux].insert(maux);
            }
        }
        else {
            //Si ya estaba al principio de la memoria no se modifica nada
            if(it->first != 0) {
            mname.erase(it->second.con_nom());
            mname.insert(make_pair(it->second.con_nom(), 0));
            mproc.insert(make_pair(0,it->second));
            it = mproc.erase(it);
            --it;
            }
            //Compactamos los huecos restantes usando it2 para mirar el proceso derecho y it para el izquierdo
            while(it2 != mproc.end()) {
                int maux = it->second.con_memo();
                if(it->first + maux != it2->first) {
                    mname.erase(it2->second.con_nom());
                    mname.insert(make_pair(it2->second.con_nom(), it->first + maux));
                    mproc.insert(make_pair(it->first + maux,it2->second));
                    it2 = mproc.erase(it2);
                    --it2;
                }
                ++it2;
                ++it;
            }
            if(freememory != 0) {
                huecos.clear();
                huecos[freememory].insert(memory-freememory);
            }
        }
    }
}

void Procesador::print_proc() const {
    for(map<int, Proceso>::const_iterator it = mproc.begin(); it != mproc.end(); ++it) {
        cout << it->first << " ";
        it->second.out_proces();
    }
}
