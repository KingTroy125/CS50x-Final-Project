#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

typedef uint8_t byte;

int main(void)
{
    // Open the raw file containing the deleted data
    FILE *raw = fopen("card.raw", "r");
    if (raw == NULL)
    {
        // Print an error message and return 1 if the raw file does not exist
        fprintf(stderr, "Could not open card.raw\n");
        return 1;
    }

    // Buffer to store data read from the raw file
    byte buffer[512];

    // Variable to keep track of the number of files recovered
    int file_count = 0;

    // File pointer for the current JPEG being written
    FILE *img = NULL;

    // Read the raw file 512 bytes at a time
    while (fread(buffer, sizeof(byte), 512, raw) == 512)
    {
        // Check if we have found the start of a new JPEG
        if (buffer[0] == 0xFF && buffer[1] == 0xD8 && buffer[2] == 0xFF && (buffer[3] & 0xF0) == 0xE0)
        {
            // If we are already writing an image, close it
            if (img != NULL)
            {
                fclose(img);
            }

            // Create a new filename for the JPEG
            char filename[8];
            sprintf(filename, "%03i.jpg", file_count++);

            // Open a new file to write the image data
            img = fopen(filename, "w");
            if (img == NULL)
            {
                // Print an error message if we can't open the new JPEG file
                fprintf(stderr, "Could not open %s for writing\n", filename);
                fclose(raw);
                return 2;
            }
        }

        // If we are writing an image, write the buffer to the file
        if (img != NULL)
        {
            fwrite(buffer, sizeof(byte), 512, img);
        }
    }

    // Close the last opened image file and raw file
    if (img != NULL)
    {
        fclose(img);
    }
    fclose(raw);

    return 0; // Exit successfully
}
