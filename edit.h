#ifndef EDIT_H
#define EDIT_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
// Return value for successful execution
#define SUCCESS 0
// Return value for failed execution
#define FAILURE -1

// Edit the specified tag in the MP3 file
int edit_tags(char *option, char *new_data, char *filename);
// Edit the required ID3 frame with new data
int edit_frame(FILE *src, FILE *dest, char *frame_id, char *new_data);

#endif