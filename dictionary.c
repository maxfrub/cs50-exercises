// Implements a dictionary's functionality

#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>

#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
} node;

void free_linked(node *cursor);

// TODO: Choose number of buckets in hash table
const unsigned int N = (LENGTH - 10) * (('Z' - 'A') * ((45 + 1) % 20));

// Hash table
node *table[N];

// TODO: Keep track of all the words
int words = 0;

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    int hash_value = hash(word);
    node *cursor = table[hash_value];
    while (cursor != NULL)
    {
        if (strcasecmp(cursor->word, word) == 0)
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
    // TODO: Improve this hash function
    int i = 0;
    unsigned int val = 0;

    while (word[i] != '\0')
    {
        if (word[i] != '\'')
        {
            val += toupper(word[i]) - ('A' * ((i + 1) % 20));
        }
        i++;
    }

    return val % N;
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    FILE *dict = fopen(dictionary, "r");
    if (dict == NULL)
    {
        return false;
    }

    char word[LENGTH + 1];

    while (fscanf(dict, "%s", word) != EOF)
    {
        node *n = malloc(sizeof(node));
        if (n == NULL)
        {
            return false;
        }

        strcpy(n->word, word);

        int i = hash(n->word);

        words++;

        if (table[i] != NULL)
        {
            n->next = table[i];
            table[i] = n;
        }
        else
        {
            table[i] = n;
            n->next = NULL;
        }
    }

    fclose(dict);

    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    return words;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    // TODO
    for (int i = 0; i < N; i++)
    {
        if (table[i] != NULL)
            free_linked(table[i]);
    }
    return true;
}

void free_linked(node *cursor)
{
    if (cursor == NULL)
    {
        return;
    }
    free_linked(cursor->next);

    free(cursor);
}
