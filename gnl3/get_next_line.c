#include "get_next_line.h"

char	ft_getc(fd)
{
	static t_buf buf;

	if (buf.n == 0)
	{
		buf.n = read(fd, buf.buf, BUFFER_SIZE);
		if (buf.n < 0)
		{
			buf.n = 0;
			return (READ_ERROR);
		}
		buf.bufp = buf.buf;
	}
	if (--buf.n >= 0)
		return((unsigned char)*buf.bufp++);
	buf.n = 0;
	return (EOF);
}

int	ft_putc(t_str *str, char c)
{
	char *tmp;
	int	i;

	if ((str->len + 1) > str->cap)
	{
		tmp = str->str;
		str->str = malloc((str->cap + BUFFER_SIZE) * sizeof(char));
		if (!str->str)
			return (free(str->str), 1);
		i = 0;
		while (i < str->len)
		{
			str->str[i] = tmp[i];
			i++;
		}
		free(tmp);
		str->cap += BUFFER_SIZE;
	}
	str->str[str->len] = c;
	str->len++;
	return (0);
}

char	*get_next_line(int fd)
{
	t_str	str;
	char	c;

	str.str = NULL;
	str.cap = 0;
	str.len = 0;
	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	while (1)
	{
		c = ft_getc(fd);
		if (c == READ_ERROR)
			return (free(str.str), NULL);
		if (c == EOF)
			break ;
		if (ft_putc(&str, c))
			return (NULL);
		if (c == '\n')
			break ;
	}
	if (str.len > 0)
		if (ft_putc(&str, '\0'))
			return (NULL);
	return (str.str);
}

/* int	main(void)
{
	int		fd = 0;
	char	*line;

	line = get_next_line(fd);
	while (line)
	{
		printf("%s", line);
		free(line);
		line = get_next_line(fd);
	}
} */
