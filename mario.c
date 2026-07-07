#include <stdio.h>
#include <cs50.h>

void build(int h);

int main(void)
{
    int height;
    do
    {
        height = get_int("Height: ");
    }
    while (height < 1);

    build(height);
}


void build(int h)
{
    for (int i = h; i > 0; i--)
    {
        for (int k = i - 1; k > 0; k--)
        {
            printf(" ");
        }
        for (int j = i; j <= h; j++)
        {
            printf("#");
        }
        printf("\n");
    }
}
