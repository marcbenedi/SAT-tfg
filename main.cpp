#include <iostream>
#include <string>
#include "CnfConverter.h"

void print(std::string s){
        std::cout << s << std::endl;
}

int main() {

    BoolFunc p = std::string("p");
    p.print();
    BoolFunc q = std::string("q");
    q.print();
    BoolFunc r = std::string("r");
    r.print();

    print("JAULALAMIDI");

    BoolFunc f = p + q * r;
    print("IEEEEEEEEEEEEEPA");
    f.print();

    //Cnf cnf = CnfConverter::tseitin(f);
    //cnf.print();


}
