// Implements a dictionary's functionality
#include <stdio.h>
#include <stdbool.h>

#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// Number of buckets in hash table
const unsigned int N = 1;

// Hash table
node *table[N];

// Returns true if word is in dictionary else false
bool check(const char *word)
{
    // TODO
    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    // TODO
    return 0;
}

// Loads dictionary into memory, returning true if successful, else: false
bool load(const char *dictionary)
{
    // TODO
    // Let's start by opening the file
    FILE *file_dict = fopen(dictionary, "r");
    if (file_dict == NULL)
    {
        printf("Not a valid file!\n");
        return 1; 
    }

    //char word[100];
    char word = malloc(46 * sizeof(char));

    while (fscanf(file_dict, "%s", word) != EOF)
    {
        // now you want to remove the trailing newline character
        // then create a node for every word

    }

    fclose(file_dict);
    free(word);

    return true;
}

// Returns number of words in dictionary if loaded else 0 if not yet loaded
unsigned int size(void)
{
    // TODO
    return 0;
}

// Unloads dictionary from memory, returning true if successful else false
bool unload(void)
{
    // TODO
    return false;
}
