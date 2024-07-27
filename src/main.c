#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

#include "image.h"
#include "editor.h"
#include "argparse.h"


int main(int argc, char *argv[])
{
  if(argc <= 1)
  {
    help();
    return 1;

  }

  FunctionList functions = parse_args(argc, argv);

  read_png_file(input_path);
  process_functions(&functions);

  return 0;
}