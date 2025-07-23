#include <stdio.h>
#include <stdlib.h>

void	print_board(int *tab, int n)
{
	int i = 0;
	while (i < n)
		printf("%d ", tab[i++]);
	printf("\n");
}

int test(int *tab, int pos)
{
	int i = 0;

	while (i < pos)
	{
		if (tab[pos] == tab[i])
			return 0;
		if (abs(tab[pos] - tab[i]) == abs(pos - i))
			return 0;
		i++;
	}
	return 1;
}

void solve(int *tab, int pos, int *count, int n)
{
	int i;
	if (pos == n)
	{
		(*count)++;
		print_board(tab, n);
	}
	else
	{
		i = 0;
		while (i < n)
		{
			tab[pos] = i;
			if (test(tab, pos))
				solve(tab, pos + 1, count, n);
			i++;
		}
	}
}

int	ft_n_queens_puzzle(int n)
{
	int i = 0;
	int *tab;
	int count;

	tab = malloc(n * sizeof(int));
	if (!tab)
		exit(1);
	while (i < n)
		tab[i++] = -1;
	solve(tab, 0, &count, n);
	return (count);
}

int	main(int argc, char **argv)
{
	int n;
	if (argc != 2)
		return (1);
	n = atoi(argv[1]);
	printf("Solutions found for a %dx%d board: %d\n", n, n, ft_n_queens_puzzle(n));
	return (0);
}
