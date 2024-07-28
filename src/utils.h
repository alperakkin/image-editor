#define HISTOGRAM_LENGTH 25
#include <ctype.h>

typedef struct {
    char* name;
    char* value;
    int histogram[HISTOGRAM_LENGTH];
    int max;
    int min;
} ColorMode;

typedef struct {
    char* str;
    double number;
} Arg;

bool is_numeric(const char *str) {
    char *endptr;
    int errno = 0;

    if (!isdigit(*str) && *str != '.') {
        return false;
    }
    double val = strtod(str, &endptr);

    if (errno != 0 || *endptr != '\0' || str == endptr) {
        return false;
    }
    return true;
}

Arg* split_args(char* args, int count, char seperator)
{
    char *token;
    int ind = 0;
    Arg* arguments = malloc(count * sizeof(Arg));


    token = strtok(args, &seperator);


    while (token != NULL)
    {

        if (is_numeric(token) == true) {

            arguments[ind++].number = atof(token);

        }
        else {
            arguments[ind++].str = token;
        }

        token = strtok(NULL, &seperator);
    }

    return arguments;

}


void print_color(ColorMode color, char* text)
{
    printf("\033[%sm%s\033[0m", color.value, text);
}

void print_color_block(int index, ColorMode color)
{
    char* block = "\xE2\x96\x89";
    int bin_width = (color.max - color.min + 10 - 1)/10;
    printf("|");
        for (int col=0; col<25; col++)
        {
            if (color.histogram[col] >= index * 50 * bin_width  && color.histogram[col] != 0)
            {
                print_color(color, block);
            }
            else
            {
                printf(" ");
            }
        }


}

void print_x_axis(ColorMode red, ColorMode green, ColorMode blue)
{
    printf("--------------------------->\t\t");
    printf("--------------------------->\t\t");
    printf("--------------------------->\t\t\n");
    // x axis
    printf("   50   100   150   200   ");
    printf("\t\t");
    printf("   50   100   150   200   ");
    printf("\t\t");
    printf("   50   100   150   200   \n");


    printf("\t   ");
    print_color(red, "Red");
    printf("\t\t\t\t\t   ");
    print_color(green, "Green");
    printf("\t\t\t\t   ");
    print_color(blue, "Blue");

}

void print_table(ColorMode red, ColorMode green, ColorMode blue)
{
    system("clear");


    printf("^\t\t\t\t\t^\t\t\t\t\t^\t\n");
    for (int i=10; i>=0;i--)
    {
        // RED

        print_color_block(i, red);

        // GREEN
        printf("\t\t");
        print_color_block(i, green);


        // BLUE
        printf("\t\t");
        print_color_block(i, blue);
        printf("\n");
    }


    print_x_axis(red, green, blue);
    printf("\n\n\n");
}

void hex_to_rgb(const char* hex_code, int* r, int* g, int* b) {

    if (hex_code[0] == '#') {
        hex_code++;
    }

    sscanf(hex_code, "%02x%02x%02x", r, g, b);
}