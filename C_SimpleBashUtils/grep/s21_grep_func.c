#include "s21_grep_func.h"

#include <getopt.h>
#include <regex.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "s21_grep.h"

// === FUNC DECLARATION ===

void initFlags(FLAGS *flags);
int parseFlags(int argc, char **argv, FLAGS *flags);
void add_pattern(FLAGS *flags, const char *pattern);
void procces_file(const char *filename, FLAGS flags, int multi_file);
void process_line(const char *line, const char *filename, FLAGS flags,
                  int multi_file, int line_num, int *match_count,
                  regex_t *regex);
void free_regex(regex_t *regex_list, FLAGS flags);

// === FUNC REALIZATION ===

void initFlags(FLAGS *flags) {
  flags->e = false;
  flags->i = false;
  flags->v = false;
  flags->c = false;
  flags->l = false;
  flags->n = false;

  flags->pattern_list = NULL;
  flags->pattern_amount = 0;
}

int parseFlags(int argc, char **argv, FLAGS *flags) {
  int error = OK;

  int option;
  const char *allowedSymbs = "e:ivcln";

  while (!error) {
    option = getopt(argc, argv, allowedSymbs);
    if (option == -1) break;

    if (option == 'e') {
      flags->e = true;
      add_pattern(flags, optarg);
    } else if (option == 'i')
      flags->i = true;
    else if (option == 'v')
      flags->v = true;
    else if (option == 'c')
      flags->c = true;
    else if (option == 'l')
      flags->l = true;
    else if (option == 'n')
      flags->n = true;
    else
      error = INVALID_OPTION;
  }

  return error;
}

void patterns_check(FLAGS *flags, int argc, char **argv) {
  if (!flags->e && optind < argc) {
    add_pattern(flags, argv[optind]);
    optind++;
  }
}

void add_pattern(FLAGS *flags, const char *pattern) {
  flags->pattern_amount++;
  flags->pattern_list =
      realloc(flags->pattern_list, flags->pattern_amount * sizeof(char *));
  flags->pattern_list[flags->pattern_amount - 1] = strdup(pattern);
}

void procces_file(const char *filename, FLAGS flags, int multi_file) {
  FILE *file = fopen(filename, "r");
  if (!file) {
    printf("%s: %s\n", filename, ERROR_FILE);
    return;
  }

  char *line = NULL;
  int cflags = REG_EXTENDED | (flags.i ? REG_ICASE : 0);

  regex_t *regex_list = malloc(flags.pattern_amount * sizeof(regex_t));
  for (int i = 0; i < flags.pattern_amount; i++) {
    if (regcomp(&regex_list[i], flags.pattern_list[i], cflags) != 0) {
      free_regex(regex_list, flags);
      fclose(file);
      return;
    }
  }

  ssize_t read;
  size_t len = 0;
  int line_num = 0;
  int match_count = 0;
  while ((read = getline(&line, &len, file)) != -1) {
    line_num++;
    process_line(line, filename, flags, multi_file, line_num, &match_count,
                 regex_list);

    free(line);
    line = NULL;
    len = 0;
  }

  if (flags.c) {
    if (multi_file) printf("%s:", filename);
    printf("%d\n", match_count);
  }
  if (flags.l && match_count > 0) {
    printf("%s\n", filename);
  }

  free_regex(regex_list, flags);
  fclose(file);
}

void process_line(const char *line, const char *filename, FLAGS flags,
                  int multi_file, int line_num, int *match_count,
                  regex_t *regex_list) {
  int match = 0;
  for (int i = 0; i < flags.pattern_amount && !match; i++) {
    if (regexec(&regex_list[i], line, 0, NULL, 0) == 0) match = 1;
  }

  if ((match && !flags.v) || (!match && flags.v)) {
    (*match_count)++;
    if (!flags.c && !flags.l) {
      if (multi_file) printf("%s:", filename);
      if (flags.n) printf("%d:", line_num);
      printf("%s", line);
      if (line[strlen(line) - 1] != '\n') printf("\n");
    }
  }
}

void free_regex(regex_t *regex_list, FLAGS flags) {
  for (int i = 0; i < flags.pattern_amount; i++) {
    regfree(&regex_list[i]);
  }
  free(regex_list);
}