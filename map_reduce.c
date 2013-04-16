#include "map_reduce.h"

int proc_is_master(const int proc_id)
{
    return proc_id == 0;
}

int main(int argc, char *argv[])
{
    int procs_num;
    int proc_id;
    int get_rngs_msg_tag = 112;
    int integrate_msg_tag = 111;
    MPI_Status status;

    char **log_lines,
         ***proc_lines;

    int log_lines_len;
    const char *log_path = argv[1];

    int i;

    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &procs_num);
    MPI_Comm_rank(MPI_COMM_WORLD, &proc_id);

    if (proc_is_master(proc_id)) {
        log_lines_len = read_lines_from_log(log_path, &log_lines);
        divide_jobs(log_lines, log_lines_len, procs_num, &proc_lines);
    }

    MPI_Finalize();
    return EXIT_SUCCESS;
}
