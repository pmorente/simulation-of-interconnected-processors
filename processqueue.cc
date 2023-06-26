
#include <iostream>  
#include <string>  
#include <map> 
//#include <vector>

#include "cluster.hh"
#include "process.hh"
#include "priority.hh"
#include "processqueue.hh"
   
 
ProcessQueue::ProcessQueue() {
      
}  

char ProcessQueue::addProcess_ProcessQueue(const string& priorityID, const Process& process) {

    map<string, Priority>::iterator itToAreaProcesses = areaProcesses.find(priorityID);
    
     if(itToAreaProcesses != areaProcesses.end()) {
        
          return (itToAreaProcesses->second).pushProcess_priority(process);  

     }else return '5'; 
}


char ProcessQueue::addPriority_ProcessQueue(const string& priorityID) {
     
     if(areaProcesses.insert(make_pair(priorityID, Priority(priorityID))).second) return '0';
     else return '4';

}
  

char ProcessQueue::elimPriority_ProcessQueue(const string& priorityID) {
     
     map<string, Priority>::iterator itToAreaProcesses = areaProcesses.find(priorityID);  

     if(itToAreaProcesses != areaProcesses.end()) {
          
          //Consultamos si la Prioridad está vacia
          if((itToAreaProcesses->second).empty_priority()) {

               areaProcesses.erase(itToAreaProcesses); 
               return '0';

          }else return '6'; 

     }else return '5'; 

}

void ProcessQueue::sendProcesses_ProcessQueue(int n, Cluster& myCluster) {
     
     map<string, Priority>::iterator itToAreaProcesses = areaProcesses.begin();
     
     if(itToAreaProcesses != areaProcesses.end()) {
  
          int countedElementsPriority = 0;
          int sizePriority = (itToAreaProcesses->second).size_priority(); 
     
               while(itToAreaProcesses != areaProcesses.end() and n > 0) {
          
                    //Comprobamos si ya hemos recorrido todos los elementos de la Prioridad
                    if((countedElementsPriority < sizePriority)) {

                         //Extraemos y eliminamos el primer Proceso de la Prioridad
                         const Process processFromPriority = (itToAreaProcesses->second).popProcess_priority();
                
                              if(myCluster.fromProcessQueueInsert_cluster(processFromPriority)) {

                                   //Proceso acceptado por el Cluster
                                   (itToAreaProcesses->second).increaseAccProc_priority();
                                   --n; 
                                   ++countedElementsPriority;

                              }else{
                                   
                                   //Proceso rechazado por el Cluster, volvemos a insertar el Proceso al final de la Prioridad
                                   (itToAreaProcesses->second).increaseDenProc_priority(); 
                                   (itToAreaProcesses->second).pushProcess_priority(processFromPriority);
                                   
                                   ++countedElementsPriority; 
                    
                              }
                    }else{

                         //Saltamos a la siguiente Prioridad y reseteamos los elementos contados y tam.Prioridad
                         ++itToAreaProcesses;
                         countedElementsPriority = 0; 
                         if(itToAreaProcesses != areaProcesses.end()) { sizePriority = (itToAreaProcesses->second).size_priority();}  
                    }
          
               }

     }
} 


void ProcessQueue::print_ProcessQueue() const {

     map<string, Priority>::const_iterator itToAreaProcesses = areaProcesses.begin();

          while(itToAreaProcesses != areaProcesses.end()) {

               cout << (itToAreaProcesses->first) << endl;
               (itToAreaProcesses->second).print_priority(); 

          ++itToAreaProcesses; 
          }
}

char ProcessQueue::printPriority_ProcessQueue(const string& priorityID) const {
     
     map<string, Priority>::const_iterator itToAreaProcesses = areaProcesses.find(priorityID);

          if(itToAreaProcesses != areaProcesses.end()) {
             
               (itToAreaProcesses->second).print_priority(); 

               return '0';

          }else return '5'; //No se ha encontrado la Prioridad
}

