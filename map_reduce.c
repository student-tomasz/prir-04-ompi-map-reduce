#include "map_reduce.h"

int proc_is_master(const int proc_id)
{
    return proc_id == 0;
}

int main(int argc, char *argv[])
{
    int procs_num;
    int proc_id;

    char **log_lines,
         ***procs_lines;
    int *procs_lines_lens;

    int lines_len;
    char **lines;
    char **words;
    int *words_count;

    int log_lines_len;
    const char *log_path = argv[1];

    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &procs_num);
    MPI_Comm_rank(MPI_COMM_WORLD, &proc_id);

    if (proc_is_master(proc_id)) {
        log_lines_len = read_lines_from_log(log_path, &log_lines);
        divide_jobs(log_lines, log_lines_len, procs_num, &procs_lines, &procs_lines_lens);
        send_lines_len_to_procs(procs_num, procs_lines_lens);
        // send_lines_to_procs(procs_num, procs_lines);
    }
    else {
        receive_lines_len(&lines_len);
        fprintf(stdout, "SLV%d otrzymal %d linii\n", proc_id, lines_len);
        // receive_lines(&lines);
        // digest_lines(lines, &words, &words_count);
    }

    MPI_Finalize();
    return EXIT_SUCCESS;
}
