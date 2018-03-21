#include "VarsManager.h"

VarsManager::VarsManager(){};

VarsManager VarsManager::getInstance(){
    if(instance == NULL){
        instance = new VarsManager;
    }
    return *instance;
}

int VarsManager::newId(const std::string & name) {
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

void VarsManager::freeId(int id){
    //TODO: if id belongs also to cudd_to_index, delete from it too.
    recyclable.push(id);
    //Delete id from the map
    std::map<std::string,int>::iterator it_delete;
    bool found = false;
    for (std::map<std::string,int>::iterator it = name_to_index.begin();
            it != name_to_index.end() && !found; ++it )
        if (it->second == id){
            it_delete = it;
            found = true;
        }
    //If the key is "" we will not find it
    if (found)
        name_to_index.erase(it_delete);

}

int VarsManager::getLastId(){return last_id;}

void VarsManager::storeCuddWithId(int cudd, int id){
    cudd_to_index[cudd] = id;
    //BUG: this map never releases memory
}
int VarsManager::getIdFromCudd(int cudd){
    return cudd_to_index[cudd];
}
BDD VarsManager::bddVar(){
    return mgr.bddVar();
}

BDD VarsManager::bddVar(int i){
    return mgr.bddVar(i);
}

DdManager* VarsManager::getCuddMgr(){
    return mgr.getManager();
}

VarsManager* VarsManager::instance = NULL;
