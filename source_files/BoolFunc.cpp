#include "BoolFunc.h"
/////////////////////////////////////////////CONSTRUCTORS///////////////////////
//Empty default constructor
BoolFunc::BoolFunc() {}

//Converting constructors

BoolFunc::BoolFunc(const std::string & name) {
    type = NOD_ID;
    value = VarsManager::getInstance()->newId(name);
}

BoolFunc::BoolFunc(NodeType param_type, Formula const & param_child): type(param_type), value(UNDEF) {
    assert(param_type == NOD_NOT);
    child1 = param_child;
}

BoolFunc::BoolFunc(NodeType param_type, Formula const & left, Formula const & right): type(param_type), value(UNDEF) {
    assert(param_type == NOD_AND || param_type == NOD_OR || param_type == NOD_XOR);
    child1 = left;
    child2 = right;
}
BoolFunc::BoolFunc(NodeType param_type, Formula const & left, Formula const & right, int param_value):
    type(param_type), value(param_value) {
        child1 = left;
        child2 = right;
    }

BoolFunc::~BoolFunc() {
    //QUESTION: En cas que sigui NOD_ID s'ha d'eliminar del map la variable?
    // potser no perque potser algu tambe l'esta fent servir ...
    if(type == NOD_ID) VarsManager::getInstance()->freeId(value);
    //delete child1; //BUG: b = !b recursiu
    child1 = NULL;
    //delete child2;
    child2 = NULL;
}

//////////////////////////////////GETTERS AND SETTERS///////////////////////////
NodeType BoolFunc::getType() const {return type;}
int BoolFunc::getValue() const {return value;}
const Formula BoolFunc::getChild1() const {return child1;}
const Formula BoolFunc::getChild2() const {return child2;}
void BoolFunc::setType(NodeType t){type = t;}
void BoolFunc::setValue(int v){value = v;}
void BoolFunc::setChild1(Formula const & c){child1 = c;}
void BoolFunc::setChild2(Formula const & c){child2 = c;}

/////////////////////////////////////////////NODE CONSTRUCTORS//////////////////

Formula BoolFunc::newNot(Formula const & f) {
    return std::make_shared<BoolFunc>(NOD_NOT,f);
}

Formula BoolFunc::newAnd(Formula
    const & a, Formula
    const & b) {
    return std::make_shared<BoolFunc>(NOD_AND,a,b);
}

Formula BoolFunc::newOr(Formula
    const & a, Formula
    const & b) {
    return std::make_shared<BoolFunc>(NOD_OR,a,b);
}
Formula BoolFunc::newXor(Formula
    const & a, Formula
    const & b) {
    return std::make_shared<BoolFunc>(NOD_XOR,a,b);
}

Formula BoolFunc::newLit(std::string var_name) {
    return std::make_shared<BoolFunc>(var_name);
}

//////////////////////////////OTHER FUNCTIONS///////////////////////////////////
void BoolFunc::print(int level) const {
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

// BoolFunc & BoolFunc::operator = (const BoolFunc & param){
//   std::cout << "operator = " << std::endl;
//   param.print();
//   if (this == &param) {
//         std::cout << "Les adreces son iguals" << std::endl;
//         return *this;
//   }
//   else{
//       std::cout << "Les adreces son diferents" << std::endl;
//       type = param.type;
//       value = param.value;
//       child1 = param.child1;
//       child2 = param.child2;
//       child3 = param.child3;
//   }
//   BoolFunc *t = new BoolFunc(param.type, *param.child1);
//   std::cout << "pene" << std::endl;
//   t->print();
//   return *t;
// }

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

// Formula operator = (Formula & f){
//     std::cout<<"copy constructor called\n";
//     return std::make_shared<BoolFunc>(f->getType(),f->getChild1(),f->getChild2(),f->getValue());
// }
//BUG: Els operadors tipus += no funcionen bé
Formula operator += (const Formula & lhs, const Formula & rhs) {
    Formula old_lhs = std::make_shared<BoolFunc>(lhs->getType(),lhs->getChild1(),lhs->getChild2(),lhs->getValue());

    lhs->setType(NOD_OR);
    lhs->setChild2(rhs);
    lhs->setChild1(old_lhs);
    lhs->setValue(UNDEF);
    return lhs;
}

Formula operator *= (const Formula & lhs, const Formula & rhs) {
    Formula old_lhs = std::make_shared<BoolFunc>(lhs->getType(),lhs->getChild1(),lhs->getChild2(),lhs->getValue());

    lhs->setType(NOD_AND);
    lhs->setChild2(rhs);
    lhs->setChild1(old_lhs);
    lhs->setValue(UNDEF);
    return lhs;
}

Formula operator ^= (const Formula & lhs, const Formula & rhs) {
    Formula old_lhs = std::make_shared<BoolFunc>(lhs->getType(),lhs->getChild1(),lhs->getChild2(),lhs->getValue());

    lhs->setType(NOD_XOR);
    lhs->setChild2(rhs);
    lhs->setChild1(old_lhs);
    lhs->setValue(UNDEF);
    return lhs;
}
