#include "jobs.h"

void divide_jobs(char **log_lines, int log_lines_len, int procs_num, char ****proc_lines) /* wskaznik na tablice tablicy stringow */
{
    int i, j, line_id;

    int jobs_num = procs_num - 1;

    int lines_per_job = round((double)log_lines_len / jobs_num);
    fprintf(stderr, "%d\n", lines_per_job);

    *proc_lines = malloc(sizeof(**proc_lines) * jobs_num);

    for (i = 0; i < jobs_num-1; i++) {
        (*proc_lines)[i] = malloc(sizeof(***proc_lines)*lines_per_job);
    }
    int lines_for_last_job = log_lines_len - (jobs_num-1) * lines_per_job;
    (*proc_lines)[jobs_num-1] = malloc(sizeof(***proc_lines)*lines_for_last_job);

    for (i = 0; i < jobs_num-1; i++) {
        for (j = 0; j < lines_per_job; j++) {
            line_id = i*lines_per_job + j;
            (*proc_lines)[i][j] = log_lines[line_id];
            fprintf(stderr, "MSTR przydziela SLV%d przydziela linie %d\n", i, line_id);
        }
    }
    i = jobs_num-1;
    for (j = 0; j < lines_for_last_job; j++) {
        line_id = i*lines_per_job+j;
        (*proc_lines)[i][j] = log_lines[line_id];
        fprintf(stderr, "MSTR przydziela SLV%d przydziela linie %d\n", i, line_id);
    }
}
