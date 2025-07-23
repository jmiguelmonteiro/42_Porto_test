#include <stdio.h>

void	print_bits(unsigned char bit)
{
	int	i;
	unsigned char res;

	i = 8;
	while(i--)
	{
		res = ((bit >> i) & 1) + '0';
		printf("%c", res);
	}
}

unsigned char	swap_bits(unsigned char bit)
{
	return (bit >> 4 | bit << 4);
}

unsigned char	reverse_bits(unsigned char bit)
{
	int	i;
	unsigned char res = 0;

	i = 8;
	while(i--)
	{
		res = (res << 1) | (bit & 1);
		bit = bit >> 1;
	}
	return res;
}

int	main(void)
{
	print_bits(4);
	printf("\n");
	print_bits(swap_bits(4));
	printf("\n");
	print_bits(reverse_bits(swap_bits(4)));
	printf("\n");
}
