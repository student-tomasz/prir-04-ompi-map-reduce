#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <mpi.h>
#include "logs.h"
#include "jobs.h"

void divide_jobs(char **log_lines, int log_lines_len, int procs_num, char ****proc_lines);
