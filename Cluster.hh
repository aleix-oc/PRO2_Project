/** @file Cluster.hh
    @brief Especificación de la clase Cluster
*/
#ifndef _CLUSTER_HH_
#define _CLUSTER_HH_

#include "Procesador.hh"
#ifndef NO_DIAGRAM
#include "BinTree.hh"
#include <iostream>
#include <list>
#include <map>
#endif
using namespace std;

/** @class Cluster
    @brief Representa un cluster
*/
class Cluster {
private:
/** @brief Estructura del cluster y su atributo de tiempo
*/
  BinTree<pair<string, int>> a;
  map<string, Procesador> m;
  int time;
public:

    //CONSTRUCTORAS
    /** @brief Creadora por defecto
      \pre <em>cierto</em>
      \post Declara un cluster vacio
    */
    Cluster();

    /** @brief Mete procesadores en el cluster
      \pre <em>cierto</em>
      \post Cluster con ciertos procesadores
    */
    void configurar_cluster();

    //MODIFICADORAS
    /** @brief Cambiadora el cluster
      \pre Cluster no vacio y el nuevo cluster no sera vacio
      \post El cluster original se ha fusionado con el nuevo
    */
    void modificar_cluster();

    /** @brief Coloca un proceso en un procesador
      \pre Cluster no vacio
      \post A uno de los procesadores se le ha añadido un proceso
    */
    void alta_proceso_procesador();

    /** @brief Elimina un proceso de un procesador
      \pre Cluster no vacio
      \post A uno de los procesadores se le ha quitado un proceso
    */
    void baja_proceso_procesador();

    /** @brief El tiempo avanza
      \pre El tiempo que avance sera mayor que 0
      \post El tiempo ha aumentado en t unidades de tiempo y ha afectado a todos los procesos en ejecucion
    */
    void avanzar_tiempo();

    /** @brief Se compacta la memoria de un procesador
      \pre Cluster no vacio
      \post Se han movido de la manera más ajustada los procesos de un procesador
    */
    void compactar_memoria_procesador();

    /** @brief Se compacta la memoria de todos los procesadores del cluster
      \pre Cluster no vacio
      \post Se han movido de la manera más ajustada los procesos de cada procesador
    */
    void compactar_memoria_cluster();

    /** @brief Intenta enviar el proceso p
      \pre b = false y p no vacio
      \post b = true si se ha enviado p si no false
    */
    void enviar(const Proceso& p, bool& b);

    //ESCRITURA
    /** @brief Escribe la memoria de un procesador
      \pre <em>cierto</em>
      \post En la salida se ven los procesos de un procesador y sus posiciones en la memoria
    */
    void imprimir_procesador() const;

    /** @brief Escribe todas las memorias del cluster
      \pre <em>cierto</em>
      \post En la salida se ven todos los procesos y sus posiciones en la memoria de cada procesador
    */
    void imprimir_procesadores_cluster() const;

    /** @brief Escribe la distribucion de los procesadores del cluster
      \pre <em>cierto</em>
      \post En la salida se ve la estructura de los procesadores del cluster
    */
    void imprimir_estructura_cluster();

private:

  /** @brief Lee los datos del cluster
      \pre <em>cierto</em>
      \post Se han leido los datos
    */
  void readcluster(BinTree<pair<string, int>>& a);

  /** @brief Imprime la estructura del cluster
      \pre <em>cierto</em>
      \post Se ha imprimido la estructura
    */
  void writecluster(const BinTree<pair<string, int>>& a);

  /** @brief Modifica el cluster a partir del procesador de identificador idproc
      \pre b = false y el procesador idproc esta en el cluster y no tiene procesos
      \post Si se ha modificado el cluster b = true
    */
  void modify(BinTree<pair<string, int>>& t, const string &idproc, bool& b);

  /** @brief Comprueba si hay un procesador candidato al que enviar el proceso de nombre pnombre y memoria pmemo
      \pre b = false y count = aux = 0 y candidato = " "
      \post Si b = true candidato es el procesador al que mandaremos el proceso
    */
  void send(const BinTree<pair<string, int>>& a,const int& pmemo, const int&pnombre, bool& b, int& count, int& aux, string& candidato, int& minaj, int& free);
};
#endif
