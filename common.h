#ifndef COMMON_H
#define COMMON_H

#include <stdio.h>

#define SUCCESS 0

#define FAILURE -1

// Check whether the given file is a valid MP3 file
int is_mp3_file(char *filename);

// Read a 4-byte frame size in Big Endian format
int read_size(FILE *fp);

// Write a 4-byte frame size in Big Endian format
void write_size(FILE *fp, int size);

// Copy data from the source file to the destination file
void copy_data(FILE *src, FILE *dest);

#endif