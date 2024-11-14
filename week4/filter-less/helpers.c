#include "helpers.h"
#include <math.h>
#include <stdio.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int o = 0; o < height; o++)
    {
        for (int l = 0; l < width; l++)
        {
            BYTE x = image[o][l].rgbtBlue;
            BYTE y = image[o][l].rgbtGreen;
            BYTE z = image[o][l].rgbtRed;
            float p = (x + y + z) / 3.0;
            BYTE t = round(p);
            image[o][l].rgbtBlue = t;
            image[o][l].rgbtGreen = t;
            image[o][l].rgbtRed = t;
        }
    }
}
// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    for (int o = 0; o < height; o++)
    {
        for (int l = 0; l < width; l++)
        {
            float sepiaR = .393 * image[o][l].rgbtRed + .769 * image[o][l].rgbtGreen +
                           .189 * image[o][l].rgbtBlue;
            float sepiaG = .349 * image[o][l].rgbtRed + .686 * image[o][l].rgbtGreen +
                           .168 * image[o][l].rgbtBlue;
            float sepiaB = .272 * image[o][l].rgbtRed + .534 * image[o][l].rgbtGreen +
                           .131 * image[o][l].rgbtBlue;
            BYTE t1, t2, t3;
            if (sepiaR >= 255)
            {
                t1 = 255;
            }
            else
            {
                t1 = round(sepiaR);
            }
            if (sepiaG >= 255)
            {
                t2 = 255;
            }
            else
            {
                t2 = round(sepiaG);
            }
            if (sepiaB >= 255)
            {
                t3 = 255;
            }
            else
            {
                t3 = round(sepiaB);
            }
            image[o][l].rgbtRed = t1;
            image[o][l].rgbtGreen = t2;
            image[o][l].rgbtBlue = t3;
        }
    }
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    for (int o = 0; o < height; o++)
    {
        for (int l = 0; l < round(width / 2); l++)
        {
            RGBTRIPLE temp = image[o][l];
            image[o][l] = image[o][(width - 1) - l];
            image[o][(width - 1) - l] = temp;
        }
    }
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE temp_image[height][width];
    int totalR = 0;
    int totalG = 0;
    int totalB = 0;
    float counter = 0.00;
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            totalR = 0;
            totalG = 0;
            totalB = 0;
            counter = 0.00;

            for (int x = -1; x < 2; x++)
            {
                for (int y = -1; y < 2; y++)
                {
                    int currentx = i + x;
                    int currenty = j + y;
                    if (currentx >= 0 && currentx < height && currenty >= 0 && currenty < width)
                    {
                        totalR += image[currentx][currenty].rgbtRed;
                        totalG += image[currentx][currenty].rgbtGreen;
                        totalB += image[currentx][currenty].rgbtBlue;
                        counter++;
                    }
                }
            }
            temp_image[i][j].rgbtRed = round((float) totalR / counter);
            temp_image[i][j].rgbtGreen = round((float) totalG / counter);
            temp_image[i][j].rgbtBlue = round((float) totalB / counter);
        }
    }
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j] = temp_image[i][j];
        }
    }
}
