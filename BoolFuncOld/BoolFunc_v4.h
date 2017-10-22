/**
 * Comments starting with MARC: are questions or temporal comments
 */
#ifndef BOOLFUNC_H
#define BOOLFUNC_H

#include <string>
#include <memory>
#include <map>
#include <iostream>
#include <assert.h>

#define TRUE 1
#define FALSE 0
#define UNDEF -1

enum NodeType {
        NOD_ID, //start with '_' or alphabetic char, followed by alphanumeric, '_' or '$' chars
        NOD_CONST, //0, 1  (true TRUE false FALSE)          (1'b0 and 1'b1) -> no se que signifiquen
        NOD_NOT, //!, ~ (not NOT)
        NOD_AND, // &, && (and AND)
        NOD_OR, // |, || (or OR)
        NOD_XOR, // ^ (xor XOR)
        NOD_COND // bool ? true : false   (if bool then true else false)
};

class BoolFunc;

typedef std::shared_ptr<BoolFunc> Formula; //MARC: Shared pointer -> amb contador de referències

class BoolFunc
{
private:

/**
 * Var name -> unique int id
 */
static std::map<std::string, int> name_to_index;
/**
 * Used to assign unique int id in name_to_index
 * 0 and 1 reserved to FALSE and TRUE respectively
 * MARC: Podria ser un uint?
 * MARC: Realment no faria falta que el 0 i el 1 estiguin exclosos
 *       ja que sabrem si es true o false depenent del NodeType
 */
static int last_id;

/**
 * if type == (NOD_CONST | NOD_ID) child.size() == 0
 * otherwise 2
 * MARC: potser no fa falta fer-ho amb un vector pero es més fàcil d'escalar per si
 * s'afegeixen nous tipus de node
 */

//Formula childs[3] = {NULL,NULL,NULL};
Formula child1 = NULL, child2 = NULL, child3 = NULL;

NodeType type;
/**
 * if type == NOD_CONST then value is {0,1}
 * else if type == NOD_ID then value is {2, max_int}
 * otherwise is ignored
 */
int value;

//MARC: No se si es com Java i fa falta posar-lo explicitament privat
//Empty default constructor
BoolFunc(){
}

static int newId(){
        ++last_id;
        return last_id;
}

public:

BoolFunc(NodeType type, int value) : type(type), value(value){
        assert (type == NOD_CONST || type == NOD_ID);
        if(type == NOD_CONST)
          assert (value == UNDEF || value == TRUE || value ==  FALSE);
}

//MARC: Passar un pointer per refefrència no té molt de sentit no? (es com ho fan a pblib formula.h)
//MARC: Mirar si el smart pointer fa el que toca en aquest cas
BoolFunc(NodeType param_type, Formula const & param_child) : type(param_type), value(UNDEF){
  assert(param_type == NOD_NOT);
        child1 = param_child;
}

BoolFunc(NodeType param_type, Formula const & left, Formula const & right) : type(param_type), value(UNDEF){
        assert(param_type == NOD_AND || param_type == NOD_OR || param_type == NOD_XOR);
        child1 = left;
        child2 = right;
}

BoolFunc(NodeType param_type, Formula const & condition, Formula const & t, Formula const & f) : type(param_type), value(UNDEF){
        assert(param_type == NOD_COND);
        child1 = condition;
        child2 = t;
        child3 = f;
}

static Formula newFalse() {
        return std::make_shared<BoolFunc>(NOD_CONST, FALSE);
}
static Formula newTrue() {
        return std::make_shared<BoolFunc>(NOD_CONST, TRUE);
}
static Formula newUndef() {
        return std::make_shared<BoolFunc>(NOD_CONST, UNDEF);
}

//NOT
static Formula newNot(Formula const & f) {
        return std::make_shared<BoolFunc>(NOD_NOT,f);
}

//AND
static Formula newAnd(Formula const & a, Formula const & b){
        return std::make_shared<BoolFunc>(NOD_AND,a,b);
}

static Formula newOr(Formula const & a, Formula const & b){
        return std::make_shared<BoolFunc>(NOD_OR,a,b);
}
static Formula newXor(Formula const & a, Formula const & b){
        return std::make_shared<BoolFunc>(NOD_XOR,a,b);
}

static Formula newLit(std::string var_name){
        int lit = newId();
        assert(name_to_index.find(var_name)==name_to_index.end()); //MARC:Ens volem assegurar que la var_name no estigui utilitzada.
        name_to_index[var_name] = lit;
        return std::make_shared<BoolFunc>(NOD_ID,lit);
}

static Formula newCond(Formula const & condition, Formula const & t, Formula const & f){
  return std::make_shared<BoolFunc>(NOD_COND,condition,t,f);
}

~BoolFunc(){
}             //MARC: Mirar que s'ha de fer a la destructora

void print(int level=0){
        std::cout << "-----------------------" << std::endl;
        for(int i = 0; i < level; ++i) std::cout << "\t";
        std::cout << "Type: ";
        switch (type) {
        case NOD_ID:
                std::cout << "ID" << std::endl;
                break;
        case NOD_CONST:
                std::cout << "CONST" << std::endl;
                break;
        case NOD_NOT:
                std::cout << "NOT" << std::endl;
                break;
        case NOD_AND:
                std::cout << "AND" << std::endl;
                break;
        case NOD_OR:
                std::cout << "OR" << std::endl;
                break;
        case NOD_XOR:
                std::cout << "XOR" << std::endl;
                break;
        case NOD_COND:
                std::cout << "TRI_COND" << std::endl;
                break;
        }
        for(int i = 0; i < level; ++i) std::cout << "\t";
        std::cout << "Value: " << value << std::endl;
        if(child1 != NULL) child1->print(level+1);
        if(child2 != NULL) child2->print(level+1);
        if(child3 != NULL) child3->print(level+1);
        std::cout << "-----------------------" << std::endl;
}

};

//Operators
// Formula operator = (std::string s){
//
// }

Formula operator ! (Formula const & f){
        return BoolFunc::newNot(f);
}
Formula operator ~ (Formula const & f){
        return BoolFunc::newNot(f);
}
Formula operator & (Formula const & a, Formula const & b){
        return BoolFunc::newAnd(a, b);
}
Formula operator * (Formula const & a, Formula const & b){
        return BoolFunc::newAnd(a, b);
}
Formula operator | (Formula const & a, Formula const & b){
        return BoolFunc::newOr(a, b);
}
Formula operator + (Formula const & a, Formula const & b){
        return BoolFunc::newOr(a, b);
}
Formula operator ^ (Formula const & a, Formula const & b){
        return BoolFunc::newXor(a, b);
}

int BoolFunc::last_id = 0;
std::map<std::string, int> BoolFunc::name_to_index = {};

#endif // BOOLFUNC_H
