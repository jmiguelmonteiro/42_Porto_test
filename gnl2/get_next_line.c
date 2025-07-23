/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: josemigu <josemigu@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/23 12:48:38 by josemigu          #+#    #+#             */
/*   Updated: 2025/07/23 15:22:31 by josemigu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	ft_strlen(char *str)
{
	int i = 0;
	while (str[i])
		i++;
	return i;
}

char	*ft_strjoin_free(char *s1, char *s2)
{
	char	*ret;
	int		l1 = ft_strlen(s1);
	int		l2 = ft_strlen(s2);
	int		i = 0;

	ret = malloc((l1 + l2 + 1) * sizeof (char));
	if (!ret)
		return (NULL);
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

char	*shift_line(char *keep)
{
	int		pos = 0;
	int		i = 0;
	char	*tmp;

	if (!keep || !*keep)
		return (NULL);
	while (keep[pos] && keep[pos] != '\n')
		pos++;
	if (keep[pos] == '\0')
		pos--;
	tmp = malloc((ft_strlen(keep) - pos) * sizeof(char));
	if (!tmp)
		return (NULL);
	while (i < (ft_strlen(keep) - pos))
	{
		tmp[i] = keep[i + pos + 1];
		i++;
	}
	free(keep);
	return (tmp);
}

char	*extract_line(char *keep)
{
	int		pos = 0;
	int		i = 0;
	char	*line;

	if (!keep || !*keep)
		return (NULL);
	while (keep[pos] && keep[pos] != '\n')
		pos++;
	if (keep[pos] == '\0')
		pos--;
	line = malloc((pos + 2) * sizeof(char));
	if (!line)
		return (NULL);
	while (i < (pos +1))
	{
		line[i] = keep[i];
		i++;
	}
	line[i] = '\0';
	return (line);
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
		keep = ft_strjoin_free(keep, buffer);
		if (!keep)
			return (free(keep), NULL);
	}
	return (keep);
}

char	*get_next_line(int fd)
{
	static char	*keep;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0 )
		return (NULL);
	if (!keep)
	{
		keep = malloc(1 * sizeof(char));
		keep[0] = '\0';
	}
	keep = read_line(fd, keep);
	if (!keep)
		return (NULL);
	line = extract_line(keep);
	if (!line)
		return (NULL);
	keep = shift_line(keep);
	if (!keep)
		return (NULL);
	return (line);
}

/* int	main(int argc, char **argv)
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
} */
