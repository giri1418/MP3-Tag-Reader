MP3 Tag Reader & Editor
A command-line application written in C to read and edit metadata stored in MP3 files. The program works with ID3v2 tag frames and uses binary file handling to update metadata while copying the remaining MP3 data.
Features
- View supported MP3 metadata.
- Edit individual metadata fields:
  - Title
  - Artist
  - Album
  - Year
  - Content type / Genre
  - Comment
- Display a help menu with command usage.
- Validate the ID3 header before displaying tags.
- Rewrite the MP3 file using a temporary file when editing tags.
Technologies and Concepts
- C programming
- Structures, enumerations, strings, and functions
- Command-line arguments (argc and argv)
- File handling using FILE *
- Binary file operations (fread, fwrite, fseek)
- ID3v2 frame and header processing
- Header files and modular programming
Project Structure
MP3 Tag reader/
├── main.c          # Main function, command-line options, and help menu
├── view.c          # Reads and displays MP3 metadata
├── view.h          # View function declarations
├── edit.c          # Updates the selected metadata frame
├── edit.h          # Edit function declarations
├── common.c        # Common file and frame utility functions
├── common.h        # Common function declarations
├── types.h         # Status values, edit types, and ID3 frame constants
├── validate.h      # Operation and argument-validation declarations
└── sample.mp3      # Sample MP3 file for testing
Compilation
Open a terminal in the project directory and compile the source files:
gcc main.c view.c edit.c common.c -o mp3_tag_reader
If compilation succeeds, an executable named mp3_tag_reader will be created.
Usage
1. Display the help menu
./mp3_tag_reader -h
2. View MP3 metadata
./mp3_tag_reader -v sample.mp3
The program displays the supported fields found in the MP3 file.
3. Edit metadata
General format:
./mp3_tag_reader -e <option> "<new value>" <file.mp3>
Option	Metadata field	ID3v2 frame
-t	Title	TIT2
-a	Artist	TPE1
-A	Album	TALB
-y	Year	TYER
-m	Content type / Genre	TCON
-c	Comment	COMM


Examples:
./mp3_tag_reader -e -t "New Song Title" sample.mp3
./mp3_tag_reader -e -a "New Artist" sample.mp3
./mp3_tag_reader -e -A "New Album" sample.mp3
./mp3_tag_reader -e -y "2026" sample.mp3
./mp3_tag_reader -e -m "Rock" sample.mp3
./mp3_tag_reader -e -c "Updated comment" sample.mp3
After editing, view the file again to check the updated metadata:
./mp3_tag_reader -v sample.mp3
Important: Editing replaces the original MP3 file with the rewritten file. Keep a backup of important MP3 files before testing. Run the executable from a directory where it has permission to create temp.mp3.

How It Works
1. The program reads command-line arguments to determine whether the user wants to view or edit a tag.
2. For viewing, it opens the MP3 file in binary read mode and checks for the ID3 header.
3. It scans ID3v2 frames and identifies supported frame IDs such as TIT2, TPE1, and TALB.
4. For editing, it creates a temporary file, copies the ID3 header and frames, and writes the selected frame with the new value.
5. The remaining MP3 data is copied to the temporary file.
6. The temporary file is renamed to the original filename after the edit operation.
Limitations
- The implementation handles the specific ID3v2 frames listed above; it is not a complete implementation of every ID3 version or frame type.
- The file must contain an ID3 header for the view operation to read its tags.
- Always test with a backup copy of your MP3 file.


Author
Kancharla Giri Babu


License
No license has been specified for this project. Add a license file if you intend to define reuse and distribution permissions.
