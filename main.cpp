#include "BoolFunc.h"
#include <iostream>
#include <string>

void print(std::string s){
        std::cout << s << std::endl;
}

int main() {

    BoolFunc b = FALSE;
    BoolFunc c = TRUE;

    BoolFunc z = std::string("a");

    BoolFunc d = b + c;
    d.print();
}
