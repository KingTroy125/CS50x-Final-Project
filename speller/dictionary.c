// Implements a dictionary's functionality

#include <ctype.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <strings.h>

#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// TODO: Choose number of buckets in hash table
const unsigned int N = 26;

// Hash table
node *table[N];

// Declare variables
unsigned int word_count;
unsigned int hash_value;

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    // Hash the word to obtain the hash_value (aka bucket position)
    hash_value = hash(word);

    // Point cursor to the first node
    node *cursor = table[hash_value];

    // Go trough the linked list
    while (cursor != 0)
    {
        if (strcasecmp(word, cursor->word) == 0)
        {
            return true;
        }

        cursor = cursor->next;
    }
    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    // This Hash function uses the Division Modulo Method retrieved from https://www.digitalbithub.com/learn/division-modulo-method-hashing-technique and has been adapted for this particular problem as explained below.

    // This Hash function takes the sum of the ASCII value of all the word characters (char_sum) and divide it by the number of buckets (N). The remainder represents the bucket that the word belongs to.

    unsigned long char_sum = 0;

    for (int i = 0; i < strlen(word); i++)
    {
        char_sum += tolower(word[i]);
    }

    return char_sum % N;
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    // Load the dictionary
    FILE *file = fopen(dictionary, "r");

    // Verify if file can be opened
    if (file == NULL)
    {
        printf("Unable to open %s\n", dictionary);
        return false;
    }

    // Declare a container variable
    char word[LENGTH + 1];

    // Scan dictionary for strings up until EOF
    while (fscanf(file, "%s", word) != EOF)
    {
        // Allocate memory for the new node
        node *n = malloc(sizeof(node));

        // Check if memmory allocation was successful
        if (n == NULL)
        {
            return false;
        }

        // Copy word into node
        strcpy(n->word, word);
        hash_value = hash(word);
        n->next = table[hash_value];
        table[hash_value] = n;
        word_count++;
    }

    fclose(file);
    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    if (word_count > 0)
    {
        return word_count;
    }
    return 0;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    // Iterate through buckets
    for (int i = 0; i < N; i++)
    {
        // Set cursor to the start of the linked list
        node *cursor = table[i];

        // If coursor is not NULL, free memory
        while (cursor != NULL)
        {
            // Create temp
            node *tmp = cursor;

            // Move cursor to next node
            cursor = cursor->next;

            // Free up temp;
            free(tmp);
        }
    }
    return true;
}
