#ifndef VARSMANAGER_H
#define VARSMANAGER_H

#include <vector>
#include <assert.h>

class VarsManager {
private:
/**
 * Used to assign unique int id in name_to_index
 * 0 and 1 reserved to FALSE and TRUE respectively
 * MARC: Podria ser un uint?
 * MARC: Realment no faria falta que el 0 i el 1 estiguin exclosos
 *       ja que sabrem si es true o false depenent del NodeType
 */
static int last_id;

public:

static int newId() {
        //MARC: Que puguis marcar com a unused una variable i així pugui retornar el seu inten un futur
        ++last_id;
        return last_id;
}
};

int VarsManager::last_id = 0;

#endif // VARSMANAGER_H
