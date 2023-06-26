/** @file Priority.hh
    @brief Especificación de la clase Priority
*/

#ifndef _PRIORITY_HH_ 
#define _PRIORITY_HH_
 

//Define clases que necesite la Clase Priority
#include "process.hh"
 
  

#ifndef NO_DIAGRAM             
#include <iostream>  
#include <string> 
#include <set>
#include <list>    
#endif                          


/** @class Priority
    @brief Representa una cola de procesos (<em>Process</em>) identificada con residencia en el Área de Procesos Pendientes (<em>ProcessQueue</em>) .      
   
*/

using namespace std;
class Priority {

 private:
 
   /** @brief
      Identificador de Prioridad
    */
   //Identificador de Prioridad
   string Id;

    /** @brief
      Conjunto de Identificadores de Procesos que contiene la Prioridad
    */
   //Conjunto de Identificadores de Procesos que contiene la Prioridad
   set<int> idsProcessesInQueue; 

    /** @brief
      Cola de espera de los Procesos dentro de la Prioridad
    */
   //Cola de espera de los Procesos dentro de la Prioridad
   list<Process> queueProcesses;
   
   /** @brief
      Número de Procesos de la Prioridad acceptados por un Cluster
    */
   //Número de Procesos de la Prioridad acceptados por un Cluster
   int acceptedProcesses;

    /** @brief
      Número de Procesos de la Prioridad rechazados por un Cluster
    */
   //Número de Procesos de la Prioridad rechazados por un Cluster
   int deniedProcesses;

 public:

 //Constructoras

  Priority(); 
    
    /** @brief Creadora por defecto. 

      Se ejecuta automáticamente al declarar una Prioridad.
      \pre <em>cierto</em>
      \post El resultado es una Prioridad identificada con cero procesos, cero procesos aceptados y rechazados.
  */  
  Priority(const string& idPriority);


 //Modificadoras
 
  /** @brief Añadidura de Proceso en Prioridad

       Añade si no existe el Proceso a la Prioridad
      \pre  <em>cierto</em>
      \post En el parámetro implícito si el proceso no existe se añade en la cola de espera y función retorna 0, de lo contrario, ya existe un proceso con el mismo identificador y la función retorna error 7.  
  */
  char pushProcess_priority(const Process& process);


  /** @brief Eliminadora de Proceso en Prioridad

       Elimina el Proceso más antiguo de la Prioridad
      \pre Existe en el parámetro implícito un proceso que eliminar.
      \post En el parámetro implícito el proceso más antiguo ya no existe.  
  */
  Process popProcess_priority();


 /** @brief Incrementadora de Procesos Acceptados de Prioridad

       Incrementa en +1 el valor de procesos acceptados. 
      \pre  <em>cierto</em>
      \post En el parámetro implícito el valor acceptedProcesses queda incrementado una unidad.    
  */
  void increaseAccProc_priority();


 /** @brief Incrementadora de Procesos Rechazados de Prioridad

       Incrementa en +1 el valor de procesos rechazados. 
      \pre  <em>cierto</em>
      \post En el parámetro implícito el valor deniedProcesses queda incrementado una unidad.    
  */
  void increaseDenProc_priority();



 //Consultoras

  /** @brief Consultora Tamaño Prioridad

       Muestra el número de elementos de la Prioridad.     
      \pre  <em>cierto</em>
      \post Función retorna el número de elementos >= 0 del parám.implíc.      
  */
  int size_priority() const; 

  
  /** @brief Comprueba Prioridad vacía

       Comprueba si la Prioridad es vacía o contiene algun elemento.    
      \pre  <em>cierto</em>
      \post Función vale true si la Prioridad está vacía, de lo contrario false y la Prioridad aún contiene algun elemento.     
  */
  bool empty_priority() const;


  /** @brief Impresora de Prioridad 

      Imprime la Prioridad en terminal.  
      \pre <em>cierto</em> 
      \post Imprime la Prioridad por el output-terminal.
  */
  void print_priority() const;


};

#endif
