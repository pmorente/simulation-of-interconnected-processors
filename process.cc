
#include <iostream> 
#include <string>
#include "process.hh"

//Modificadoras
Process::Process() {
} 
     
void Process::readAll_process(int ProcessID) { 
    
    id = ProcessID; 
    cin >> memory_needed >> execution_time;
          
}

bool Process::decreaseTimeExec_process(int timeToDecrease){

    if(timeToDecrease >= execution_time) {
       execution_time = 0;
       return false; 

    }else{
      execution_time = execution_time - timeToDecrease;
      return true; 
    }
}


//Consultoras

int Process::checkId_process() const {

    return id;
}

int Process::checkMemoryNeed_process() const {

    return memory_needed;
}

int Process::checkExecTime_process() const {

    return execution_time;
}

void Process::print_process() const {
     
    cout << id;
    cout << " " << memory_needed;
    cout << " " << execution_time;
}




