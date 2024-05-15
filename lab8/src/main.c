#include <fcntl.h>
#include <sys/stat.h>
#include <stdio.h>
#include <unistd.h>

#include "utils.h"
#include "worker.h"

#define FIFO_FILE "fifo_in"



int main() {
    
    puts("Creating a new FIFO file...");
    if (mkfifo(FIFO_FILE, 0666) != 0) {
        perror("mkfifo failed");
        puts("Cannot create fifo_in file\nMaybe its already created");

    }

    puts("Opening the FIFO file...");

    int fifo_in;

    if ((fifo_in = open("fifo_in", O_RDONLY)) < 0) {
        perror("Cannot open fifo_in file");
        return 1;
    }

    int running = 1;
    char command;

    while (running) {
        
        read(fifo_in, &command, sizeof(char));

        switch (command) {
            case 'q':
                puts("Quitting...");
                running = 0;
                break;
            case 'h':
                puts("Help: q - quit, h - help");
                break;
            case 't':
                puts("Awaiting for search range...");

                /* skiping to the new line character */
                while (command != '\n') {
                    read(fifo_in, &command, sizeof(char));
                } 

                int lower_bound = get_number_from_fifo(fifo_in);
                printf("Lower bound set to  %d\n", lower_bound);
                int upper_bound = get_number_from_fifo(fifo_in);
                printf("Upper bound set to  %d\n", upper_bound);

                if (lower_bound > upper_bound) {
                    puts("Invalid range");
                    break;
                }
                printf("Searching for primes in range: %d - %d\n", lower_bound, upper_bound);

                puts("Awaiting for the number of subprocesses...");
                int number_of_subprocesses = get_number_from_fifo(fifo_in);
                if (number_of_subprocesses < 1) {
                    puts("Invalid number of subprocesses");
                    break;
                }
                printf("Number of subprocesses set to %d\n", number_of_subprocesses);

                start_task(lower_bound, upper_bound, number_of_subprocesses);

                break;
            case '\n':
                break;
            default:
                puts("Unknown command");
        }
    }

    unlink(FIFO_FILE);


    return 0;
}