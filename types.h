#ifndef TYPES_H
#define TYPES_H

// Enumeration for function return status
typedef enum
{
    SUCCESS,    // Operation completed successfully
    FAILURE     // Operation failed
} Status;

// Enumeration for different edit options
typedef enum
{
    EDIT_TITLE,      // Edit title tag
    EDIT_ARTIST,     // Edit artist tag
    EDIT_ALBUM,      // Edit album tag
    EDIT_YEAR,       // Edit year tag
    EDIT_GENRE,      // Edit genre tag
    EDIT_COMPOSER    // Edit composer tag
} EditType;

// Frame ID for title
#define TITLE_FRAME      "TIT2"

// Frame ID for artist
#define ARTIST_FRAME     "TPE1"

// Frame ID for album
#define ALBUM_FRAME      "TALB"

// Frame ID for year
#define YEAR_FRAME       "TYER"

// Frame ID for genre
#define GENRE_FRAME      "TCON"

// Frame ID for composer
#define COMPOSER_FRAME   "TCOM"

// Size of the ID3 header in bytes
#define HEADER_SIZE      10

// Size of each frame header in bytes
#define FRAME_HEADER_SIZE 10

// Maximum size of tag data
#define MAX_TAG_SIZE     256

#endif