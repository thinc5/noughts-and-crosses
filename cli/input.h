#ifndef CLI_INPUT_H
#define CLI_INPUT_H

#include <stdbool.h>
#include <stddef.h>

int poll_input(int fd, char *buffer, int max_size);
bool parse_move(char *buffer, size_t *target);
char parse_yn(char *buffer);

#endif
