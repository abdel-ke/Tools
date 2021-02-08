/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdel-ke <abdel-ke@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/04 10:17:23 by knabouss          #+#    #+#             */
/*   Updated: 2021/01/30 12:56:59 by abdel-ke         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdarg.h>
#include <stdlib.h>
#include <stdio.h>

typedef struct  s_struct
{
	int		width;
	int		point;
	int		precision;
	char	specifier;
	int		sign;
	int		count;
	int		len;
	int		d;
	long	l;
	unsigned int x;
	char *s;
}               t_struct;

int     ft_strlen(char *s)
{
	int     i;
	i = 0;
	if (!s)
		return (i);
	while (*s++)
		i++;
	return (i);
}

void    ft_putchar(char c)
{
	write(1, &c, 1);
}

void    ft_putstr(char *s)
{
	while (*s)
		ft_putchar(*s++);
}

void    ft_putnbr(int a)
{
	if (a == -2147483648)
	{
		ft_putstr("2147483648");
		return ;
	}
	if (a > 9)
		ft_putnbr(a / 10);
	ft_putchar((a % 10) + '0');
}

void    init_flags(t_struct *gnrl)
{
	gnrl->width = 0;
	gnrl->point = 0;
	gnrl->precision = 0;
	gnrl->specifier = 0;
	gnrl->sign = 0;
	gnrl->len = 0;
}

int     is_dig(char c)
{
	return (c >= '0' && c <= '9');
}

int     ft_atoi(char **s)
{
	int a;
	a = 0;
	while(is_dig(**s))
	{
		a = (a * 10) + (**s - 48);
		(*s)++;
	}
	return(a);
}

void    gather_flags(t_struct *gnrl, char **s, va_list arg)
{
	(*s)++;
	while(**s)
	{
		if (**s == 'd' || **s == 's' || **s == 'x')
		{
			gnrl->specifier = **s;
			if (**s == 'd')
				gnrl->d = va_arg(arg, int);
			else if (**s == 'x')
				gnrl->x = va_arg(arg, unsigned int);
			else if (**s == 's')
				gnrl->s = va_arg(arg, char *);
			(*s)++;
			break;
		}
		else if (**s == '.')
		{
			gnrl->point = 1;
			(*s)++;
			gnrl->precision = ft_atoi(s);
			(*s)--;
		}
		else if (is_dig(**s))
		{
			gnrl->width = ft_atoi(s);
			(*s)--;
		}
		(*s)++;
	}
}

int     nbrlen(int a)
{
	int l;
	l = 1;
	while(a / 10)
	{
		a /= 10;
		l++;
	}
	return(l);
}

void    correct_dec(t_struct *gnrl)
{
	gnrl->len = nbrlen(gnrl->d);
	if (gnrl->d < 0)
		gnrl->sign = 1;
	if (gnrl->sign)
		gnrl->d *= -1;
	if (!gnrl->d && gnrl->point && gnrl->precision == 0)
		gnrl->len = 0;
	gnrl->precision -= (gnrl->precision > gnrl->len) ? gnrl->len : gnrl->precision;
	gnrl->width -= (gnrl->width > gnrl->len + gnrl->precision + gnrl->sign) ?  gnrl->len + gnrl->precision + gnrl->sign : gnrl->width;
}

void    print_dec(t_struct *gnrl)
{
	while(gnrl->width)
	{
		ft_putchar(' ');
		gnrl->count++;
		gnrl->width--;
	}
	if (gnrl->sign)
	{
		ft_putchar('-');
		gnrl->count++;
	}
	while(gnrl->precision)
	{
		ft_putchar('0');
		gnrl->count++;
		gnrl->precision--;
	}
	if (gnrl->len)
		ft_putnbr((long long)gnrl->d);
	gnrl->count += gnrl->len;
}

void    correct_str(t_struct *gnrl)
{
	gnrl->len = gnrl->s != NULL ? ft_strlen(gnrl->s) : 6;
	gnrl->len = (gnrl->point && gnrl->len > gnrl->precision) ? gnrl->precision : gnrl->len;
	gnrl->width -= (gnrl->width > gnrl->len) ? gnrl->len : gnrl->width;
}

void    print_str(t_struct *gnrl)
{
	while(gnrl->width)
	{
		ft_putchar(' ');
		gnrl->count++;
		gnrl->width--;
	}
	if (!gnrl->s)
		gnrl->s = "(null)";
	gnrl->count += gnrl->len;
	while (gnrl->len)
	{
		ft_putchar(*gnrl->s);
		gnrl->len--;
		gnrl->s++;
	}
}

char    hex_dig(int n)
{
	if (n < 10)
		return (n + '0');
	else
		return (n + 'W');
}

char    *hex_conv(unsigned int u, int step)
{
	static char *hex;
	static int l;
	if (!step)
	{
		hex = (char *)malloc(17);
		int i = 0;
		while (i < 17)
			hex[i++] = 0;
		l = 0;
	}
	if (u / 16)
		hex_conv(u / 16, 1);
	hex[l++] = hex_dig(u % 16);
	return (hex);
}

void     correct_hex(t_struct *gnrl)
{
	gnrl->s = hex_conv(gnrl->x, 0);
	gnrl->len = ft_strlen(gnrl->s);
	if (!gnrl->x && gnrl->point && gnrl->precision == 0)
		gnrl->len = 0;
	gnrl->precision -= (gnrl->precision > gnrl->len) ? gnrl->len : gnrl->precision;
	gnrl->width -= (gnrl->width > gnrl->precision + gnrl->len) ? gnrl->precision + gnrl->len : gnrl->width;
}

void    print_hex(t_struct *gnrl)
{
	while(gnrl->width)
	{
		ft_putchar(' ');
		gnrl->count++;
		gnrl->width--;
	}
	while(gnrl->precision)
	{
		ft_putchar('0');
		gnrl->count++;
		gnrl->precision--;
	}
	gnrl->count += gnrl->len;
	while (gnrl->len)
	{
		ft_putchar(*gnrl->s);
		gnrl->s++;
		gnrl->len--;
	}
}

void    global_print(t_struct *gnrl)
{
	if (gnrl->specifier == 'd')
	{
		correct_dec(gnrl);
		print_dec(gnrl);
	}
	else if (gnrl->specifier == 's')
	{
		correct_str(gnrl);
		print_str(gnrl);
	}
	else if (gnrl->specifier == 'x')
	{
		correct_hex(gnrl);
		print_hex(gnrl);
	}
}

int     ft_printf(const char *s, ...)
{
	va_list arg;
	t_struct gnrl;
	gnrl.count = 0;
	va_start(arg, s);
	while(*s)
	{
		while(*s != '%' && *s)
		{
			ft_putchar(*s);
			gnrl.count++;
			s++;
		}
		if (*s == '%' && *s)
		{
			init_flags(&gnrl);
			gather_flags(&gnrl, (char **)&s, arg);
			global_print(&gnrl);
		}
	}
	return(gnrl.count);
}