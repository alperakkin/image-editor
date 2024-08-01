#define DEFAULT_VALUE "found";

void help() {

    printf("----------------- Help -------------------\n\n");
    printf("Following command format should be used to run the editor:\n\n");
    printf("./image-editor -i input.png -<option> -o output.png\n\n");
    printf("------------------------------------------\n\n");
    printf("Use the image-editor with following options:\n\n");
    printf("-h: Help\n");
    printf("-i: Read Image File\n");
    printf("-o: Save Image File\n");
    printf("-g: Set pixels to grayscale\n");
    printf("-c: Set contrast\n");
    printf("-b: Set brightness\n");
    printf("--gaussian: Set Gaussian Blur\n");
    printf("--kernel-size: Kernel Size (Required By: Gaussian)\n");
    printf("--sigma: Sigma (Required By: Gaussian)\n");
    printf("-r: Resize Image\n");
    printf("--histogram: Get Histogram Of Channels\n");
    printf("-f: Color Filter\n");
    printf("--strength: Filter Strength (Required By: Color Filter)\n");
    printf("--opacity: Opacity\n");
    printf("--color: Color [Hex Value] (Required By: Color Filter)n");
    printf("-l: Add Image Layer\n");
    printf("--path: New Layer Image Path (Required By: Add Image Layer)\n");
    printf("--pos: Position Of The Image (Required By: Add Image Layer)\n");
    printf("--alpha-mask: Alpha Mask (Required By: Add Image Layer)\n");
    printf("\n");
    printf("-------------------------------------------\n\n");

}

char* find_argument(char* arg, char* argv[], int argc, bool raise)
{

    int index = 0;

    for (int i=0;i<argc;i++)
    {
        if (strcmp(arg, argv[i]) == 0) index=++i;

    }
    if (index==0 && raise)
    {
        help();

        char formatted_string[100];
        sprintf(formatted_string, "Please provide %s argument", arg);
        raise_error(formatted_string);

    }

    else if (index==0) {
        return NULL;
    }
    if (index > argc) return DEFAULT_VALUE;
    return argv[index];
}


void parse_args(int argc, char *argv[])
{

    Image image;
    Image output;



    if (find_argument("-h", argv, argc, false)) help();

    char* input_path = find_argument("-i", argv, argc, true);
    if (input_path) image = read_png_file(input_path);

    if (find_argument("-g", argv, argc, false)) grayscale(image);

    char* contrast_val = find_argument("-c", argv, argc, false);
    if (contrast_val)
    {
        float factor = (float) atof(contrast_val);
        output = contrast(image, factor);
    };

    char* brightness_ratio = find_argument("-b", argv, argc, false);
    if (brightness_ratio)
    {
        float ratio = (float) atof(brightness_ratio);
        brightness(image, ratio);
    }

    char* gauss= find_argument("--gaussian", argv, argc, false);
    if (gauss)
    {

        int kernel_size = (int) atof(find_argument("--kernel-size", argv, argc, true));
        float sigma = (float) atof(find_argument("--sigma", argv, argc, true));

        output = gaussian(image, kernel_size, sigma);

    }

    char* dimensions = find_argument("-r", argv, argc, false);
    if (dimensions)
    {
        char* size[2];
        split_args(dimensions, size, 'x');

        int width = (int) atof(size[0]);
        int height = (int) atof(size[1]);
        output = resize(image, width, height);
    }

    if (find_argument("--histogram", argv, argc, false))  histogram(image);

    if (find_argument("-f", argv, argc, false))
    {
        float strength = (float) atof(find_argument("--strength", argv, argc, true));
        char* color = find_argument("--color", argv, argc, true);

        output = filter(image, color, strength);
    }

    char* factor = find_argument("--opacity", argv, argc, false);
    if(factor) output = opacity(image, (float) atof(factor));

    char* layer = find_argument("-l", argv, argc, false);
    if (layer)
    {
        char* path = find_argument("--path", argv, argc, true);
        char* position = find_argument("--pos", argv, argc, true);
        int alpha = (int) atof(find_argument("--alpha-mask", argv, argc, true));

        char* size[2];
        split_args(position, size, 'x');

        int x = (int) atof(size[0]);
        int y = (int) atof(size[1]);

        Image patch = read_png_file(path);

        output = add_layer(image, patch, x, y, alpha);


    }

    if (find_argument("--crop", argv, argc, false))
    {



        int left;
        char* left_value = find_argument("--left", argv, argc, false);
        if(!left_value) left = 0; else left = (int) atof(left_value);

        int right;
        char* right_value = find_argument("--right", argv, argc, false);
        if(!right_value) right = 0; else right = (int) atof(right_value);

        int top;
        char* top_value = find_argument("--top", argv, argc, false);
        if(!top_value) top = 0; else top = (int) atof(top_value);

        int bottom;
        char* bottom_value = find_argument("--bottom", argv, argc, false);
        if(!bottom_value) bottom = 0; else bottom = (int) atof(bottom_value);


        output = crop(image, left, right, top, bottom);
    }


    OUTPUT_PATH = find_argument("-o", argv, argc, true);
    write_png_file(OUTPUT_PATH, output);







}