#ifndef BUFFER_SIZE
# define BUFFER_SIZE 5
#endif

#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

void	ft_filter(char *haystack, char *needle)
{
	char	*p;
	while ((p = memmem(haystack, strlen(haystack), needle, strlen(needle))))
	{
		size_t i = 0;
		while (i < strlen(needle))
			p[i++] = '*';
	}
}

int	main(int argc, char **argv)
{
	char	buffer[BUFFER_SIZE];
	char	*str = NULL;
	char	*tmp = NULL;
	int		bytes_read = 0;
	int		total_read = 0;

	if (argc != 2)
		return (1);
	
	while ((bytes_read = read(0, buffer, BUFFER_SIZE)) > 0)
	{
		tmp = str;
		str = realloc(tmp, (total_read + bytes_read + 1) * sizeof(char));
		if (!str)
		{
			perror("Error");
			free(tmp);
			return (1);
		}
		memmove(str + total_read, buffer, bytes_read);
		total_read += bytes_read;
		str[total_read] = '\0';
	}
	if (bytes_read < 0)
	{
		perror("Error");
		free(str);
		return (1);
	}
	if (!str)
		return (1);
	ft_filter(str, argv[1]);
	printf("%s", str);
	free(str);
	return (0);
}
