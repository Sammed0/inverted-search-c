/* File Name   : file_validation.c
   Functions   : validate_cla(), istextpresent(), insert_first(),
                 print_list(), insert_ht(), validate_files(),
                 delet_elemtent()
   Name        : Sammed Kuranagi
   Date        : 24-04-2026
   Description : This source file contains functions related to file validation,
                 command line argument checking, linked list creation, hash
                 table initialization, and file list validation.
*/

#include "invt.h"

// Validating the command line arguments
int validate_cla(int argc, char *argv[], flist **head_f_list)
{
    // Check minimum arguments
    if(argc < 2)
    {
        return FAILURE;
    }

    // Traverse all command line file names
    for(int i = 1; i < argc; i++)
    {
        // Check whether file is .txt file
        if(strstr(argv[i], ".txt") != NULL)
        {
            flist *temp = *head_f_list;
            int isduplicate = 0;

            // Check duplicate file names
            while(temp != NULL)
            {
                if(strcmp(argv[i], temp->data) == 0)
                {
                    isduplicate = 1;
                    break;
                }

                temp = temp->link;
            }

            // If not duplicate insert into file list
            if(!isduplicate)
            {
                if(insert_first(argv[i], head_f_list) == FAILURE)
                {
                    return FAILURE;
                }
            }
            else
            {
                // Duplicate file warning
                fprintf(stderr, "Warning: skipping duplicate file: %s\n", argv[i]);
            }
        }
    }

    return SUCCESS;
}


// Checking whether file is empty or not
int istextpresent(char *filename)
{
    FILE *fptr;

    // Open file in read mode
    if((fptr = fopen(filename, "r")) == NULL)
    {
        fprintf(stderr, "Could not open file: %s\n", filename);
        return FAILURE;
    }

    // Move pointer to end of file
    fseek(fptr, 0, SEEK_END);

    // Get file size
    long size = ftell(fptr);

    fclose(fptr);

    // If file size is zero means empty file
    if(size == 0)
    {
       fprintf(stderr, "File is empty: %s\n", filename);
       return FAILURE;
    }

    return SUCCESS;
}


// Inserting node at first in file linked list
int insert_first(char *filename, flist **head_f_list)
{
    // Check file contains text or not
    if(istextpresent(filename) == FAILURE)
    {
        return FAILURE;
    }

    // Allocate memory for new node
    flist *new_node = malloc(sizeof(flist));

    if(!new_node)
        return FAILURE;

    // Allocate memory for file name
    new_node->data = malloc(strlen(filename) + 1);

    if(!new_node->data)
    {
        free(new_node);
        return FAILURE;
    }

    // Copy file name
    strcpy(new_node->data, filename);

    new_node->link = NULL;

    // If list empty
    if(*head_f_list == NULL)
    {
        *head_f_list = new_node;
        return SUCCESS;
    }
    else
    {
        // Insert at beginning
        new_node->link = *head_f_list;
        *head_f_list = new_node;
        return SUCCESS;
    }
}


// Printing the file names linked list
void print_list(flist **head_f_list)
{
    // Check list empty
    if(*head_f_list == NULL)
    {
        printf("ERROR : LIST IS EMPTY\n");
        return;
    }

    flist *temp = *head_f_list;

    printf("head ->");

    // Traverse and print nodes
    while(temp != NULL)
    {
        printf(" %s->", temp->data);
        temp = temp->link;
    }

    printf(" NULL\n");
}


// Hash table creation
void insert_ht(ht_arr *table)
{
    // Initialize all indexes
    for(int i = 0; i < TABLE_SIZE; i++)
    {
        table[i].index = i;
        table[i].head = NULL;
    }

    printf("Hash_Table is successfully created\n");
}


// Validating file names already present in database
void validate_files(ht_arr *h_table, flist **head_f_list)
{
    // Traverse all hash table indexes
    for(int i = 0; i < TABLE_SIZE; i++)
    {
        if(h_table[i].head == NULL)
        {
            continue;
        }

        m_node *mtemp = h_table[i].head;

        // Traverse main nodes
        while(mtemp != NULL)
        {
            s_node *stemp = mtemp->s_link;

            // Traverse sub nodes
            while(stemp != NULL)
            {
                flist *temp = *head_f_list;

                // Traverse file linked list
                while(temp != NULL)
                {
                    flist *next = temp->link;

                    // If file already exists remove from file list
                    if(strcmp(stemp->f_name, temp->data) == 0)
                    {
                        delet_elemtent(head_f_list, stemp->f_name);
                        break;
                    }

                    temp = next;
                }

                stemp = stemp->link;
            }

            mtemp = mtemp->m_link;
        }
    }
}


// Delete specific element from file linked list
void delet_elemtent(flist **head_f_list, char *data)
{
    flist *temp = *head_f_list;
    flist *pre = NULL;

    // Traverse list
    while(temp != NULL)
    {
        // If matching node found
        if(strcmp(temp->data, data) == 0)
        {
            // If deleting first node
            if(temp == *head_f_list)
            {
                *head_f_list = temp->link;
            }
            else
            {
                pre->link = temp->link;
            }

            // Free node memory
            free(temp);
            return;
        }

        pre = temp;
        temp = temp->link;
    }
}