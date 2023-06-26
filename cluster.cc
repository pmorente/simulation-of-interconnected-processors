
#include <iostream> 
#include <string> 
#include "BinTree.hh"   
 
#include "processor.hh" 
#include "process.hh"

#include "cluster.hh"
 
 

Cluster::Cluster() {

}

void Cluster::config_cluster() {

     //Eliminamos el Cluster antiguo y creamos el nuevo
     clusterProcessors.clear();
     i_config_cluster(clusterStructure);        

}


void Cluster::i_config_cluster(BinTree<string> &clusterTree) {
     
    string processorID;
    cin >> processorID;  
   
    if(processorID != "*") { 

        int spaceProcessor;
         cin >> spaceProcessor; 
        
        //Creamos e insertamos el Procesador en el mapa id/procesador
        clusterProcessors.insert(make_pair(processorID, Processor(processorID, spaceProcessor))); 
        
        //Vamos haciendo llamadas recursivas para ir creando los diferentes nodos
	    BinTree<string> left;
	     i_config_cluster(left);
	    BinTree<string> right;
	     i_config_cluster(right);

        //Al finalizar la entrada de datos, volvemos a las llamadas anteriores creando el nuevo árbol
        clusterTree = BinTree<string>(processorID, left, right);
    }    
} 


void Cluster::i_fromProcessQueueInsert_cluster(const BinTree<string>& clusterTree, int idProcess, int sizeProcess, int distance, map<string, Processor>::iterator& itToProcessor, int& op_adjustedSpace, int& op_freeMemoryAfter, int& op_distance, bool& started) {
     
    if(not(clusterTree.empty())){

       //Iterador apuntando al Procesador del nodo
       map<string, Processor>::iterator itToclusterProcessors = clusterProcessors.find(clusterTree.value());

        if(not((itToclusterProcessors->second).existsProcess_processor(idProcess))){ 

            //No existe en el nodo que estamos evaluando (Procesador) ningun proceso con id igual, entonces; 
            //Si aún no se ha inicializado: Miramos si hemos inicializado nuestros parámetros con el primer candidato a contener el Proceso, ya que los parámetros que traemos de la primera llamada son inválidos
            //Si hemos inicializado: Se efectuaran las comparaciones pertinentes para escoger el mejor

            if(not(started)){
        
                pair<bool,int> rootAdjustedSpace = (itToclusterProcessors->second).adjustedSpace(sizeProcess); 
 
                    if(rootAdjustedSpace.first){
                        
                        //Inicializamos nuestro primer candidato con los parámetros del nodo evaluado
                        itToProcessor = itToclusterProcessors;
                        op_adjustedSpace = rootAdjustedSpace.second; 
                        op_freeMemoryAfter = (itToclusterProcessors->second).freeMemoryAfter(sizeProcess);
                        op_distance = distance; 

                        //Started pasa a valer true, para no volver a inicializar 
                        started = true; 
                    }
            }else{ 
       
                //Consultamos el hueco más ajustado que tiene el Procesador del nodo evaluado
                pair<bool,int> nodeAdjustedSpace = (itToclusterProcessors->second).adjustedSpace(sizeProcess); 
                
                    //Utilizamos el bool que nos devuelve adjustedSpace que nos dice si el proceso cabe o no
                    if(nodeAdjustedSpace.first){

                        //Buscamos también el espacio libre después de inserción para la posible comparación/efectuar el cambio si en la comparación hueco ajust. el Proc.Nodo es mejor que nuestro candidato 
                        int nodeFreeMemoryAfter = (itToclusterProcessors->second).freeMemoryAfter(sizeProcess);


                            if(nodeAdjustedSpace.second != op_adjustedSpace) {
                                
                                //Los huecos ajust. son diferentes
                                //Comparación de huecos ajust.

                                if(nodeAdjustedSpace.second < op_adjustedSpace){

                                    //El evaluado es mejor que el candidato, actualizamos candidato
                                    itToProcessor = itToclusterProcessors;
                                    op_adjustedSpace = nodeAdjustedSpace.second; 
                                    op_freeMemoryAfter = nodeFreeMemoryAfter;
                                    op_distance = distance; 
                                }

                            }else{
 
                                if(nodeFreeMemoryAfter != op_freeMemoryAfter){

                                        //-huecos ajust. iguales
                                        //Los esp.libres después de inserción son diferentes
                                        //Comparación de esp.libres después de inserción

                                        if(nodeFreeMemoryAfter > op_freeMemoryAfter) {
                                            
                                            //El evaluado es mejor que el candidato, actualizamos candidato
                                            itToProcessor = itToclusterProcessors;
                                            op_adjustedSpace = nodeAdjustedSpace.second; 
                                            op_freeMemoryAfter = nodeFreeMemoryAfter;
                                            op_distance = distance;   
                                        }

                                }else{

                                        if(distance != op_distance){

                                            //-huecos ajust. iguales
                                            //-esp.libres desp. inserción iguales
                                            //Las distancias a raíz son diferentes
                                            //Comparación de distancias

                                            if(distance < op_distance) {

                                                //El evaluado es mejor que el candidato, actualizamos candidato
                                                itToProcessor = itToclusterProcessors;
                                                op_adjustedSpace = nodeAdjustedSpace.second; 
                                                op_freeMemoryAfter = nodeFreeMemoryAfter;
                                                op_distance = distance;
                                            }
                                        }

                                        //Llegado este punto (distancias iguales), entonces no modificaremos nuestro candidato porque al recorrer el árbol por preorden,
                                        //sabemos que el candidato esta más a la izquierda que el evaluado, entonces es mejor. 
                                }
                            }
                    }
            }
        }

    //Vamos en recorrido preorden analizando todos los nodos del árbol
    i_fromProcessQueueInsert_cluster(clusterTree.left(), idProcess, sizeProcess, distance + 1, itToProcessor, op_adjustedSpace, op_freeMemoryAfter, op_distance, started);
    i_fromProcessQueueInsert_cluster(clusterTree.right(), idProcess, sizeProcess, distance + 1, itToProcessor, op_adjustedSpace, op_freeMemoryAfter, op_distance, started);

    }

}

