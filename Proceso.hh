/** @file Proceso.hh
    @brief Especificacion de la clase Proceso
*/
#ifndef _PROCESO_HH_
#define _PROCESO_HH_

#ifndef NO_DIAGRAM
#include <iostream>
#endif
using namespace std;
/** @class Proceso
    @brief Representa un proceso
*/
class Proceso {
private:
/**  @brief Datos del proceso
*/
  int nom;
  int memo;
  int tej;
public:
    //CONSTRUCTORAS
    /** @brief Creadora por defecto
      \pre <em>cierto</em>
      \post Proceso vacio
    */
    Proceso();

    /** @brief Crea un proceso no vacio
      \pre <em>cierto</em>
      \post Proceso con nombre, memoria que ocupa y tiempo de ejecucion
    */
    Proceso(int n, int m, int t);

    //CONSULTORAS
    /** @brief Consultora del nombre del proceso
      \pre Proceso no vacio
      \post Devuelve el nombre del proceso
    */
    int con_nom() const;

    /** @brief Consultora de la memoria del proceso
      \pre Proceso no vacio
      \post Devuelve la memoria del proceso
    */
    int con_memo() const;

    /** @brief Consultora del tiempo del proceso
      \pre Proceso no vacio
      \post Devuelve el tiempo del proceso
    */
    int con_tej() const;

    //MODIFICADORAS
    /** @brief Modificadora del tiempo de ejecucion
      \pre t > 0
      \post El tiempo del proceso ha disminuido t unidades de tiempo
    */
    void modify_tej(int t);

    //IMPRESORAS
    /** @brief Impresora del proceso
      \pre Proceso no vacio
      \post Imprime el proceso
    */
    void out_proces() const;
};
#endif
