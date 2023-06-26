/** @file Processor.hh
    @brief Especificación de la clase Processor 
*/
 
#ifndef _PROCESSOR_HH_
#define _PROCESSOR_HH_
 
//Define clases que necesite la Clase Processor
#include "process.hh"
 
#ifndef NO_DIAGRAM 
#include <iostream>            
#include <map>   
#include <string>
#include <set> 
        
#endif                           

 
/** @class Processor
    @brief Representa un Procesador con memoria propia y ejecutador de Procesos (<em>Process</em>). La memoria tiene una cierta cantidad de posiciones, indexadas desde 0. Cada procesador puede tener un número diferente de posiciones en memoria.     
   
*/ 

using namespace std;

class Processor {  

    private: 
         /** @brief
          Identificador de Procesador.
        */
        //Identificador de Procesador.  
        string id;
         
         /** @brief
          Valor Límite de Memoria del Procesador.
        */
        //Valor Límite de Memoria del Procesador.
        int memoryLimit; 
        
        /** @brief
          Conjunto de espacios libres en Memoria.
        */
        //Conjunto de espacios libres en Memoria. 
        int freeSpace;

        /** @brief
          Key como la posición de memoria, y el contenido como Proceso que empieza en esta posición.
        */
        //Key como la posición de memoria, y el contenido como Proceso que empieza en esta posición. 
        map<int, Process> memory;

         /** @brief
          Key como bloque continuo de espacios libres, y el contenido es el conjunto en memoria de posiciones iniciales donde empieza este bloque de espacios libres.
        */
        //Key como bloque continuo de espacios libres, y el contenido es el conjunto en memoria de posiciones iniciales donde empieza este bloque de espacios libres.  
        map<int, set<int>> freeMemory; 

         /** @brief
           Key como el identificador del Proceso, y el contenido es la posición inicial donde empieza en el mapa memory. 
        */
        //Key como el identificador del Proceso, y el contenido es la posición inicial donde empieza en el mapa memory.  
        map<int,int> data; 




      //Funciones privadas de la Clase Cluster

      /** @brief Eliminadora de Proceso Presente 

      Elimina el proceso apuntado que existe ya en la memoria del Procesador y libera su espacio.  
      \pre El Proceso existe en Memoria y es el apuntado por el iterador pasado por valor.
      \post El Proceso ya no existe en Memoria, memory y data ya no contienen información respecto dicho proceso y freeMemory tiene una nueva Key con el espacio liberado y la posición inicial de ese bloque, o , si ya existe un bloque de espacio libre de ese tamaño la posición inicial del nuevo bloque queda añadida en el set de la existente Key. 
    */   
      void elimProcess(map<int, Process>::iterator itToMemory, map<int, int>::iterator itToData);



    /** @brief Consultora de Memoria No Compactada 

      Consulta si la Memoria del Procesador no esta compactada. 
      \pre  El parám.implíc tiene por lo menos un proceso en memoria. 
      \post Función retorna True si la memoria del parám.implíc no está compactada, de o contrario, retorna false y la memoria del parám.implíc está compactada.   
    */ 
      bool notCompacted() const; 



    public:
    
    //Constructoras 
    
    Processor(); 

    /** @brief Creadora por defecto. 

      Se ejecuta automáticamente al declarar un Procesador.
      \pre <em>cierto</em>
      \post El resultado es un Procesador inicializado con su respectivo ID, límite de memoria y freeSpace igual al límite de memoria. 
    */  
    Processor(const string& processorID, int space);


    //Modificadoras
    


    /** @brief Añadidura de Procesos del Procesador  

      Añade si hay espacio suficiente un Proceso dentro del Procesador, este se añade en el primer espacio compatible libre que haya en el Procesador.
      \pre El proceso debe estar inicializado.  
      \post En el parámetro implícito, si existe el suficiente espacio el proceso es añadido en el procesador y función retorna 0, de lo contrario, si existe ya un proceso con el mismo Id función retorna error 8, o si el proceso no se puede colocar función retorna error 9, y el param.implícito no es modificado.
    */ 
    char addProcess_processor(const Process& newProcess);


