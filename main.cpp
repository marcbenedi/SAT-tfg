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

    Formula i = (p*q) + !(!r*q);

    //Cnf result = CnfConverter::tseitin(i);
    //result.print();

    Formula r2 = BoolFunc::newLit("d");
    Formula j = !(p*(q+r))+!r2;

    Cnf result2 = CnfConverter::tseitin(j);
    result2.print();



}
