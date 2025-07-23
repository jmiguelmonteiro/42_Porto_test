#define _GNU_SOURCE
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>

#ifndef BUFFER_SIZE
#define BUFFER_SIZE 42
#endif

/* void *realloc(void *ptr, size_t bytes)
{
	(void)ptr;
	(void)bytes;
	return NULL;
} */

void ft_filter(char *haystack, char *seed)
{
	char *p;

	while ((p = memmem(haystack, strlen(haystack), seed, strlen(seed))))
	{
		size_t i = 0;
		while (i < strlen(seed))
			p[i++] = '*';
	}
}

int main(int argc, char **argv)
{

    char *temp[BUFFER_SIZE];
    char *buffer;
    char *res = NULL;
    int total_read;
    ssize_t bytes;

	(void)argv;

    if(argc != 2)
        return 1;

    while((bytes = read(0, temp, BUFFER_SIZE)) > 0)
    {
        buffer = realloc(res, (total_read + bytes + 1));
        if(!buffer)
        {
            perror("realloc");
            free(buffer);
            return 1;
        }
        res = buffer;
        memmove((res + total_read), temp, bytes);
        total_read = total_read + bytes;
        res[total_read] = '\0';
    }

    if(bytes < 0)
    {
        free(res);
        perror("bytes");
        return 1;
    }
    if(!res)
    {
        free(res);
        return 1;
    }
    ft_filter(res, argv[1]);
	printf("Result: %s", res);
    free(res);
    return 0;
}
