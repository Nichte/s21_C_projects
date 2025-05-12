#ifndef S21_CAT_FUNC
#define S21_CAT_FUNC

#include <stdbool.h>

#define MAX_LINE_LEN 1000

typedef struct {
  bool b;  // number nonempty strings
  bool e;  // shows end of string '$'
  bool v;  // shows invis elements
  bool n;  // number all strings
  bool s;  // squeeze empty strings
  bool t;  // shows tabs
} FLAGS;

void initFlags(FLAGS *flags);
int parseFlags(int argc, char **argv, FLAGS *flags, int *optind);
int handleFlags(int argc, char **argv, FLAGS flags, int optind);

#endif