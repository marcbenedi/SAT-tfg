#ifndef VARSMANAGER_H
#define VARSMANAGER_H

#include <assert.h>
#include <queue>
#include <iostream>
#include <map>

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

    /**
     * Var name -> unique int id
     */
    static std::map < std::string, int > name_to_index;
    /**
     * BDD Var int -> unique int id
     */
    static std::map < int, int > cudd_to_index;

public:

    static int newId(const std::string & name) {
        //Comprovar si existeix en el map.
        bool exists = name_to_index.find(name) != name_to_index.end();

        if(exists) assert(false);
        //MARC: Aleshores hauria de tenir una estructura amb una referència a totes les formules creades
        //TODO:Si existeix es copia

        int id;

        if(!recyclable.empty()){
            id = recyclable.front();
            recyclable.pop();
        }
        else{
            ++last_id;
            id = last_id;
        }

        if (name != ""){name_to_index[name] = id;} //MARC: "" s'utilitza quan no és important el nom
        return id;

    }

    static void freeId(int id){
        //TODO: eliminar del map tambe l'string
        recyclable.push(id);
    }

    static int getLastId(){return last_id;}

    static void storeCuddWithId(int cudd, int id){
        cudd_to_index[cudd] = id;
    }
    static int getIdFromCudd(int cudd){
        return cudd_to_index[cudd];
    }

};

int VarsManager::last_id = 0;
std::queue<int> VarsManager::recyclable;
std::map < std::string, int > VarsManager::name_to_index = {};
std::map <int,int> VarsManager::cudd_to_index = {};

#endif // VARSMANAGER_H
