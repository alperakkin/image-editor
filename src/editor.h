#include <float.h>

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

    double factors[2];
    int KERNEL_SIZE;
    float sigma;
    split_factors(args, factors, 'x');

    KERNEL_SIZE = factors[0];
    sigma = factors[1];




    double **kernel = kernel_filter(KERNEL_SIZE, sigma);
    apply_kernel(kernel, KERNEL_SIZE);
    write_png_file(OUTPUT_PATH, pixels, width, height);



}

void resize(char* args)
{

    double factors[2];
    split_factors(args, factors, 'x');
    int image_width = factors[0];
    int image_height = factors[1];

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

}


