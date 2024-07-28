#include <float.h>
#include <stdlib.h>
#include "utils.h"
#include "helpers.h"


const char* INPUT_PATH;
const char* OUTPUT_PATH;




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
  write_png_file(OUTPUT_PATH, pixels, width, height);
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

    write_png_file(OUTPUT_PATH, pixels, width, height);

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

    write_png_file(OUTPUT_PATH, pixels, width, height);
}




void gaussian(char* args)
{


    int KERNEL_SIZE;
    float sigma;
    Arg* arguments = split_args(args, 2, 'x');

    KERNEL_SIZE = arguments[0].number;
    sigma = arguments[1].number;



    double **kernel = kernel_filter(KERNEL_SIZE, sigma);
    apply_kernel(kernel, KERNEL_SIZE);
    write_png_file(OUTPUT_PATH, pixels, width, height);
    free(arguments);


}

void resize(char* args)
{


    Arg* arguments = split_args(args, 2, 'x');
    int image_width = arguments[0].number;
    int image_height = arguments[1].number;

    png_bytep* new_image = alloc_image(image_height, image_width);

    double x_scale = (double) width/image_width;
    double y_scale = (double) height/image_height;

    for (int i=0; i<image_height; i++){

        for (int j=0; j<image_width; j++){

            int row_val = (int) (i * y_scale);
            int col_val = (int) (j * x_scale);


            png_bytep px = &(pixels[row_val][col_val * 4]);

            png_bytep px_n = &(new_image[i][j * 4]);


            px_n[0] = px[0];  // R
            px_n[1] = px[1];  // G
            px_n[2] = px[2];  // B
            px_n[3] = px[3];  // Alpha




        }

    }



    write_png_file(OUTPUT_PATH, new_image, image_width, image_height);
    free(arguments);
}


void histogram()
{
    ColorMode red = {
        .name = "red",
        .value = "31",
        .min = 1000000,
        .max = 0,
        .histogram = {
        0,0,0,0,0,
        0,0,0,0,0,
        0,0,0,0,0,
        0,0,0,0,0,
        0,0,0,0,0
        }
    };
    ColorMode green = {
        .name = "green",
        .value = "32",
        .min = 1000000,
        .max = 0,
        .histogram = {
        0,0,0,0,0,
        0,0,0,0,0,
        0,0,0,0,0,
        0,0,0,0,0,
        0,0,0,0,0
        }
    };
    ColorMode blue = {
        .name = "blue",
        .value = "34",
        .min = 1000000,
        .max = 0,
        .histogram = {
        0,0,0,0,0,
        0,0,0,0,0,
        0,0,0,0,0,
        0,0,0,0,0,
        0,0,0,0,0
        }
    };

    for(int y = 0; y < height; y++)
    {
        png_bytep row = pixels[y];
        for(int x = 0; x < width; x++)
        {
            png_bytep px = &(row[x * 4]);

            int block = (int) 25*px[0]/255;
            red.histogram[block]++;
            block = (int) 25*px[1]/255;
            green.histogram[block]++;
            block = (int) 25*px[2]/255;
            blue.histogram[block]++;


            if (red.max < px[0]) red.max=px[0];
            if (blue.max < px[1]) blue.max=px[1];
            if (green.max < px[2]) green.max=px[2];

            if (red.min > px[0]) red.min=px[0];
            if (blue.min > px[1]) blue.min=px[1];
            if (green.min > px[2]) green.min=px[2];

        }
    }


    print_table(red, green, blue);


}

void filter(char* args)
{
    int r, g, b;

    Arg* arguments = split_args(args, 2, 'x');
    char* hex_code = arguments[0].str;
    double opacity = arguments[1].number;

    hex_to_rgb(hex_code, &r, &g, &b);

    if (opacity > 1.0) opacity = 1;

    for(int y = 0; y < height; y++)
    {
        png_bytep row = pixels[y];
        for(int x = 0; x < width; x++)
        {
            png_bytep px = &(row[x * 4]);

            px[0] = (int) (opacity * r + (1-opacity) * px[0]);
            px[1] = (int) (opacity * g + (1-opacity) * px[1]);
            px[2] = (int) (opacity * b + (1-opacity) * px[2]);

        }
    }


    write_png_file(OUTPUT_PATH, pixels, width, height);
    free(arguments);


}

