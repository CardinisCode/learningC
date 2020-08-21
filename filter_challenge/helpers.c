#include "helpers.h"
#include <math.h>
#include <stdlib.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int row = 0; row < height; row++)
    {
        for (int col = 0; col < width; col++)
        {
            RGBTRIPLE current_pixel = image[row][col];
            double average = (current_pixel.rgbtBlue + current_pixel.rgbtGreen + current_pixel.rgbtRed) / 3.0;
            // int avg_int = (int) ceil(average);
            int avg_int = round(average);
            image[row][col].rgbtBlue = avg_int;
            image[row][col].rgbtGreen = avg_int;
            image[row][col].rgbtRed = avg_int;
        }
    }
    return;
}

        // -   sepiaRed = .393 * originalRed + .769 * originalGreen + .189 * originalBlue
        // -   sepiaGreen = .349 * originalRed + .686 * originalGreen + .168 * originalBlue
        // -   sepiaBlue = .272 * originalRed + .534 * originalGreen + .131 * originalBlue


// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    for (int row = 0; row < height; row++)
    {
        for (int col = 0; col < width; col++)
        {
            RGBTRIPLE current_pixel = image[row][col];
            // -   sepiaRed = .393 * originalRed + .769 * originalGreen + .189 * originalBlue
            int sepiaRed = round(0.393 * current_pixel.rgbtRed + 0.769 * current_pixel.rgbtGreen + 0.189 * current_pixel.rgbtBlue);
            // -   sepiaGreen = .349 * originalRed + .686 * originalGreen + .168 * originalBlue
            int sepiaGreen = round(0.349 * current_pixel.rgbtRed + 0.686 * current_pixel.rgbtGreen + 0.168 * current_pixel.rgbtBlue);
            // -   sepiaBlue = .272 * originalRed + .534 * originalGreen + .131 * originalBlue
            int sepiaBlue = round(0.272 * current_pixel.rgbtRed + 0.534 * current_pixel.rgbtGreen + 0.131 * current_pixel.rgbtBlue);

            if (sepiaRed > 255)
            {
                sepiaRed = 255;
            }

            if (sepiaGreen > 255)
            {
                sepiaGreen = 255;
            }

            if (sepiaBlue > 255)
            {
                sepiaBlue = 255;
            }

            image[row][col].rgbtRed = sepiaRed;
            image[row][col].rgbtGreen = sepiaGreen;
            image[row][col].rgbtBlue = sepiaBlue;
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    int midpoint = width / 2; 

    for (int row = 0; row < height; row++)
    {
        for (int col = 0; col < midpoint; col++)
        {
            RGBTRIPLE current_pixel = image[row][col];
            int swap_index = width - 1 - col; 
            RGBTRIPLE swap_pixel = image[row][swap_index];

            // Let's swap the pixels around
            RGBTRIPLE temp = image[row][col]; // current pixel -> temp
            current_pixel = image[row][swap_index]; // swap pixel -> current pixel
            swap_pixel = temp; 

            image[row][col] = current_pixel;
            image[row][swap_index] = swap_pixel;
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    //  RGBTRIPLE(*image)[width] = calloc(height, width * sizeof(RGBTRIPLE));
    RGBTRIPLE (*temp_image)[width] = calloc(height, width * sizeof(RGBTRIPLE));
    
    for (int row = 0; row < height; row++)
    {
        for (int col = 0; col < width; col++)
        {
            RGBTRIPLE current_pixel = image[row][col];
            int red = 0, green = 0, blue = 0; 
            double count = 0.0;

            // Let's draw the grid around the current pixel
            for (int r = -1; r <= 1; r++)
            {
                if (row + r < 0 || row + r >= height)
                {
                    continue;
                }

                for (int c = -1; c <= 1; c++)
                {
                    if (col + c < 0 || col + c >= width)
                    {
                        continue;
                    }
                    
                    RGBTRIPLE current_item = image[row + r][col + c];
                    red += current_item.rgbtRed; 
                    green += current_item.rgbtGreen;
                    blue += current_item.rgbtBlue;
                    count++; 
                }
            }

            int avg_red = (int) round(red / count);
            int avg_green = (int) round(green / count);
            int avg_blue = (int) round(blue / count);

            temp_image[row][col].rgbtRed = avg_red;
            temp_image[row][col].rgbtGreen = avg_green;
            temp_image[row][col].rgbtBlue = avg_blue;
            
        }
    }
    for (int r = 0; r < height; r++)
    {
        for (int c = 0; c < width; c++)
        {
            image[r][c] = temp_image[r][c];
        }
    }
    // image = temp_image;
    free(temp_image);
    return;
}