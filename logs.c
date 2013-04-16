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

void digest_lines(char **lines, int lines_len, char ***words, int **words_count, int *words_len)
{
    int i;
    char *line, *word;

    *words = NULL;
    *words_count = NULL;
    *words_len = 0;

    for (i = 0; i < lines_len; i++) {
        line = lines[i];
        word = strtok(line, WORD_DELIMITERS);
        while (word != NULL) {
            // fprintf(stderr, "token:%s\n",word);
            if (word_is_present(word, *words, *words_len)) {
                inc_word_count(word, *words, *words_count, *words_len);
            }
            else {
                add_word_to_words(word, words, words_count, words_len);
            }
            word = strtok(NULL, WORD_DELIMITERS);
        }
    }
}

int word_is_present(char *word, char **words, int words_len)
{
    int i;
    for (i = 0; i < words_len; i++) {
        if (strcmp(word, words[i]) == 0) {
            return 1;
        }
    }
    return 0;
}

void inc_word_count(char *word, char **words, int *words_count, int words_len)
{
    int i;
    for (i = 0; i < words_len; i++) {
        if (strcmp(word, words[i]) == 0) {
            words_count[i] += 1;
            break;
        }
    }
}

void add_word_to_words(char *word, char ***words, int **words_count, int *words_len)
{
    *words = realloc(*words, sizeof(**words) * ((*words_len)+1));
    if (*words == NULL) {
        fprintf(stderr, "Moar memory for words, dude!\n");
        exit(EXIT_FAILURE);
    }
    *words_count = realloc(*words_count, sizeof(**words_count) * ((*words_len)+1));
    if (*words_count == NULL) {
        fprintf(stderr, "Moar memory for words_count, dude!\n");
        exit(EXIT_FAILURE);
    }
    (*words)[*words_len] = malloc(sizeof(***words) * WORD_LEN);
    strncpy((*words)[*words_len], word, WORD_LEN);
    (*words_count)[*words_len] = 1;
    (*words_len)++;
}
