#include <ctype.h>

#define HISTOGRAM_LENGTH 25


typedef struct {
  int width;
  int height;
  png_byte color_type;
  png_byte bit_depth;
  png_bytep *pixels;
} Image;


typedef struct {
    unsigned char R, G, B, A;
} Color;

typedef struct {
    char* name;
    char* value;
    int histogram[HISTOGRAM_LENGTH];
    int max;
    int min;
} ColorMode;





void split_args(char* expression, char** factors, char separator)
{
    char *token;
    int ind = 0;

    token = strtok(expression, &separator);

    while (token != NULL)
    {
        factors[ind++] = token;
        token = strtok(NULL, &separator);
    }
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

void raise_error(char* message)
{
    printf("\033[31mError: %s\n\033[0m", message);
    exit(1);
}

Color hex_to_rgb(char* hex_code)
{
    Color color = {
        .R=0,
        .G=0,
        .B=0,
        .A=0
    };

    if (hex_code == NULL || strlen(hex_code) < 7) raise_error("Invalid hex code.");

    if (hex_code[0] == '#') hex_code++;

    if (strlen(hex_code)==6)
    {
        if (sscanf(hex_code, "%02hhx%02hhx%02hhx", &color.R, &color.G, &color.B) != 3) raise_error("Failed to parse hex code.\n");
    }
    if (strlen(hex_code)==8)
    {
        if (sscanf(hex_code, "%02hhx%02hhx%02hhx%02hhx", &color.R, &color.G, &color.B, &color.A) != 4) raise_error("Failed to parse hex code.\n");
    }


    return color;
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
