#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "comm.h"

int read_lines_from_log(const char *log_path, char ***log_lines);
void add_line_to_log_lines(char* line, char ***log_lines, int *log_lines_len);
