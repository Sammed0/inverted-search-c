/* File Name   : update_db.c
   Functions   : update_db()
   Name        : Sammed Kuranagi
   Date        : 24-04-2026
   Description : This source file contains the function used to update or
                 restore the database from a previously saved backup file.
*/

#include "invt.h"

// Function to update database from backup file
int update_db(ht_arr *h_table)
{
    // Check whether hash table is empty
    for(int i = 0; i < TABLE_SIZE; i++)
    {
        if(h_table[i].head != NULL)
        {
            printf("ERROR : Hash table is not empty\n");
            return FAILURE;
        }
    }

    char filename[20];

    // Get file name from user
    printf("Enter the file name : ");
    scanf("%s", filename);

    // Validate file extension
    if(strstr(filename, ".txt") == NULL)
    {
        printf("ERROR : file name is not valid\n");
        return FAILURE;
    }

    // Open file in read mode
    FILE *fp = fopen(filename, "r");

    if(!fp)
        return FAILURE;

    // Check magic string
    char magic_string[20];

    int len = strlen(MAGIC_STRING);

    fread(magic_string, 1, len, fp);

    magic_string[len] = '\0';

    // Compare magic string
    if(strcmp(magic_string, MAGIC_STRING) != 0)
    {
        printf("ERROR : The Magic String is not matching\n");

        fclose(fp);

        return FAILURE;
    }

    // Read each line after magic string
    char line[256];

    while(fscanf(fp, "%255[^\n]", line) == 1)
    {
        // Remove newline from buffer
        fgetc(fp);

        // Split line using delimiters
        char *token = strtok(line, ";#\n");

        if(token == NULL)
            continue;

        // Get word
        token = strtok(NULL, ";#\n");

        if(token == NULL)
            continue;

        char word[30];

        strncpy(word, token, sizeof(word) - 1);

        word[sizeof(word) - 1] = '\0';

        // Get file count
        token = strtok(NULL, ";#\n");

        if(token == NULL)
            continue;

        int f_count = atoi(token);

        // Traverse all files for same word
        for(int j = 0; j < f_count; j++)
        {
            char *wcount_tok = strtok(NULL, ";#\n");
            char *fname_tok  = strtok(NULL, ";#\n");

            if(wcount_tok == NULL || fname_tok == NULL)
                break;

            int w_count = atoi(wcount_tok);

            // Insert word multiple times based on count
            for(int k = 0; k < w_count; k++)
            {
                insert_word(h_table, word, fname_tok);
            }
        }
    }

    // Close file
    fclose(fp);

    return SUCCESS;
}