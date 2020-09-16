// Implements a dictionary's functionality
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <strings.h>
#include <stdlib.h>
#include <ctype.h>

#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// Number of buckets in hash table
// Let's create 100 buckets to optimize for speed
const unsigned int HASHTABLE_SIZE = 100;

// Hash table
node *table[HASHTABLE_SIZE];

// To keep count of every word I add to the dictionary as I go along
int number_words = 0;

// Returns true if word is in dictionary else false
bool check(const char *word)
{
    // #1: Let's convert our word to lowercase letters
    char *word_copy = malloc(46 * sizeof(char));
    int word_length = strlen(word);

    for (int i = 0; i < word_length; i++)
    {
        word_copy[i] = tolower(word[i]);
    }
    word_copy[word_length] = '\0';

    // #2: Let's get the hash index for our parameter: word.
    int hash_index = hash(word_copy);

    // #3: Access linked list at that index in the hashtable:
    node *cursor = table[hash_index];

    // #4: Traverse the linked list, looking for 'word'
    while(cursor != NULL)
    {
        // If the word at the current node matches our 'word' parameter:
        if (strcasecmp(cursor->word, word_copy) == 0)
        {
            //printf("Current word: %s found in the dictionary\n", word);
            free(word_copy);
            return true;
        }
        else
        {
            // Otherwise, we advance the cursor:
            cursor = cursor->next;
            //printf("The next word in the linked list: %s\n", cursor->word);
        }
    }
    //printf("Current word: %s NOT found in the dictionary!\n", word);
    free(word_copy);
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
    
    // Every hash must be within the range 0 -> n - 1
    // Since we're using 100 buckets and our dictionaries files
    // will have far more than 100 words, let's ensure our resulting hash code stays
    // well within the accepted range -> using mod:
    if (hash_code > HASHTABLE_SIZE - 1)
    {
        return hash_code % HASHTABLE_SIZE;
    }

    // If it's within the default range by default, 
    //  it goes through without modification:
    return hash_code;
}

// Loads dictionary into memory, returning true if successful, else: false
bool load(const char *dictionary)
{
    // Let's start by opening the file & checking it has opened successfully:
    FILE *file_dict = fopen(dictionary, "r");
    if (file_dict == NULL)
    {
        printf("Not a valid file!\n");
        return 1;
    }

    char *current_word = malloc(46 * sizeof(char));

    // Now we need to scan through every line of the file, until we reach the end of file (EOF)
    // Our goal is to "grab" the word on every line and add it to our dictionary
    while (fscanf(file_dict, "%s", current_word) != EOF)
    {
        // To do: 
        // #1: We need to create a node for every word & ensure it gets created successfully:
        node *n = malloc(sizeof(node));
        if (n == NULL)
        {
            // If not, then we need to free up the memory we've allocated
            unload();
            return 1;
        }

        // #2: We Add / copy the current word (from the file) (in)to the current node
        strcpy(n->word, current_word);
        n->next = NULL;

        // #3: We need to find which slot (within our array within the table) to put the current word
        // To do this: 

        // #3.1: We use our hash function to create a hash index:
        int hash_index = hash(n->word);

        // #3.2 Using the hash index, we create the head of the node 
        node *head_node = table[hash_index];

        // #4: We can now add items to our head node

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
    // #5: We're done, so we can close the file and free up any allocated memory we no longer need:
    fclose(file_dict);
    free(current_word);

    return true;
}


// Returns number of words in dictionary if loaded else 0 if not yet loaded
unsigned int size(void)
{
    // We've been keeping track of every word added our dictionary
    // so we can just return this count here:
    return number_words;
}

// Unloads dictionary from memory, returning true if successful else false
bool unload(void)
{
    // For every node in our table:
    for (int i = 0; i < HASHTABLE_SIZE; i++)
    {
        // We set our cursor to point to the head node (found at table[i])
        node *cursor = table[i];

        // Now we have our linked list at the current slot in the array
        // We can iterate through the linked list and free up every node 
        // in the list, whilst ensuring we don't accidentally lose any 
        // nodes in the process -> we don't want memory leaks. 
        while (cursor != NULL)
        {
            node *tmp = cursor;
            cursor = cursor->next;
            free(tmp);
        }
    }
    // At this point we've reached the end of every array in our table
    // So we've been successful and can return true. 
    return true;
}
