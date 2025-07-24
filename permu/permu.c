#include <stdio.h>
#include <string.h>

void	swap(char *a, char *b)
{
	char	tmp = *a;
	*a = *b;
	*b = tmp;
}

void	sort(char *str, int start, int end)
{
	int	i = start;
	while (i < end - 1)
	{
		int	j = i + 1;
		while (j < end)
		{
			if (str[i] > str[j])
				swap(&str[i], &str[j]);
			j++;
		}
		i++;
	}
}

int	next_perm(char *str, int len)
{
	int	i = len - 2;
	while (i >= 0 && str[i] >= str[i + 1])
		i--;
	if (i < 0)
		return (0);
	int	j = len - 1;
	while (str[j] <= str[i])
		j--;
	swap(&str[i], &str[j]);
	sort(str, i + 1, len);
    return 1;
}

void    permut(char *str, int begin, int end)
{
    if (begin == end)
        printf("%s\n", str);
    else
    {
        int i = begin;
        while (i <= end)
        {
            swap(&str[begin], &str[i]);
            permut(str, begin + 1, end);
            swap(&str[begin], &str[i]);
            i++;
        }
    }
}

int	main(int ac, char **av)
{
	if (ac != 2)
		return (1);
	char	str[100];
	char	*str2;
	int		len = 0;

	while (av[1][len])
	{
		str[len] = av[1][len];
		len++;
	}
	str[len] = '\0';
	sort(str, 0, len);
	printf("%s\n", str);
	while (next_perm(str, len))
	{
		printf("%s\n", str);
	}
	printf("\n");
    str2 = strdup(str);
    permut(str2, 0, len - 1);
}
