#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[])
{
    
    if(argc != 2){
        fprintf(stderr, "ERROR: command must be : ./image-to-ascii <filename>\n");
        exit(1);
    }

    FILE *image;

    if((image = fopen(argv[1],"rb")) == NULL){
        fprintf(stderr, "ERROR: unable to load image\n");
        exit(1);
    }

    fclose(image);
    
    return 0;
}