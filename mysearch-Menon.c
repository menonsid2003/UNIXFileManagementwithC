#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <unistd.h> // Required for getcwd

#define PATH_MAX 4096 // Manually define PATH_MAX if it's not provided

void printContents(const char *path)
{
    DIR *dir = opendir(path);
    if (dir == NULL)
    {
        perror("Error opening directory");
        return;
    }

    printf("Current Path %s/\n", path);

    struct dirent *entry;
    while ((entry = readdir(dir)) != NULL) // Base Case for recursion exit
    {
        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0)
        {
            continue; // Skip current directory (.) and parent directory (..)
        }

        char fullPath[PATH_MAX];
        snprintf(fullPath, PATH_MAX, "%s/%s", path, entry->d_name);

        if (entry->d_type == 4) // Use the numerical constant 4 instead of DT_DIR because of Linux Windows difference
        {
            printContents(fullPath); // Recursively explore sub-directory
        }

        printf("Filename: %s\n", entry->d_name);
    }

    closedir(dir);
}

int main(int argc, char *argv[])
{
    char *rootDir;

    if (argc == 1)
    {
        // Print entire root path instead of ./
        char cwd[PATH_MAX];
        if (getcwd(cwd, sizeof(cwd)) != NULL)
        {
            rootDir = cwd; // Use the current working directory as the root
        }
        else
        {
            perror("Error getting current working directory");
            return 1;
        }
    }
    else if (argc == 2)
    {
        rootDir = argv[1]; // Use provided directory as root
    }
    else
    {
        printf("Usage: %s [directory]\n", argv[0]);
        return 1;
    }

    printContents(rootDir);

    printf("Search has finished!\n");
    return 0;
}
