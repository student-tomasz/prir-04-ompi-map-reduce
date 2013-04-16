#include "jobs.h"

void divide_jobs(char **log_lines, int log_lines_len, int procs_num, char ****procs_lines, int **procs_lines_lens) /* wskaznik na tablice tablicy stringow */
{
    int i, j, line_id;

    int lines_per_proc = round((double)log_lines_len / (procs_num-1));

    *procs_lines = malloc(sizeof(**procs_lines) * procs_num);
    *procs_lines_lens = malloc(sizeof(**procs_lines_lens) * procs_num);

    for (i = 1; i < procs_num-1; i++) {
        (*procs_lines)[i] = malloc(sizeof(***procs_lines)*lines_per_proc);
        (*procs_lines_lens)[i] = lines_per_proc;
    }
    int lines_for_last_proc = log_lines_len - (procs_num-2) * lines_per_proc;
    (*procs_lines)[procs_num-1] = malloc(sizeof(***procs_lines)*lines_for_last_proc);
    (*procs_lines_lens)[procs_num-1] = lines_for_last_proc;

    for (i = 1; i < procs_num-1; i++) {
        for (j = 0; j < lines_per_proc; j++) {
            line_id = (i-1)*lines_per_proc + j;
            (*procs_lines)[i][j] = log_lines[line_id];
            fprintf(stderr, "MSTR przydziela SLV%d przydziela linie %d\n", i, line_id);
        }
    }
    i = procs_num-1;
    for (j = 0; j < lines_for_last_proc; j++) {
        line_id = (i-1)*lines_per_proc+j;
        (*procs_lines)[i][j] = log_lines[line_id];
        fprintf(stderr, "MSTR przydziela SLV%d przydziela linie %d\n", i, line_id);
    }
}

void send_lines_len_to_procs(const int procs_num, int *procs_lines_lens)
{
    int proc_id;
    int lines_for_proc;

    for (proc_id = 1; proc_id < procs_num; proc_id++) {
        lines_for_proc = procs_lines_lens[proc_id];
        MPI_Send(&lines_for_proc, 1, MPI_INT, proc_id, LINE_LEN_MSG, MPI_COMM_WORLD);
    }
}

void receive_lines_len(int *lines_len)
{
    MPI_Status status;
    MPI_Recv(lines_len, 1, MPI_INT, MSTR_ID, LINE_LEN_MSG, MPI_COMM_WORLD, &status);
}

void send_lines_to_procs(const int procs_num, char ***procs_lines, int *procs_lines_lens)
{
    int proc_id, i;
    int lines_for_proc;

    for (proc_id = 1; proc_id < procs_num; proc_id++) {
        lines_for_proc = procs_lines_lens[proc_id];
        for (i = 0; i < lines_for_proc; i++) {
            MPI_Send(procs_lines[proc_id][i], LINE_LEN, MPI_CHAR, proc_id, LINE_MSG, MPI_COMM_WORLD);
            fprintf(stderr, "MSTR wyslal do SLV%d linie \"%s\"\n", proc_id, procs_lines[proc_id][i]);
        }
    }
}

void receive_lines(char ***lines, int lines_len)
{
    int i;
    MPI_Status status;

    *lines = malloc(sizeof(**lines) * lines_len);
    for (i = 0; i < lines_len; i++) {
        (*lines)[i] = malloc(sizeof(***lines) * LINE_LEN);
    }

    for (i = 0; i < lines_len; i++) {
        MPI_Recv((*lines)[i], LINE_LEN, MPI_CHAR, MSTR_ID, LINE_MSG, MPI_COMM_WORLD, &status);
    }
}
