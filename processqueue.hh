/** @file ProcessQueue.hh
    @brief Especificación de la clase ProcessQueue 
*/
 
#ifndef _PROCESSQUEUE_HH_
#define _PROCESSQUEUE_HH_ 
  
 
//Define clases que necesite la Clase ProcessQueue
#include "cluster.hh"
#include "process.hh"
#include "priority.hh"
 

#ifndef NO_DIAGRAM             
#include <iostream>  
#include <string> 
#include <map>   
#include <vector>  
#endif                          


/** @class ProcessQueue
    @brief Representa una Área de Procesos(<em>Process</em>) Pendientes. Estos procesos se ordenan para salir siguiendo una Prioridad manipulable indicada por un string y designada por el Usuario.      
   
*/
using namespace std;

class ProcessQueue {

  private: 
     
    /** @brief
     Key como el Identificador de la Prioridad, el contenido es la Prioridad con ese Id. 
    */ 
    //Key como el Identificador de la Prioridad, el contenido es la Prioridad con ese Id.  
    map<string, Priority> areaProcesses;  

    
  public:

  //Constructoras
    
    /** @brief Creadora por defecto. 

      Se ejecuta automáticamente al declarar una Área de Procesos Pendientes.
      \pre <em>cierto</em>
      \post El resultado es una Área de procesos pendientes inicializado con las n Prioridades que entran por input al ser llamada la constructora. 
  */  
  ProcessQueue();  


  // Modificadoras 


  /** @brief Añadir Proceso en Área de Procesos Pendientes

      Añade un Proceso (<em>Process</em>) con una cierta prioridad dentro del Área de Procesos Pendientes.
      \pre El Proceso que se recibe debe estar inicializado.
      \post En el parámetro implícito, el Proceso queda añadido en su Prioridad correspondiente y función retorna 0, de lo contrario, si no existe en el Área una prioridad con el mismo Id función retorna error 5, o si existe ya un proceso con el mismo Id función retorna error 7, y el param.implícito no es modificado.
  */  
  char addProcess_ProcessQueue(const string& priorityID, const Process& process);

  
  /** @brief Añadir Prioridad en Área de Procesos Pendientes

      Añade una nueva prioridad dentro del Área de Procesos Pendientes.
      \pre  Identificador de Prioridad formado por letras y digitos.
      \post En el parámetro implícito, este pasa a tener una nueva prioridad si esta no existe con dicho identificador y función retorna 0, de lo contrario, si ya existe esta Prioridad en el Área, función retorna error 4, y el param.implícito no es modificado.
  */   
  char addPriority_ProcessQueue(const string& priorityID);


  /** @brief Eliminar Prioridad en Área de Procesos Pendientes

      Elimina una prioridad si existe con el mismo nombre que el identificador dentro del Área de Procesos Pendientes.
      \pre  Identificador de Prioridad formado por letras y digitos.
      \post En el parámetro implícito, si la prioridad existe esta queda eliminada y función retorna 0, de lo contrario, si no existe el identificador en el Área función retorna error 5, si la prioridad tiene procesos pendientes función retorna error 6, y el param.implícito no es modificado.
  */ 
  char elimPriority_ProcessQueue(const string& priorityID);
  


 /** @brief  Enviar Procesos del Área de Procesos Pendientes a Cluster

      Se intentan enviar n Procesos (<em>Process</em>) del Área de Procesos Pendientes al Cluster que se obtienen por orden de Prioridad, los no acceptados son devueltos al Área. 
      \pre Cluster debe estar inicializado. 
      \post En el parámetro implícito, r procesos donde  0 <= r =< n son eliminados (Estos han sido enviados al Clúster), y n - r procesos son colocados de nuevo en sus respectivas Prioridades. Además, las Prioridades que han visto sus filas modificadas actualizan sus marcadores de num.Procesos Colocados en Cluster y num.Procesos Rechazados por Cluster   
    */
   void sendProcesses_ProcessQueue(int n, Cluster& myCluster); 
    

    
     

  // Consultoras
  
  /** @brief Imprimir Área de Procesos Pendientes

      Imprime el Área de Procesos Pendientes.
      \pre  <em>cierto</em>
      \post En el terminal-output se imprime el parámetro implícito (Área de Procesos Pendientes).   
  */ 
  void print_ProcessQueue() const;
  

  /** @brief Imprimir Procesos de cierta Prioridad del Área de Procesos Pendientes

      Imprime todos los procesos de la Prioridad si existe que se le indica del Área de Procesos Pendientes.
      \pre  <em>cierto</em>
      \post Si la Prioridad existe se imprimen en terminal-output los procesos de la Prioridad indicada, de lo contrario, si no existe en el Área una prioridad con el mismo Id función retorna error 5.
  */ 
  char printPriority_ProcessQueue(const string& priorityID) const; 



};
#endif
