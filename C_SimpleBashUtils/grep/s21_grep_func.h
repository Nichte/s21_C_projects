#ifndef _S21_GREP_FUNC_H_
#define _S21_GREP_FUNC_H_

#include "s21_grep.h"

void initFlags(FLAGS *flags);
int parseFlags(int argc, char **argv, FLAGS *flags);
void patterns_check(FLAGS *flags, int argc, char **argv);
void procces_file(const char *filename, FLAGS flags, int multi_file);

#endif