bool Cluster::fromProcessQueueInsert_cluster(const Process& newProcess) {
     
     //Declaramos todas las variables que vamos a usar para la busq. del Procesador óptimo
     map<string, Processor>::iterator itToProcessor = clusterProcessors.end(); 
     //int op_adjustedSpace = -1, op_freeMemoryAfter = -1, op_distance = -1;
     int  op_adjustedSpace, op_freeMemoryAfter, op_distance; 
     bool started = false; 

    i_fromProcessQueueInsert_cluster(clusterStructure, newProcess.checkId_process(), newProcess.checkMemoryNeed_process(), 0, itToProcessor,op_adjustedSpace, op_freeMemoryAfter, op_distance, started); 

    if(started) { 

        //Añadimos proceso en Procesador óptimo
        (itToProcessor->second).addProcess_processor(newProcess); 
        return true; 

    }return false; 

     
}
 

void Cluster::busq_modif_cluster(BinTree<string>& clusterTree, const string& processorID, const BinTree<string>& newClusterTree, bool& changeMade) {
       
    if(not(clusterTree.empty())){

        if(clusterTree.value() == processorID) {
          
          //Comprobamos si no tiene Procesadores auxiliares
          if(((clusterTree.left()).empty()) and ((clusterTree.right()).empty())) {

            //Realizamos la substitución en el nodo donde id_nodo = processorID
             changeMade = true; 
             clusterTree = newClusterTree; 
          }
          
        }else{
           
           //Vamos nodo a nodo buscando el Procesador
           BinTree<string> left =  clusterTree.left();
           busq_modif_cluster(left, processorID, newClusterTree, changeMade);  
           BinTree<string> right = clusterTree.right();
           busq_modif_cluster(right, processorID, newClusterTree, changeMade); 
           
           //Creamos solo el nuevo árbol si el cambio se ha realizado 
           if(changeMade) clusterTree = BinTree<string> (clusterTree.value(), left, right); 
              
        } 
    }
}


