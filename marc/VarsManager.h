#ifndef VARSMANAGER_H
#define VARSMANAGER_H

#include <assert.h>
#include <queue>
#include <iostream>

class VarsManager {
private:
    VarsManager();
    /**
     * Used to assign unique int id in name_to_index
     * 0 and 1 reserved to FALSE and TRUE respectively
     * MARC: Podria ser un uint?
     * MARC: Realment no faria falta que el 0 i el 1 estiguin exclosos
     *       ja que sabrem si es true o false depenent del      NodeType
     */
    static int last_id;

    //When an id is unused is pushed into this queue for a future use.
    static std::queue<int> recyclable;

public:

    static int newId() {
        if(!recyclable.empty()){
            int front = recyclable.front();
            recyclable.pop();
            return front;
        }
        else{
            ++last_id;
            return last_id;
        }
    }

    static void freeId(int id){
        recyclable.push(id);
    }

    static int getLastId(){return last_id;}

};

int VarsManager::last_id = 0;
std::queue<int> VarsManager::recyclable;

#endif // VARSMANAGER_H
