#ifndef BOOLFUNC_H
#define BOOLFUNC_H

#include <string>
using namespace std;

// node types
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

class BoolFunc
{
private:

BoolFunc *first;
BoolFunc *second;
BoolFunc *third;   //Used when type == NOD_COND
/**
 * Una altra opció que he pensat es tenir un vector de (BoolFunc *) i que segons
 * el tipus de node tingui una mida o una altra
 *
 * vector<BoolFunc*> childs;
 *
 */

node_type type;
string value;

public:

//Empty default constructor
BoolFunc(){
}

BoolFunc(BoolFunc* first, BoolFunc* second, BoolFunc* third,
         node_type type, string value){
        this->first = first;
        this->second = second;
        this->third = third;
        this->type = type;
        this->value = value;
}

//Getters
BoolFunc* getFirst(){
        return first;
}
BoolFunc* getSecond(){
        return second;
}
BoolFunc* getThird(){
        return third;
}
node_type getType(){
        return type;
}
string getValue(){
        return value;
}

//Setters
void setFirst(BoolFunc* param){
        first = param;
}
void setSecond(BoolFunc* param){
        second = param;
}
void setThird(BoolFunc* param){
        third = param;
}
void setType(node_type param){
        type = param;
}
void setValue(string param){
        value = param;
}

/**
 * Se li podria passar un parametre per indicar amb quin mètode ha de fer la conversió
 * p.e : 1 == afegir variable auxiliar per cada node_type
 * p.e : 4 == utilitzant l'heuristica que segons la situació aplica un mètode o un altre
 * podria retornar un CNFFunc == vector<vector<int> >
 */
BoolFunc toCNF();

void print();

};

#endif // BOOLFUNC_H
