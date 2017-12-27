#ifndef VARSMANAGER_H
#define VARSMANAGER_H

#include <assert.h>
#include <queue>
#include <iostream>
#include <map>
#include "util.h"
#include "cudd.h"
#include "cuddObj.hh"

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

    static Cudd mgr;

public:

    static int newId(const std::string & name) {
        //Check if exists in the map
        bool exists = name_to_index.find(name) != name_to_index.end();

        if(exists) assert(false);
        //IDEA: Si existeix es copia
        //Aleshores hauria de tenir una estructura amb una referència a totes les formules creades

        int id;

        if(!recyclable.empty()){
            id = recyclable.front();
            recyclable.pop();
        }
        else{
            ++last_id;
            id = last_id;
        }

        //NOTE: "" is used when it does not need to be stored
        if (name != ""){name_to_index[name] = id;}
        return id;

    }

    static void freeId(int id){
        //TODO: delete from the map also the string related to it.
        //if id belongs also to cudd_to_index, delete from it too.
        recyclable.push(id);
    }

    static int getLastId(){return last_id;}

    static void storeCuddWithId(int cudd, int id){
        cudd_to_index[cudd] = id;
    }
    static int getIdFromCudd(int cudd){
        return cudd_to_index[cudd];
    }
    static BDD bddVar(){
        return mgr.bddVar();
    }

    static BDD bddVar(int i){
        return mgr.bddVar(i);
    }

};

int VarsManager::last_id = 0;
std::queue<int> VarsManager::recyclable;
std::map < std::string, int > VarsManager::name_to_index = {};
std::map <int,int> VarsManager::cudd_to_index = {};
Cudd VarsManager::mgr;

#endif // VARSMANAGER_H
