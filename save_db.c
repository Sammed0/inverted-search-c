/* File Name   : save_db.c
   Functions   : save_db()
   Name        : Sammed Kuranagi
   Date        : 24-04-2026
   Description : This source file contains the function used to save the
                 current database contents into a backup text file using a
                 predefined format.
*/

#include "invt.h"

// Function to save database into backup file
int save_db(ht_arr *h_table)
{
    char filename[20];

    // Get backup file name from user
    printf("Enter the backup file name : ");
    scanf("%s", filename);

    // Validate file extension
    if(strstr(filename, ".txt") == NULL)
    {
        printf("ERROR : file name is not valid\n");
        return FAILURE;
    }

    FILE *fp;

    // Open file in write mode
    fp = fopen(filename, "w");

    if(fp == NULL)
    {
        printf("file open is error\n");
        return FAILURE;
    }

    // Write magic string at beginning
    fprintf(fp, MAGIC_STRING);

    // Traverse all hash table indexes
    for(int i = 0; i < TABLE_SIZE; i++)
    {
        m_node *temp = h_table[i].head;

        h_table[i].head = NULL;

        // Traverse main nodes
        while(temp != NULL)
        {
            // Write index, word, file count
            fprintf(fp, "#%d;%s;%d;", i, temp->word, temp->f_count);

            s_node *temp1 = temp->s_link;

            // Traverse sub nodes
            while(temp1 != NULL)
            {
                // Write word count and file name
                fprintf(fp, "%d;%s;", temp1->w_count, temp1->f_name);

                temp1 = temp1->link;
            }

            // End of one record
            fprintf(fp, "#\n");

            temp = temp->m_link;
        }
    }

    // Close file
    fclose(fp);

    return SUCCESS;
}