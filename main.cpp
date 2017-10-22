#include "BoolFunc.h"
#include <iostream>
#include <string>

void print(std::string s){
        std::cout << s << std::endl;
}

int main() {

    BoolFunc b = FALSE;
    print("cout de b = FALSE");
    b.print();
    //BoolFunc c = b;
    //BoolFunc d = c;
    print("Assignació b = !b");
    b = !b; //<--Destructura infinita recursiva
    print("print de b = b!");
    b.print();
    //b.print();
    //print("hola");
    //BoolFunc a = !b;
    //a.print();
}
