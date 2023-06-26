/** @file Cluster.hh
    @brief Especificación de la clase Cluster 
*/
    
#ifndef _CLUSTER_HH_
#define _CLUSTER_HH_

//Define clases que necesite la Clase Cluster
#include "processor.hh"
#include "process.hh"

#ifndef NO_DIAGRAM             
#include <iostream> 
#include <string> 
#include "BinTree.hh"       
#endif                        
  

/** @class Cluster
    @brief Representa un Cluster de Procesadores (<em>Processor</em>) organizado como un árbol. 
   
*/

using namespace std;

class Cluster {

    private:
    /** @brief
      Mapa que contiene el Identificador del Procesador como key, y dicho Procesador con ese Id como contenido. 
    */
    //Mapa que contiene el Identificador del Procesador como key, y dicho Procesador con ese Id como contenido. 
    map<string, Processor> clusterProcessors;
    
    /** @brief
      BinTree formado por los Identificadores de los Procesadores y representa la estructura del Cluster
    */
    //BinTree formado por los Identificadores de los Procesadores y representa la estructura del Cluster
    BinTree<string> clusterStructure;
    

    /** @brief Configuradora de Cluster Recursiva 

      Lee y configura un Cluster de Procesadores. En la estructura en árbol del Cluster, en función, el carácter "*" representa un nodo vacio. 
      \pre <em>cierto</em>
      \post <i>clusterProcessors</i> contiene todos los Procesadores ordenados por su Identificador  y <i>clusterStructure</i> contiene la estructura del Cluster en forma de árbol. 
    */ 
    void i_config_cluster(BinTree<string> &clusterTree);
    

    /** @brief Impresora Estructura Cluster Recursiva 

      Imprime toda la estructura del Cluster.  
      \pre <em>cierto</em>
      \post Se imprime el árbol <i>clusterStructure</i> 
    */ 
    void i_printStructure_cluster(const BinTree<string>& copyClusterStructure) const; 
    

    /** @brief Buscadora/Modificadora de Estructura Cluster Recursiva

      Busca la posición del Procesador con dicho Id en el Cluster y si este no tiene Procesadores auxiliares, entonces crea y guarda en el árbol <i>clusterStructure</i> el árbol resultante de insertar en el nodo donde se encontraba el Procesador buscado el subarbol pasado por valor constante.   
      \pre <em>cierto</em>
      \post Si se encuentra y no tiene Procesadores auxiliares, entonces <i>clusterStructure</i> es un nuevo árbol donde el nodo que contenía processorID ahora es el inicio del árbol newClusterStructure y changeMade es verdadero, de lo contrario, este tiene Procesadores auxiliares y changeMade es falso. 
    */
    static void busq_modif_cluster(BinTree<string> &clusterStructure, const string& processorID, const BinTree<string>& newClusterStructure, bool& changeMade);
    

    /** @brief Buscadora de Mejor Posición Recursiva

      Esta función busca el mejor Procesador para insertar un proceso, Si un proceso se puede colocar en más de un procesador, se elige el que disponga de un hueco más ajustado respecto a tal proceso. En caso de empate entre varios procesadores, se designa el que quede con más memoria libre. Si persiste el empate, se escoge el más cercano a la raíz del árbol de procesadores y si todavía es necesario desempatar, el de más a la izquierda.  
      \pre <em>cierto</em>
      \post El valor <i>started</i> booleano indica si el Proceso puede entrar en el algun Procesador, si este es true entonces <i>itToProcessor</i> apunta al Procesador óptimo, de lo contrario <i>started</i> es false y <i>itToProcessor</i> apunta al final del mapa de Procesadores
    */
    void i_fromProcessQueueInsert_cluster(const BinTree<string>& clusterTree, int idProcess, int sizeProcess, int distance, map<string, Processor>::iterator& itToProcessor, int& op_adjustedSpace, int& op_freeMemoryAfter, int& op_distance, bool& started);
    
    
    
    public:
    
    //Constructoras

    /** @brief Creadora por defecto. 

      Se ejecuta automáticamente al declarar un Cluster.
      \pre <em>cierto</em>
      \post El resultado es un Cluster no inicializado.
    */  
    Cluster();


    //Modificadoras

 
    /** @brief Inicializadora de Cluster

      Inicializa el Clúster de Procesadores (<em>processor</em>) con estructura de árbol con los elementos que le llegan por la entrada. Hay que tener en cuenta que la entrada del carácter "*" representa un nodo vacio. Si se quiere declarar un nodo como hoja, la siguiente entrada a dicho nodo debe ser igual a **. 
      \pre La entrada debe cumplir con las restricciones mencionadas en la infografía de la función. (la entrada del carácter "*" representa un nodo vacio)
      \post El parámetro implícito pasa a estar inicializado con los procesadores con sus respectivas memorias y connexiones leídas por la entrada.
    */
    void config_cluster();


     
/** @brief Modificadora de Cluster
      
      Si p es un Identificador de un Procesador (<em>processor</em>) del Clúster y p como Procesador no tiene procesos en ejecución o Procesadores auxiliares, entonces se añade un nuevo cluster 'newCluster' en esa posición, de lo contrario se imprime un mensaje de error.  
      \pre El parámetro implícito esta inicializado, el Clúster que se le añade también esta inicializado.   
      \post En el parámetro implícito, si p existe y no tiene procesos en ejecución o Procesadores auxiliares entonces el parám.implíc. pasa a tener el nuevo árbol en la posición donde se encontraba el id.p y la función retorna 0, de lo contrario, si Identificador no encontrado en Cluster función retorna error 1 , o si Procesador tiene procesos en ejecución función retorna error 2, o si tiene procesadores auxiliares función retorna error 3, y en los últimos tres casos el parám.implícito no es modificado.
    */
    char modif_cluster(const string& p, const Cluster& newCluster); 
 
 

