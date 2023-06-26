
#include <iostream>  
#include <string> 
#include <set>
#include <list>   

#include "priority.hh" 
#include "process.hh" 
   
Priority::Priority() {
     
}
 
Priority::Priority(const string& idPriority) {

    //Iniciamos la Prioridad con cero Procesos
      Id = idPriority;
      acceptedProcesses = 0;
      deniedProcesses = 0; 
}

char Priority::pushProcess_priority(const Process& process) {

      //Intentamos insertar el nuevo Proceso
      if(idsProcessesInQueue.insert(process.checkId_process()).second) { 

        //Insertado correctamente
        queueProcesses.push_back(process);
        return '0';

      }else return '7'; //ya existe el Proceso en Prioridad

}

Process Priority::popProcess_priority() {

    //Obtenemos el primer elemento de la Prioridad
    const Process popProcess = *(queueProcesses.begin()); 
    
    //Lo eliminamos de la Prioridad
    queueProcesses.erase(queueProcesses.begin()); 
    idsProcessesInQueue.erase(popProcess.checkId_process());  
  
  return popProcess; 
}

void Priority::increaseAccProc_priority() {

    ++acceptedProcesses; 
}

void Priority::increaseDenProc_priority() {

    ++deniedProcesses; 
}


int Priority::size_priority() const {

    return queueProcesses.size(); 
}

bool Priority::empty_priority() const {

    if(queueProcesses.empty()) return true;
    else return false; 
}

void Priority::print_priority() const{

    list<Process>::const_iterator itToQueueProcesses = queueProcesses.begin(); 
    
    while(itToQueueProcesses != queueProcesses.end()) {
         
        (*itToQueueProcesses).print_process();
        cout << endl; 

    ++itToQueueProcesses;     
    }
    cout << acceptedProcesses << " " << deniedProcesses << endl;
     
} 