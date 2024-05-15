#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

#include "worker.h"

int is_prime_number(int n) {
    if (n <= 1)
    {
        return 0;
    }

    for (int i = 2; i * i <= n; i++)
    {
        if (n % i == 0)
        {
            return 0;
        }
    }

    return 1;
}

void *find_primes_thread(void *args) {
    thread_args *t_args = (thread_args *) args;

    for (int i = t_args->lower_bound; i < t_args->upper_bound; i++) {
        if (is_prime_number(i)) {
            write(t_args->communication_pipe_write, &i, sizeof(int));
        }
    }

    free(t_args);

    return NULL;
}

void find_primes(int lower_bound, int upper_bound, int communication_pipe[2]) {
    pthread_t threads[THREADS_IN_SUBPROCESS];

    int batch_size = (upper_bound - lower_bound) / THREADS_IN_SUBPROCESS;
    
    for (int i = 0; i < THREADS_IN_SUBPROCESS; i++) {
        thread_args *args = malloc(sizeof(thread_args));
        args->lower_bound = lower_bound + i * batch_size;
        if (i == THREADS_IN_SUBPROCESS - 1) {
            args->upper_bound = upper_bound;
        } else {
            args->upper_bound = lower_bound + (i + 1) * batch_size - 1;
        }
        args->communication_pipe_write = communication_pipe[1];

        if (pthread_create(&threads[i], NULL, find_primes_thread, (void *) args) != 0) {
            perror("pthread_create failed");
            free(args);
        }
    }
    
    for (int i = 0; i < THREADS_IN_SUBPROCESS; i++) {
        pthread_join(threads[i], NULL);
    }
    int end = -1;
    write(communication_pipe[1], &end, sizeof(int));
}


int invoke_n_subprocesses(int n, int lower_bound, int upper_bound, int* communication_pipes) {

    int batch_size = (upper_bound - lower_bound) / n;

    for (int i = 0; i < n; i++) {
        int pid = fork();
        if (pid == 0) {
            // child process

            close(communication_pipes[2*i]);
            if (i == n - 1) {
                find_primes(lower_bound + i*batch_size, upper_bound, &communication_pipes[2 * i]);
                
            } else {
                find_primes(lower_bound + i*batch_size, lower_bound + (i+1) * batch_size - 1, &communication_pipes[2*i]);
            }
            close(communication_pipes[2 * i + 1]);
            exit(0);
        }
        if (pid == -1) {
            perror("fork failed");
            return 1;
        }
    }

    return 0;
}

int sort_func(const void *p1, const void *p2) {
    return (*(int *)p1 - *(int *)p2);
}


int start_task(int lower_bound, int upper_bound, int number_of_subprocesses) {
    // int communication_pipe[2];
    int *communication_pipes = (int*) malloc(sizeof(int) * 2 * number_of_subprocesses);

    for (int i = 0; i < number_of_subprocesses; i++) {
        if (pipe(&communication_pipes[2*i]) == -1) {
            perror("pipe failed");
            free(communication_pipes);
            return 1;
        }
    }
    
    if (invoke_n_subprocesses(number_of_subprocesses, lower_bound, upper_bound, communication_pipes) != 0) {
        return 1;
    }

    puts("Waiting for subprocesses to finish...");
    int* prime_number = (int*)calloc(upper_bound - lower_bound, sizeof(int));
    int current = 0;
    int subprocesses_still_working = number_of_subprocesses;
    int *subprocess_working = (int*) malloc(number_of_subprocesses * sizeof(int));

    for (int i = 0; i < number_of_subprocesses; i++) {
        subprocess_working[i] = 1;
    }

    while (subprocesses_still_working > 0) {
        int number;
        for (int i = 0; i < number_of_subprocesses; i++) {
            if (subprocess_working[i] == 0) continue;
            read(communication_pipes[2*i], &number, sizeof(int));
            if (number == -1) {
                subprocesses_still_working--;
                subprocess_working[i] = 0;
                continue;
            }
            prime_number[current++] = number;
        }
        
        
    }

    for (int i = 0; i < number_of_subprocesses; i++) {
        close(communication_pipes[2*i]);
        close(communication_pipes[2*i + 1]);
    }
    qsort(prime_number, current, sizeof(int), sort_func);

    for (int i = 0; i < current; i++) {
        printf("%d\n", prime_number[i]);
    }

    free(prime_number);
    free(communication_pipes);

    return 0;
}
