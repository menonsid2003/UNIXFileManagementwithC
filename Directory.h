#ifndef DIRECTORY_H
#define DIRECTORY_H

#include <time.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <dirent.h>
#include <sys/stat.h>
typedef struct dirent Dir;
typedef struct stat DirInfo;
typedef struct tm TimeInfo;

char *newString(int length)
{
	return (char *)malloc(length * sizeof(char));
}

int equals(char *string1, char *string2)
{
	return strcmp(string1, string2) == 0 ? 1 : 0;
}

DirInfo getDirInfo(char *dir)
{
	DirInfo dirInfo;
	stat(dir, &dirInfo);
	return dirInfo;
}

void printTime(time_t *time)
{
	int stringLength = 20;
	char string[stringLength];
	TimeInfo *timeInfo = (TimeInfo *)localtime(time);
	strftime(string, stringLength, "%b %d %H:%M",
			 timeInfo);
	printf("Time: %s\t", string);
}

#endif