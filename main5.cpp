#include <iostream>
#include <string>
#include <vector>
#include <unistd.h>
#include <sys/wait.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <pthread.h>
using namespace std;

void calc(int & j){
    for (size_t i = 0; i < 9999; i++) {
        j++;
    }
    sleep(5);
    std::cout << "j" << j << '\n';

}

int main() {

    int j =  0;

    pid_t pid = fork();

    if (pid == 0)
    {
        // child process
        calc(j);
        std::cout << "chil J "<<j << '\n';

    }
    else if (pid > 0)
    {
        // parent process
        int status = 0;
        wait(status);
        std::cout << "parent J "<< j << '\n';
    }
    else
    {
        // fork failed
        std::cout << "fork failed!" << '\n';
        return 1;
    }
}
