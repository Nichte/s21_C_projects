#include "s21_cat_func.h"

#include <getopt.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

#include "s21_cat.h"

struct option long_options[] = {{"number-nonblank", no_argument, 0, 0},
                                {"number", no_argument, 0, 0},
                                {"squeeze-blank", no_argument, 0, 0},
                                {0, 0, 0, 0}};

// === FUNCITON DECLARATION ===

int handle_flag_option(int option, int optIndex, struct option *long_options,
                       FLAGS *flags);
void handle_files(FILE *stream, FLAGS flags);
void process_char(int c, FLAGS flags, int *empty_line_flag, bool *new_line,
                  long *line_number);
void handle_squeeze_blank(int c, int *empty_line_flag);
void handle_number(bool *new_line, long *line_number);
void handle_number_nonblank(int c, bool *new_line, long *line_number);
void handle_show_tabs(int *c);
void handle_non_printing(int *c);
void handle_show_ends(int c);

// === FUNCTION REALIZATION ===

void initFlags(FLAGS *flags) {
  flags->b = false;
  flags->e = false;
  flags->v = false;
  flags->n = false;
  flags->s = false;
  flags->t = false;
}

int parseFlags(int argc, char **argv, FLAGS *flags, int *optind) {
  int error = OK;

  int option;
  int optIndex = 0;
  const char *allowedSymbs = "+bevEnstT";

  while (!error) {
    option = getopt_long(argc, argv, allowedSymbs, long_options, &optIndex);
    if (option == -1) break;  // no more flags

    error = handle_flag_option(option, optIndex, long_options, flags);
    (*optind)++;
  }

  return error;
}

// Function to handle individual options
int handle_flag_option(int option, int optIndex, struct option *long_options,
                       FLAGS *flags) {
  int error = OK;
  bool T_flag = false, E_flag = false;

  if (option == 0) {
    if (strcmp(long_options[optIndex].name, "number-nonblank") == 0)
      flags->b = true;
    if (strcmp(long_options[optIndex].name, "number") == 0) flags->n = true;
    if (strcmp(long_options[optIndex].name, "squeeze-blank") == 0)
      flags->s = true;
  } else if (option == 'b')
    flags->b = true;
  else if (option == 'e')
    flags->e = true;
  else if (option == 'v') {
    if (T_flag)
      flags->t = true;
    else if (E_flag)
      flags->e = true;
  } else if (option == 'n')
    flags->n = true;
  else if (option == 's')
    flags->s = true;
  else if (option == 't')
    flags->t = true;
  else if (option == 'T')
    T_flag = true;
  else if (option == 'E')
    E_flag = true;
  else
    error = INVALID_OPTION;

  return error;
}

int handleFlags(int argc, char **argv, FLAGS flags, int optind) {
  int error = OK;
  if (argv[optind] == NULL) error = NO_ARGV;

  bool no_file_flag = true;

  for (int i = optind; i < argc; i++) {
    FILE *stream = fopen(argv[i], "r");

    if (stream == NULL) continue;
    no_file_flag = false;

    handle_files(stream, flags);
    fclose(stream);
  }

  if (no_file_flag) error = NO_FILE;
  return error;
}

void handle_files(FILE *stream, FLAGS flags) {
  int c;
  long line_number = 1;
  int empty_line_flag = 0;
  bool new_line = true;

  while ((c = fgetc(stream)) != EOF)
    process_char(c, flags, &empty_line_flag, &new_line, &line_number);
}

void process_char(int c, FLAGS flags, int *empty_line_flag, bool *new_line,
                  long *line_number) {
  // -s flag: Squeeze blank lines. If more than 2 consecutive blank lines, skip
  // printing.
  if (flags.s) {
    handle_squeeze_blank(c, empty_line_flag);
    if (*empty_line_flag > 2) return;
  }
  // -b flag: Number nonempty output lines, overrides -n.
  if (flags.b) handle_number_nonblank(c, new_line, line_number);
  // -n flag: Number all output lines.
  else if (flags.n)
    handle_number(new_line, line_number);
  // -t flag: Display tabs as ^I.
  if (flags.t) handle_show_tabs(&c);
  // -v flag: Display nonprinting characters except for LFs and TABs.
  if (flags.v) handle_non_printing(&c);
  // -e flag: Display $ at end of each line.
  if (flags.e) handle_show_ends(c);

  if (c == '\n') {
    *new_line = true;
  }
  printf("%c", c);
}

// --- flag-functions realization
// Function to handle the -s (squeeze-blank) flag
void handle_squeeze_blank(int c, int *empty_line_flag) {
  if (c == '\n')
    (*empty_line_flag)++;
  else
    *empty_line_flag = 0;
}

// Function to handle the -b (number-nonblank) flag
void handle_number_nonblank(int c, bool *new_line, long *line_number) {
  if (*new_line && c != '\n') {
    printf("%6ld\t", (*line_number)++);
    *new_line = false;
  }
}

// Function to handle the -n (number) flag
void handle_number(bool *new_line, long *line_number) {
  if (*new_line) {
    printf("%6ld\t", (*line_number)++);
    *new_line = false;
  }
}

// Function to handle the -t (show tabs) flag
void handle_show_tabs(int *c) {
  if (*c == '\t') {
    printf("^");
    *c = 'I';
  }
}

// Function to handle the -v (show non-printing) flag
void handle_non_printing(int *c) {
  if (*c != '\n' && *c != '\t') {
    if (*c >= 0 && *c <= 31) {
      printf("^");
      *c += 64;
    } else if (*c == 127) {
      printf("^");
      *c -= 64;
    }
  }
}

// Function to handle the -e (show ends) flag
void handle_show_ends(int c) {
  if (c == '\n') printf("$");
}