#include <stdio.h>
#include <string.h>
#include "edit.h"

// Edit the selected MP3 tag
int edit_tags(char *option, char *new_data, char *filename)
{
    // File pointers for source and temporary file
    FILE *src;
    FILE *dest;

    // Pointer to store the frame ID
    char *frame;

    // Select Title frame
    if (strcmp(option, "-t") == 0)
        frame = "TIT2";

    // Select Artist frame
    else if (strcmp(option, "-a") == 0)
        frame = "TPE1";

    // Select Album frame
    else if (strcmp(option, "-A") == 0)
        frame = "TALB";

    // Select Year frame
    else if (strcmp(option, "-y") == 0)
        frame = "TYER";

    // Select Genre frame
    else if (strcmp(option, "-m") == 0)
        frame = "TCON";

    // Select Comment frame
    else if (strcmp(option, "-c") == 0)
        frame = "COMM";

    // Handle invalid edit option
    else
    {
        printf("Invalid Edit Option\n");
        return FAILURE;
    }

    // Open the MP3 file in read mode
    src = fopen(filename, "rb");
    if (src == NULL)
    {
        printf("Unable to open MP3 file\n");
        return FAILURE;
    }

    // Create a temporary file
    dest = fopen("temp.mp3", "wb");
    if (dest == NULL)
    {
        printf("Unable to create temp file\n");
        fclose(src);
        return FAILURE;
    }

    // Edit the required frame
    if (edit_frame(src, dest, frame, new_data) == FAILURE)
    {
        fclose(src);
        fclose(dest);
        remove("temp.mp3");
        return FAILURE;
    }

    // Close both files
    fclose(src);
    fclose(dest);

    // Delete the original file
    remove(filename);

    // Rename the temporary file
    if (rename("temp.mp3", filename) != 0)
    {
        printf("Error: Unable to rename temp file\n");
        return FAILURE;
    }

    // Display success message
    printf("\nTag Updated Successfully\n");

    return SUCCESS;
}

// Edit the selected ID3 frame
int edit_frame(FILE *src, FILE *dest, char *frame_id, char *new_data)
{
    // Store frame ID
    char id[5];

    // Store frame size bytes
    unsigned char size_buf[4];

    // Store header bytes
    char header[10];

    // Temporary buffer for copying data
    char temp[1024];

    // Variables for frame size and byte count
    int size;
    int new_size;
    int bytes;

    // Move file pointer to the beginning
    rewind(src);

    // Read the 10-byte ID3 header
    if (fread(header, 1, 10, src) != 10)
        return FAILURE;

    // Write the header to the destination file
    fwrite(header, 1, 10, dest);

    // Read each frame until the end
    while (fread(id, 1, 4, src) == 4)
    {
        // Add string terminator
        id[4] = '\0';

        // Stop if end of frames is reached
        if (id[0] == 0)
            break;

        // Read the frame size
        if (fread(size_buf, 1, 4, src) != 4)
            break;

        // Convert size bytes to integer
        size = (size_buf[0] << 24) |
               (size_buf[1] << 16) |
               (size_buf[2] << 8)  |
               size_buf[3];

        // Read frame flags
        if (fread(header, 1, 2, src) != 2)
            break;

        // Write frame ID
        fwrite(id, 1, 4, dest);

        // Check if this is the frame to edit
        if (strcmp(id, frame_id) == 0)
        {
            // Calculate new frame size
            new_size = strlen(new_data) + 1;

            // Convert new size into bytes
            size_buf[0] = (new_size >> 24) & 0xFF;
            size_buf[1] = (new_size >> 16) & 0xFF;
            size_buf[2] = (new_size >> 8) & 0xFF;
            size_buf[3] = new_size & 0xFF;

            // Write updated frame size
            fwrite(size_buf, 1, 4, dest);

            // Write frame flags
            fwrite(header, 1, 2, dest);

            // Skip old frame data
            fseek(src, size, SEEK_CUR);

            // Write text encoding byte
            fputc(0x00, dest);

            // Write the updated tag value
            fwrite(new_data, 1, strlen(new_data), dest);
        }
        else
        {
            // Copy original frame size
            fwrite(size_buf, 1, 4, dest);

            // Copy frame flags
            fwrite(header, 1, 2, dest);

            // Store remaining frame size
            int remaining = size;

            // Copy frame data in chunks
            while (remaining > 0)
            {
                // Calculate bytes to copy
                bytes = (remaining > sizeof(temp)) ? sizeof(temp) : remaining;

                // Read frame data
                fread(temp, 1, bytes, src);

                // Write frame data
                fwrite(temp, 1, bytes, dest);

                // Reduce remaining bytes
                remaining -= bytes;
            }
        }
    }

    // Copy the remaining MP3 audio data
    while ((bytes = fread(temp, 1, sizeof(temp), src)) > 0)
    {
        fwrite(temp, 1, bytes, dest);
    }

    // Return success
    return SUCCESS;
}