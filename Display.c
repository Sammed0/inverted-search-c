/* File Name   : display_db.c
   Functions   : display_table()
   Name        : Sammed Kuranagi
   Date        : 24-04-2026
   Description : This source file contains the function used to display the
                 complete contents of the database in tabular format.
*/

#include "invt.h"

// Function to display the complete hash table contents
void display_table(ht_arr *table) 
{
    // Print table header line
    printf("=====================================================================================================\n");

    // Print column names
    printf("| Index |        Word      | Files_Count |      File Name       | Word_Count |\n");

    // Print separator line
    printf("=====================================================================================================\n");

    // Traverse all hash table indexes
    for (int i = 0; i < TABLE_SIZE; i++) 
    {
        // Get head of main node list at current index
        m_node *main = table[i].head;

        // Traverse all main nodes
        while (main) 
        {
            // Print first row with index, word, and file count
            printf("| %-5d | %-16.16s | %-11d |", 
                   i, main->word, main->f_count);

            // Get sub node list
            s_node *sub = main->s_link;

            // If no sub nodes present
            if (sub == NULL) 
            {
                printf(" %-20s | %-10s |\n", "-", "-");
            } 
            else 
            {
                // Print first sub node details
                printf(" %-20.20s | %-10d |\n", sub->f_name, sub->w_count);

                // Move to next sub node
                sub = sub->link;

                // Print remaining sub nodes
                while (sub) 
                {
                    // Keep index, word, file count columns blank
                    printf("| %-5s | %-16s | %-11s | %-20.20s | %-10d |\n", 
                           " ", " ", " ", sub->f_name, sub->w_count);

                    // Move to next sub node
                    sub = sub->link;
                }
            }

            // Print separator after each main node
            printf("=====================================================================================================\n");

            // Move to next main node
            main = main->m_link;
        }
    }
}