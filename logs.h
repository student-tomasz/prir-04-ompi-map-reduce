#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "comm.h"

#define WORD_DELIMITERS " ,.!?\""

int read_lines_from_log(const char *log_path, char ***log_lines);
void add_line_to_log_lines(char* line, char ***log_lines, int *log_lines_len);
void digest_lines(char **lines, int lines_len, char ***words, int **words_count, int *words_len);
int word_is_present(char *word, char **words, int words_len);
void inc_word_count(char *word, char **words, int *words_count, int words_len);
void add_word_to_words(char *word, char ***words, int **words_count, int *words_len);
