#include "view.h"

// Check whether the MP3 file contains an ID3 header
int check_header(FILE *fp)
{
    // Buffer to store the header
    char header[4];

    // Move to the beginning of the file
    rewind(fp);

    // Read the first 3 bytes
    fread(header, 1, 3, fp);

    // Add null terminator
    header[3] = '\0';

    // Check if the header is "ID3"
    if(strcmp(header, "ID3") == 0)
        return SUCCESS;

    // Return failure if ID3 header is not found
    return FAILURE;
}

// View all required MP3 tags
int view_tags(char *filename)
{
    // File pointer for the MP3 file
    FILE *fp;

    // Open the MP3 file in binary read mode
    fp = fopen(filename, "rb");

    // Check if the file opened successfully
    if(fp == NULL)
    {
        printf("ERROR : Unable to open %s\n", filename);
        return FAILURE;
    }

    // Verify the ID3 header
    if(check_header(fp) == FAILURE)
    {
        printf("ERROR : ID3v2 tag not found\n");
        fclose(fp);
        return FAILURE;
    }

    // Display heading
    printf("\n------------- MP3 TAG INFO -------------\n\n");

    // Move to the beginning of the file
    rewind(fp);

    // Skip the 10-byte ID3 header
    fseek(fp, 10, SEEK_SET);

    // Read and display the title
    read_frame(fp, "TIT2", "Title");

    // Read and display the artist
    read_frame(fp, "TPE1", "Artist");

    // Read and display the album
    read_frame(fp, "TALB", "Album");

    // Read and display the year
    read_frame(fp, "TYER", "Year");

    // Read and display the content type
    read_frame(fp, "TCON", "Content type");

    // Read and display the comment
    read_frame(fp, "COMM", "Comment");

    // Close the MP3 file
    fclose(fp);

    return SUCCESS;
}

// Read the specified frame and display its value
int read_frame(FILE *fp, const char *frame_id, const char *tag_name)
{
    // Buffer to store frame ID
    char id[5];

    // Buffer to store frame data
    char data[300];

    // Buffer to store frame size
    unsigned char size_buf[4];

    // Variable to store frame size
    int size;

    // Move to the beginning of the file
    rewind(fp);

    // Skip the ID3 header
    fseek(fp, 10, SEEK_SET);

    // Read each frame one by one
    while (fread(id, 1, 4, fp) == 4)
    {
        // Add null terminator
        id[4] = '\0';

        // Read the frame size
        fread(size_buf, 1, 4, fp);

        // Convert frame size into integer
        size = (size_buf[0] << 24) |
               (size_buf[1] << 16) |
               (size_buf[2] << 8)  |
                size_buf[3];

        // Skip the 2-byte frame flags
        fseek(fp, 2, SEEK_CUR);

        // Check whether the frame matches
        if (strcmp(id, frame_id) == 0)
        {
            // Skip the text encoding byte
            fgetc(fp);

            // Read the frame data
            fread(data, 1, size - 1, fp);

            // Add null terminator
            data[size - 1] = '\0';

            // Display the tag value
            printf("%-12s : %s\n", tag_name, data);

            return SUCCESS;
        }
        else
        {
            // Skip the current frame data
            fseek(fp, size, SEEK_CUR);
        }

        // Stop if an invalid frame size is found
        if (size <= 0)
            break;
    }

    // Return failure if the frame is not found
    return FAILURE;
}