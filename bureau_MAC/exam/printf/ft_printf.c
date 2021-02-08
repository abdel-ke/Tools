#include <unistd.h>
#include <stdarg.h>
int ft_maxi(int a, int b)
{
	if (a > b)
		return (a);
	return (b);
}
int ft_mini(int a, int b)
{
	if (a < b)
		return (a);
	return (b);
}
int ft_strlen(char *str)
{
	int i;

	i = 0;
	while (str[i] != '\0')
		i++;
	return (i);
}
int ft_putnbr(unsigned int n, int base)
{
	int		i;
	char	str[12];
	
	if (n == 0)
	{
		write (1,"0",1);
		return (0);
	}
	i = 0;
	while (n != 0)
	{
		str[i] = n % base < 10  ? n % base + 48 : n % base + 87 ;
		n = n / base;
		i++;	
	}
	while (i > 0)
	{
		i--;
		write(1, str + i, 1);
	}
	return (0);
}
int ft_intlen(unsigned int n, int base)
{
	int i;

	i = 1;
	while (n / base != 0)
	{
		n = n / base;
		i++;	
	}
	return (i);
}
int ft_print_s(char *str, int width, int precision)
{
	int min;
	int len;
	int i;
	
	if (str == NULL)
		str = "(null)";
	len = ft_strlen(str);
	min = precision < 0 ? len : ft_mini(precision, len);
	i = 0;
	while (i < width - min)
	{
		write(1," ",1);
		i++;
	}
	write(1, str, min);
	return (i + min);
}
int ft_print_x(unsigned int l, int width, int precision)
{
	int		i;
	int		max;
	int		len;

	len = ft_intlen(l, 16);
	max = ft_maxi(precision, len);
	if (precision == 0 && l == 0)
		max = 0;
	i = 0;
	while (i < width - max)
	{
		write(1, " ", 1);
		i++;
	}
	i = 0;
	while (i < precision - len)
	{
		write(1, "0", 1);
		i++;
	}
	if (precision != 0 || l != 0)
		ft_putnbr(l, 16);
	return (ft_maxi(max , width));
}
int ft_print_d(int n, int width, int precision)
{
	long	l;
	int		i;
	int		max;
	int		len;

	l = n;
	l = l < 0 ? -l : l;
	len = ft_intlen(l, 10);
	max = ft_maxi(precision, len);
	if (precision == 0 && n == 0)
		max = 0;
	if (n < 0)
		max++;
	i = 0;
	while (i < width - max)
	{
		write(1, " ", 1);
		i++;
	}
	if (n < 0)
		write(1,"-",1);
	i = 0;
	while (i < precision - len)
	{
		write(1, "0", 1);
		i++;
	}
	if (precision != 0 || n != 0)
		ft_putnbr((unsigned int)l, 10);
	return (ft_maxi(max , width));
}
char              *ft_scan_flags(char *str, int *width, int *precision)
{
	*width = 0;
	*precision = -1;

	while (*str < 58 && *str > 47)
	{
		*width = *width * 10 + *str - 48;
		str++;
	}
	if (*str == '.')
	{
		*precision = 0;
		str++;
	}
	while (*str < 58 && *str > 47)
	{
		*precision = *precision * 10 + *str - 48;
		str++;
	}
	return (str);
}
int ft_print(char c, va_list *pa, int width, int precision)
{
	if (c == 's')
		return (ft_print_s(va_arg(*pa, char*), width, precision));
	if (c == 'd')
		return (ft_print_d(va_arg(*pa, int), width, precision));
	if (c == 'x')
		return (ft_print_x(va_arg(*pa,unsigned int), width, precision));
	return (0);
}
int ft_printf(const char *str, ...)
{
	va_list	pa;
	int		i;
	int		width;
	int		precision;

	i = 0;
	va_start(pa, str);
	while(*str != '\0')
	{
		while(*str == '%')
		{
			str = ft_scan_flags((char*)++str, &width, &precision);
			i += ft_print(*str, &pa, width, precision);
			if (*str == 'd' || *str == 's' || *str == 'x')
				str++;
		}
		if (*str != '\0')
		{
			write(1, str++, 1);
			i++;
		}
	}
	va_end(pa);
	return (i);
}
