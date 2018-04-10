#include "VarsManager.h"

VarsManager::VarsManager(){}

VarsManager* VarsManager::getInstance(){
    if(instance == NULL){
        std::cout << "new instance" << '\n';
        instance = new VarsManager;
        std::cout << "hem creat de nou i getLastID" <<instance->getLastId() << '\n';
        std::cout << "ladreca es " << instance << '\n';
        std::cout << "pero la cola es" << '\n';
        while (!instance->recyclable.empty()) {
            std::cout << instance->recyclable.front() << '\n';
            instance->recyclable.pop();
        }
    }
    return instance;
}

int VarsManager::newId(const std::string & name) {
    //Check if exists in the map
    bool exists = name_to_index.find(name) != name_to_index.end();

    if(exists) {
        return name_to_index[name];
    }

    int id;

    if(!recyclable.empty()){
        std::cout << "pene2lol" << '\n';
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
void VarsManager::setLastId(int n){last_id = n;}

void VarsManager::storeCuddWithId(int cudd, int id){
    cudd_to_index[cudd] = id;
    //BUG: this map never releases memory
}
int VarsManager::getIdFromCudd(int cudd){
    return cudd_to_index[cudd];
}
int VarsManager::getCuddFromId(int id){
    std::map<int,int>::iterator it = cudd_to_index.begin();
    while (it != cudd_to_index.end()) {
        if(it->second == id)
            return it->first;
        it++;
    }
    return -1;
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

int VarsManager::getNumIds(){
    return name_to_index.size();
}

void VarsManager::clearInstance(){
    delete instance;
    instance = NULL;
}

VarsManager::~VarsManager(){
    std::cout << "me destruyen primo" << '\n';
}

// VarsManager* VarsManager::instance = NULL;
std::unique_ptr<VarsManager> VarsManager::instance;
