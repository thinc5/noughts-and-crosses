#include "input.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <nac.h>

int poll_input(int fd, char *buffer, int max_size) {
    memset(buffer, '\0', max_size);
    
    size_t position = 0;
    char last_read = '\0';
    while ((last_read = getchar()) != EOF)
    {
        switch (last_read) {
            case '\b':
                if (position > 1) {
                    buffer[position] = '\0';
                    position--;
                }
                break;
            case '\n':
                if (position > 0) {
                    return position;
                }
                break;
            default:
                if (position + 1 < max_size) {
                    buffer[position] = last_read;
                    position++;
                }
                break;
        }
    }
    return false;
}

bool parse_move(char *buffer, size_t *target) {
    char *x_str = strtok(buffer, ",");
    char *y_str = strtok(NULL, ",");
    if (x_str == NULL || y_str == NULL){
        return false;
    }

    int x = atoi(x_str);
    int y = atoi(y_str);
    if (x < 1 || x > 3 || y < 1 || y > 3) {
        return false;
    }

    *target = (size_t) (x - 1) + ((y - 1) * NAC_DIMENSIONS);

    return true;
}

char parse_yn(char *buffer) {
    if (strlen(buffer) != 1) {
        return '\0';
    }

    char ans = buffer[0];
    if (ans == 'y' || ans == 'Y') {
        return 'y';
    }

    if (ans == 'n' || ans == 'N') {
        return 'n';
    }

    return '\0';
}
