/****************************************************************************
 * dictionary.c
 *
 * Computer Science 50
 * Problem Set 5
 *
 * Implements a dictionary's functionality.
 ***************************************************************************/

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "dictionary.h"

#define MAXWORDLENGTH 45 

struct trieNode
{
    bool isWord;
    struct trieNode* children[27];  //An array of memory addresses to other trieNodes
};   

void add(char*, struct trieNode*);


/**
 * Returns true if word is in dictionary else false.
 */
bool check(const char* word)
{
    // TODO
    return false;
}

/**
 * Loads dictionary into memory.  Returns true if successful else false.
 */
bool load(const char* dictionary)
{
    //We'll load using a trie
    // The root node will have 27 characters (including '). 
    // Each child will point to a new node as necessary
    // root node should have word=false
    
    
    //Establish root
    struct trieNode* root = malloc(sizeof(struct trieNode));
    root->isWord=false;
    
    //Not sure if this is necessary yet
    for(int i=0; i<27; i++)
        root->children[i]=NULL;
        
    char currWord[MAXWORDLENGTH+2]; //add room for '\n' and '\0'
    
    FILE* file;
    file = fopen(dictionary,"r");
    
    if(file == NULL)
        return false;
    
    while(fgets(currWord, MAXWORDLENGTH+2, file)  )
        add(currWord, root);        //Pass in the memory address to the trie Node root       
        
    return false;
}

/**
 * Returns number of words in dictionary if loaded else 0 if not yet loaded.
 */
unsigned int size(void)
{
    // TODO
    return 0;
}

/**
 * Unloads dictionary from memory.  Returns true if successful else false.
 */
bool unload(void)
{
    // TODO
    return false;
}

void add(char* currWord, struct trieNode* parent)
{  
    if(currWord[0]=='\n')
        parent->isWord=true;
        
    else
    {
        int index;
        if(currWord[0]=='\'')
            index = 26;
        else
            index = currWord[0]-97;
        
        if(parent->children[index]==NULL)
        {
            struct trieNode* newNode = malloc(sizeof(struct trieNode));
            newNode->isWord = false;
            for(int i=0; i<27; i++)
                newNode->children[i]=NULL;
            parent->children[index] = newNode;

        }
        add(&currWord[1], parent->children[index]);
    }
}
