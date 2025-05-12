#include "s21_grep.h"

#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>

#include "s21_grep_func.h"

void free_pattern_list(FLAGS *flags);

int main(int argc, char **argv) {
  int error = OK;
  FLAGS flags;
  initFlags(&flags);

  if (argc < 3) error = NO_ARGV;
  if (!error) {
    error = parseFlags(argc, argv, &flags);
    patterns_check(&flags, argc, argv);
  }
  if (!error) {
    int multi_file = (argc - optind) > 1;
    for (int i = optind; i < argc; i++)
      procces_file(argv[i], flags, multi_file);
  }

  if (flags.pattern_list) free_pattern_list(&flags);
  if (error) printf("s21_grep error");
  return error;
}

// --- FUNCTIONS ---

void free_pattern_list(FLAGS *flags) {
  for (int i = 0; i < flags->pattern_amount; i++) free(flags->pattern_list[i]);

  free(flags->pattern_list);
}
