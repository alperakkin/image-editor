
#include <float.h>
#include <stdlib.h>
#include "utils.h"
#include "helpers.h"








const char* INPUT_PATH;
const char* OUTPUT_PATH;




void grayscale(Image image){
  for (int y = 0; y < image.height; y++)
    {
        png_bytep row = image.pixels[y];
        for(int x = 0; x < image.width; x++)
        {
          png_bytep px = &(row[x * 4]);
          int avg = (int)(px[0] + px[1] + px[2]) / 3;
          px[0] = avg;
          px[1] = avg;
          px[2] = avg;
        }
    }

  write_png_file(OUTPUT_PATH, image);
}



Image  contrast(Image image, float f)
{
    Intensity statistics = intensity(image);

    for(int y = 0; y < image.height; y++)
    {
        png_bytep row = image.pixels[y];
        for(int x = 0; x < image.width; x++)
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

    return image;


}

Image brightness(Image image, float ratio)
{

    for(int y = 0; y < image.height; y++)
    {
        png_bytep row = image.pixels[y];
        for(int x = 0; x < image.width; x++)
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



    return image;

}




Image gaussian(Image image, int kernel_size, float sigma)
{
    double **kernel = kernel_filter(kernel_size, sigma);
    apply_kernel(kernel, kernel_size, image);

    return image;
}

Image resize(Image image, int width, int height)
{

    Image new_image = alloc_image(height, width);

    double x_scale = (double)image.width/width;
    double y_scale = (double) image.height/height;

    for (int i=0; i<height; i++){

        for (int j=0; j<width; j++){

            int row_val = (int) (i * y_scale);
            int col_val = (int) (j * x_scale);


            png_bytep px = &(image.pixels[row_val][col_val * 4]);

            png_bytep px_n = &(new_image.pixels[i][j * 4]);


            px_n[0] = px[0];  // R
            px_n[1] = px[1];  // G
            px_n[2] = px[2];  // B
            px_n[3] = px[3];  // Alpha




        }

    }


    free_image(image);
    return new_image;

}


void histogram(Image image)
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

    for(int y = 0; y < image.height; y++)
    {
        png_bytep row = image.pixels[y];
        for(int x = 0; x < image.width; x++)
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

Image filter(Image image, char* color, float strength)
{

    int r, g, b;

    char* hex_code = color;

    hex_to_rgb(hex_code, &r, &g, &b);

    if (strength > 1.0) strength = 1.0;

    for(int y = 0; y < image.height; y++)
    {
        png_bytep row = image.pixels[y];
        for(int x = 0; x < image.width; x++)
        {
            png_bytep px = &(row[x * 4]);

            px[0] = (int) (strength * r + (1-strength) * px[0]);
            px[1] = (int) (strength * g + (1-strength) * px[1]);
            px[2] = (int) (strength * b + (1-strength) * px[2]);

        }
    }

    return image;
}

Image opacity(Image image, float factor)
{
    if (factor > 1) factor = 1;

    for(int y = 0; y < image.height; y++)
    {
        png_bytep row = image.pixels[y];
        for(int x = 0; x < image.width; x++)
        {
            png_bytep px = &(row[x * 4]);

            px[3] = (int) (factor * 255);


        }
    }

    return image;

}

// void add_layer(char* args)
// {
//   Image image = read_png_file(INPUT_PATH);
//   printf("Add Layer Not Implemented!");
// }
