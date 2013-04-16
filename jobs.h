#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <mpi.h>
#include "comm.h"

void divide_jobs(char **log_lines, int log_lines_len, int procs_num, char ****procs_lines, int **procs_lines_lens);
void send_lines_len_to_procs(const int procs_num, int *procs_lines_lens);
void send_lines_to_procs(const int procs_num, char ***procs_lines, int *procs_lines_lens);
void receive_lines_len(int *lines_len);
void receive_lines(char ***lines, int lines_len);
