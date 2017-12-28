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

class SatSolver{
private:
    SatSolver();
public:
    static void solve(Cnf cnf){
        std::string input = cnf.picosat();
        std::string command = "picosat";
        std::system(command.c_str());
        std::system(cnf.picosat().c_str());
    }
    static std::string solve2(Cnf cnf){

        std::string cnfPicosat = cnf.picosat();

        int fd_pipe[2];
    	int control_pipe = pipe(fd_pipe);
    	if (control_pipe < 0)std::cerr << "Error pipe()" << std::endl;
    	//pipe_fd[0] = read
    	//pipe_fd[1] = write


        pid_t pID = fork();
        if (pID < 0){
            //error
            std::cerr << "Failed to fork" << std::endl;
            exit(1);
        }else if(pID == 0){
            //child
            close(fd_pipe[1]); //close unused
            //Volem que el nostre canal d'entrada sigui el de lectura de la pipe
			int control_dup2 = dup2(fd_pipe[0],STDIN_FILENO);
			if (control_dup2 < 0)std::cerr << "Error al dup2" << std::endl;
            //Volem que el nostre canal de sortido sigui el d'escriptura de la pipe
			// control_dup2 = dup2(fd_pipe[1],STDOUT_FILENO);
			// if (control_dup2 < 0)std::cerr << "Error al dup2" << std::endl;
            close(fd_pipe[0]);

            execlp("picosat","picosat",NULL);

            // Read a string using first pipe
            char concat_str[100];
            read(STDIN_FILENO, concat_str, 100);
            write(STDOUT_FILENO, concat_str, strlen(concat_str)+1);

            exit(0);
        }else {
            //parent
            close(fd_pipe[0]);

            //char input_str[100] = "p cnf 2 2 -1 2 0 -2 -1 0";

            write(fd_pipe[1], cnfPicosat.c_str(), cnfPicosat.length()+1);
            close(fd_pipe[1]);

            int status;
            waitpid(pID, &status, 0); // Wait for the child process to return.

            return "fake reslt";
        }
    }
};

#endif // SATSOLVER_H
