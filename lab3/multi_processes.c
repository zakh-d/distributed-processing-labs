#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <unistd.h>
#include <pwd.h>


void run_multiple_processes(char* tasks[][8], int num_tasks) {

    int* pids = (int*) malloc(num_tasks * sizeof(int));
    
    for (int i = 0; i < num_tasks; i++) {
        
        int pid = fork();

        if (pid == 0) {
            // child process
            execvp(tasks[i][0], tasks[i]);
            break;
        } else {
            // parent process
            pids[i] = pid;
        }
    }

    if (num_tasks > 0 && pids[0]) {
        for (int i = 0; i < num_tasks; i++) {
            waitpid(pids[i], NULL, 0);
        }
    }

    free(pids);
}


int main() {
    char *homedir = getpwuid(getuid())->pw_dir;
    char* tasks[][8] = {
        {"wget", "https://ftp.psnc.pl/linux/linuxmint/iso/stable/21.3/linuxmint-21.3-cinnamon-64bit.iso", NULL},
        {"sleep", "5", NULL},
        {"find", homedir, "-type", "d", "-name", "lab3",  NULL},
        {"ping", "-c", "10", "pg.edu.pl", NULL},
    };

    run_multiple_processes(tasks, 4);
    
    return 0;
}