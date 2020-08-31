#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

typedef uint8_t BYTE;
typedef enum { false, true } bool;

int main(int argc, char *argv[])
{
    if (argc !=2)
    {
        // Usage: ./recover image
        fprintf(stderr, "Usage: ./recover image\n");
        return 1;
    }

    FILE *memory_card = fopen(argv[1], "r");
    if (memory_card == NULL)
    {
        fprintf(stderr, "Could not open %s.\n", argv[1]);
        return 1;
    }
    
    // Let's create the FAT blocks (512bytes) according to the FAT filesystem
    int block_size = 512; 
    BYTE buffer[block_size]; // buffer

    //int jpeg_index_array[50], potential_jpegs = 0; 
    char jpeg_filename[10]; 
    int current_jpeg = 0; 
    sprintf(jpeg_filename, "%03i.jpeg", current_jpeg);
    FILE *current_image = fopen(jpeg_filename, "w");
    bool found_jpeg = false;

    while (fread(buffer, block_size, 1, memory_card) == 1)
    {
        // // First 3 512byte blocks 
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0)
        {
            if (found_jpeg == false)
            {
                found_jpeg = true;
                fwrite(buffer, block_size, 1, current_image);
            }
            else
            {
                current_jpeg++;
                fclose(current_image);
                sprintf(jpeg_filename, "%03i.jpeg", current_jpeg);
                FILE *current_image = fopen(jpeg_filename, "w");
                fwrite(buffer, block_size, 1, current_image);
            }
            
        }
        else if (found_jpeg)
        {
            fwrite(buffer, block_size, 1, current_image);
        }
    }
    fclose(current_image);
    return 0;
}