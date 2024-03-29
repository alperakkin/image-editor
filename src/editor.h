struct Function {
    char* argument;
    void (*name)(char* argument);

};

typedef struct {
    struct Function *functions;
    int length;
}FunctionList;

typedef struct {
    int min;
    int max;
} Intensity;

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

Intensity intensity()
{
    Intensity intensity_data = {255, 0};
    for(int y = 0; y < height; y++)
    {
        png_bytep row = pixels[y];
        for(int x = 0; x < width; x++)
        {
            png_bytep px = &(row[x * 4]);
            int avg = (int)(px[0] + px[1] + px[2]) / 3;

            if (avg<= intensity_data.min) intensity_data.min = avg;
            if (avg>= intensity_data.max) intensity_data.max = avg;

        }

     }
    return intensity_data;
}

void contrast(char* factor)
{
    float f = atof(factor);

    Intensity statistics = intensity();

    for(int y = 0; y < height; y++)
    {
        png_bytep row = pixels[y];
        for(int x = 0; x < width; x++)
        {
            png_bytep px = &(row[x * 4]);

            int avg = (int)(px[0] + px[1] + px[2]) / 3;

            int contrast_applied =  255  *
                ((float)(avg - statistics.min) /
                (float)(statistics.max - statistics.min));

            float ratio = f * ((float) contrast_applied / (float) avg);

            int red = (int) px[0] * ratio;
            int green = (int) px[1] * ratio;
            int blue = (int) px[2] * ratio;



            if (red > 255) red = 255;
            if (red < 0) red = 0;
            if (green > 255) green = 255;
            if (green < 0) green = 0;
            if (blue > 255) blue = 255;
            if (blue < 0) blue = 0;


            px[0] = red;
            px[1] = green;
            px[2] = blue;


        }
    }


}

void brightness(char* factor)
{
    float ratio = atof(factor);


    for(int y = 0; y < height; y++)
    {
        png_bytep row = pixels[y];
        for(int x = 0; x < width; x++)
        {
            png_bytep px = &(row[x * 4]);


            int red = (int) px[0] * ratio;
            int green = (int) px[1] * ratio;
            int blue = (int) px[2] * ratio;



            if (red > 255) red = 255;
            if (red < 0) red = 0;
            if (green > 255) green = 255;
            if (green < 0) green = 0;
            if (blue > 255) blue = 255;
            if (blue < 0) blue = 0;


            px[0] = red;
            px[1] = green;
            px[2] = blue;


        }
    }


}

void cleanup(FunctionList *function_list)
{
    for(int i=0; i<function_list->length; i++)
    {
        free(&function_list->functions[i]);
    }
}

void process_functions(FunctionList *function_list)
{
    for(int i=0; i<function_list->length; i++)
    {
        struct Function func = function_list->functions[i];

        func.name(func.argument);

    }

    cleanup(function_list);


}
