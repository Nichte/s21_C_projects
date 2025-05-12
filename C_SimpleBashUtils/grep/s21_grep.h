#ifndef _S21_GREP_H_
#define _S21_GREP_H_

#include <stdbool.h>

#define MAX_LINE_LEN 4096
#define MAX_AMOUNT_PATTERNS 1000

#define OK 0
#define NO_ARGV -1
#define ERR_MEM -2
#define ERR_FILE -3
#define INVALID_OPTION -4

#define ERROR_MSG "usage: grep [-eivcln] [pattern] [file]\n"
#define ERROR_MEM_MSG "Memory allocation error\n"
#define ERROR_FILE "Can't open the file\n"

typedef struct FLAGS {
  bool e;  // template
  bool i;  // ignor reg
  bool v;  // invert search
  bool c;  // count founds
  bool l;  // shows found files
  bool n;  // shows file&row of found template

  int pattern_amount;
  char **pattern_list;
  char *pattern_file;
} FLAGS;

#endif