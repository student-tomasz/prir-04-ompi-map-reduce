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
    int words_len;
    char **words;
    int *words_count;

    int log_lines_len;
    const char *log_path = argv[1];

    int i;


    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &procs_num);
    MPI_Comm_rank(MPI_COMM_WORLD, &proc_id);

    if (proc_is_master(proc_id)) {
        log_lines_len = read_lines_from_log(log_path, &log_lines);
        divide_jobs(log_lines, log_lines_len, procs_num, &procs_lines, &procs_lines_lens);
        send_lines_len_to_procs(procs_num, procs_lines_lens);
        send_lines_to_procs(procs_num, procs_lines, procs_lines_lens);
    }
    else {
        receive_lines_len(&lines_len);
        receive_lines(&lines, lines_len);
        digest_lines(lines, lines_len, &words, &words_count, &words_len);
    }

    MPI_Finalize();
    return EXIT_SUCCESS;
}
