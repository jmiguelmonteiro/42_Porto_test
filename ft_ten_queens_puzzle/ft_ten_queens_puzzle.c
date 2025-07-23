/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ten_queens_puzzle.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: josemigu <josemigu@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 18:12:48 by josemigu          #+#    #+#             */
/*   Updated: 2025/07/18 10:48:56 by josemigu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>

void	print_board(int	*board)
{
	int	i;
	char c;
	
	i = 0;
	while (i < 10)
	{
		c = board[i++] + '0';
		write(1, &c, 1);
	}
	write(1, "\n", 1);
}

int	ft_abs(int a)
{
	if (a > 0)
		return (a);
	return (-a);
}

int	test(int *board, int pos)
{
	int	i;

	i = 0;
	while (i < pos)
	{
		if (board[i] == board[pos] || ft_abs(board[i] - board[pos]) == ft_abs(i - pos))
			return (0);
		i++;
	}
	return (1);
}

void	solve(int *board, int pos, int *count)
{
	int i;
	
	if (pos == 10)
	{
		*count += 1;
		print_board(board);
	}
	else
	{
		i = 0;
		while (i < 10)
		{
			board[pos] = i;
			if (test(board, pos))
				solve(board, pos + 1, count);
			i++;
		}
	}
}

int	ft_ten_queens_puzzle(void)
{
	int	i;
	int	count;
	int	board[10];

	i = 0;
	count = 0;
	while (i < 10)
		board[i++] = -1;	
	solve(board, 0, &count);
	return (count);
}

int	main(void)
{
	printf("Solutions found: %d\n", ft_ten_queens_puzzle());
	return (0);
}
