#include <iostream>
#include <string>
#include "CnfConverter.h"

void print(std::string s){
        std::cout << s << std::endl;
}

int main() {

    BoolFunc p = std::string("p");
    //p.print();
    BoolFunc q = std::string("q");
    //q.print();

    p *= q;
}
