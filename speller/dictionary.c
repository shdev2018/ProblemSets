// Implements a dictionary's functionality
#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "dictionary.h"


typedef struct node
{
    bool isword;
    struct node *chars[27];
} node;



node *root = NULL;
int dictionarysize = 0;
bool loaded = false;


bool freetrie(node *parent);


// Loads dictionary into memory, returning true if successful else false
bool load(const char *dictionary)
{
    // Open the dictionary file for reading
    FILE *fp = fopen(dictionary, "r");

    // Check to make sure file has been read
    if (fp == NULL)
    {
        return false;
    }

    // Create root node
    root = (node *)malloc(sizeof(node));
    if (root == NULL)
    {
        return false;
    }
    root->isword = false;
    memset(root->chars, 0x00, sizeof(node *) * 27);

    // Initialize
    int pos, c, index, words = 0;
    char word[LENGTH];

    // Read in each word from Dictionary
    while (fscanf(fp, "%s", word) != EOF)
    {
        // Point temp to root
        node *temp = root;
        // Build trie char by char
        for (index = 0; index < strlen(word); index++)
        {
            c = word[index];

            // Get correct node ptr
            if (c == '\'' && index > 0)
            {
                pos = 26;
            }
            else if (islower(c))
            {
                pos = c - 97;
            }
            // If destination node doesn't already exist, create node
            if (temp->chars[pos] == NULL)
            {
                temp->chars[pos] = (node *)malloc(sizeof(node));
                if (temp->chars[pos] == NULL)
                {
                    return false;
                }
                else
                {
                    temp = temp->chars[pos];
                    temp->isword = false;
                    memset(temp->chars, 0x00, sizeof(node *) * 27);
                }
            }
            else
            {
            // Point to next/new node
            temp = temp->chars[pos];
            }
        }
        // set last node to isword, prepare for new word
        temp->isword = true;
        words++;
        pos = -1;
    }
    // Close stream
    fclose(fp);
    dictionarysize = words;

    // Success
    loaded = true;
    return true;


}




// Returns true if word is in dictionary else false
bool check(const char *word)
{
    int pos, c, index;
    node *trav = root;

    for (index = 0; index < strlen(word); index++)
    {
        c = word[index];

        // Get correct node ptr
        if (c == '\'' && index > 0)
        {
            pos = 26;
        }
        else if (isupper(c))
        {
            pos = c - 65;
        }
        else if (islower(c))
        {
            pos = c - 97;
        }

        if (trav->chars[pos] == NULL)
        {
            return false;
        }
        else
        {
            trav = trav->chars[pos];
        }
    }

    if (trav->isword)
    {
        return true;
    }
    else
    {
        return false;
    }

}




// Returns number of words in dictionary if loaded else 0 if not yet loaded
unsigned int size(void)
{
    if (loaded)
    {
        return dictionarysize;
    }
    else
    {
        return 0;
    }
}




// Unloads dictionary from memory, returning true if successful else false
bool unload(void)
{
    if (freetrie(root))
    {
        return true;
    }
    else
    {
        return false;
    }
}


bool freetrie(node *parent)
{
    for (int i = 0; i < 27; i++)
    {
        if (parent->chars[i] != NULL)
        {
            freetrie(parent->chars[i]);
        }
    }
    free(parent);
    return true;
}