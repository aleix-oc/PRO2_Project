/** @file Procesador.hh
    @brief Especificacion de la clase Procesador
*/
#ifndef _PROCESADOR_HH_
#define _PROCESADOR_HH_

#include "Proceso.hh"
#ifndef NO_DIAGRAM
#include <map>
#include <set>
#endif
using namespace std;

/** @class Procesador
    @brief Representa un procesador
*/
class Procesador {
private:
/** @brief Datos sobre la memoria del procesador
*/
  int memory;
  int freememory;
/** @brief Estructuras usadas para gestionar la memoria
*/
  map<int, Proceso> mproc;
  map<int, int> mname;
  map<int, set<int>> huecos;
public:
    //CONSTRUCTORAS
    /** @brief Creadora por defecto
      \pre <em>cierto</em>
      \post Tenemos un procesador vacio
    */
    Procesador();

    /** @brief Crea el procesador con memoria n
      \pre n > 0
      \post Procesador con memoria n
    */
    Procesador(int n);

    //CONSULTORAS
    /** @brief Consultora de la memoria libre
      \pre Procesador con memoria
      \post Devuelve la memoria libre del procesador
    */
    int con_free() const;

    /** @brief Consultora del hueco mas ajustado para m en el procesador
      \pre Hay al menos un hueco para m en el procesador
      \post Devuelve el hueco mas ajustado
    */
    int hueco_ajustado(int m);

    /** @brief Consulta si hay al menos un hueco para m
      \pre m > 0
      \post true si hay un hueco para m como minimo si no false
    */
    bool hueco(int m);

    /** @brief Consulta si el procesador no tiene procesos
      \pre Procesador con memoria
      \post true si no tiene procesos si no false
    */
    bool no_tiene_procesos() const;

    /** @brief Consulta si el procesador contiene al proceso de nombre n
      \pre n >= 0
      \post true si contiene al proceso n si no false
    */
    bool search(int n) const;

    //MODIFICADORES
    /** @brief Gestiona los huecos cuando se quita el proceso de nombre n
      \pre El proceso n esta en el procesador
      \post Los huecos han sufrido los cambios pertinentes por eliminar n
    */
    void baja(int n);

    /** @brief Borra el proceso n del procesador
      \pre El proceso n esta en el procesador
      \post El proceso n ya no esta en el procesador
    */
    void borra(int n);

    /** @brief Adelanta el tiempo de los procesos del procesador n unidades de tiempo
      \pre n > 0
      \post Los procesos ejecutados se han eliminado y el tiempo del resto ha sido adelantado
    */
    void adelantar(int n);

    /** @brief Añade el proceso p al procesador
      \pre p no vacio y no esta en el procesador
      \post El procesador contiene al proceso p
    */
    void alta(const Proceso& p);

    /** @brief Compacta la memoria del procesador
      \pre El procesador tiene memoria
      \post Se han compactado todos los procesos del procesador sin dejar huecos
    */
    void compact();

    //IMPRESORAS
    /** @brief Imprime los procesos del procesador y sus posiciones en memoria
      \pre <em>cierto</em>
      \post Se han imprimido todos los datos de los procesos del procesador
    */
    void print_proc() const;
};
#endif
