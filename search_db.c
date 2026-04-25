/* File Name   : search_db.c
   Functions   : search_db()
   Name        : Sammed Kuranagi
   Date        : 24-04-2026
   Description : This source file contains the function used to search a given
                 word in the database and display its file details and count.
*/

#include "invt.h"

// Function to search a word in database
int search_db(ht_arr *ht_table)
{
    char word[20];

    // Get word from user
    printf("Enter the word to search : ");
    scanf("%s", word);

    // Find index using first character
    int index = index_find(word[0]);

    // Print table header
    printf("===================================================================================\n");
    printf("| Index |        Word        | Files_Count |      File Name      | Word_Count |\n");
    printf("===================================================================================\n");

    // Get main node list of that index
    m_node *mtemp = ht_table[index].head;

    int found = 0;

    // Traverse main nodes
    for (int i = 0; mtemp != NULL; i++)
    {
        // If word matched
        if(strcmp(mtemp->word, word) == 0)
        {
            found = 1;

            // Print word details
            printf("| %-5d | %-18s | %-11d |",
                   index, mtemp->word, mtemp->f_count);

            // Get sub node list
            s_node *sub = mtemp->s_link;

            // If no sub nodes
            if (sub == NULL)
            {
                printf(" %-19s | %-10s |\n", "-", "-");
            }
            else
            {
                // Traverse sub nodes
                while (sub)
                {
                    // Print file name and word count
                    printf(" %-19s | %-10d |\n", sub->f_name, sub->w_count);

                    // Print blank columns for next sub nodes
                    if (sub->link != NULL)
                    {
                        printf("| %-5s | %-18s | %-11s |", "", "", "");
                    }

                    sub = sub->link;
                }
            }

            // Print closing line
            printf("===================================================================================\n");

            return SUCCESS;
        }

        // Move to next main node
        mtemp = mtemp->m_link;
    }

    // If word not found
    if(!found)
    {
        printf("Word not found in the database.\n");
    }

    return FAILURE;
}