    /** @brief Añadidura de Proceso en Cluster
      
      Añade el Proceso al Procesador (<em>processor</em>) con el mismo Identificador del Cluster
      \pre El Proceso debe estar inicializado.    
      \post En el parámetro implícito, si existe el Procesador con el mismo Identificador, tiene el espacio suficiente y el proceso no es repetido el parám.implíc. pasa a tener dicho Proceso y función retorna 0, de lo contrario, si identificador de Procesador no encontrado en Cluster función retorna error 1, o si existe ya un proceso con el mismo Identificador función retorna error 8, o si el proceso no se puede colocar función retorna error 9, y en los tres últimos casos parám.implíc. no se ve modificado.
    */
    char addProcess_cluster(const string& processorID,const Process& newProcess); 
    

    /** @brief Eliminadora de Proceso en Cluster
      
      Elimina el Proceso del Procesador (<em>processor</em>) con el mismo Identificador del Cluster.
      \pre  <em>cierto</em>   
      \post En el parámetro implícito, si existe un Procesador y dentro un proceso donde los identificadores pasados por valor coinciden, dicho Procesador ya no contiene dicho proceso y función retorna 0, de lo contrario, si identificador de Procesador no encontrado función retorna error 1, o si el proceso no se encuentra función retorna error X, y en ambos casos el parám.implíc. no se ve modificado.
    */
    char elimProcess_cluster(const string& processorID, int processID); 
    


    /** @brief Compactadora de Memoria de Procesador en Cluster

      Pone en orden consecutivo todos los Procesos (<em>process</em>) del Procesador (<em>processor</em>) si existe con Identificador igual al del parámetro pasado por valor del Clúster. 
      \pre <em>cierto</em>  
      \post En el parámetro implícito, si existe un Procesador con el mismo Identificador este se compacta, de lo contrario, si no existe el Procesador en Cluster función retorna error 1 y el parám.implíc. no se ve modificado.
    */ 
    char compactMemory_cluster(const string& processorID); 
    

    /** @brief Compactadora Total de Memoria en Cluster

      Pone en orden consecutivo y sin dejar espacios todos los Procesos (<em>process</em>) de todos los Procesadores (<em>processor</em>) del Clúster. 
      \pre <em>cierto</em>
      \post El resultado es la compactación de los Procesos de todos los Procesadores del Clúster.  
    */ 
    void compactAllMemory_cluster(); 


    /** @brief Avanzar Tiempo del Cluster

      Avanza t unidades el tiempo del Cluster.  
      \pre t >= 0  
      \post El parám.implíc. pasa a tener ++t unidades de tiempo y todos los procesos en ejecución se les disminuye t unidades su tiempo de ejecución.   
    */ 
    void advanceTime_cluster(int addedTime);



     /** @brief Insertadora Óptima de Procesos

      Añade el proceso si este cabe en el Cluster en la mejor posición del Cluster, la colocación del proceso sigue las siguientes reglas; hueco más ajustado/ mayor tamaño libre después de insertado, mś cerca de la raíz, más a la izquierda 
      \pre <em>cierto</em> 
      \post Si el proceso se ha añadido, la función retorna true, de lo contrario, el proceso no se ha podido añadir y la función retorna false.    
    */ 
    bool fromProcessQueueInsert_cluster(const Process& newProcess); 



    // Consultoras
    

    /** @brief Impresora de Procesador de Cluster

      Imprime si existe el Procesador (<em>processor</em>) con el mismo Identificador pasado por valor en la función    
      \pre <em>cierto</em>  
      \post Si el Procesador existe se imprime el Procesador por terminal y función retorna 0, de lo contrario, no existe el Procesador en Cluster y función retorna error 1.
    */ 
    char printProcessor_cluster(const string& processorID) const;
    
  

    /** @brief Impresora Total de Procesadores de Cluster

      Imprime todos los Procesos de todos los  Procesadores (<em>processor</em>) del Cluster.    
      \pre  <em>cierto</em>  
      \post En terminal-output quedan imprimidos todos los Procesadores del parám.implíc.      
    */ 
    void printAllProcessor_cluster() const;


    /** @brief Impresora de Estructura de Cluster

      Imprime toda la estructura de árbol del Cluster implícito.    
      \pre  <em>cierto</em>
      \post En terminal-output queda imprimida la estructura del parám.implíc.    
    */
    void printStructure_cluster() const; 
    
    

};
#endif
