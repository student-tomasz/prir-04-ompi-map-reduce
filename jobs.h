#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <mpi.h>

#define LINE_LEN_MSG 110
#define LINE_MSG 111

void divide_jobs(char **log_lines, int log_lines_len, int procs_num, char ****procs_lines, int **procs_lines_lens);
void send_lines_len_to_procs(const int procs_num, int *procs_lines_lens);
void send_lines_to_procs(const int procs_num, char ***procs_lines);
void receive_lines_len(int *lines_len);
