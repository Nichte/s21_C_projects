#include "s21_cat.h"

#include <stdio.h>

#include "s21_cat_func.h"

int main(int argc, char **argv) {
  int error = OK;

  FLAGS flags;
  initFlags(&flags);

  int optind = 1;
  error = parseFlags(argc, argv, &flags, &optind);

  if (!error) error = handleFlags(argc, argv, flags, optind);

  if (error) printf("s21_cat error");
  return error;
}
