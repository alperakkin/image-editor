


typedef struct {
    int min;
    int max;
} Intensity;



Intensity intensity(Image image)
{
    Intensity intensity_data = {255, 0};
    for(int y = 0; y < image.height; y++)
    {
        png_bytep row = image.pixels[y];
        for(int x = 0; x < image.width; x++)
        {
            png_bytep px = &(row[x * 4]);
            int avg = (int)(px[0] + px[1] + px[2]) / 3;

            if (avg<= intensity_data.min) intensity_data.min = avg;
            if (avg>= intensity_data.max) intensity_data.max = avg;

        }

     }
    return intensity_data;
}


double** kernel_filter(int kernel_size, float sigma)
{
    double **kernel = (double **) malloc(kernel_size * sizeof(double));

    for(int row=0; row<kernel_size; row++)
    {
        kernel[row] = (double *) malloc(kernel_size * sizeof(double));
        for(int col=0; col<kernel_size; col++)
        {
            int dist_row =  abs(row - (int) (kernel_size / 2));
            int dist_col =  abs(col - (int) (kernel_size / 2));

            double sigma_squared = sigma * sigma;
            double exponent = -((dist_row * dist_row + dist_col * dist_col) / (2.0 * sigma_squared));
            double gauss_value = exp(exponent) / (2.0 * M_PI * sigma_squared);

            kernel[row][col] =  gauss_value;

        }

    }

    return kernel;

}

void apply_kernel(double**kernel, int KERNEL_SIZE, Image image)
{
    int KERNEL_RADIUS = (KERNEL_SIZE / 2) -1;
    png_bytep* output = (png_bytep*)malloc(image.height * sizeof(png_bytep));


    for (int i = 0; i < image.height; ++i) {
        output[i] = (png_bytep)malloc(image.width * 4 * sizeof(png_byte));
    }


    for (int y = 0; y < image.height; ++y) {
        for (int x = 0; x < image.width; ++x) {
            double r_sum = 0, g_sum = 0, b_sum = 0;
            double kernel_sum = 0;
            for (int ky = -KERNEL_RADIUS; ky <= KERNEL_RADIUS; ++ky) {
                for (int kx = -KERNEL_RADIUS; kx <= KERNEL_RADIUS; ++kx) {
                    int ix = x + kx;
                    int iy = y + ky;

                    if (ix >= 0 && ix < image.width && iy >= 0 && iy < image.height) {
                        png_bytep px = image.pixels[iy] + ix * 4;

                        double kernel_value = kernel[KERNEL_RADIUS + ky][KERNEL_RADIUS + kx];

                        r_sum += px[0] * kernel_value;
                        g_sum += px[1] * kernel_value;
                        b_sum += px[2] * kernel_value;

                        kernel_sum += kernel_value;
                    }
                }
            }
            png_bytep out_px = output[y] + x * 4;

            out_px[0] = (png_byte)(r_sum / kernel_sum) % 255;
            out_px[1] = (png_byte)(g_sum / kernel_sum) % 255;
            out_px[2] = (png_byte)(b_sum / kernel_sum) % 255;

            int avg = (int) ((int) out_px[0] + out_px[1] + out_px[2])/3;
            if (avg > 0) out_px[3] = 255;
        }
    }


    for (int i = 0; i < image.height; ++i) {
        memcpy(image.pixels[i], output[i], image.width * 4 * sizeof(png_byte));
        free(output[i]);
    }
    free(output);


}

Image bilinear_interpolation(Image image)
{
    for(int y = 0; y < image.height; y++)
    {
        png_bytep row = image.pixels[y];
        for(int x = 0; x < image.width; x++)
        {
            png_bytep px = &(row[x * 4]);


            int red = 0;
            int green = 0;
            int blue = 0;
            int alpha = 0;
            int count = 0;
            int kernel = 1;


            if (px[3] == 0)
            {
                for(int i=y-kernel; i<=y+kernel; i++)
                {
                    for(int j=x-kernel; j<=x+kernel; j++)
                    {
                       if (i < 0 || i >= image.height || j < 0 || j >= image.width) continue;

                            png_bytep neighbor_row = image.pixels[i];
                            png_bytep neighbor_px = &(neighbor_row[j * 4]);


                            if (neighbor_px[3] == 0) continue;


                            red += neighbor_px[0];
                            green += neighbor_px[1];
                            blue += neighbor_px[2];
                            alpha += neighbor_px[3];
                            count++;

                    }
                }


                if (count < kernel * 8) continue;

                red = (int) red / count;
                green = (int) green / count;
                blue = (int) blue / count;
                alpha = (int) alpha / count;

                px[0] = red;
                px[1] = green;
                px[2] = blue;
                px[3] = alpha;


            }

        }

    }
    return image;
}

