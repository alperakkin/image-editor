#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

#include "image.h"
#include "editor.h"

char* input_path;
char* output_path;

void help() {
    printf("------------- Help ---------------\n\n");
    printf("Following command format should be used to run the editor:\n");
    printf("./image-editor -i input.png -<option> -o output.png\n\n");
    printf("Use image-editor with following option:\n");
    printf("-i: Read Image File\n");
    printf("-o: Save Image File\n");
    printf("-g: Set pixels to grayscale\n");
    printf("-c: Set contrast\n");
    printf("-b: Set brightness\n");
    printf("--gaussian: Set Gaussian Blur\n");
}





void push(FunctionList *function_list,  void (*name)(char*), char* arg){
    struct Function new_func = {arg, name};
    function_list->functions[function_list->length++] = new_func;

}


FunctionList parse_args(int argc, char *argv[])
{
    FunctionList function_list;
    function_list.functions = \
        (struct Function *)malloc(argc * sizeof(struct Function));
    function_list.length = 0;

    for(int i=1; i<argc; i++)
    {
        if (strcmp(argv[i], "-h") == 0) help();
        if (strcmp(argv[i], "-i") == 0) input_path = argv[i+1];
        if (strcmp(argv[i], "-o") == 0) output_path = argv[i+1];
        if (strcmp(argv[i], "-g") == 0) push(&function_list, grayscale, NULL);
        if (strcmp(argv[i], "-c") == 0) push(&function_list, contrast, argv[i+1]);
        if (strcmp(argv[i], "-b") == 0) push(&function_list, brightness, argv[i+1]);
        if (strcmp(argv[i], "--gaussian") == 0) push(&function_list, gaussian, argv[i+1]);

    }


    return function_list;


}

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
  write_png_file(output_path);

  return 0;
}