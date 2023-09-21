#include "Directory.h"
#include <unistd.h> // for getcwd()
#include <limits.h> // for PATH_MAX

#define PATH_MAX 4096 // Manually define PATH_MAX if it's not provided

void listFiles(char *dir, int detailed)
{
    DIR *directory;
    struct dirent *entry;
    DirInfo dirInfo;
    char *currentDir = ".";
    char fullPath[PATH_MAX];

    if (dir == NULL)
    {
        dir = currentDir;
    }

    directory = opendir(dir);
    if (directory == NULL)
    {
        perror("Error opening directory");
        exit(EXIT_FAILURE);
    }

    while ((entry = readdir(directory)) != NULL)
    {
        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0)
        {
            continue; // Skip "." and ".." entries
        }
        if (detailed)
        {
            printf("%s/%s", dir, entry->d_name);
            dirInfo = getDirInfo(fullPath);

            // Print detailed file information
            printf("File name: %s\n", entry->d_name);
            printf("Owner: %d\n", dirInfo.st_uid);
            printf("Group: %d\n", dirInfo.st_gid);
            printf("File size: %ld Bytes\n", dirInfo.st_size);
            printf("Number of Blocks Allocated: %ld\n", dirInfo.st_blocks);
            printf("Number of Links: %ld\n", dirInfo.st_nlink);
            printf("File permissions: ");
            printf((S_ISDIR(dirInfo.st_mode)) ? "d" : "-");  // Directory or not
            printf((dirInfo.st_mode & S_IRUSR) ? "r" : "-"); // Read for User
            printf((dirInfo.st_mode & S_IWUSR) ? "w" : "-"); // Write for User
            printf((dirInfo.st_mode & S_IXUSR) ? "x" : "-"); // Execute for User
            printf((dirInfo.st_mode & S_IRGRP) ? "r" : "-"); // Read for Group
            printf((dirInfo.st_mode & S_IWGRP) ? "w" : "-"); // Write for Group
            printf((dirInfo.st_mode & S_IXGRP) ? "x" : "-"); // Execute for Group
            printf((dirInfo.st_mode & S_IROTH) ? "r" : "-"); // Read for Other
            printf((dirInfo.st_mode & S_IWOTH) ? "w" : "-"); // Write for Other
            printf((dirInfo.st_mode & S_IXOTH) ? "x" : "-"); // Execute for Other
            printf("\n");
            printf("Inode: %ld\n", dirInfo.st_ino);
            printf("\n");
        }
        else
        {
            // Just print the file name
            printf("%s\n", entry->d_name);
        }
    }

    closedir(directory);
}

int main(int argc, char *argv[])
{
    int detailed = 0;
    char *targetDir = NULL;

    if (argc == 2)
    {
        if (strcmp(argv[1], "-l") == 0)
        {
            detailed = 1;
        }
        else
        {
            targetDir = argv[1];
        }
    }
    else if (argc == 3)
    {
        if (strcmp(argv[1], "-l") == 0)
        {
            detailed = 1;
            targetDir = argv[2];
        }
        else if (strcmp(argv[2], "-l") == 0)
        {
            detailed = 1;
            targetDir = argv[1];
        }
    }

    listFiles(targetDir, detailed);
    return 0;
}
