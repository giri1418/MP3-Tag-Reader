#ifndef VIEW_H
#define VIEW_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SUCCESS 0
#define FAILURE -1

// Display all ID3 tags from the MP3 file
int view_tags(char *filename);
// Verify whether the MP3 file contains a valid ID3 header
int check_header(FILE *fp);
// Read and display the specified ID3 frame from the file
int read_frame(FILE *fp, const char *frame_id, const char *tag_name);

#endif