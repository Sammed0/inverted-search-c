/* File Name   : create_db.c
   Functions   : create_db(), insert_word(), index_find()
   Name        : Sammed Kuranagi
   Date        : 24-04-2026
   Description : This source file contains functions used to create the
                 database by reading words from files and inserting them into
                 the hash table using linked list nodes.
*/

#include "invt.h"

// Function to create database by reading all files in file linked list
int create_db(ht_arr *ht_table, flist *head)
{
    flist *temp = head;          // Temporary pointer to traverse file list
    char word[20];              // Buffer to store each word from file

    while(temp != NULL)
    { 
        // Open file in read mode
        FILE *fp = fopen(temp->data, "r");

        if(fp != NULL)
        {
            // Read words one by one from file
            while(fscanf(fp, "%s", word) == 1)
            {
                // Insert word into hash table
                if(insert_word(ht_table, word, temp->data) == FAILURE)
                {
                    return FAILURE;
                }
            } 

            // Close file after reading
            fclose(fp); 
        }
        else
        {
            // File opening failed
            return FAILURE;
        }

        // Move to next file node
        temp = temp->link;
    }

    return SUCCESS;
}


// Function to find index based on first character of word
int index_find(const char ch)
{
    // If lowercase alphabet
    if(ch >= 'a' && ch <= 'z')
    {
        return ch - 'a';
    }

    // If uppercase alphabet
    else if(ch >= 'A' && ch <= 'Z')
    {
        char lower = tolower(ch);
        return lower - 'a';
    }

    // If digit
    else if(isdigit(ch))
    {
        return 26;
    }

    // Special characters
    else
    {
        return 27;
    }
}


// Function to insert word into hash table
int insert_word(ht_arr * ht_table, const char *word, const char *filename)
{
    // Find index using first letter
    int index = index_find(word[0]); 

    // Get head of that index linked list
    m_node *main = ht_table[index].head;

    // Traverse main nodes
    while(main != NULL)
    {
        // If word already exists
        if(strcmp(word, main->word) == 0)
        {
            s_node *sub = main->s_link;

            // Traverse sub nodes (file list)
            while(sub != NULL)
            {  
                // If same file found
                if(strcmp(filename, sub->f_name) == 0)
                {
                    // Increase word count
                    sub->w_count++;
                    return SUCCESS;
                } 

                sub = sub->link;
            }

            // File not found, create new sub node
            s_node *new_subnode = malloc(sizeof(s_node));

            if(!new_subnode)
            {
                printf("Sub-node Dynamical allocation is Failued\n");
                return FAILURE;
            }

            new_subnode->f_name = strdup(filename);
            new_subnode->w_count = 1;

            // Insert at beginning
            new_subnode->link = main->s_link;
            main->s_link = new_subnode;

            // Increase file count
            main->f_count++;

            return SUCCESS;
        }

        // Move to next main node
        main = main->m_link;
    }

    // Word not found, create new main node
    m_node *new_Mnode = malloc(sizeof(m_node));

    if(!new_Mnode)
    {
        printf("main-node Dynamical allocation is Failued\n");
        return FAILURE;
    }

    new_Mnode->word = strdup(word);
    new_Mnode->f_count = 1;

    // Create new sub node for first file
    s_node *new_Snode = malloc(sizeof(s_node));

    if(!new_Snode)
    {
        printf("Sub-node Dynamical allocation is Failued\n");
        return FAILURE;
    }

    new_Snode->f_name = strdup(filename);
    new_Snode->w_count = 1;
    new_Snode->link = NULL;

    // Link sub node to main node
    new_Mnode->s_link = new_Snode;

    // Insert main node at beginning
    new_Mnode->m_link = ht_table[index].head;
    ht_table[index].head = new_Mnode;

    return SUCCESS;
}