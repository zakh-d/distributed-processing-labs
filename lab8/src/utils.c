#include <unistd.h>

int get_number_from_fifo(int fifo_in) {
    char digit;
    int number = 0;
    while (1) {
        read(fifo_in, &digit, sizeof(char));
        if (digit == '\n') {
            break;
        }
        if (digit < '0' || digit > '9') {
            continue;
        }
        number = number * 10 + (digit - '0');
    }
    return number;
}