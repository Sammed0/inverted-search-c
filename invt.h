/* File Name   : invt.h
   Name        : Sammed Kuranagi
   Date        : 24-04-2026
   Description : This header file contains macro definitions, structure
                 declarations, and function prototypes required for the
                 Inverted Search project.
*/

#ifndef INVT_H
#define INVT_H

// Standard input output functions
#include <stdio.h>

// String handling functions
#include <string.h>

// Dynamic memory allocation functions
#include <stdlib.h>

// Character checking functions
#include <ctype.h>

// Return status macros
#define SUCCESS 0
#define FAILURE 1

// Total hash table size
#define TABLE_SIZE 28

// Magic string used in save/update file
#define MAGIC_STRING "&&**"


// Sub node structure
// Stores file name and word count
typedef struct sub_node
{
    int w_count;            // Count of word in that file
    char *f_name;          // File name
    struct sub_node *link; // Link to next sub node

}s_node;


// Main node structure
// Stores word and linked list of files
typedef struct main_node
{
    char *word;             // Word stored in database
    int f_count;            // Number of files containing word
    s_node *s_link;         // Link to sub node list
    struct main_node *m_link; // Link to next main node
    
}m_node;


// Hash table array structure
typedef struct hash_arra
{
    int index;      // Hash table index
    m_node *head;   // Head pointer of main node list

}ht_arr;


// File linked list structure
typedef struct f_list
{
    char *data;          // File name
    struct f_list *link; // Link to next file node

}flist;



// Mainly needed prototypes...

// Initialize hash table
void insert_ht(ht_arr *table);

// Validate command line arguments
int validate_cla(int argc, char *argv[], flist **head_f_list);

// Check file is empty or not
int istextpresent(char *filename);

// Insert file name into linked list
int insert_first(char *filename, flist **head_f_list);

// Print file linked list
void print_list(flist **head_f_list);



// Creating database prototypes...

// Create database from files
int create_db(ht_arr *ht_table, flist *head);

// Insert word into database
int insert_word(ht_arr * ht_table, const char *word, const char *filename);

// Find hash index
int index_find(const char ch);



// Display database prototypes...

// Display complete database
void display_table(ht_arr *table);


// Search word in database
int search_db(ht_arr *ht_table);

// Save database into file
int save_db(ht_arr *h_table);


// Update database from saved file
int update_db(ht_arr *h_table);

// Validate files already present
void validate_files(ht_arr *h_table, flist **head_f_list);

// Delete element from file list
void delet_elemtent(flist **head_f_list, char *data);

#endif