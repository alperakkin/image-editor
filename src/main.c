#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>

#include "utils.h"
#include "image.h"
#include "editor.h"
#include "argparse.h"




int main(int argc, char *argv[])
{
  if(argc <= 2)
  {
    help();
    return 1;

  }

  parse_args(argc, argv);

  return 0;
}