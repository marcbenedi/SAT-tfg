#ifndef SATSOLVER_H
#define SATSOLVER_H

#include <cstdlib>
#include <cstdio>
#include <iostream>
#include <memory>
#include <stdexcept>
#include <string>
#include <array>
#include <cerrno>
#include <cstring>
#include <sys/wait.h>

#include "Cnf.h"

class SatSolver{
private:
    SatSolver();
public:
    static void solve(Cnf cnf){
        //TODO: Fer traducció de variables per a que picosat funcioni
        std::string input = cnf.picosat();
        std::string command = "picosat";
        std::system(command.c_str());
        std::system(cnf.picosat().c_str());
    }
    static std::string solve2(Cnf cnf){

        std::string cnfPicosat = cnf.picosat();

        int fd_pipe[2];
        int fd_pipe2[2];
    	int control_pipe = pipe(fd_pipe);
    	if (control_pipe < 0)std::cerr << "Error pipe()" << std::endl;
        control_pipe = pipe(fd_pipe2);
    	if (control_pipe < 0)std::cerr << "Error pipe()" << std::endl;

        pid_t pID = fork();
        if (pID < 0){
            //error
            std::cerr << "Failed to fork" << std::endl;
            exit(1);
        }else if(pID == 0){
            //child
            close(fd_pipe[1]); //close unused
            close(fd_pipe2[0]);

			int control_dup2 = dup2(fd_pipe[0],STDIN_FILENO);
			if (control_dup2 < 0)std::cerr << "Error dup2()" << std::endl;
            close(fd_pipe[0]);

            control_dup2 = dup2(fd_pipe2[1],STDOUT_FILENO);
			if (control_dup2 < 0)std::cerr << "Error dup2()" << std::endl;
            close(fd_pipe2[1]);

            int control_execlp = execlp("picosat","picosat",NULL);
            if (control_execlp < 0)std::cerr << "Error execlp()" << std::endl;

            exit(0);
        }else {
            //parent
            close(fd_pipe[0]);
            close(fd_pipe2[1]);

            //char input_str[100] = "p cnf 2 2 -1 2 0 -2 -1 0";

            write(fd_pipe[1], cnfPicosat.c_str(), cnfPicosat.length()+1);
            close(fd_pipe[1]);

            int status;
            waitpid(pID, &status, 0); // Wait for the child process to return.
            //read child output

            //COMBAK: Buscar una mida adequada per aquest buffer
            char buffer[100] = {};
            read(fd_pipe2[0], buffer, sizeof(buffer));
            //write(STDOUT_FILENO, concat_str, strlen(concat_str)+1);

            close(fd_pipe2[0]);
            return buffer;
        }
    }
};

#endif // SATSOLVER_H
