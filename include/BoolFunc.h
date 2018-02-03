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
    BoolFunc() {}

    //Converting constructors

    BoolFunc(const std::string & name) {
        //QUESTION: Què passa si name ja existeix a VarsManager?
        type = NOD_ID;
        value = VarsManager::newId(name);
    }

    BoolFunc(NodeType type, int value): type(type), value(value) {
        assert(type == NOD_ID);
    }

    BoolFunc(NodeType param_type, Formula const & param_child): type(param_type), value(UNDEF) {
        assert(param_type == NOD_NOT);
        child1 = param_child;
    }

    BoolFunc(NodeType param_type, Formula const & left, Formula const & right): type(param_type), value(UNDEF) {
        assert(param_type == NOD_AND || param_type == NOD_OR || param_type == NOD_XOR);
        child1 = left;
        child2 = right;
    }

    ~BoolFunc() {
        //QUESTION: En cas que sigui NOD_ID s'ha d'eliminar del map la variable?
        if(type == NOD_ID) VarsManager::freeId(value);
        //delete child1; //BUG: b = !b recursiu
        child1 = NULL;
        //delete child2;
        child2 = NULL;
    }

//////////////////////////////////GETTERS AND SETTERS///////////////////////////
    NodeType getType() const {return type;}
    int getValue() const {return value;}
    const Formula getChild1() const {return child1;}
    const Formula getChild2() const {return child2;}
    void setType(NodeType t){type = t;}
    void setValue(int v){value = v;}
    void setChild1(Formula const & c){child1 = c;}
    void setChild2(Formula const & c){child2 = c;}

/////////////////////////////////////////////NODE CONSTRUCTORS//////////////////

    static Formula newNot(Formula const & f) {
        return std::make_shared<BoolFunc>(NOD_NOT,f);
    }

    static Formula newAnd(Formula
        const & a, Formula
        const & b) {
        return std::make_shared<BoolFunc>(NOD_AND,a,b);
    }

    static Formula newOr(Formula
        const & a, Formula
        const & b) {
        return std::make_shared<BoolFunc>(NOD_OR,a,b);
    }
    static Formula newXor(Formula
        const & a, Formula
        const & b) {
        return std::make_shared<BoolFunc>(NOD_XOR,a,b);
    }

    static Formula newLit(std::string var_name) {
        int lit = VarsManager::newId(var_name);
        return std::make_shared<BoolFunc>(NOD_ID,lit);
    }

//////////////////////////////OTHER FUNCTIONS///////////////////////////////////
    void print(int level = 0) const {
        for (int i = 0; i < level; ++i) std::cout << "\t";
        std::cout << "-----------------------" << std::endl;
        for (int i = 0; i < level; ++i) std::cout << "\t";
        std::printf("Address %p\n", (void *)this);
        for (int i = 0; i < level; ++i) std::cout << "\t";
        std::cout << "Type: ";
        switch (type) {
        case NOD_ID:
            std::cout << "ID" << std::endl;
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
        }
        for (int i = 0; i < level; ++i) std::cout << "\t";
        std::cout << "Value: " << value << std::endl;
        if (child1 != NULL) child1->print(level + 1);
        if (child2 != NULL) child2->print(level + 1);
        std::cout << "-----------------------" << std::endl;
    }

    // BoolFunc & operator = (const BoolFunc & param){
    //   std::cout << "operator = " << std::endl;
    //   param.print();
    //   if (this == &param) {
    //         std::cout << "Les adreces son iguals" << std::endl;
    //         return *this;
    //   }
    //   else{
    //       std::cout << "Les adreces son diferents" << std::endl;
    //       //type = param.type;
    //       //value = param.value;
    //       //child1 = param.child1;
    //       //child2 = param.child2;
    //       //child3 = param.child3;
    //   }
    //   BoolFunc *t = new BoolFunc(param.type, *param.child1);
    //   std::cout << "pene" << std::endl;
    //   t->print();
    //   return *t;
    // }

};

//////////////////////////////FORMULA OPERATORS/////////////////////////////////
Formula operator!(Formula const & f) {
    return BoolFunc::newNot(f);
}
Formula operator~(Formula const & f) {
    return BoolFunc::newNot(f);
}
Formula operator & (Formula const & a, Formula const & b) {
    return BoolFunc::newAnd(a, b);
}
Formula operator * (Formula const & a, Formula const & b) {
    return BoolFunc::newAnd(a, b);
}
Formula operator | (Formula const & a, Formula const & b) {
    return BoolFunc::newOr(a, b);
}
Formula operator + (Formula const & a, Formula const & b) {
    return BoolFunc::newOr(a, b);
}
Formula operator ^ (Formula const & a, Formula const & b) {
    return BoolFunc::newXor(a, b);
}
//BUG: Els operadors tipus += no funcionen bé
Formula operator += (const Formula & lhs, const Formula & rhs) {
    return BoolFunc::newOr(lhs, rhs);
}

Formula operator *= (const Formula & lhs, const Formula & rhs) {
    return BoolFunc::newAnd(lhs, rhs);
}

Formula operator ^= (const Formula & lhs, const Formula & rhs) {
    return BoolFunc::newXor(lhs, rhs);
}

#endif // BOOLFUNC_H
