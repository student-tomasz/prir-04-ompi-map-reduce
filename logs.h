#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define LINE_MAX_LEN 2048

int read_lines_from_log(const char *log_path, char ***log_lines);
void add_line_to_log_lines(char* line, char ***log_lines, int *log_lines_len);
