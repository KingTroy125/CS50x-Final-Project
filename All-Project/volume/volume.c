#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

// WAV file header structure (44 bytes)
typedef struct
{
    char riff_header[4];           // "RIFF" marker
    int32_t wav_size;               // Size of the file (excluding first 8 bytes)
    char wave_header[4];            // "WAVE" marker
    char fmt_header[4];             // "fmt " marker
    int32_t fmt_chunk_size;         // Size of format chunk
    int16_t audio_format;           // Audio format (1 = PCM)
    int16_t num_channels;           // Number of channels (1 = mono, 2 = stereo)
    int32_t sample_rate;            // Samples per second
    int32_t byte_rate;              // Bytes per second
    int16_t block_align;            // 2 = 16-bit mono, 4 = 16-bit stereo
    int16_t bits_per_sample;        // Bits per sample
    char data_header[4];            // "data" marker
    int32_t data_size;              // Size of data chunk
} wav_header;

int main(int argc, char *argv[])
{
    // Check command-line arguments
    if (argc != 4)
    {
        fprintf(stderr, "Usage: ./volume input.wav output.wav factor\n");
        return 1;
    }

    // Open input file
    FILE *input = fopen(argv[1], "r");
    if (input == NULL)
    {
        fprintf(stderr, "Could not open input file.\n");
        return 1;
    }

    // Open output file
    FILE *output = fopen(argv[2], "w");
    if (output == NULL)
    {
        fprintf(stderr, "Could not open output file.\n");
        fclose(input);
        return 1;
    }

    // Parse volume factor
    float factor = atof(argv[3]);

    // Read WAV header
    wav_header header;
    if (fread(&header, sizeof(wav_header), 1, input) != 1)
    {
        fprintf(stderr, "Could not read WAV header.\n");
        fclose(input);
        fclose(output);
        return 1;
    }

    // Write header to output file
    if (fwrite(&header, sizeof(wav_header), 1, output) != 1)
    {
        fprintf(stderr, "Could not write WAV header.\n");
        fclose(input);
        fclose(output);
        return 1;
    }

    // Buffer to store samples
    int16_t sample;

    // Read and modify samples
    while (fread(&sample, sizeof(int16_t), 1, input) == 1)
    {
        // Scale the sample
        sample *= factor;

        // Write modified sample
        if (fwrite(&sample, sizeof(int16_t), 1, output) != 1)
        {
            fprintf(stderr, "Error writing sample.\n");
            fclose(input);
            fclose(output);
            return 1;
        }
    }

    // Close files
    fclose(input);
    fclose(output);

    return 0;
}
