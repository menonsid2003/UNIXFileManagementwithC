#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>  // Required for open()
#include <unistd.h> // Required for read() and close()

#define BLOCK_SIZE 4096 // Size of the block to read from the file (adjust as needed)

void printLastLines(int fileDescriptor, int numLines)
{
    off_t totalBytes = lseek(fileDescriptor, 0, SEEK_END); // Move to the end of the file
    off_t blockSize = BLOCK_SIZE;

    if (totalBytes < blockSize)
    {
        blockSize = totalBytes; // If the file is smaller than the block size, read the entire file
    }

    char *buffer = (char *)malloc((blockSize + 1) * sizeof(char));
    buffer[blockSize] = '\0';

    off_t bytesRemaining = totalBytes;
    int linesCount = 0;           // Count number of lines in the file starting from the bottom
    int trailingNewlineCount = 0; // Count of trailing newline characters used for counting down each line as it is printed

    // Read the entire file into the buffer
    lseek(fileDescriptor, 0, SEEK_SET); // Move to the beginning of the file
    ssize_t bytesRead = read(fileDescriptor, buffer, totalBytes);

    // Search for newline characters from the end of the buffer
    for (ssize_t i = bytesRead - 1; i >= 0 && linesCount < numLines; i--)
    {
        if (buffer[i] == '\n')
        {
            linesCount++;
            if (linesCount >= numLines)
            {
                // If we found enough lines, print them
                if (trailingNewlineCount > 0)
                {
                    write(STDOUT_FILENO, &buffer[i + 1], bytesRead - i - 1);
                }
                else
                {
                    write(STDOUT_FILENO, &buffer[i + 1], bytesRead - i - 1); // Print the last line even if it's empty
                }
                break;
            }
            trailingNewlineCount = 0; // Reset trailingNewlineCount when a newline is encountered
        }
        else
        {
            // Count the trailing newline characters
            trailingNewlineCount++;
        }
    }

    // If the number of lines requested is larger than the total number of lines in the file, print every line
    if (linesCount < numLines)
    {
        lseek(fileDescriptor, 0, SEEK_SET); // Move to the beginning of the file

        ssize_t bytesRead;
        while ((bytesRead = read(fileDescriptor, buffer, blockSize)) > 0)
        {
            write(STDOUT_FILENO, buffer, bytesRead);
        }
    }

    free(buffer);
}

int main(int argc, char *argv[])
{
    if (argc != 3)
    {
        printf("Usage: %s <num_lines> <file>\n", argv[0]);
        return 1;
    }

    int numLines = atoi(argv[1]);
    if (numLines <= 0)
    {
        printf("Invalid number of lines: %s\n", argv[1]);
        return 1;
    }

    char *filename = argv[2];

    int fileDescriptor = open(filename, O_RDONLY);
    if (fileDescriptor == -1)
    {
        perror("Error opening file");
        return 1;
    }

    printf("These are the last %d lines of %s:\n", numLines, filename);
    printLastLines(fileDescriptor, numLines);

    close(fileDescriptor);
    printf("\n");
    return 0;
}