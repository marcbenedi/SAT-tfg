#include <iostream>
#include <string>
#include "CnfConverter.h"

void print(std::string s){
        std::cout << s << std::endl;
}

int main() {

    Formula p = BoolFunc::newLit("a");
    Formula q = BoolFunc::newLit("b");
    Formula r = BoolFunc::newLit("c");

    Formula i = (p*q) + !(!p*(q+!r));
    //i->print();
    Cnf result = CnfConverter::tseitin(i);
    result.printPicosatFormat();

}
