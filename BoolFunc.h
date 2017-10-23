#ifndef BOOLFUNC_H
#define BOOLFUNC_H

#include <string>
#include <memory>
#include <map>
#include <iostream>
#include <assert.h>
#include "VarsManager.h"

#define TRUE 1
#define FALSE 0
#define UNDEF - 1

enum NodeType {
    NOD_ID, //start with '_' or alphabetic char, followed by alphanumeric, '_' or '$' chars
    NOD_CONST, //0, 1  (TRUE FALSE)
    NOD_NOT, //!, ~ (not NOT)
    NOD_AND, // *, && (and AND)
    NOD_OR, // +, || (or OR)
    NOD_XOR, // ^ (xor XOR)
    NOD_COND // bool ? true : false   (if bool then true else false)
};

class BoolFunc;

//Shared pointer with reference counter
//typedef std::shared_ptr < BoolFunc > Formula;

class BoolFunc {
    private:

        /**
         * Var name -> unique int id
         */
        static std::map < std::string, int > name_to_index;

    const BoolFunc * child1 = NULL; // Modifiable pointer  const value
    const BoolFunc * child2 = NULL;
    const BoolFunc * child3 = NULL;

    NodeType type;
    /**
     * if type == NOD_CONST then value is {TRUE,FALSE}
     * else if type == NOD_ID then value is {1, max_int}
     * otherwise is ignored = UNDEF
     */
    int value;

    //MARC: Es pot construïr un UNDEF??
    BoolFunc(NodeType type, int value): type(type), value(value) {
        assert(type == NOD_CONST || type == NOD_ID);
        if (type == NOD_CONST)
            assert(value == UNDEF || value == TRUE || value == FALSE);
    }

    BoolFunc(NodeType param_type, BoolFunc const & param_child): type(param_type), value(UNDEF) {
        assert(param_type == NOD_NOT);
        child1 = & param_child;
        //std::cout<< "constructor NOT " << std::endl;
        //std::printf("My address %p\n", (void *)this);
        //std::printf("Child address %p\n", &param_child);
    }

    BoolFunc(NodeType param_type, BoolFunc const & left, BoolFunc const & right): type(param_type), value(UNDEF) {
        assert(param_type == NOD_AND || param_type == NOD_OR || param_type == NOD_XOR);
        child1 = & left;
        child2 = & right;
    }

    BoolFunc(NodeType param_type, BoolFunc const & condition, BoolFunc const & t, BoolFunc const & f): type(param_type), value(UNDEF) {
        assert(param_type == NOD_COND);
        child1 = & condition;
        child2 = & t;
        child3 = & f;
    }

    public:

    NodeType getType() const {return type;}
    int getValue() const {return value;}
    const BoolFunc* getChild1() const {return child1;}
    const BoolFunc* getChild2() const {return child2;}
    const BoolFunc* getChild3() const {return child3;}
    void setType(NodeType t){type = t;}
    void setValue(int v){value = v;}
    void setChild1(BoolFunc const & c){child1 = &c;}
    void setChild2(BoolFunc const & c){child2 = &c;}
    void setChild3(BoolFunc const & c){child3 = &c;}

    static BoolFunc newFalse() {
        return BoolFunc(NOD_CONST, FALSE);
    }
    static BoolFunc newTrue() {
        return BoolFunc(NOD_CONST, TRUE);
    }
    static BoolFunc newUndef() {
        return BoolFunc(NOD_CONST, UNDEF);
    }

    static BoolFunc newNot(BoolFunc
        const & f) {
        return BoolFunc(NOD_NOT, f);
    }

    static BoolFunc newAnd(BoolFunc
        const & a, BoolFunc
        const & b) {
        return BoolFunc(NOD_AND, a, b);
    }

    static BoolFunc newOr(BoolFunc
        const & a, BoolFunc
        const & b) {
        return BoolFunc(NOD_OR, a, b);
    }
    static BoolFunc newXor(BoolFunc
        const & a, BoolFunc
        const & b) {
        return BoolFunc(NOD_XOR, a, b);
    }

    static BoolFunc newLit(std::string var_name) {
        assert(name_to_index.find(var_name) == name_to_index.end());
        int lit = VarsManager::newId();
        name_to_index[var_name] = lit;
        return BoolFunc(NOD_ID, lit);
    }

    static BoolFunc newCond(BoolFunc
        const & condition, BoolFunc
        const & t, BoolFunc
        const & f) {
        return BoolFunc(NOD_COND, condition, t, f);
    }

    ~BoolFunc() {
        //MARC: En cas que sigui NOD_ID s'ha d'eliminar del map la variable?
        if(type == NOD_ID) VarsManager::freeId(value);
        std::printf("Destructor of %p\n", (void *)this);
        //delete child1; //MARC: b = !b recursiu
        child1 = NULL;
        //delete child2;
        child1 = NULL;
        //delete child3;
        child1 = NULL;
    }

    void print(int level = 0) const {
        std::cout << "-----------------------" << std::endl;
        for (int i = 0; i < level; ++i) std::cout << "\t";
        std::printf("Address %p\n", (void *)this);
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
        for (int i = 0; i < level; ++i) std::cout << "\t";
        std::cout << "Value: " << value << std::endl;
        if (child1 != NULL) child1->print(level + 1);
        if (child2 != NULL) child2->print(level + 1);
        if (child3 != NULL) child3->print(level + 1);
        std::cout << "-----------------------" << std::endl;
    }

    //Empty default constructor
    BoolFunc() {}

    //Converting constructors
    BoolFunc(int i) {
        assert(i == TRUE || i == FALSE || i == UNDEF);
        type = NOD_CONST;
        value = i;
    }

    BoolFunc(const std::string & name) {
        type = NOD_ID;
        //Comprovar si existeix en el map.
        bool exists = name_to_index.find(name) != name_to_index.end();
        //Si no existeix es crea
        if (!exists) {
            int lit = VarsManager::newId();
            name_to_index[name] = lit;
            value = lit;
            return;
        }
        //MARC: Aleshores hauria de tenir una estructura amb una referència a totes les formules creades
        //Si existeix es copia
        assert(false);
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

//Operators

BoolFunc operator!(BoolFunc const & f) {
    return BoolFunc::newNot(f);
}
BoolFunc operator~(BoolFunc const & f) {
    return BoolFunc::newNot(f);
}
BoolFunc operator & (BoolFunc const & a, BoolFunc const & b) {
    return BoolFunc::newAnd(a, b);
}
BoolFunc operator * (BoolFunc const & a, BoolFunc const & b) {
    return BoolFunc::newAnd(a, b);
}
BoolFunc operator | (BoolFunc const & a, BoolFunc const & b) {
    return BoolFunc::newOr(a, b);
}
BoolFunc operator + (BoolFunc const & a, BoolFunc const & b) {
    return BoolFunc::newOr(a, b);
}
BoolFunc operator ^ (BoolFunc const & a, BoolFunc const & b) {
    return BoolFunc::newXor(a, b);
}

BoolFunc operator += (const BoolFunc & lhs, const BoolFunc & rhs) {
    return BoolFunc::newOr(lhs, rhs);
}

BoolFunc operator *= (const BoolFunc & lhs, const BoolFunc & rhs) {
    return BoolFunc::newAnd(lhs, rhs);
}

BoolFunc operator ^= (const BoolFunc & lhs, const BoolFunc & rhs) {
    return BoolFunc::newXor(lhs, rhs);
}

std::map < std::string, int > BoolFunc::name_to_index = {};

#endif // BOOLFUNC_H
