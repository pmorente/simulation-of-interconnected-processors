/** @file Process.hh
    @brief Especificación de la clase Process 
*/
 
#ifndef _PROCESS_HH_ 
#define _PROCESS_HH_

//Define clases que necesite la Clase Process
  
 
#ifndef NO_DIAGRAM           
#include <iostream> 
#include <string>

#endif                          
 
   
/** @class Process
    @brief Representa un Proceso con su propio Identificador, cantidad de memoria que necesita y tiempo de ejecución. Este puede ser añadido en un Procesador (<em>Processor</em>) o en una Prioridad (<em>Priority</em>).      
   
*/

using namespace std;
class Process { 

    private:
        /** @brief
          Identificador del Proceso.
        */
        //Identificador del Proceso.   
        int id;

        /** @brief
         Memoria continua necesaria que necesita el Proceso para poder ser insertado.
        */
        //Memoria continua necesaria que necesita el Proceso para poder ser insertado.
        int memory_needed;

        /** @brief
          Tiempo que falta de ejecución para que el Proceso se termine.
        */
        //Tiempo que falta de ejecución para que el Proceso se termine.  
        int execution_time; 


    public:
    
    //Constructoras
    
    /** @brief Creadora por defecto. 

      Se ejecuta automáticamente al declarar un Proceso.
      \pre <em>cierto</em>
      \post El resultado es un Proceso no inicializado.
    */  
    Process();

   //Modificadoras
    
    /** @brief Lectora de Proceso Entero 

      Lee un proceso entero. 
      \pre Proceso no inicializado. 
      \post El resultado es el proceso inicializado. 
    */
    void readAll_process(int processID); 

    /** @brief Decrementadora de Tiempo de Ejecución de Proceso 

       Decrementa n tiempos el tiempo de ejecución del proceso e indica con true si aún queda tiempo de ejecución o false si el proceso ya se ha ejecutado.  
      \pre Proceso inicializado. 
      \post Si n < execution_time del parámetro implícito, el Tiempo de Ejecución de este se reduce n tiempos y función retorna true, de lo contrario, n >= execution_time del parámetro implícito, este pasa a valer 0 y función retorna false.   
    */
    bool decreaseTimeExec_process(int timeToDecrease); 


    //Consultoras
   

    /** @brief Consultora de Identificación del Proceso 

      Consulta la Identificación del proceso. 
      \pre Proceso inicializado. 
      \post El resultado es un string con el Identificador del proceso. 
    */
    int checkId_process() const;


    /** @brief Consultora de Memoria Necesaria para el Proceso 

      Consulta la memoria necesaria del proceso para poder ser ejecutado. 
      \pre Proceso inicializado. 
      \post El resultado es un entero con la memoria necesaria del proceso. 
    */
    int checkMemoryNeed_process() const;


    /** @brief Consultora de Tiempo de Ejecución del Proceso 

      Consulta el tiempo de ejecución del Proceso. 
      \pre Proceso inicializado. 
      \post El resultado es un entero con el tiempo de ejecución del proceso. 
    */
    int checkExecTime_process() const;


    /** @brief Impresora del Proceso 

      Imprime el proceso en terminal.  
      \pre Proceso inicializado. 
      \post Imprime el proceso por el output-terminal.
    */
    void print_process() const; 



};
#endif
