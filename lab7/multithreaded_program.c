#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <math.h>

typedef struct {
    int *data;
    int size;
    int capacity;
} array;


typedef struct {
    int lower_bound;
    int upper_bound;
    int thread_id;
    pthread_mutex_t file_mutex;
    pthread_mutex_t array_mutex;
    array *prime_numbers;
    FILE* file;
} thread_args;




int parse_args(int argc, char *argv[], int* thread_number, int* lower_bound, int* upper_bound);
void* thread_function(void* arg);
int number_of_primes_in_interval(int lower_bound, int upper_bound);


int sort_func(const void *p1, const void *p2) {
    return (*(int *)p2 - *(int *)p1);
}

int main(int argc, char *argv[])
{
    int lower_bound, upper_bound, thread_number;
    
    if (parse_args(argc, argv, &thread_number, &lower_bound, &upper_bound) != 0)
    {
        return -1;
    }

    int number_of_primes = number_of_primes_in_interval(lower_bound, upper_bound) * 3 / 2;

    int *prime_numbers = (int *)malloc(number_of_primes * sizeof(int));
    array prime_numbers_array = {prime_numbers, 0, number_of_primes};

    int step = (upper_bound - lower_bound) / thread_number;

    pthread_t *threads = (pthread_t *)malloc(thread_number * sizeof(pthread_t));

    pthread_mutex_t file_mutex;
    pthread_mutex_init(&file_mutex, NULL);

    pthread_mutex_t array_mutex;
    pthread_mutex_init(&array_mutex, NULL);

    FILE* output_file = fopen("output.txt", "a");

    for (int i = 0; i < thread_number; i++)
    {
        thread_args *args = (thread_args *)malloc(sizeof(thread_args));
        args->lower_bound = lower_bound + i * step;
        args->upper_bound = lower_bound + (i + 1) * step;
        args->thread_id = i + 1;
        args->file_mutex = file_mutex;
        args->array_mutex = array_mutex;
        args->file = output_file;
        args->prime_numbers = &prime_numbers_array;

        pthread_create(&threads[i], NULL, thread_function, (void *)args);
        printf("Thread %d created\n", i + 1);
    }
    
    for (int i = 0; i < thread_number; i++)
    {
        int *result;
        pthread_join(threads[i], (void**)&result);
        printf("Thread %d found %d prime numbers\n", i + 1, *result);
        free(result);
    }


    qsort(prime_numbers, prime_numbers_array.size, sizeof(int), sort_func);
    for (int i = 0; i < prime_numbers_array.size; i++)
    {
        printf("%d ", prime_numbers[i]);
    }

    printf("\n");

    fclose(output_file);
    pthread_mutex_destroy(&file_mutex);
    pthread_mutex_destroy(&array_mutex);
    free(threads);
    free(prime_numbers);

    return 0;
}


int number_of_primes_in_interval(int lower_bound, int upper_bound)
{
    int prime_numbers_less_than_upper_bound = ceil(upper_bound / log((double) upper_bound));
    int prime_numbers_less_than_lower_bound = 0;
    if (lower_bound > 1) {
        prime_numbers_less_than_lower_bound = ceil(lower_bound / log((double) lower_bound));
    }

    return prime_numbers_less_than_upper_bound - prime_numbers_less_than_lower_bound;
}


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

void* thread_function(void* arg)
{
    thread_args *args = (thread_args *)arg;
    int *counter = (int*)malloc(sizeof(int));
    for (int i = args->lower_bound; i < args->upper_bound; i++)
    {
        if (is_prime_number(i))
        {
            (*counter)++;
            pthread_mutex_lock(&args->file_mutex);
            fprintf(args->file, "Thread %d found number %d\n", args->thread_id, i);
            pthread_mutex_unlock(&args->file_mutex);

            pthread_mutex_lock(&args->array_mutex);
            if (args->prime_numbers->size < args->prime_numbers->capacity)
            {
                args->prime_numbers->data[args->prime_numbers->size++] = i;
            }
            pthread_mutex_unlock(&args->array_mutex);
        }
    }
    free(args);
    return (void*)counter;
}

int parse_args(int argc, char *argv[], int* thread_number, int* lower_bound, int* upper_bound)
{
    if (argc != 4)
    {
        printf("Usage: %s <thread_number> <lower_bound> <upper_bound>\n", argv[0]);
        return -1;
    }

    *thread_number = atoi(argv[1]);
    *lower_bound = atoi(argv[2]);
    *upper_bound = atoi(argv[3]);


    if (*thread_number <= 0)
    {
        printf("Error: thread_number must be greater than 0\n");
        return -1;
    }

    if (*lower_bound >= *upper_bound)
    {
        printf("Error: lower_bound must be less than upper_bound\n");
        return -1;
    }

    return 0;
}