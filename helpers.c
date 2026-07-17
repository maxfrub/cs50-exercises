#include "helpers.h"
#include <math.h>
#include <stdio.h>

typedef struct {
    float gx;
    float gy;
} sobel;

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // Calculate average
            int average = round((image[i][j].rgbtRed + image[i][j].rgbtGreen + image[i][j].rgbtBlue) / 3.0);
            // Set color
            image[i][j].rgbtRed = average;
            image[i][j].rgbtGreen = average;
            image[i][j].rgbtBlue = average;
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE temp_img[height][width];
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            temp_img[i][j].rgbtRed = image[i][j].rgbtRed;
            temp_img[i][j].rgbtGreen = image[i][j].rgbtGreen;
            temp_img[i][j].rgbtBlue = image[i][j].rgbtBlue;
        }
    }
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][width - 1 - j].rgbtRed = temp_img[i][j].rgbtRed;
            image[i][width - 1 - j].rgbtGreen = temp_img[i][j].rgbtGreen;
            image[i][width - 1 - j].rgbtBlue = temp_img[i][j].rgbtBlue;
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE temp_img[height][width];
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            temp_img[i][j].rgbtRed = image[i][j].rgbtRed;
            temp_img[i][j].rgbtGreen = image[i][j].rgbtGreen;
            temp_img[i][j].rgbtBlue = image[i][j].rgbtBlue;
        }
    }
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int r = 0;
            int g = 0;
            int b = 0;
            float reps = 0.0;

            for (int k = -1; k < 2; k++)
            {
                for (int n = -1; n < 2; n++)
                {
                    if (i + k >= 0 && i + k < height && j + n >= 0 && j + n < width)
                    {
                        r += temp_img[i + k][j + n].rgbtRed;
                        g += temp_img[i + k][j + n].rgbtGreen;
                        b += temp_img[i + k][j + n].rgbtBlue;
                        reps++;
                    }
                }
            }
            image[i][j].rgbtRed = round(r / reps);
            image[i][j].rgbtGreen = round(g / reps);
            image[i][j].rgbtBlue = round(b / reps);
        }
    }
    return;
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE temp_img[height][width];
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            temp_img[i][j].rgbtRed = image[i][j].rgbtRed;
            temp_img[i][j].rgbtGreen = image[i][j].rgbtGreen;
            temp_img[i][j].rgbtBlue = image[i][j].rgbtBlue;
        }
    }
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            sobel r;
            sobel g;
            sobel b;

            r.gx = 0;
            r.gy = 0;
            g.gx = 0;
            g.gy = 0;
            b.gx = 0;
            b.gy = 0;

            for (int k = -1; k < 2; k++)
            {
                for (int n = -1; n < 2; n++)
                {
                    sobel in;
                    in.gx = n;
                    in.gy = n;
                    if (k == 0)
                    {
                        in.gx += in.gx;
                        in.gy = 0;
                    }
                    if (n == 0)
                    {
                        if (k == -1)
                            in.gy = -2;
                        else if (k == 1)
                            in.gy = 2;
                    }
                    if (n == 1 && k == -1)
                        in.gy = -1;
                    else if (n == -1 && k == 1)
                        in.gy = 1;

                    if (i + k >= 0 && i + k < height && j + n >= 0 && j + n < width)
                    {
                        r.gx += temp_img[i + k][j + n].rgbtRed * in.gx;
                        g.gx += temp_img[i + k][j + n].rgbtGreen * in.gx;
                        b.gx += temp_img[i + k][j + n].rgbtBlue * in.gx;
                        r.gy += temp_img[i + k][j + n].rgbtRed * in.gy;
                        g.gy += temp_img[i + k][j + n].rgbtGreen * in.gy;
                        b.gy += temp_img[i + k][j + n].rgbtBlue * in.gy;
                    }
                }
            }
            int value = round(sqrt(r.gx * r.gx + r.gy * r.gy));
            if (value > 255)
            {
                value = 255;
            }
            image[i][j].rgbtRed = value;
            value = round(sqrt(g.gx * g.gx + g.gy * g.gy));
            if (value > 255)
            {
                value = 255;
            }
            image[i][j].rgbtGreen = value;
            value = round(sqrt(b.gx * b.gx + b.gy * b.gy));
            if (value > 255)
            {
                value = 255;
            }
            image[i][j].rgbtBlue = value;
        }
    }
    return;
}
