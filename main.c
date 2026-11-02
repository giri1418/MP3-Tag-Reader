/*
Author      : Kancharla Giri Babu
Date        : 02-08-2026
Title       : MP3 Tag Reader
Description :

This is an MP3 Tag Reader project developed using C language.
Using this project we can read and modify the metadata (ID3v2 tags)
stored in an MP3 file without affecting the audio data.

Using this project we can perform the following operations :

- View MP3 tag information
- Edit the Title (TIT2)
- Edit the Artist (TPE1)
- Edit the Album (TALB)
- Edit the Year (TYER)
- Edit the content type (TCON)
- Edit the Comment (COMM)
- Display all supported ID3v2 tags
- Save the updated tag information to the MP3 file

The project reads the ID3v2 header and extracts the required frames
to display the metadata. While editing, it updates the selected frame
and rewrites the tag information without damaging the MP3 audio data.

The supported ID3v2 frames are :

- TIT2  : Title
- TPE1  : Artist
- TALB  : Album
- TYER  : Year
- TCON  : Content type
- COMM  : Comment

In this project, we use concepts such as
strings, functions, structures, arrays, command-line arguments,
file handling, file pointers, binary file operations, and dynamic memory.

The program also checks whether the given file is a valid MP3 file
and handles invalid files or unsupported tags appropriately.
*/
#include <stdio.h>
#include <string.h>
#include "view.h"
#include "edit.h"


// Display the help menu with usage instructions
void print_help(void)
{
    // Print project title
    printf("\n---------------- MP3 TAG READER & EDITOR ----------------\n");

    // Display view command
    printf("\nTo View:\n");
    printf("./a.out -v sample.mp3\n");

    // Display edit commands
    printf("\nTo Edit:\n");
    printf("./a.out -e -t \"New Title\" sample.mp3\n");
    printf("./a.out -e -a \"Artist\" sample.mp3\n");
    printf("./a.out -e -A \"Album\" sample.mp3\n");
    printf("./a.out -e -y \"Year\" sample.mp3\n");
    printf("./a.out -e -m \"Content type\" sample.mp3\n");
    printf("./a.out -e -c \"Comment\" sample.mp3\n");
}

// Main function of the program
int main(int argc, char *argv[])
{
    // Check whether command-line arguments are provided
    if(argc < 2)
    {
        // Display help if no arguments are given
        print_help();
        return 1;
    }

    // Check for help option
    if(strcmp(argv[1], "-h") == 0)
    {
        // Display help information
        print_help();
    }

    // Check for view option
    else if(strcmp(argv[1], "-v") == 0)
    {
        // Validate the number of arguments
        if(argc != 3)
        {
            printf("Usage : ./a.out -v file.mp3\n");
            return 1;
        }

        // View MP3 tags
        view_tags(argv[2]);
    }

    // Check for edit option
    else if(strcmp(argv[1], "-e") == 0)
    {
        // Validate the number of arguments
        if(argc != 5)
        {
            printf("Usage : ./a.out -e option value file.mp3\n");
            return 1;
        }

        // Edit the selected MP3 tag
        edit_tags(argv[2], argv[3], argv[4]);
    }

    // Handle invalid options
    else
    {
        printf("Invalid Option\n");

        // Display help menu
        print_help();
    }

    // Exit the program successfully
    return 0;
}