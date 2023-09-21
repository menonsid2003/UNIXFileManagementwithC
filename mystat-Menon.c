#include "Directory.h"

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("Usage: %s <file_or_directory>\n", argv[0]);
        return 1;
    }

    DirInfo dirInfo = getDirInfo(argv[1]);

    printf("File Information of %s\n", argv[0]);
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
    printf("File Inode: %ld\n", dirInfo.st_ino);

    return 0;
}