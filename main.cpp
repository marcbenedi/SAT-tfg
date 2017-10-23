#include "BoolFunc.h"
#include <iostream>
#include <string>
#include "Clause.h"

void print(std::string s){
        std::cout << s << std::endl;
}

int main() {

    Clause c = Clause(5,1,2,3,4,5);
    c.print();

}
