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

    static int newId(const std::string & name);

    static void freeId(int id);

    static int getLastId();

    static void storeCuddWithId(int cudd, int id);
    static int getIdFromCudd(int cudd);
    static BDD bddVar();

    static BDD bddVar(int i);

    static DdManager* getCuddMgr();

};

#endif // VARSMANAGER_H
