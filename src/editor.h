struct Function {
    void (*function_name)();
    char* argument;
};

typedef struct {
    struct Function *functions;
    int length;
}FunctionList;

void process_png_file(png_bytep *pixels) {
  for(int y = 0; y < height; y++) {
    png_bytep row = pixels[y];
    for(int x = 0; x < width; x++) {
      png_bytep px = &(row[x * 4]);
      // Pixel information
      //printf("%4d, %4d = RGBA(%3d, %3d, %3d, %3d)\n", x, y, px[0], px[1], px[2], px[3]);
    }
  }
}

void grayscale(){
    for(int y = 0; y < height; y++)
    {
        png_bytep row = pixels[y];
        for(int x = 0; x < width; x++)
        {
            png_bytep px = &(row[x * 4]);
            int avg = (int)(px[0] + px[1] + px[2]) / 3;
            px[0] = avg;
            px[1] = avg;
            px[2] = avg;
    }
  }
}

void process_functions(FunctionList *function_list){
    for(int i=0; i<function_list->length; i++)
    {
        function_list->functions[i].function_name();
    }

}
