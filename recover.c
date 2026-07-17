#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("Usage: ./recover FILE\n");
        return 1;
    }
    FILE *file = fopen(argv[1], "r");

    uint8_t buffer[512];
    int jpegs = -1;

    char filename[8];
    FILE *file2;

    while (fread(&buffer, 1, 512, file) == 512)
    {
        // Check if its the start of a JPEG
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff &&
            (buffer[3] & 0xf0) == 0xe0)
        {
            jpegs++;
            if (jpegs != 0)
            {
                fclose(file2);
            }
            sprintf(filename, "%03i.jpg", jpegs);
            FILE *jpeg = fopen(filename, "w");
            file2 = jpeg;
            fwrite(&buffer, 1, 512, jpeg);
        }
        else
        {
            if (jpegs > -1)
            {
                fwrite(&buffer, 1, 512, file2);
            }
        }
    }
    fclose(file2);
    fclose(file);
}
