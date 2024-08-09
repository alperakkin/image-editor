
#include <float.h>
#include <stdlib.h>
#include "utils.h"
#include "helpers.h"






const char* INPUT_PATH;
const char* OUTPUT_PATH;




Image grayscale(Image image)
{
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

 return image;
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

    Image new_image = alloc_image(width, height);

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
    free_image(image);


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

Image add_layer(Image image, Image patch, int pos_x, int pos_y, int alpha)
{
    if (pos_x < 0 || pos_x > image.width || pos_y < 0 || pos_y > image.height)  raise_error("Invalid position!");

    for(int y = 0; y < patch.height; y++)
    {
        png_bytep row = patch.pixels[y];
        for(int x = 0; x < patch.width; x++)
        {
           png_bytep px = &(row[x * 4]);
           int org_x = x + pos_x;
           int org_y = y + pos_y;
           if (org_x <= image.width && org_y <= image.height)
           {
            png_bytep image_row = image.pixels[org_y];
            png_bytep org_px = &(image_row[org_x * 4]);

            if (px[3] <= alpha) continue;

            org_px[0] = px[0];
            org_px[1] = px[1];
            org_px[2] = px[2];



           }





        }
    }

    return image;
}

Image crop(Image image, int left, int right, int top, int bottom)
{
    if (left < 0 || left > image.width || top < 0 || top > image.height ||
        right < 0 || right > image.width || bottom < 0 || bottom > image.height)  raise_error("Invalid Crop Parameters!");

    int new_height = image.height - (top + bottom);
    int new_width = image.width - (left + right);

    Image cropped = alloc_image(new_width, new_height);


    for(int y = 0; y < cropped.height; y++)
    {
        png_bytep row = cropped.pixels[y];
        png_bytep org_row = image.pixels[y+top];
        for(int x = 0; x < cropped.width; x++)
        {

            png_bytep px = &(row[x * 4]);
            png_bytep org_px = &(org_row[(x + left) * 4]);

            px[0] = org_px[0];
            px[1] = org_px[1];
            px[2] = org_px[2];
            px[3] = org_px[3];
        }
    }


    free_image(image);
    return cropped;

}



Image rotate_image(Image image, double angle)
{

    double radians = angle * M_PI / 180;
    double cos_value =  cos(radians);
    double sin_value = sin(radians);
    int width = image.width;
    int height = image.height;
    const int SCALE = 4;

    image = resize(image, image.width * SCALE, image.height * SCALE);

    int new_width = (int)(fabs(image.width * cos_value) + fabs(image.height * sin_value));
    int new_height = (int)(fabs(image.width * sin_value) + fabs(image.height * cos_value));

    Image rotated = alloc_image(new_width, new_height);


    int x0 = (int) image.width / 2;
    int y0 = (int) image.height / 2;

    int new_x0 = new_width / 2;
    int new_y0 = new_height / 2;

    for(int y = 0; y < image.height; y++)
    {
        png_bytep row = image.pixels[y];

        for(int x = 0; x < image.width; x++)
        {
            int new_x = (int) (new_x0 + (x-x0) * cos_value + (y-y0) * sin_value);
            int new_y = (int) (new_y0 - (x-x0) * sin_value + (y-y0) * cos_value);


            if (new_x < 0 || new_x >= new_width || new_y < 0 || new_y >= new_height) continue;

            png_bytep rotated_row = rotated.pixels[new_y];
            png_bytep px = &(row[x * 4]);
            png_bytep rotated_px = &(rotated_row[new_x * 4]);




            rotated_px[0] = px[0];
            rotated_px[1] = px[1];
            rotated_px[2] = px[2];
            rotated_px[3] = px[3];

        }
    }


    rotated = bilinear_interpolation(rotated);
    int kernel_size = 6;
    float sigma = 1.8;
    rotated = gaussian(rotated, kernel_size, sigma);
    rotated = resize(rotated,width, height);





    return rotated;
}

Image invert(Image image)
{
    for(int y = 0; y < image.height; y++)
    {
        png_bytep row = image.pixels[y];
        for(int x = 0; x < image.width; x++)
        {
            png_bytep px = &(row[x * 4]);

            px[0] = 255 - px[0];
            px[1] = 255 - px[1];
            px[2] = 255 - px[2];



        }
    }

    return image;
}

Image add_border(Image image, char* color, int size)
{

    int r, g, b;

    char* hex_code = color;

    hex_to_rgb(hex_code, &r, &g, &b);

    for(int y = 0; y < image.height; y++)
    {
        png_bytep row = image.pixels[y];
        for(int x = 0; x < image.width; x++)
        {
            png_bytep px = &(row[x * 4]);


            if (x < size || x > (image.width - size) ||
                y < size || y > (image.height - size))
                {
                    px[0] = r;
                    px[1] = g;
                    px[2] = b;

                }

        }
    }

    return image;
}


Image mask(Image image, char* color, float threshold)
{
    int r, g, b;

    char* hex_code = color;

    hex_to_rgb(hex_code, &r, &g, &b);



    int r_min = (int) (r * threshold);
    int g_min = (int) (g * threshold);
    int b_min = (int) (b * threshold);

    int r_max = (int)(r + (255 - r) * (1 - threshold));
    int g_max = (int)(g + (255 - g) * (1 - threshold));
    int b_max = (int)(b + (255 - b) * (1 - threshold));


    for(int y = 0; y < image.height; y++)
    {
        png_bytep row = image.pixels[y];

        for(int x = 0; x < image.width; x++)
        {
            png_bytep px = &(row[x * 4]);

            if( px[0] >= r_min && px[0] <= r_max &&
                px[1] >= g_min && px[1] <= g_max &&
                px[2] >= b_min && px[2] <= b_max
            )
            {

                px[3] = 0;
            }

        }
    }
    return image;
}


int** alloc_matrix(int width, int height)
{
    int** rows = malloc(height * sizeof(int*));
    for (int i = 0; i < height; i++)
    {
        rows[i] = malloc(width * sizeof(int));

        for(int j = 0; j < width; j++)
        {
            rows[i][j] = 0;
        }
    }
    return rows;
}


int** sobel_filter(Image image, char direction)
{
    int sobel_matrix[3][3];

    int sobel_x[3][3] = {
        {-1, 0, 1},
        {-2, 0, 2},
        {-1, 0, 1}
    };

    int sobel_y[3][3] = {
        {-1, -2, -1},
        {0, 0, 0},
        {1, 2, 1}
    };

    for (int i=0; i<3; i++)
    {
        for (int j=0; j<3; j++)
        {
            if (direction == 'x') sobel_matrix[i][j] = sobel_x[i][j];
            if (direction == 'y') sobel_matrix[i][j] = sobel_y[i][j];
        }
    }





   int** sobel_filter_matrix = alloc_matrix(image.width, image.height);

    for (int y=0; y < image.height; y++)
    {

        int* sobel_row = sobel_filter_matrix[y];


        for (int x=0; x < image.width; x++)
        {


            for(int sy = -1; sy != 1; sy++)
            {
                for(int sx = -1; sx != 1; sx++)
                {
                    int posy = sy + y;
                    int posx = sx + x;
                    if (posy < 0 || posy > image.height || posx < 0 || posx > image.width) continue;
                    png_bytep row = image.pixels[posy];
                    png_bytep px = &(row[posx * 4]);

                    sobel_filter_matrix[y][x] = sobel_filter_matrix[y][x] +(px[0] * sobel_matrix[posy%3][posx%3]);


                }

            }




        }

    }





    return sobel_filter_matrix;
}

int** gradient_direction(int** sobel_x, int** sobel_y, int width, int height)
{
    int** gradient_matrix = alloc_matrix(width, height);

    for (int y=0; y < height; y++)
    {

        for (int x=0; x < width; x++)
        {
            gradient_matrix[y][x] = atan2(sobel_y[y][x], sobel_x[y][x]);
        }

    }

    return gradient_matrix;
}


int** gradient_magnitude(int** sobel_x, int** sobel_y, int width, int height)
{
    int** gradient_matrix = alloc_matrix(width, height);

    for (int y=0; y < height; y++)
    {

        for (int x=0; x < width; x++)
        {

            double sq = (sobel_x[y][x] * sobel_x[y][x]) + (sobel_y[y][x] * sobel_y[y][x]);
            gradient_matrix[y][x] = sqrt(sq);

        }

    }
    return gradient_matrix;
}

int** non_maximum_suppression(int** gradient_mag, int** gradient_dir, int width, int height)
{
    int** suppr_matrix = alloc_matrix(width, height);
    for (int y=0; y < height; y++)
    {

        for (int x=0; x < width; x++)
        {


            double angle = gradient_dir[y][x];

            if (angle > M_PI) angle -= M_PI;
            if (angle >=0 && angle < M_PI/8) angle = 0;
            if (angle >=M_PI/8 && angle < M_PI/4) angle = (int) M_PI/4;
            if (angle >=M_PI/4 && angle < M_PI/2) angle = (int) M_PI/2;
            if (angle >=M_PI/2 && angle < 3 * M_PI / 4) angle = (int) 3 * M_PI /4;
            if (angle >=3 * M_PI / 4 && angle < M_PI) angle = (int) M_PI;

            if (angle == 0 || angle == M_PI)
            {

                int left = 0;
                int right = 0;
                if (x-1 >= 0)
                {
                    left = gradient_mag[y][x-1];
                }
                if (x+1 < width)
                {
                    right = gradient_mag[y][x+1];
                }

                if (gradient_mag[y][x] > left && gradient_mag[y][x] > right)
                {
                    suppr_matrix[y][x]= gradient_mag[y][x];

                }
                else
                {
                    suppr_matrix[y][x] = 0;

                }
            }

            if (angle == (int) M_PI/4)
            {
                int bottom_left = 0;
                int top_right = 0;
                if (y-1 >= 0 && x-1 >= 0)
                {

                    bottom_left = gradient_mag[y-1][x-1];

                }
                if (y+1 < height && x+1 < width)
                {
                    top_right = gradient_mag[y+1][x+1];

                }

                if (gradient_mag[y][x] > bottom_left && gradient_mag[y][x] > top_right)
                {
                    suppr_matrix[y][x] = gradient_mag[y][x];

                }
                else
                {
                    suppr_matrix[y][x] = 0;

                }
            }

            if (angle == (int) 3* M_PI/4)
            {
                int bottom_right = 0;
                int top_left = 0;
                if (y-1 >= 0 && x+1 < width)
                {
                    bottom_right = gradient_mag[y-1][x+1];
                }
                if (y+1 < height && x-1 >= 0)
                {
                    top_left = gradient_mag[y+1][x-1];
                }

                if (gradient_mag[y][x] > bottom_right && gradient_mag[y][x] > top_left)
                {
                    suppr_matrix[y][x] = gradient_mag[y][x];

                }
                else
                {
                    suppr_matrix[y][x] = 0;
                }

            }

            if (angle == (int) M_PI/2)
            {
                int top = 0;
                int bottom = 0;
                if (y-1 >= 0)
                {

                    bottom = gradient_mag[y-1][x];
                }
                if (y+1 < height)
                {

                    top = gradient_mag[y+1][x];
                }

                if (gradient_mag[y][x] > bottom && gradient_mag[y][x]> top)
                {
                    suppr_matrix[y][x] = gradient_mag[y][x];

                }
                else
                {
                    suppr_matrix[y][x] = 0;

                }

            }


        }

    }

    return suppr_matrix;

}

// Image double_threshold(Image image, int high, int low)
// {
//     for (int y=0; y < image.height; y++)
//     {

//         png_bytep row = image.pixels[y];

//         for (int x=0; x < image.width; x++)
//         {
//             png_bytep px = &(row[x * 4]);

//             if (px[0] >= high) {px[0] = 255; px[3]=255;}
//             if (px[0] >= low && px[0] < high) {px[0] = 128, px[3]=255;};
//             if (px[0] < low) {px[0] = 0; px[3]=255;}

//         }
//     }

//     return image;
// }

// Image edge_tracking(Image image)
// {
//     for (int y=0; y < image.height; y++)
//     {

//         png_bytep row = image.pixels[y];

//         for (int x=0; x < image.width; x++)
//         {
//             png_bytep px = &(row[x * 4]);

//             if (px[0] == 128)
//             {


//                 for(int sy = -1; sy != 1; sy++)
//                 {
//                     for(int sx = -1; sx != 1; sx++)
//                     {
//                         int posy = sy + y;
//                         int posx = sx + x;
//                         if (posy < 0 || posy > image.height || posx < 0 || posx > image.width) continue;
//                         png_bytep e_row = image.pixels[posy];
//                         png_bytep e_px = &(e_row[posx * 4]);

//                         if(e_px[0] ==255) px[0] = 255;


//                     }

//                 }
//             }
//             printf("%d ", px[0]);
//         }
//             printf("\n");
//     }

//     return image;
// }


Image edge(Image image, int high_threshold, int low_threshold)
{
    Image blurred = gaussian(image, 3, 1.05);
    Image gray_image = grayscale(blurred);
    int** sobel_x = sobel_filter(gray_image, 'x');
    int** sobel_y = sobel_filter(gray_image, 'y');
    int** gradient_dir = gradient_direction(sobel_x, sobel_y, image.width, image.height);
    int** gradient_mag = gradient_magnitude(sobel_x, sobel_y, image.width, image.height);
    // Image suppr = non_maximum_suppression(gradient_mag, gradient_dir);
    // Image dbl_thresh = double_threshold(suppr, high_threshold, low_threshold);
    // Image result = edge_tracking(dbl_thresh);

    return gray_image;
}