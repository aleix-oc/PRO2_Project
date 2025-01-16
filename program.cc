/** @mainpage Simulacion del rendimiento de procesadores interconectados
*/
/** @file program.cc
    @brief Funcion principal
*/
#include "Cluster.hh"
#include "Area.hh"
#ifndef NO_DIAGRAM
#include <iostream>
#endif
using namespace std;

int main() {
    Cluster c;
    c.configurar_cluster();
    Area a;
    a.inicializar_area();
    string com;
    cin >> com;
    while (com != "fin") {
        if (com == "cc" or com == "configurar_cluster") {
            cout << "#" << com << '\n';
            c.configurar_cluster();
        }
        else if (com == "mc" or com == "modificar_cluster") {
            cout << "#" << com;
            c.modificar_cluster();
        }
        else if (com == "ap" or com == "alta_prioridad") {
            cout << "#" << com;
            a.alta_prioridad();
        }
        else if (com == "bp" or com == "baja_prioridad") {
            cout << "#" << com;
            a.baja_prioridad();
        }
        else if (com == "ape" or com == "alta_proceso_espera") {
            cout << "#" << com;
            a.alta_proceso_espera();
        }
        else if (com == "app" or com == "alta_proceso_procesador") {
            cout << "#" << com;
            c.alta_proceso_procesador();
        }
        else if (com == "bpp" or com == "baja_proceso_procesador") {
            cout << "#" << com;
            c.baja_proceso_procesador();
        }
        else if (com == "epc" or com == "enviar_procesos_cluster") {
            cout << "#" << com;
            a.enviar_procesos_cluster(c);
        }
        else if (com == "at" or com == "avanzar_tiempo") {
            cout << "#" << com;
            c.avanzar_tiempo();
        }
        else if (com == "ipri" or com == "imprimir_prioridad") {
            cout << "#" << com;
            a.imprimir_prioridad();
        }
        else if (com == "iae" or com == "imprimir_area_espera") {
            cout << "#" << com;
            a.imprimir_area_espera();
        }
        else if (com == "ipro" or com == "imprimir_procesador") {
            cout << "#" << com;
            c.imprimir_procesador();
        }
        else if (com == "ipc" or com == "imprimir_procesadores_cluster") {
            cout << "#" << com;
            c.imprimir_procesadores_cluster();
        }
        else if (com == "iec" or com == "imprimir_estructura_cluster") {
            cout << "#" << com;
            c.imprimir_estructura_cluster();
        }
        else if (com == "cmp" or com == "compactar_memoria_procesador") {
            cout << "#" << com;
            c.compactar_memoria_procesador();
        }
        else if (com == "cmc" or com == "compactar_memoria_cluster") {
            cout << "#" << com;
            c.compactar_memoria_cluster();
        }
        cin >> com;
    }
}
