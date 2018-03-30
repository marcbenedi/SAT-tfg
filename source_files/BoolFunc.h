#ifndef BOOLFUNC_H
#define BOOLFUNC_H

#include <string>
#include <memory>
#include <iostream>
#include <assert.h>
#include "VarsManager.h"

#define TRUE 1
#define FALSE 0
#define UNDEF -1

enum NodeType {
    NOD_ID, //start with '_' or alphabetic char, followed by alphanumeric, '_' or '$' chars
    NOD_NOT, //!, ~ (not NOT)
    NOD_AND, // *, && (and AND)
    NOD_OR, // +, || (or OR)
    NOD_XOR, // ^ (xor XOR)
};

class BoolFunc;

//Shared pointer with reference counter
typedef std::shared_ptr < BoolFunc > Formula;

class BoolFunc {
    private:

    Formula child1 = NULL;
    Formula child2 = NULL;

    NodeType type;
    /**
     * if type == NOD_ID then value is {1, max_int}
     * otherwise is ignored = UNDEF
     */
    int value;

    public:
/////////////////////////////////////////////CONSTRUCTORS///////////////////////
    //Empty default constructor
    BoolFunc();

    //Converting constructors
    BoolFunc(const std::string & name);
    BoolFunc(NodeType param_type, Formula const & param_child);
    BoolFunc(NodeType param_type, Formula const & left, Formula const & right);
    BoolFunc(NodeType param_type, Formula const & left, Formula const & right, int param_value);

    ~BoolFunc();

//////////////////////////////////GETTERS AND SETTERS///////////////////////////
    NodeType getType() const;
    int getValue() const;
    const Formula getChild1() const;
    const Formula getChild2() const;
    void setType(NodeType t);
    void setValue(int v);
    void setChild1(Formula const & c);
    void setChild2(Formula const & c);

/////////////////////////////////////////////NODE CONSTRUCTORS//////////////////

    static Formula newNot(Formula const & f);

    static Formula newAnd(Formula
        const & a, Formula
        const & b);

    static Formula newOr(Formula
        const & a, Formula
        const & b);
    static Formula newXor(Formula
        const & a, Formula
        const & b) ;

    static Formula newLit(std::string var_name);

//////////////////////////////OTHER FUNCTIONS///////////////////////////////////
    void print(int level=0) const;
    // BoolFunc & operator = (const BoolFunc & f);
};

//////////////////////////////FORMULA OPERATORS/////////////////////////////////
Formula operator!(Formula const & f);
Formula operator~(Formula const & f);
Formula operator & (Formula const & a, Formula const & b);
Formula operator * (Formula const & a, Formula const & b);
Formula operator | (Formula const & a, Formula const & b);
Formula operator + (Formula const & a, Formula const & b);
Formula operator ^ (Formula const & a, Formula const & b);
//BUG: Els operadors tipus += no funcionen bé
Formula operator += (const Formula & lhs, const Formula & rhs);
Formula operator *= (const Formula & lhs, const Formula & rhs);
Formula operator ^= (const Formula & lhs, const Formula & rhs);

#endif // BOOLFUNC_H
