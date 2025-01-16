/** @file Area.cc
    @brief Implementacion de la clase Area
*/
#include "Area.hh"

Area::Area() {
}

void Area::inicializar_area() {
    int n;
    cin >> n;
    for (int i = 0; i < n; ++i) {
        string idprio;
        cin >> idprio;
        Prioridad p;
        mp.insert(make_pair(idprio, p));
    }
}

void Area::alta_prioridad() {
    string idprio;
    cin >> idprio;
    map<string, Prioridad>::iterator it = mp.find(idprio);
    if (it != mp.end()) cout << " " << idprio << '\n' << "error: ya existe prioridad" << '\n';
    else {
        cout << " " << idprio << '\n';
        Prioridad p;
        mp.insert(make_pair(idprio, p));
    }
}

void Area::baja_prioridad() {
    string idprio;
    cin >> idprio;
    map<string, Prioridad>::iterator it = mp.find(idprio);
    if (it == mp.end()) cout << " " << idprio << '\n' << "error: no existe prioridad" << '\n';
    else if (not it->second.l.empty()) cout << " " << idprio << '\n' << "error: prioridad con procesos" << '\n';
    else {
        cout << " " << idprio << '\n';
        mp.erase(it);
    }
}

void Area::alta_proceso_espera() {
    string idprio;
    int name, mem, t;
    cin >> idprio >> name >> mem >> t;
    map<string, Prioridad>::iterator it = mp.find(idprio);
    if (it == mp.end()) cout << " " << idprio << " " << name << '\n' << "error: no existe prioridad" << '\n';
    else {
        set<int>::iterator it2 = it->second.nomsp.find(name);
        if (it2 != it->second.nomsp.end()) cout << " " << idprio << " " << name << '\n' << "error: ya existe proceso" << '\n';
        else {
            cout << " " << idprio << " " << name << '\n';
            //Actualizamos el set dde nombres y la lista de procesos
            it->second.nomsp.insert(name);
            Proceso p(name, mem, t);
            it->second.l.insert(it->second.l.end(), p);
        }
    }
}

void Area::enviar_procesos_cluster(Cluster& c) {
    int n;
    cin >> n;
    cout << " " << n << '\n';
    int enviados = 0;
    map<string, Prioridad>::iterator it = mp.begin();
    //Bucle sobre las prioridades
    while (enviados < n and it != mp.end()) {
        bool b = false;
        int x = it->second.l.size();
        list<Proceso>::iterator it2 = it->second.l.begin();
        int visitados = 0;
        //Bucle sobre los procesos de la prioridad, visitados se usa por el caso de que un proceso sea rechazado y vuelva al final de la lista
        while (enviados < n and visitados < x) {
            Proceso aux = *it2;
            it2 = it->second.l.erase(it2);
            it->second.nomsp.erase(aux.con_nom());
            c.enviar(aux, b);
            if (b) {
                b = false;
                ++it->second.colocados;
                ++enviados;
            }
            else {
                ++it->second.rechazados;
                //Si es rechazado vuelve a la lista
                it->second.l.insert(it->second.l.end(), aux);
                it->second.nomsp.insert(aux.con_nom());
            }
            ++visitados;
        }
        ++it;
    }
}

void Area::imprimir_prioridad() const {
    string idprio;
    cin >> idprio;
    map<string, Prioridad>::const_iterator it = mp.find(idprio);
    if (it == mp.end()) cout << " " << idprio << '\n' << "error: no existe prioridad" << '\n';
    else {
        cout << " " << idprio << '\n';
        for (list<Proceso>::const_iterator it2 = it->second.l.begin(); it2 != it->second.l.end(); ++it2) {
            it2->out_proces();
        }
        cout << it->second.colocados << " " << it->second.rechazados << '\n';
    }
}

void Area::imprimir_area_espera() const {
    cout << '\n';
    for (map<string, Prioridad>::const_iterator it = mp.begin(); it != mp.end(); ++it) {
        cout << it->first << '\n';
        for (list<Proceso>::const_iterator it2 = it->second.l.begin(); it2 != it->second.l.end(); ++it2) {
            it2->out_proces();
        }
        cout << it->second.colocados << " " << it->second.rechazados << '\n';
    }
}
