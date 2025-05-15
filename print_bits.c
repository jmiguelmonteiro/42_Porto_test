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

int	main(void)
{
	print_bits(4);
}
