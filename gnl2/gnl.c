#ifndef BUFFER_SIZE
# define BUFFER_SIZE 5
#endif
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdbool.h>

int	ft_strlen(char *str)
{
	int i = 0;
	while (str[i])
		i++;
	return i;
}

char	*ft_strjoin(char *s1, char *s2)
{
	char	*ret;
	int		l1 = ft_strlen(s1);
	int		l2 = ft_strlen(s2);
	int		i = 0;

	ret = malloc((l1 + l2 + 1) * sizeof (char));
	if (!ret)
		return NULL;
	while (s1[i])
	{
		ret[i] = s1[i];
		i++;
	}
	i = 0;
	while (s2[i])
	{
		ret[i + l1] = s2[i];
		i++;
	}
	ret[l1 + l2] = '\0';
	free(s1);
	return (ret);
}

bool	has_nl(char *str)
{
	int	i = 0;

	while (str[i])
	{
		if (str[i] == '\n')
			return true;
		i++;
	}
	return false;
}

char	*read_line(int fd, char *keep)
{
	char	buffer[BUFFER_SIZE + 1];
	int		bytes_read = 1;

	while (!has_nl(keep) && bytes_read > 0)
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read < 0)
			return (free(keep), NULL);
		buffer[bytes_read] = '\0';
		keep = ft_strjoin(keep, buffer);
		if (!keep)
			return (NULL);
	}
	return (keep);
}

char	*extract_line(char *keep)
{
	int		pos = 0;
	int		i = 0;
	char	*line;

	if (!*keep)
		return (NULL);
	while (keep[pos] && keep[pos] != '\n')
		pos++;
	if (keep[pos] == '\0')
		pos--;
	line = malloc((pos + 2) * sizeof(char));
	if (!line)
		return (free(keep), NULL);
	while (i < (pos +1))
	{
		line[i] = keep[i];
		i++;
	}
	line[i] = '\0';
	return (line);
}

char	*shift_line(char *keep)
{
	int		pos = 0;
	int		i = 0;
	char	*tmp;

	while (keep[pos] && keep[pos] != '\n')
		pos++;
	if (keep[pos] == '\0')
		pos--;
	tmp = malloc((ft_strlen(keep) - pos) * sizeof(char));
	if (!tmp)
		return (free(keep), NULL);
	while (i < (ft_strlen(keep) - pos))
	{
		tmp[i] = keep[i + pos + 1];
		i++;
	}
	free(keep);
	return (tmp);
}

char	*get_next_line(int fd)
{
	static char	*keep = NULL;
	char		*line = NULL;
//	char		*tmp;

	if (fd < 0 || BUFFER_SIZE <= 0 )
		return NULL;
	if (!keep)
	{
		keep = malloc(sizeof(char));
		keep[0] = '\0';
	}
	keep = read_line(fd, keep);
	if (!keep)
		return (NULL);
	line = extract_line(keep);
	if (!line)
		return (free(keep), NULL);
	keep = shift_line(keep);
	if (!keep)
		return (NULL);
	return (line);
}

int	main(int argc, char **argv)
{
	int 	fd = 0;
	char	*line;

	if (argc > 1)
		fd = open(argv[1], O_RDONLY);
	line = get_next_line(fd);
	while (line != NULL)
	{
		printf("line |%s", line);
		free(line);
		line = get_next_line(fd);
	}
	return (0);
}
