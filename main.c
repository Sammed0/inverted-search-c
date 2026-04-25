/* File Name   : main.c
   Name        : Sammed Kuranagi
   Date        : 24-04-2026
   Description : This source file contains the main function used to control the
                 Inverted Search project through menu-driven operations such as
                 create database, display database, save database, search word,
                 update database, and exit.
*/

#include "invt.h"

// Main function
int main(int argc, char *argv[])
{
    // Head pointer for file linked list
    flist *head_f_list = NULL;

    // Hash table declaration
    ht_arr h_table[TABLE_SIZE];

    // Initialize hash table
    insert_ht(h_table);

    // Flag for create database function
    int Cflag = 0;

    // Flag for update database function
    int Uflag = 0;

    // Validate command line arguments
    if(validate_cla(argc, argv, &head_f_list) == FAILURE)
    {
        printf("Entered argument is error\n");
        return FAILURE;
    }
    else
    {
        // Print valid file list
        print_list(&head_f_list);
    }

    int choise;

    do
    {
        // Display menu
        printf("1.create_db\n2.Display_db\n3.save_db\n4.search_db\n5.update_db\n6.Exit...\n");

        printf("Enter the choise : ");
        scanf("%d", &choise);

        switch(choise)
        {
            case 1:
                // Call create_db function

                if(Cflag == 0)
                {
                    // If update already done validate files
                    if(Uflag == 1)
                    {
                        validate_files(h_table, &head_f_list);

                        print_list(&head_f_list);
                    }

                    // Create database
                    if(create_db(h_table, head_f_list) == SUCCESS)
                    {
                        printf("Database created......\n");

                        Cflag = 1;
                    }
                }
                else
                {
                    printf("The create data base is only one time......\n");
                }

                break;

            case 2:
                // Call display_db function
                display_table(h_table);
                break;

            case 3:
                // Call save_db function

                if(Cflag == 1)
                {
                    if(save_db(h_table) == SUCCESS)
                    {
                        printf("Save fuction is successfully done....\n");
                    }
                }
                else
                {
                    printf("ERROR : Before the create function save function not possible....\n");
                }

                break;

            case 4:
                // Call search_db function

                if(search_db(h_table) == SUCCESS)
                {
                    printf("Searching Data base is don........\n");
                }

                break;

            case 5:
                // Call update_db function

                update_db(h_table);

                Uflag = 1;

                break;

            case 6:
                // Exit program
                printf("Exiting for the program....\n");

                return SUCCESS;

            default:
                // Invalid choice
                printf("Invalid inputes plz check..\n");
        }

    }while(choise != 6);
}