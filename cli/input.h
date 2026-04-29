#ifndef CLI_INPUT_H
#define CLI_INPUT_H

#include <nac.h>

#include <stdbool.h>
#include <stddef.h>

int poll_input(int fd, char *buffer, int max_size);
bool parse_move(char *buffer, size_t *target, NAC_DIMENSIONS dimensions);
char parse_yn(char *buffer);

#endif
