#include <iostream>
// #include <string>
// #include <stdio.h>
#include <unistd.h> //sleep
// #include <stdlib.h>
#include <vector>
#include <pthread.h> //pthread
#include <signal.h>
#include <time.h>

struct thread_data {
   std::vector<int> v;
   bool sat;
   bool finished = false;
};

void timeout(int signum)
{
    printf("Hello from handler\n");
    pthread_exit(NULL);
}

void *calc(void * p){

    signal(SIGTERM,timeout);

    struct thread_data *my_data;
    my_data = (struct thread_data *) p;
    my_data -> sat = true;
    for (size_t i = 0; i < 10; i++) {
        (my_data->v).push_back(i);
    }
    std::cout << "before sleep" << '\n';
    sleep(15);
    std::cout << "after sleep" << '\n';
    my_data->finished = true;
    pthread_exit(NULL);
}

int main() {
    pthread_t first;
    struct thread_data td;
    int c = pthread_create(&first, NULL, calc, &td);
    std::cout << "c "<<c << '\n';


    time_t seconds;
    seconds = time (NULL);
    int timeout = 20+seconds;
    while (!td.finished) {
        seconds = time (NULL);
        if(timeout == seconds ){
            int k = pthread_kill(first, SIGTERM);
            std::cout << "k " << k << '\n';
            td.finished = true;
        }
        sleep(1);
    }

    std::cout << "SAT " <<td.sat << '\n';
    for (size_t i = 0; i < td.v.size();i++) {
        std::cout << td.v[i] << '\n';
    }


}
