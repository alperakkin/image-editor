#include <stdio.h>

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