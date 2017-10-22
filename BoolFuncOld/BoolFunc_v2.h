/**
 * Comments starting with MARC: are questions or temporal comments
 */
#ifndef BOOLFUNC_H
#define BOOLFUNC_H

#include <string>
#include <memory>
#include <map>
#include <vector>
#include <assert.h>

#define TRUE 1
#define FALSE 0
#define UNDEF -1

enum node_type {
        NOD_ID, //start with '_' or alphabetic char, followed by alphanumeric, '_' or '$' chars
        NOD_CONST, //0, 1  (true TRUE false FALSE)          (1'b0 and 1'b1) -> no se que signifiquen
        NOD_NOT, //!, ~ (not NOT)
        NOD_AND, // &, && (and AND)
        NOD_OR, // |, || (or OR)
        NOD_XOR, // ^ (xor XOR)
        NOD_XNOR, // ^~, ~^ (xnor XNOR)
        //NOD_COND // bool ? true : false   (if bool then true else false)
};

class BoolFunc;

typedef std::shared_ptr<BoolFunc> Formula; //MARC: Shared pointer -> amb contador de referències

class BoolFunc
{
private:

/**
 * Var name -> unique int id
 */
static std::map<std::string, int> nameToIndex;
/**
 * Used to assign unique int id in nameToIndex
 * 0 and 1 reserved to FALSE and TRUE respectively
 * MARC: Podria ser un uint?
 * MARC: Realment no faria falta que el 0 i el 1 estiguin exclosos
 *       ja que sabrem si es true o false depenent del node_type
 */
static int last_id;

/**
 * if type == (NOD_CONST | NOD_ID) child.size() == 0
 * otherwise 2
 * MARC: potser no fa falta fer-ho amb un vector pero es més fàcil d'escalar per si
 * s'afegeixen nous tipus de node
 */
std::vector<Formula> childs;
node_type type;
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

BoolFunc(node_type type, int value) : type(type), value(value){
        assert (type == NOD_CONST);
        assert (value == UNDEF || value == TRUE || value ==  FALSE);
        // this->type = type;
        // this->value = value;
}

//MARC: Es la millor forma de passar el vector i després treballar amb ell?
BoolFunc(node_type type, int value, std::vector<Formula> & childs) : childs(childs), type(type), value(value){
        assert (type == NOD_CONST);
        assert (value == UNDEF || value == TRUE || value ==  FALSE);
}

//MARC: Passar un pointer per refefrència no té molt de sentit no? (es com ho fan a pblib formula.h)
//MARC: Mirar si el smart pointer fa el que toca en aquest cas
BoolFunc(node_type type, int value, Formula const & child): type(type), value(value){
  childs.push_back(child);
}

BoolFunc(node_type type, int value, Formula const & left, Formula const & right): type(type), value(value){
  childs.push_back(left);
  childs.push_back(right);
}

static int newId(){
        ++last_id;
        return last_id;
}

public:

static Formula newFalse() {
        return std::make_shared<BoolFunc>(NOD_CONST, FALSE);
}
static Formula newTrue() {
        return std::make_shared<BoolFunc>(NOD_CONST, TRUE);
}
static Formula newUndef() {
        return std::make_shared<BoolFunc>(NOD_CONST, UNDEF);
}

//MARC: Es podria fer override de operadors com ! ~ & && | || etc
static Formula newNot(Formula const & f) {
        return std::make_shared<BoolFunc>(NOD_NOT,UNDEF,f);
}
static Formula newAnd(Formula const & a, Formula const & b){
  return std::make_shared<BoolFunc>(NOD_AND,UNDEF,a,b);
}
static Formula newOr(Formula const & a, Formula const & b);
static Formula newXor(Formula const & a, Formula const & b);
static Formula newXnor(Formula const & a, Formula const & b);
static Formula newLit(std::string var_name){
        int lit = newId();
        assert(nameToIndex.find(var_name)!=nameToIndex.end());
        nameToIndex[var_name] = lit;
        return std::make_shared<BoolFunc>(NOD_ID,lit);
}

~BoolFunc(){
}             //MARC: Mirar que s'ha de fer a la destructora

void print();

};

#endif // BOOLFUNC_H
