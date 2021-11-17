#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../libs/libbmp/libbmp.h"

void grayscale_img(bmp_img *img)
{
    bmp_pixel *px;

    printf("image size :%dx%d\n", img->img_header.biWidth, img->img_header.biHeight);

    for (size_t y = 0; y < (size_t)img->img_header.biHeight; y++)
    {
        for (size_t x = 0; x < (size_t)img->img_header.biWidth; x++)
        {
            px = &img->img_pixels[y][x];

            int gray = (px->red + px->green + px->blue) / 3;

            bmp_pixel_init(px, gray, gray, gray);
        }
    }
}

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        fprintf(stderr, "ERROR: command must be : ./image-to-ascii <filename>\n");
        exit(1);
    }

    bmp_img img;

    if (bmp_img_read(&img, argv[1]) < 0)
    {
        fprintf(stderr, "ERROR: unable to load image\n");
        exit(1);
    }

    grayscale_img(&img);
   

    bmp_img_write(&img, "grayscale.bmp");
    bmp_img_free(&img);

    return 0;
}