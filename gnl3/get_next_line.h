#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>

#ifndef BUFFER_SIZE
# define BUFFER_SIZE 5
#endif

#define READ_ERROR -99

typedef struct	s_buf
{
	char	buf[BUFFER_SIZE];
	char	*bufp;
	int		n;
}	t_buf;

typedef struct	s_str
{
	char	*str;
	int		len;
	int		cap;
}	t_str;

char	*get_next_line(int fd);
