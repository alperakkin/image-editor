#include "argparse.h"

void help()
{

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
    printf("--color: Color [Hex Value]\n");
    printf("-l: Add Image Layer\n");
    printf("--path: New Layer Image Path (Required By: Add Image Layer)\n");
    printf("--pos: Position Of The Image (Required By: Add Image Layer)\n");
    printf("--alpha-mask: Alpha Mask (Required By: Add Image Layer)\n");
    printf("--crop: Crop Image\n");
    printf("--left: Pixels From left (Optional: If not provided left value will be evaluated as 0))\n");
    printf("--right: Pixels From right (Optional: If not provided right value will be evaluated as 0))\n");
    printf("--top: Pixels From top (Optional: If not provided top value will be evaluated as 0))\n");
    printf("--bottom: Pixels From bottom (Optional: If not provided bottom value will be evaluated as 0))\n");
    printf("--rotate: Rotate Image\n");
    printf("--invert: Invert Image\n");
    printf("--border: Add Borders\n");
    printf("--mask: Mask Color\n");
    printf("--threshold: Threshold\n");
    printf("--low: Low Value\n");
    printf("--high: Hight Value\n");
    printf("--edge: Edge Detection\n");
    printf("--template: Match Template\n");
    printf("--vignette: Apply Vignette\n");
    printf("\n");
    printf("-------------------------------------------\n\n");
}

char *find_argument(char *arg, bool raise)
{

    int index = 0;

    for (int i = 0; i < ARGC; i++)
    {
        if (strcmp(arg, ARGV[i]) == 0)
            index = ++i;
    }

    if (index == 0 && raise)
    {
        help();

        char formatted_string[100];
        sprintf(formatted_string, "Please provide %s argument", arg);
        raise_error(formatted_string);
    }
    else if (index == 0)
    {
        return NULL;
    }
    if (index > ARGC)
        return DEFAULT_VALUE;
    if (index == ARGC)
        return ARGV[index - 1];
    return ARGV[index];
}

void parse_args(int argc, char *argv[])
{

    Image image;
    Image output;

    extern char **ARGV;
    extern int ARGC;
    ARGV = argv;
    ARGC = argc;

    if (find_argument("-h", false))
        help();

    char *input_path = find_argument("-i", true);

    if (input_path)
        image = open_image(input_path);

    if (find_argument("-g", false))
        grayscale(image);

    char *contrast_val = find_argument("-c", false);
    if (contrast_val)
    {
        float factor = (float)atof(contrast_val);
        output = contrast(image, factor);
    };

    char *brightness_ratio = find_argument("-b", false);
    if (brightness_ratio)
    {
        float ratio = (float)atof(brightness_ratio);
        brightness(image, ratio);
    }

    char *gauss = find_argument("--gaussian", false);
    if (gauss)
    {

        int kernel_size = (int)atof(find_argument("--kernel-size", true));
        float sigma = (float)atof(find_argument("--sigma", true));

        output = gaussian(image, kernel_size, sigma);
    }

    char *dimensions = find_argument("-r", false);
    if (dimensions)
    {
        char *size[2];
        split_args(dimensions, size, 'x');

        int width = (int)atof(size[0]);
        int height = (int)atof(size[1]);
        output = resize(image, width, height);
    }

    if (find_argument("--histogram", false))
    {
        ColorMode red = {
            .name = "red",
            .value = "31",
            .min = 1000000,
            .max = 0,
            .histogram = {0}};
        ColorMode green = {
            .name = "green",
            .value = "32",
            .min = 1000000,
            .max = 0,
            .histogram = {0}};
        ColorMode blue = {
            .name = "blue",
            .value = "34",
            .min = 1000000,
            .max = 0,
            .histogram = {0}};
        histogram(image, &red, &green, &blue, 25);
        print_table(&red, &green, &blue);
    }

    if (find_argument("-f", false))
    {
        float strength = (float)atof(find_argument("--strength", true));
        char *color = find_argument("--color", true);

        output = filter(image, color, strength);
    }

    char *factor = find_argument("--opacity", false);
    if (factor)
        output = opacity(image, (float)atof(factor));

    char *layer = find_argument("-l", false);
    if (layer)
    {
        char *path = find_argument("--path", true);
        char *position = find_argument("--pos", true);
        int alpha = (int)atof(find_argument("--alpha-mask", true));

        char *size[2];
        split_args(position, size, 'x');

        int x = (int)atof(size[0]);
        int y = (int)atof(size[1]);

        Image patch = open_image(path);

        output = add_layer(image, patch, x, y, alpha);
    }

    if (find_argument("--crop", false))
    {

        int left;
        char *left_value = find_argument("--left", false);
        if (!left_value)
            left = 0;
        else
            left = (int)atof(left_value);

        int right;
        char *right_value = find_argument("--right", false);
        if (!right_value)
            right = 0;
        else
            right = (int)atof(right_value);

        int top;
        char *top_value = find_argument("--top", false);
        if (!top_value)
            top = 0;
        else
            top = (int)atof(top_value);

        int bottom;
        char *bottom_value = find_argument("--bottom", false);
        if (!bottom_value)
            bottom = 0;
        else
            bottom = (int)atof(bottom_value);

        output = crop(image, left, right, top, bottom);
    }

    char *rotate = find_argument("--rotate", false);
    if (rotate)
    {
        double angle = atof(rotate);
        output = rotate_image(image, angle);
    }

    if (find_argument("--invert", false))
        output = invert(image);

    char *border = find_argument("--border", false);
    if (border)
    {

        char *color = find_argument("--color", true);
        int border_size = (int)atof(border);
        output = add_border(image, color, border_size);
    }

    char *mask_opt = find_argument("--mask", false);
    if (mask_opt)
    {
        char *color = find_argument("--color", true);
        float threshold = (float)atof(find_argument("--threshold", true));
        output = mask(image, color, threshold);
    }

    char *edge_detection = find_argument("--edge", false);
    if (edge_detection)
    {
        find_argument("--threshold", true);
        int low = (int)atof(find_argument("--low", true));
        int high = (int)atof(find_argument("--high", true));
        output = edge(image, high, low);
    }

    char *template = find_argument("--template", false);
    if (template)
    {
        Image template_img = open_image(template);
        float threshold = (float)atof(find_argument("--threshold", true));

        match_template(image, template_img, threshold);
    }

    char *color_val = find_argument("--check-color", false);
    if (color_val)
    {
        float threshold = (float)atof(find_argument("--threshold", true));
        float ratio = check_color(image, color_val, threshold);
        printf("[Color: %s Fill Ratio: %f %%]\n", color_val, ratio * 10);
    }
    char *ratio_text = find_argument("--vignette", false);
    if (ratio_text)
    {
        float ratio = (float)atof(ratio_text);
        vignette(image, ratio);
    }

    OUTPUT_PATH = find_argument("-o", false);
    if (!output.name)
        output = image;
    if (OUTPUT_PATH)
        save_image(OUTPUT_PATH, output);
}