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

    static VarsManager* instance;

    VarsManager();
    /**
     * Used to assign unique int id in name_to_index
     * 0 and 1 reserved to FALSE and TRUE respectively
     * MARC: Podria ser un uint?
     * MARC: Realment no faria falta que el 0 i el 1 estiguin exclosos
     *       ja que sabrem si es true o false depenent del      NodeType
     */
    int last_id = 0;

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

public:
    /**
     * This class follows the singleton pattern. There must be only one instance of this class
     *@return Returns the current existing instance or creates a new one
     */
    static VarsManager* getInstance();

    /**
     * Given a variable name, returns the integer representing it
     * If the name already exists it returns the same integer
     * If no name is provided a new id is returned and the name is not stored
     * (This is used for variables created by transformation like tseitin)
     *@param name
     *@return an integer used for representing the variable.
     */
    int newId(const std::string & name  = "");

    /**
     * The integer representing a variable is released
     * It will be added to a recyclable queue where the variables will be assigned again when newId()
     *@param id
     */
    void freeId(int id);

    int getLastId(); void setLastId(int n);

    /**
     * Relates the two ids
     *@param cudd : the id from cudd library
     *@param id : the id from this library
     */
    void storeCuddWithId(int cudd, int id);

    /**
     * Given the cudd id returns the id from this library
     *@param cudd : the id from cudd library
     *@return id from this library
     */
    int getIdFromCudd(int cudd);

    /**
     * Given the id from this library returns the cudd id
     *@param id : id from this library
     *@return the cudd library
     */
    int getCuddFromId(int id);

    /**
     * To get a new BDD var from the cudd library
     *@return a BDD var
     */
    BDD bddVar();

    /**
     * To get a new BDD var from the cudd library identified by i
     *@param i
     *@return a BDD var identified by i
     */
    BDD bddVar(int i);

    /**
     * Returns a pointer to DdManager from the cudd library
     *@return a pointer to DdManager
     */
    DdManager* getCuddMgr();

    int getNumIds();

    /**
     * Deletes all the information stored in the class
     */
    void clearInstance();

    ~VarsManager();

};

#endif // VARSMANAGER_H
