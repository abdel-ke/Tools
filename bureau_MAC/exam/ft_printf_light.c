

#include <unistd.h>
#include <stdarg.h>
#include <stdio.h>

int     g_ret, p,w,point, g_a;
char    type;
void    ft_putchar(char c)
{
	write(1, &c, 1);
	g_ret++;
}
void    ft_putnbr(int nb)
{
	if (nb >= 0 && nb < 10)
		ft_putchar(nb + 48);
	else
	{
		ft_putnbr(nb / 10);
		ft_putnbr(nb % 10);
	}   
}
void    ft_puthex(unsigned int nb)
{
	if (nb < 10)
		ft_putchar(nb + 48);
	else if (nb < 16)
		ft_putchar(nb - 10 + 'a');
	else
	{
		ft_puthex(nb / 16);
		ft_puthex(nb % 16);
	}   
}
int     ft_numlen(unsigned int nb)
{
	int i;
	i = 1;
	while ((nb /= 10))
		i++;
	return (i);
}
int     ft_numlenx(unsigned int nb)
{
	int i;
	i = 1;
	while (nb /= 16)
		i++;
	return (i);
}
int     ft_atoi(const char *str)
{
	int res;

	res = 0;
	while (*str && *str >= '0' && *str <= '9')
	{
		res = res * 10 + (*str - 48);
		++str;
	}
	return (res);
}
int     ft_max(int a, int b)
{
	if (a < b)
		return (b);
	return (a);     
}
int     ft_min(int a, int b)
{
	if (a < b)
		return (a);
	return (b);     
}
int     ft_is_there(char *s, char c)
{
	int i = 0;
	while(s[i])
	{
		if (s[i] == c)
			return (1);
		i++;
	}
	return (0);
}
int     ft_strlen(char *s)
{
	int  i = 0;
	while (s[i])
		i++;
	return (i);
}
void    ft_get_type(char *str)
{
	int i;

	i = 0;
	while (str[i] && ft_is_there("1234567890.", str[i]))
			i++;
	type = str[i];
	g_a = i + 2;
}
void    ft_get_wpp(char *str)
{
	int i;

	i = 0;
	
	while (str[i] != type && str[i])
	{
		if (ft_is_there("1234567890", str[i]))
			w = ft_atoi(&str[i]);
		while (ft_is_there("1234567890", str[i]))
			i++;
		if (str[i] == '.')
		{
			point = 1;
			i++;
		}
		
		if (ft_is_there("1234567890", str[i]))
			p = ft_atoi(&str[i]);
		while (ft_is_there("1234567890", str[i]))
			i++;
		i++;
	}
}
void    ft_print(va_list pa)
{
	int num;
	int sign = 0;
	unsigned int numx;
	char *s;
	int i = 0;
	int numlenx;
	int numlen;
	int slen;
	if (type == 'd')
	{
		num = va_arg(pa, int);
		if (num < 0)
		{
			num *= -1;
			w--;
			sign = 1;
		}
		numlen = ft_numlen(num);
		w = w - ft_max(numlen, p);
		p = p - numlen;
	
		while (i < w)
		{
			ft_putchar(' ');
			i++;
		}
		if (sign == 1) 
			ft_putchar('-');
		i = 0;
		while (i < p)
		{
			ft_putchar('0');
			i++;
		}

		ft_putnbr(num);
	}
		
	if (type == 'x')
	{
		numx = va_arg(pa,unsigned int);

		numlenx = ft_numlenx(numx);
		w = w - ft_max(numlenx, p);
		p = p - numlenx;
		
		while (i < w)
		{
			ft_putchar(' ');
			i++;
		}
		i = 0;
		while (i < p)
		{
			ft_putchar('0');
			i++;
		}

		ft_puthex(numx);
	}
	if (type == 's')
	{
	
		s = va_arg(pa, char *);
		if (s == NULL)
			s = "(null)";

		slen = ft_strlen(s);
		w = w - ft_min(slen, p);
		
		while (i < w)
		{
			ft_putchar(' ');
			i++;
		}
		i = 0;
		if (p != 0)
			while (i < p && s[i])
				{
					ft_putchar(s[i]);
					i++;
				}
		else if (p == 0)
			return ;
		else
			while (i < slen && s[i])
				{
					ft_putchar(s[i]);
					i++;
				}
	}
}
int     ft_printf(char *s, ...)
{
	int i = 0;
	g_ret = 0;
 
	va_list pa;
	va_start(pa, s);
	while (s[i])
	{
		w = 0;
		p = 0;
		point = 0;
		g_a = 0;
		if (s[i] != '%')
			ft_putchar(s[i]);
		else
		{
			ft_get_type(&s[i + 1]);
			ft_get_wpp(&s[i + 1]);
			ft_print(pa);
		}
	s[i] == '%' ? i+=g_a : i++;
	}
	va_end(pa);
	return (g_ret);
}
int     main()
{
	// int x = ft_printf("Hexadecimal for %3.15d is %10.6x  %s\n", 42, 42, NULL);
	int x = ft_printf("kamal.....|%5.3d|.....hamid\n", -1111111111111111111103);
	// int y = printf("Hexadecimal for %3.15d is %10.6x  %s\n", 42, 42, NULL);
	// ft_puthex(-1);
	printf("%d ======= %d\n",x);
}