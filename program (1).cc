/**
 * @mainpage Simulación y gestión de una arquitectura multiprocesador con memoria propia y procesamiento simultáneo en un clúster con estructura en árbol binario 
 
En este programa modular se ofrece un menú de opciones para gestionar un Clúster con arquitectura multiprocesador de procesamiento simultáneo donde cada procesador tiene memoria propia. Se introducen las clases <em>Cluster</em>, <em>ProcessQueue</em>, <em>Processor</em>, <em>Process</em> y <em>Priority</em>.

Todos los elementos públicos y privados son documentados. 
*/

/** @file pro2_s8.cc
    @brief Programa principal <em>Simulación y gestión de un Clúster.</em>.
*/
 
  

using namespace std;
#include "cluster.hh"
#include "processqueue.hh"
#include "process.hh"

#ifndef NO_DIAGRAM 
#include <iostream> 
#include <string>  
#endif
 
/** @brief Programa principal <em>Simulación y gestión de un Clúster.</em>.
*/
int main ()

{

    Cluster myCluster;

    //Incializamos Cluster
    myCluster.config_cluster();

    ProcessQueue myQueueProc; 
    
    //Inicializamos Área de Espera
    int numberOfPriorities;
       cin >> numberOfPriorities;

       for(int i = 0; i < numberOfPriorities; ++i) {
           string priorityID;
            cin >> priorityID; 
          myQueueProc.addPriority_ProcessQueue(priorityID);
       } 


    string command; 
        cin >> command;
          
    char error;  

    while(command != "fin") {
        

        if(command == "configurar_cluster" or command == "cc") {  
            
            cout << "#" << command << endl; 

            myCluster.config_cluster();



        }else if(command == "modificar_cluster" or command == "mc") {
            
              string ProcessorID;
               cin >> ProcessorID;
              
               Cluster newCluster;
               newCluster.config_cluster(); 

               cout << "#" << command <<  " " << ProcessorID << endl;


                char error = myCluster.modif_cluster(ProcessorID, newCluster); 

                
                if(error == '1') cout << "error: no existe procesador" << endl;
                else if(error == '2') cout << "error: procesador con procesos" << endl;
                else if (error == '3') cout << "error: procesador con auxiliares" << endl;
            


        }else if(command == "alta_prioridad" or command == "ap") {

              string newPriorityID;
               cin >> newPriorityID;

               cout << "#" << command << " " << newPriorityID << endl; 


                error = myQueueProc.addPriority_ProcessQueue(newPriorityID);


                if(error == '4') cout << "error: ya existe prioridad" << endl;



        }else if(command == "baja_prioridad" or command == "bp") {
            
              string priorityID;
               cin >> priorityID;

               cout << "#" << command << " " << priorityID << endl; 
            

                error = myQueueProc.elimPriority_ProcessQueue(priorityID);
            

                if(error == '5') cout << "error: no existe prioridad" << endl;
                else if(error == '6') cout << "error: prioridad con procesos" << endl;

 

        }else if(command == "alta_proceso_espera" or command == "ape") {
            
              string priorityID;
               cin >> priorityID;
              int processID;
               cin >> processID;   
            
               cout << "#" << command << " " << priorityID << " " << processID << endl;
            
              Process newProcess;
              newProcess.readAll_process(processID);
          

                error = myQueueProc.addProcess_ProcessQueue(priorityID, newProcess); 


                if(error == '5') cout << "error: no existe prioridad" << endl;
                else if(error == '7') cout << "error: ya existe proceso" << endl;



        }else if(command == "alta_proceso_procesador" or command == "app") {

              string ProcessorID;
               cin >> ProcessorID;
              int processID;
               cin >> processID; 

               cout << "#" << command << " " << ProcessorID << " " << processID << endl;

              Process newProcess;
              newProcess.readAll_process(processID); 


                error = myCluster.addProcess_cluster(ProcessorID, newProcess); 


                if(error == '1') cout << "error: no existe procesador" << endl;
                else if(error == '8') cout << "error: ya existe proceso" << endl;
                else if(error == '9') cout << "error: no cabe proceso" << endl;



        }else if(command == "baja_proceso_procesador" or command == "bpp") {

              string ProcessorID;
               cin >> ProcessorID; 
              int ProcessID; 
               cin >> ProcessID;
             
               cout << "#" << command << " " << ProcessorID << " " << ProcessID << endl; 


                error = myCluster.elimProcess_cluster(ProcessorID, ProcessID);


                if(error == '1') cout << "error: no existe procesador" << endl;
                else if(error == 'X') cout << "error: no existe proceso" << endl;



        }else if(command == "enviar_procesos_cluster" or command == "epc") {

              int nProcessors;
               cin >> nProcessors; 
             
               cout << "#" << command << " " << nProcessors << endl; 


                myQueueProc.sendProcesses_ProcessQueue(nProcessors, myCluster);
            


        }else if(command == "avanzar_tiempo" or command == "at") {

              int timeAddons;
               cin >> timeAddons;

               cout << "#" << command << " " << timeAddons << endl; 

                
                myCluster.advanceTime_cluster(timeAddons); 



        }else if(command == "imprimir_prioridad" or command == "ipri") {

              string priorityID;
               cin >> priorityID;
            
               cout << "#" << command << " " << priorityID << endl; 


                error = myQueueProc.printPriority_ProcessQueue(priorityID); 


                if(error == '5') cout << "error: no existe prioridad" << endl;



        }else if(command == "imprimir_area_espera" or command == "iae") {
            
               cout << "#" << command << endl;


                myQueueProc.print_ProcessQueue();

        

        }else if(command == "imprimir_procesador" or command == "ipro") {

              string ProcessorID;
               cin >> ProcessorID;
            
               cout << "#" << command << " " << ProcessorID << endl; 
            

                error = myCluster.printProcessor_cluster(ProcessorID);


                if(error == '1') cout << "error: no existe procesador" << endl;



        }else if(command == "imprimir_procesadores_cluster" or command == "ipc") {

               cout << "#" << command << endl;


                myCluster.printAllProcessor_cluster(); 
 


        }else if(command == "imprimir_estructura_cluster" or command == "iec") {
            
               cout << "#" << command << endl; 


                myCluster.printStructure_cluster();



        }else if(command == "compactar_memoria_procesador" or command == "cmp") {

              string ProcessorID;
               cin >> ProcessorID;
            
               cout << "#" << command << " " << ProcessorID << endl;
            

            char error = myCluster.compactMemory_cluster(ProcessorID);


            if(error == '1') cout << "error: no existe procesador" << endl;



       }else if(command == "compactar_memoria_cluster" or command == "cmc") {
              
               cout << "#" << command << endl; 


                myCluster.compactAllMemory_cluster();
       }

    cin >> command; 
    }

}