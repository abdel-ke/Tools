#include <stdio.h>
#include <unistd.h>

void	ft_putchar(char c)
{
	write(1, &c, 1);
}

void	ft_putstr(char *str)
{
	while (*str)
		ft_putchar(*str++);
}

int		ft_strlen(char *str)
{
	int i = -1;
	while (str[++i]);
	return (i);
}

void	ft_putnbr(int nb)
{
	unsigned int nbr;
	if (nb < 0)
	{
		ft_putchar('-');
		nb *= -1;
	}
	nbr = nb;
	if (nbr < 10)
		ft_putchar(nb + 48);
	else
	{
		ft_putnbr(nbr / 10);
		ft_putnbr(nbr % 10);
	}
}

int main()
{
	ft_putnbr(2147483647);puts("");
}