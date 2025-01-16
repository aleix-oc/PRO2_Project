/** @file Area.hh
    @brief Especificacion de la clase Area
*/
#ifndef _AREA_HH_
#define _AREA_HH_

#include "Cluster.hh"
#include "Proceso.hh"
#ifndef NO_DIAGRAM
#include <map>
#include <list>
#include <set>
#include <iostream>
#endif
using namespace std;

/** @brief Estructura que gestionara los procesos del area
*/
struct Prioridad {
    int colocados = 0;
    int rechazados = 0;
    list<Proceso> l;
    set<int> nomsp;
};

/** @class Area
    @brief Representa un area de espera
*/
class Area {
private:
/** @brief Estructura del area
*/
  map<string, Prioridad> mp;
public:
    //CONSTRUCTORAS
    /** @brief Creadora por defecto
      \pre <em>cierto</em>
      \post Area vacia
    */
    Area();

    /** @brief Lee un entero positivo n y despues lee n prioridades
      \pre n > 0
      \post Area con n prioridades
    */
    void inicializar_area();

    //MODIFICADORES
    /** @brief Añade una prioridad al area
      \pre Area no vacia
      \post Hay una prioridad más en el area
    */
    void alta_prioridad();

    /** @brief Elimina una prioridad del area
      \pre Area no vacia
      \post Se ha eliminado una prioridad del area
    */
    void baja_prioridad();

    /** @brief Inserta en el area un proceso en una cierta prioridad
      \pre Area no vacia
      \post El proceso pasa a estar en una prioridad ya existente del area
    */
    void alta_proceso_espera();

    /** @brief Intenta enviar n procesos pendientes al cluster
      \pre n > 0
      \post Se han enviado ciertos procesos al cluster, otros han sido rechazados
    */
    void enviar_procesos_cluster(Cluster& c);

    //ESCRITURA
    /** @brief Escribe una prioridad del area
      \pre <em>cierto</em>
      \post En la salida se ven todos los procesos de una prioridad, sus envios y sus rechazos
    */
    void imprimir_prioridad() const;

    /** @brief Escribe todas las prioridades del area
      \pre <em>cierto</em>
      \post En la salida se ven todos los datos de cada prioridad del area por orden creciente de prioridad
    */
    void imprimir_area_espera() const;

};
#endif
