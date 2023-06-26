#include <iostream>  
#include <map>
#include <string> 
#include <set>
#include "process.hh"
#include "processor.hh" 

Processor::Processor() {
 
}  
      
Processor::Processor(const string& processorID, int space) {

    id = processorID;
    memoryLimit = space;
    freeSpace = space;
     
    //Añadimos un bloque igual al tamaño del Procesador al mapa de Espacios Libres con la posición 0. 
    freeMemory[space].insert(0); 

} 


char Processor::addProcess_processor(const Process& newProcess) {
    

    const int idOfProcess = newProcess.checkId_process();
    map<int, int>::iterator itToData = data.find(idOfProcess);

    if(itToData == data.end()){ 
   
        const int spaceNeededForProcess = newProcess.checkMemoryNeed_process(); 

        if(spaceNeededForProcess <= freeSpace){
            
            //Consultamos si existe el hueco más ajustado para el Proceso
            map<int, set<int>>::iterator itToFreeMemory = freeMemory.lower_bound(spaceNeededForProcess);

            if(itToFreeMemory != freeMemory.end()) { 
                
                //Se ha encontrado el hueco ideal para el Proceso.
                //Añadimos el Proceso en Procesador y actualizamos la Memoria.
               
                    //Inserir el nuevo Proceso en mapas en data(id/p.iniciales) y memory(p.iniciales/Proceso) 
                    data.insert(make_pair(idOfProcess, *((itToFreeMemory->second).begin())));
                
                    memory.insert(make_pair(*((itToFreeMemory->second).begin()), newProcess));
                   

                    //Actualizador mapa huecos/p.iniciales

                    const int newfreeMemoryKey = (itToFreeMemory->first) - spaceNeededForProcess; 
                    const int newfreeMemoryPosition = *((itToFreeMemory->second).begin()) + spaceNeededForProcess; 

                    //Eliminamos el hueco que habiamos encontrado con lower_bound
                    (itToFreeMemory->second).erase((itToFreeMemory->second).begin());
                    if((itToFreeMemory->second).empty()) freeMemory.erase(itToFreeMemory);

                    //Si el hueco no se ha llenado, insertamos el hueco libre sobrante
                    if(newfreeMemoryKey > 0) freeMemory[newfreeMemoryKey].insert(newfreeMemoryPosition); 
                   
                    
                freeSpace -= spaceNeededForProcess; 

                return '0';

            }else return '9';

        }else return '9';
       
    }else return '8';
}


char Processor::elimProcess_processor(int processID) {
   
    map<int, int>::iterator itToData = data.find(processID);
    
        if(itToData != data.end()){

            //Se procede a eliminar el Proceso encontrado
      
            map<int, Process>::iterator itToMemory = memory.find(itToData->second);

            elimProcess(itToMemory, itToData);

            return '0'; 
    
        }else return 'X';

}

 
void Processor::elimProcess(map<int, Process>::iterator itToMemory, map<int, int>::iterator itToData) {
   
   //Obtenemos los espacios vacios entre el proceso que queremos eliminar y los elementos de su derecha e izquierda

        //p.inicial y tam Proceso (el actual) que se va a eliminar  
        const int positionActualElement = (itToMemory)->first;
        const int sizeActualElement = ((itToMemory)->second).checkMemoryNeed_process();


        //Obtenemos hueco en la izquierda
         int sizeLeftFreeMemory;

        if(itToMemory == memory.begin()){ 

            //Caso especial, no existe un Proceso anterior
            sizeLeftFreeMemory = positionActualElement; 

        }else{

            --itToMemory;
            sizeLeftFreeMemory = positionActualElement - ((itToMemory)->first) - (((itToMemory)->second).checkMemoryNeed_process()); 
            ++itToMemory;
        }  
        

        //Obtenemos hueco por la derecha
        int sizeRightFreeMemory;
        ++itToMemory;
        if(itToMemory == memory.end()) sizeRightFreeMemory = memoryLimit - positionActualElement - sizeActualElement; //Caso especial, no existe un Proceso siguiente 
        else sizeRightFreeMemory = ((itToMemory)->first) - positionActualElement - sizeActualElement;

        --itToMemory;

   
       
        //Obtenemos suma total espacio liberado
        const int totalFreeSpaceAfterDelete = sizeActualElement + sizeLeftFreeMemory + sizeRightFreeMemory; 

            //Actualizamos Memoria del Procesador

                //Eliminamos en freeMemory(mapa huecos/p.iniciales) los huecos derecha/izquierda
                map<int, set<int>>::iterator itToFreeMemory; 

                if(sizeLeftFreeMemory != 0) { 

                    itToFreeMemory = freeMemory.find(sizeLeftFreeMemory);

                    (itToFreeMemory->second).erase(positionActualElement-sizeLeftFreeMemory); 
                    if((itToFreeMemory->second).empty()) freeMemory.erase(itToFreeMemory);
     
                }

                if(sizeRightFreeMemory != 0) { 
        
                    itToFreeMemory = freeMemory.find(sizeRightFreeMemory);

                    (itToFreeMemory->second).erase(positionActualElement+sizeActualElement); 
                    if((itToFreeMemory->second).empty()) freeMemory.erase(itToFreeMemory);
       
                }

                //Actualizamos los tres mapas de la Memoria
                freeMemory[totalFreeSpaceAfterDelete].insert(positionActualElement - sizeLeftFreeMemory); 
                memory.erase(itToMemory);
                data.erase(itToData); 

        freeSpace += sizeActualElement;

}


