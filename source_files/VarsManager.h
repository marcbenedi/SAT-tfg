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
    int last_id;

    //When an id is unused is pushed into this queue for a future use.
    std::queue<int> recyclable;

    /**
     * Var name -> unique int id
     */
    std::map < std::string, int > name_to_index;
    /**
     * BDD Var int -> unique int id
     */
    std::map < int, int > cudd_to_index;

    Cudd mgr;

    static VarsManager* instance;

public:
    static VarsManager getInstance();
    int newId(const std::string & name  = "");
    void freeId(int id);
    int getLastId();
    void storeCuddWithId(int cudd, int id);
    int getIdFromCudd(int cudd);
    BDD bddVar();
    BDD bddVar(int i);
    DdManager* getCuddMgr();

};

#endif // VARSMANAGER_H
