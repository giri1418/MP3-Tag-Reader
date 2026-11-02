#include "common.h"
#include <string.h>

// Check whether the given file has a .mp3 extension
int is_mp3_file(char *filename)
{
    // Find the last occurrence of '.'
    char *ext = strrchr(filename, '.');

    // Return failure if no extension is found
    if (ext == NULL)
        return FAILURE;
    
    // Compare the extension with ".mp3"
    if (strcmp(ext, ".mp3") == 0)
        return SUCCESS;
    
    // Return failure if the extension is not .mp3    
    return FAILURE;
}

// Read a 4-byte integer (big-endian) from the file
int read_size(FILE *fp)
{
    // Buffer to store 4 bytes
    unsigned char buf[4];
    
    // Read 4 bytes from the file
    fread(buf, 1, 4, fp);
    
    // Convert the 4 bytes into an integer
    return (buf[0] << 24) |
           (buf[1] << 16) |
           (buf[2] << 8)  |
            buf[3];
}

// Write a 4-byte integer (big-endian) to the file
void write_size(FILE *fp, int size)
{
    // Buffer to store 4 bytes
    unsigned char buf[4];

    // Split the integer into four bytes
    buf[0] = (size >> 24) & 0xFF;
    buf[1] = (size >> 16) & 0xFF;
    buf[2] = (size >> 8) & 0xFF;
    buf[3] = size & 0xFF;

    // Write the 4 bytes to the file
    fwrite(buf, 1, 4, fp);
}

// Copy all data from the source file to the destination file
void copy_data(FILE *src, FILE *dest)
{
    // Temporary buffer for file copying
    char buffer[1024];
    // Variable to store the number of bytes read
    int bytes;

    // Read and write until the end of the source file
    while ((bytes = fread(buffer, 1, sizeof(buffer), src)) > 0)
    {
        // Write the read bytes to the destination file
        fwrite(buffer, 1, bytes, dest);
    }
}