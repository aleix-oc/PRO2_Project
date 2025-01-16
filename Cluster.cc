/** @file Cluster.cc
    @brief Implementacion de la clase Cluster
*/
#include "Cluster.hh"

Cluster::Cluster() {
    time = 0;
}

void Cluster::readcluster(BinTree<pair<string, int>>& t) {
    pair<string, int> p;
    cin >> p.first;
    if (p.first != "*") {
        cin >> p.second;
        Procesador pc(p.second);
        m.insert(make_pair(p.first, pc));
        BinTree<pair<string, int>> left;
        readcluster(left);
        BinTree<pair<string, int>> right;
        readcluster(right);
        t = BinTree<pair<string, int>> (p, left, right);
    }
}

void Cluster::configurar_cluster() {
    m.clear();
    readcluster(a);
}

void Cluster::modify(BinTree<pair<string, int>>& t, const string& idproc, bool& b) {
    if (not t.empty()) {
        if (t.value().first == idproc) {
            b = true;
            if (t.left().empty() and t.right().empty()) {
                cout << " " << idproc << '\n';
                m.erase(idproc);
                BinTree<pair<string, int>> nou;
                readcluster(nou);
                t = nou;
            }
            else cout << " " << idproc << '\n' << "error: procesador con auxiliares" << '\n';
        }
        else {
            BinTree<pair<string, int>> left = t.left();
            BinTree<pair<string, int>> right = t.right();
            modify(left, idproc, b);
            //Usamos el booleano para eficiencia
            if (not b) modify(right, idproc, b);
            t = BinTree<pair<string, int>>(t.value(), left, right);
        }
    }
}

void Cluster::modificar_cluster() {
    string idproc;
    cin >> idproc;
    map<string, Procesador>::iterator it = m.find(idproc);
    if (it == m.end()) cout << " " << idproc << '\n' << "error: no existe procesador" << '\n';
    else {
        if (not (it->second.no_tiene_procesos())) cout << " " << idproc << '\n' << "error: procesador con procesos" << '\n';
        else {
            bool b = false;
            modify(a, idproc, b);
        }
    }
}

void Cluster::alta_proceso_procesador() {
    string idproc;
    int name, mem, t;
    cin >> idproc >> name >> mem >> t;
    map<string, Procesador>::iterator it = m.find(idproc);
    if (it == m.end()) cout << " " << idproc << " " << name << '\n' << "error: no existe procesador" << '\n';
    else {
        if (it->second.search(name)) cout << " " << idproc << " " << name << '\n' << "error: ya existe proceso" << '\n';
        else {
            //Miramos si hay hueco para el proceso
            if (it->second.hueco(mem)) {
                cout << " " << idproc << " " << name << '\n';
                Proceso p(name, mem, t);
                it->second.alta(p);
            }
            else cout << " " << idproc << " " << name << '\n' << "error: no cabe proceso" << '\n';
        }
    }
}

void Cluster::baja_proceso_procesador() {
    string idproc;
    int name;
    cin >> idproc >> name;
    map<string, Procesador>::iterator it = m.find(idproc);
    if (it == m.end()) cout << " " << idproc << " " << name << '\n' << "error: no existe procesador" << '\n';
    else {
        if (not it->second.search(name)) cout << " " << idproc << " " << name << '\n' << "error: no existe proceso" << '\n';
        else {
           cout << " " << idproc << " " << name << '\n';
           //Una gestiona huecos, la otra los otros contenedores del procesador
           it->second.baja(name);
           it->second.borra(name);
        }
    }
}

void Cluster::avanzar_tiempo() {
    int n;
    cin >> n;
    time += n;
    cout << " " << n << '\n';
    for (map<string, Procesador>::iterator it = m.begin(); it != m.end(); ++it) {
        it->second.adelantar(n);
    }
}

void Cluster::compactar_memoria_procesador() {
    string idproc;
    cin >> idproc;
    map<string, Procesador>::iterator it = m.find(idproc);
    if (it == m.end()) cout << " " << idproc << '\n' << "error: no existe procesador" << '\n';
    else {
        cout << " " << idproc << '\n';
        it->second.compact();
    }
}

void Cluster::compactar_memoria_cluster() {
    cout << '\n';
    for (map<string, Procesador>::iterator it = m.begin(); it != m.end(); ++it) {
        it->second.compact();
    }
}

void Cluster::writecluster(const BinTree<pair<string, int>>& t) {
    if (not t.empty()) {
        cout << "(" << t.value().first;
        writecluster(t.left());
        writecluster(t.right());
        cout << ")";
    }
    else cout << " ";
}

void Cluster::imprimir_estructura_cluster() {
    cout << '\n';
    writecluster(a);
    cout << '\n';
}

void Cluster::imprimir_procesador() const{
    string id;
    cin >> id;
    map<string, Procesador>::const_iterator it = m.find(id);
    if (it == m.end()) cout << " " << id << '\n' << "error: no existe procesador" << '\n';
    else {
        cout << " " << id << '\n';
        it->second.print_proc();
    }
}

void Cluster::imprimir_procesadores_cluster() const{
    cout << '\n';
    for (map<string, Procesador>::const_iterator it = m.begin(); it != m.end(); ++it) {
        cout << it->first << '\n';
        it->second.print_proc();
    }
}

void Cluster::enviar(const Proceso& p, bool& b) {
    //Declaramos todas las variables auxiliares usadas para comparar si un procesador es aceptable
    int count = 0;
    int aux = 0;
    string candidato = " ";
    int minaj = 0;
    int free = 0;
    int pmemo = p.con_memo();
    int pnombre = p.con_nom();
    send(a, pmemo, pnombre, b, count, aux, candidato, minaj, free);
    //Si ha sido aceptado
    if (b) {
        map<string, Procesador>::iterator it = m.find(candidato);
        it->second.alta(p);
    }
}

void Cluster::send(const BinTree<pair<string, int>>& a,const int& pmemo, const int& pnombre, bool& b, int& count, int& aux, string& candidato, int& minaj, int& free) {
    if (not a.empty()) {
        map <string, Procesador>::iterator it = m.find(a.value().first);
        //Si hay hueco y no esta el proceso en el procesador
        if (it->second.hueco(pmemo) and not it->second.search(pnombre)) {
            int huecoaux = it->second.hueco_ajustado(pmemo);
            int freeaux = it->second.con_free();
            b = true;
            //Si es el primero que encontramos
            if (candidato == " ") {
                candidato = it->first;
                aux = count;
                minaj = huecoaux;
                free = freeaux;
            }
            else {
                if (huecoaux < minaj) {
                    candidato = it->first;
                    aux = count;
                    minaj = huecoaux;
                    free = freeaux;
                }
                else if (huecoaux == minaj) {
                    if (freeaux > free) {
                        candidato = it->first;
                        aux = count;
                        free = freeaux;
                    }
                    else if (freeaux == free and count < aux) {
                        candidato = it->first;
                        aux = count;
                    }
                }
            }
        }
        ++count;
        int auxiliarheight = count;
        BinTree<pair<string, int>> left = a.left();
        BinTree<pair<string, int>> right = a.right();
        send(left, pmemo, pnombre, b, count, aux, candidato, minaj, free);
        //Usamos auxiliarheight en el arbol derecho porque count puede haberse modificado
        send(right, pmemo, pnombre, b, auxiliarheight, aux, candidato, minaj, free);
    }
}
