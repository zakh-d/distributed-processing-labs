#ifndef WORKER_H
#define WORKER_H
#define THREADS_IN_SUBPROCESS 4

typedef struct {
    int lower_bound;
    int upper_bound;
    int communication_pipe_write;
} thread_args;

int start_task(int lower_bound, int upper_bound, int number_of_subprocesses);


#endif