#include "logs.h"

int read_lines_from_log(const char *log_path, char ***log_lines)
{
    *log_lines = malloc(sizeof(**log_lines)); /* cokolwiek allokuję, ponieważ potem za każdym razem i tak wywoływany jest na tym realloc */
    int log_lines_len = 0;

    FILE* log_file = fopen(log_path, "r");
    if (log_file == NULL) {
        fprintf(stderr, "Plik %s nie do odczytu.\n", log_path);
        exit(EXIT_FAILURE);
    }

    char *line = (char *)malloc(sizeof(*line) * LINE_LEN);
    if (line == NULL) {
        fprintf(stderr, "Moar memory plox.\n");
        exit(EXIT_FAILURE);
    }

    int line_pos = 0;
    char ch;
    while ((ch = getc(log_file)) != EOF) {
        if (ch == '\n' || line_pos == LINE_LEN-1) {
            line[line_pos] = '\0';
            add_line_to_log_lines(line, log_lines, &log_lines_len);

            line_pos = 0;
            continue;
        }

        line[line_pos] = ch;
        line_pos++;
    }

    free(line);
    return log_lines_len;
}

void add_line_to_log_lines(char* line, char ***log_lines, int *log_lines_len)
{
    *log_lines = realloc(*log_lines, sizeof(**log_lines)*((*log_lines_len)+1));
    if (*log_lines == NULL) {
        fprintf(stderr, "Moar memory, dude!\n");
        exit(EXIT_FAILURE);
    }
    char **log_line = *log_lines + *log_lines_len;

    *log_line = malloc(sizeof(***log_lines)*LINE_LEN);
    strncpy(*log_line, line, LINE_LEN);
    (*log_lines_len)++;
}
