#ifndef CLI_INPUT_H
#define CLI_INPUT_H

#include <stdbool.h>
#include <stddef.h>

bool poll_input(char **buffer);
bool parse_move(char *buffer, size_t *target);
char parse_yn(char *buffer);

#endif