    /** @brief Eliminadora de Procesos del Procesador  

      Elimina del Procesador si existe el proceso con el mismo identificador que el de la entrada.
      \pre <em>cierto</em>
      \post En el parámetro implícito, si existe dicho proceso este queda eliminado y función retorna 0, de lo contrario, si el proceso no se encuentra función retorna error X y el param.implícito no es modificado.
    */
    char elimProcess_processor(int processID);

    
    /** @brief Decrementadora de Tiempo en Procesos del Procesador  

      Decrementa el value pasado por valor a todos los procesos del Procesador, si los procesadores finalizan estos se eliminan del Procesador 
      \pre <em>cierto</em>
      \post En el parámetro implícito, todos los procesos con <i>execution_time > timeDecrease</i>, pasan a tener <i>execution_time = execution_time - timeDecrease</i>. Los procesos donde <i>execution_time <= timeDecrease</i> son eliminados del Parám.implícito. 
    */
    void decreaseTime_processor(int timeDecrease); 



    /** @brief Compactadora de Memoria del Procesador 

      Al ejecutarse compacta la memoria del procesador y elimina cualquier espacio que pueda haver entre procesos en la memoria.  
      \pre <em>cierto</em>
      \post En el parámetro implícito, se compacta su memoria sin dejar espacios intercalados entre procesos. 
    */ 
    void compactMemory_processor(); 

    
    //Consultoras

    /** @brief Consultora Hueco más Ajustado

      Por un lado consulta si existe el hueco libre más ajustado en Procesador sobre un tamaño pasado por valor y por otro lado lo devuelve. 
      \pre  <em>cierto</em>  
      \post Si existe un hueco ajustado al respectivo <i>sizeProcess</i>, función devuelve true y ese tamaño ajustado, de lo contrario, <i>sizeProcess</i> > max(Huecos Libres) función retorna false y -1.   
    */ 
    pair<bool,int> adjustedSpace(int sizeProcess) const;

    /** @brief Consultora Espacio Libre después de Inserción 

      Consulta el espacio libre que quedará en el Procesador después de inserir un Proceso (<em>Process</em>) con un respectivo tamaño.  
      \pre  <i>freeSpace</i> del parám.implíc tiene que ser mayor o igual al <i>sizeProcess</i> pasado por valor.
      \post Función devuelve la cantidad de espacios vacios si se insertara un Proceso con dicho tamaño.  
    */ 
    int freeMemoryAfter(int sizeProcess) const;


    /** @brief Consultora Existe Proceso 

      Consulta si existe un Proceso (<em>Process</em>) con dicho ID. 
      \pre  <em>cierto</em>  
      \post Función devuelve True si existe un Proceso con Identificador igual a <i>processID</i> en el parám. implíc, de lo contrario retorna False y no existe dicho Proceso.  
    */ 
    bool existsProcess_processor(int processID) const;


     /** @brief Consultora de Procesador Vacio

      Consulta si el Procesador está vacio.
      \pre  <em>cierto</em>  
      \post El resultado es true si el procesador esta vacio, de lo contrario false y el procesador contiene algun proceso.  
    */ 
    bool empty_processor() const; 


    /** @brief Consultora del Identificador del Procesador

      Consulta el identificador del Procesador.  
      \pre  <em>cierto</em>  
      \post EL resultado es el Identificador del Procesador.  
    */ 
    string checkID_processor() const; 


    /** @brief Consultora de Memoria del Procesador

      Consulta la memoria del Procesador.   
      \pre  <em>cierto</em> 
      \post EL resultado es la Memoria del Procesador.  
    */
    int checkMemory_processor() const;


    /** @brief Consultora de Espacios Libres del Procesador 

      Consulta los espacios libres que le quedan al Procesador. 
      \pre  <em>cierto</em> 
      \post El resultado es un entero con la memoria libre disponible del Procesador. 
    */ 
    int checkFreeSpace_processor() const; 
   
    
    /** @brief Impresora de Procesos del Procesador

      Imprime todos los Procesos (<em>Process</em>) del Procesador.  
      \pre <em>cierto</em>
      \post El resultado es el output por terminal de todos los procesos de de Procesador. 
    */ 
    void printProcesses_processor() const;


   
};
#endif

    


