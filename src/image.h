#include <stdlib.h>
#include <stdio.h>
#include <png.h>



typedef struct {
  int width;
  int height;
  png_byte color_type;
  png_byte bit_depth;
  png_bytep *pixels;
} Image;

Image read_png_file(const char *FILENAME) {
  FILE *fp = fopen(FILENAME, "rb");

  Image image;

  png_structp png = png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
  if(!png) abort();

  png_infop info = png_create_info_struct(png);
  if(!info) abort();

  if(setjmp(png_jmpbuf(png))) abort();

  png_init_io(png, fp);

  png_read_info(png, info);

  image.width      = png_get_image_width(png, info);
  image.height     = png_get_image_height(png, info);
  image.color_type = png_get_color_type(png, info);
  image.bit_depth  = png_get_bit_depth(png, info);

  // Read any color_type into 8bit depth, RGBA format.
  // See http://www.libpng.org/pub/png/libpng-manual.txt

  if(image.bit_depth == 16)
    png_set_strip_16(png);

  if(image.color_type == PNG_COLOR_TYPE_PALETTE)
    png_set_palette_to_rgb(png);

  // PNG_COLOR_TYPE_GRAY_ALPHA is always 8 or 16bit depth.
  if(image.color_type == PNG_COLOR_TYPE_GRAY && image.bit_depth < 8)
    png_set_expand_gray_1_2_4_to_8(png);

  if(png_get_valid(png, info, PNG_INFO_tRNS))
    png_set_tRNS_to_alpha(png);

  // These color_type don't have an alpha channel then fill it with 0xff.
  if(image.color_type == PNG_COLOR_TYPE_RGB ||
     image.color_type == PNG_COLOR_TYPE_GRAY ||
     image.color_type == PNG_COLOR_TYPE_PALETTE)
    png_set_filler(png, 0xFF, PNG_FILLER_AFTER);

  if(image.color_type == PNG_COLOR_TYPE_GRAY ||
     image.color_type == PNG_COLOR_TYPE_GRAY_ALPHA)
    png_set_gray_to_rgb(png);

  png_read_update_info(png, info);

  image.pixels = (png_bytep*)malloc(sizeof(png_bytep) * image.height);
  for(int y = 0; y < image.height; y++) {
    image.pixels[y] = (png_byte*)malloc(png_get_rowbytes(png,info));
  }

  png_read_image(png, image.pixels);

  fclose(fp);

  png_destroy_read_struct(&png, &info, NULL);

  return image;
}


Image alloc_image(image_height, image_width){
  Image new_image;
  new_image.width = image_width;
  new_image.height = image_height;
  new_image.pixels = (png_bytep*) malloc(sizeof(png_bytep) * image_height);
  for(int y = 0; y < image_height; y++) {
        new_image.pixels[y] = (png_byte*) malloc(sizeof(png_byte) * image_width * 4 );

  }
  return new_image;
}

void free_image(Image image)
{
  for(int y = 0; y < image.height; y++) {
    free(image.pixels[y]);
  }
  free(image.pixels);


}

void write_png_file(const char *FILENAME, Image image)
{
  int y;

  FILE *fp = fopen(FILENAME, "wb");
  if(!fp) abort();

  png_structp png = png_create_write_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
  if (!png) abort();


  png_infop info = png_create_info_struct(png);
  if (!info) abort();


  if (setjmp(png_jmpbuf(png))) abort();


  png_init_io(png, fp);

  png_set_IHDR(
    png,
    info,
    image.width, image.height,
    8,
    PNG_COLOR_TYPE_RGBA,
    PNG_INTERLACE_NONE,
    PNG_COMPRESSION_TYPE_DEFAULT,
    PNG_FILTER_TYPE_DEFAULT
  );
  png_write_info(png, info);

  if (!image.pixels) abort();


  png_write_image(png, image.pixels);
  png_write_end(png, NULL);

  free_image(image);

  fclose(fp);

  png_destroy_write_struct(&png, &info);
}

