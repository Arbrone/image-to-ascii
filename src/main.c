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

void convert_to_ascii(bmp_img *img)
{
    char *grayscale_order = "$@B%8&WM#*oahkbdpqwmZO0QLCJUYXzcvunxrjft/\\|()1{}[]?-_+~<>i!lI;:,\"^`'. ";

    int height = img->img_header.biHeight;
    int width = img->img_header.biWidth;

    // ouvrir un fichier
    FILE *output = fopen("output.txt", "w");

    // définir la taille d'un bloc
    #define BLOCK_HEIGHT 1
    #define BLOCK_WIDTH  1

    for (int y = height-1; y >= 0; y -= BLOCK_HEIGHT)
    {

        for (int x = 0; x < width; x += BLOCK_WIDTH)
        {
            bmp_pixel *px = &img->img_pixels[y][x];

            int gray = (px->red + px->green + px->blue) / 3;

            int index_normalized = gray%70;
            
            fprintf(output,"%c", grayscale_order[index_normalized]);


        }
            fprintf(output,"\n");
    }

    fclose(output);
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
    convert_to_ascii(&img);

    bmp_img_write(&img, "grayscale.bmp");
    bmp_img_free(&img);

    return 0;
}