void Processor::compactMemory_processor() {

    if (not(memory.empty()) and (freeSpace != 0) and notCompacted()) {

        //Compactamos primero el mapa memory (p.iniciales/Proceso)

        int position = 0;
        map<int, Process>::iterator itToMemory = memory.begin();
        map<int, Process>::iterator copyItToMemory;
        
        while (itToMemory != memory.end()) {
         
          if(position != itToMemory->first) { 

            //El Proceso no esta en la posición correcta, lo recolocamos;

                //Lo insertamos en su posición correcta y actualizamos el mapa data (id/p.iniciales)
                copyItToMemory = memory.insert(itToMemory, make_pair(position, itToMemory->second));

                map<int, int>::iterator itToData = data.find((itToMemory->second).checkId_process());
                itToData->second = position; 
                
                //Borramos el Proceso mal colocado
                memory.erase(itToMemory);
                itToMemory = copyItToMemory;
          }

        position += itToMemory->second.checkMemoryNeed_process();
        ++itToMemory;

        }
            
            //Limpiamos mapa y añadimos un único hueco libre, el resultante después del compactado
            freeMemory.clear();
            freeMemory[memoryLimit - position].insert(position);
    }
}


bool Processor::notCompacted() const {

    //Apuntamos al último Proceso
    map<int, Process>::const_iterator itToMemory = memory.end();
    --itToMemory; 
    
    //Calculamos el hueco entre el último proceso y el límite de la Memoria y comparamos con Espacio Libre 
    if(memoryLimit - ((itToMemory->first) + (itToMemory->second).checkMemoryNeed_process()) == freeSpace) return false;
    else return true; 
}

pair<bool,int> Processor::adjustedSpace(int sizeProcess) const {
 
    if(sizeProcess > freeSpace) return make_pair(false,-1); //El Proceso no cabe

    map<int, set<int>>::const_iterator itToFreeMemory = freeMemory.lower_bound(sizeProcess);

    if(itToFreeMemory != freeMemory.end()) return make_pair(true, itToFreeMemory->first); //Devolvemos el hueco más ajustado
    else return make_pair(false, -1); //No se ha encontrado ningun hueco continuo >= sizeProcess

}

int Processor::freeMemoryAfter(int sizeProcess) const{

    return (freeSpace - sizeProcess); 
}


void Processor::decreaseTime_processor(int timeDecrease) {

  
    map<int, Process>::iterator itToMemory = memory.begin();
   
    while(itToMemory != memory.end()){

        if(not((itToMemory->second).decreaseTimeExec_process(timeDecrease))) {
            
            //El Proceso ha terminado y debe ser eliminado
            map<int, Process>::iterator copyItToMemory = itToMemory;
            map<int,int>::iterator itToData = data.find((itToMemory->second).checkId_process()); 
            ++itToMemory;

            elimProcess(copyItToMemory, itToData);

        }else ++itToMemory; 
    
    } 
    
}

bool Processor::existsProcess_processor(int processID) const{
    
    map<int,int>::const_iterator itToData = data.find(processID);

    if(itToData != data.end()) return true;
    else return false; 
}

bool Processor::empty_processor() const {

    if(data.empty()) return true;
    else return false; 
}

string Processor::checkID_processor() const {

    return id;
}

int Processor::checkMemory_processor() const {

    return memoryLimit; 
}

int Processor::checkFreeSpace_processor() const {

    return freeSpace; 
}

void Processor::printProcesses_processor() const {

   map<int,Process>::const_iterator itToMemory = memory.begin();

    while(itToMemory != memory.end()) {

        cout << itToMemory->first << " " ;
        (itToMemory->second).print_process(); 
        cout << endl; 

    ++itToMemory; 
    }
}