#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, string argv[])
{
    // Check for correct number of command-line arguments
    if (argc != 2)
    {
        printf("Usage: ./caesar key\n");
        return 1;
    }

    // Validate that the key is a positive integer
    for (int i = 0; argv[1][i] != '\0'; i++)
    {
        if (!isdigit(argv[1][i]))
        {
            printf("Usage: ./caesar key\n");
            return 1;
        }
    }

    // Convert key to an integer
    int key = atoi(argv[1]);

    // Prompt user for plaintext
    string plaintext = get_string("plaintext: ");

    printf("ciphertext: ");

    // Iterate through each character in the plaintext
    for (int i = 0, len = strlen(plaintext); i < len; i++)
    {
        char c = plaintext[i];

        // Encrypt uppercase letters
        if (isupper(c))
        {
            printf("%c", (((c - 'A') + key) % 26) + 'A');
        }
        // Encrypt lowercase letters
        else if (islower(c))
        {
            printf("%c", (((c - 'a') + key) % 26) + 'a');
        }
        // Non-alphabetic characters remain unchanged
        else
        {
            printf("%c", c);
        }
    }

    printf("\n");
    return 0;
}
