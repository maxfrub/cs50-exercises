// Modifies the volume of an audio file

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

// Number of bytes in .wav header
const int HEADER_SIZE = 44;

void copy_head(FILE *input, FILE *output);
void change_volume(float v, FILE *input, FILE *output);

int main(int argc, char *argv[])
{
    // Check command-line arguments
    if (argc != 4)
    {
        printf("Usage: ./volume input.wav output.wav factor\n");
        return 1;
    }

    // Open files and determine scaling factor
    FILE *input = fopen(argv[1], "r");
    if (input == NULL)
    {
        printf("Could not open file.\n");
        return 1;
    }

    FILE *output = fopen(argv[2], "w");
    if (output == NULL)
    {
        printf("Could not open file.\n");
        return 1;
    }

    float factor = atof(argv[3]);

    // Copy header from input file to output file
    copy_head(input, output);

    // Read samples from input file and write updated data to output file
    change_volume(factor, input, output);

    // Close files
    fclose(input);
    fclose(output);
}

void copy_head(FILE *input, FILE *output)
{
    char c;
    for (int i = 0; i < HEADER_SIZE; i++)
    {
        fread(&c, sizeof(char), 1, input);
        fwrite(&c, sizeof(char), 1, output);
    }
}

void change_volume(float v, FILE *input, FILE *output)
{
    int16_t c;
    while (fread(&c, sizeof(int16_t), 1, input) != 0)
    {
        c *= v;
        fwrite(&c, sizeof(int16_t), 1, output);
    }
}