char  Cluster::modif_cluster(const string& processorID, const Cluster& newCluster) {
 
    //Buscamos el Procesador en el mapa id/Procesador
    map<string, Processor>::iterator itToClusterProcessors = clusterProcessors.find(processorID);

        if(itToClusterProcessors != clusterProcessors.end()) {

            //Miramos si el Procesador está vacio 
            if((itToClusterProcessors->second).empty_processor()) {
          
                bool changeMade; 

                //Llamamos a la función que busca/añade nueva cluster estructura a cluster estructura original si no tiene Proc.auxiliares
                busq_modif_cluster(clusterStructure, processorID, newCluster.clusterStructure, changeMade);
           
                //Miramos si se ha realizado el cambio en la estructura, sea true habrá que hacer lo mismo con el mapa id/Procesador
                if(changeMade) {  
                    
                    //Borramos el Procesador substituido
                    clusterProcessors.erase(processorID);

                    //Añadimos los procesadores que contenía el nuevo Cluster al original
                    //Aprovechamos que los Porcesadores del nuevo mapa están ordenados
                    //para hacer más rápida "en ciertos casos" la inserción. 
                    map<string, Processor>::const_iterator itToNewClusterProcessors = newCluster.clusterProcessors.begin(); 
                    map<string, Processor>::const_iterator hintIterator = clusterProcessors.begin(); 
              
              
                        while(itToNewClusterProcessors != newCluster.clusterProcessors.end()) {

                            //Guardamos el iterador para utilizarlo como hint en la próxima iteración
                            hintIterator = clusterProcessors.insert(hintIterator, *itToNewClusterProcessors);
              
                        ++itToNewClusterProcessors;  
                        }

                    return '0'; 

                }else return '3';


        }else return '2';

    }else return '1'; 

     
}

char Cluster::addProcess_cluster(const string& processorID,const Process& newProcess) {


    map<string, Processor>::iterator itToClusterProcessors = clusterProcessors.find(processorID);

        if(itToClusterProcessors != clusterProcessors.end()) {

            char error = (itToClusterProcessors->second).addProcess_processor(newProcess);   
             return error;

        }else return '1';

}

char Cluster::elimProcess_cluster(const string& processorID, int processID) {
     
    map<string, Processor>::iterator itToClusterProcessors = clusterProcessors.find(processorID);

        if(itToClusterProcessors != clusterProcessors.end()) {

            const char error = (itToClusterProcessors->second).elimProcess_processor(processID);
             return error;

        }else return '1';

}

void Cluster::advanceTime_cluster(int addedTime) {
    
    map<string, Processor>::iterator itToClusterProcessors = clusterProcessors.begin(); 
    
        while(itToClusterProcessors != clusterProcessors.end()) {
         
            (itToClusterProcessors->second).decreaseTime_processor(addedTime);
        
        ++itToClusterProcessors; 
        }

}


char Cluster::compactMemory_cluster(const string& processorID) {

    map<string, Processor>::iterator itToClusterProcessors = clusterProcessors.find(processorID);

        if(itToClusterProcessors != clusterProcessors.end()) {

            (itToClusterProcessors->second).compactMemory_processor();
             return '0';

        }else return '1';
}

void Cluster::compactAllMemory_cluster() {
    
    map<string, Processor>::iterator itToClusterProcessors = clusterProcessors.begin(); 
    
        while(itToClusterProcessors != clusterProcessors.end()) {
         
            (itToClusterProcessors->second).compactMemory_processor();
        
        ++itToClusterProcessors; 
        }

}

char Cluster::printProcessor_cluster(const string& processorID) const {

    map<string, Processor>::const_iterator itToClusterProcessors = clusterProcessors.find(processorID);

        if(itToClusterProcessors != clusterProcessors.end()) {

            (itToClusterProcessors->second).printProcesses_processor();
             return '0'; 

        }else return '1';

}

void Cluster::printAllProcessor_cluster() const {
     
    map<string, Processor>::const_iterator itToClusterProcessors = clusterProcessors.begin();

        while(itToClusterProcessors != clusterProcessors.end()) {

            cout << itToClusterProcessors->first << endl; //Imprimimos Identificador Procesador
            (itToClusterProcessors->second).printProcesses_processor();
        
        ++itToClusterProcessors;
        }

}

void Cluster::printStructure_cluster() const {

    //Recursiva privada que imprime la estructura    
    i_printStructure_cluster(clusterStructure);
    cout << endl; 

}

void Cluster::i_printStructure_cluster(const BinTree<string>& copyClusterStructure) const {
     
    if (not copyClusterStructure.empty()) {
        cout << "(" << copyClusterStructure.value() ;

        //Vamos nodo a nodo imprimiendo cada elemento
		i_printStructure_cluster(copyClusterStructure.left()); 
		i_printStructure_cluster(copyClusterStructure.right());

    cout << ")" ;
    }else cout << " "; 
  
}










