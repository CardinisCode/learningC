// Implements a dictionary's functionality
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>

#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// Number of buckets in hash table
const unsigned int HASHTABLE_SIZE = 100;

// Hash table
node *table[HASHTABLE_SIZE];

int number_words = 0;

// Returns true if word is in dictionary else false
bool check(const char *word)
{
    // #1: Let's get the hash index for our parameter: word. 
    int hash_index = hash(word);
    printf("Inside my check function: word %s\t hash: %i\n", word, hash_index);

    // #2: Access linked list at that index in the hashtable:
    node *cursor = table[hash_index];
    printf("Current word: %s\n", cursor->word);

    // #3: Traverse the linked list, looking for 'word'
    while(cursor != NULL)
    {
        // If the word at the current node matches our 'word' parameter:
        if (strcasecmp(cursor->word, word) == 0)
        {
            printf("Current word: %s found in the dictionary\n", word);
            return true;
        }
        else
        {
            // Otherwise, we advance the cursor:
            cursor = cursor->next;
            printf("The next word in the linked list: %s\n", cursor->word);
        }
    }
    printf("Current word: %s NOT found in the dictionary!\n", word);
    return false;
}

// Hashes word to a number
// Sources for hash function: 
// 1 - http://www.cse.yorku.ca/~oz/hash.html 
// 2 - https://gist.github.com/choaimeloo/ffb96f7e43d67e81f0d44c08837f5944
unsigned int hash(const char *word)
{
    unsigned long hash_code = 5381; 

    for (int i = 0, n = strlen(word); i < n; i++)
    {
        hash_code = (hash_code << 2) ^ word[i];
    }
    if (hash_code > HASHTABLE_SIZE - 1)
    {
        return hash_code % HASHTABLE_SIZE;
    }
    return hash_code;
}

// Loads dictionary into memory, returning true if successful, else: false
bool load(const char *dictionary)
{
    // Let's start by opening the file
    FILE *file_dict = fopen(dictionary, "r");
    if (file_dict == NULL)
    {
        printf("Not a valid file!\n");
        return 1; 
    }

        //char word[100];
    char *current_word = malloc(46 * sizeof(char));



    printf("Dictionary\n");
    while (fscanf(file_dict, "%s", current_word) != EOF)
    {
        //printf("Word: %s\t", current_word);
        // We need to create a node for every word

        node *n = malloc(sizeof(node));
        if (n == NULL)
        {
            // unload();
            return 1;
        }

        strcpy(n->word, current_word);
        n->next = NULL;

        // Now to use our hash function to create a hash index:
        int hash_index = hash(n->word);
        //printf("Hash Index: %i\n", hash_index);
        node *head_node = table[hash_index];
        
        // If our head node is empty, then we just need to start a linked list at this location
        if (head_node == NULL)
        {
            table[hash_index] = n;
            number_words++;
        }
        // Otherwise we just need to add the current node into the linked list at this index
        else 
        {
            n->next = table[hash_index];
            table[hash_index] = n;
            number_words++;
        }
    }
    printf("\n");

    fclose(file_dict);
    free(current_word);

    return true;
}


// Returns number of words in dictionary if loaded else 0 if not yet loaded
unsigned int size(void)
{
    printf("There are %i number of words in this dictionary!\n", number_words);
    return number_words;
}

// Unloads dictionary from memory, returning true if successful else false
bool unload(void)
{
    // TODO
    return false;
}


