/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abastida <abastida@student.42barcelona.co  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/07 17:33:04 by abastida          #+#    #+#             */
/*   Updated: 2023/12/07 17:56:01 by abastida         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdarg.h>
//#include <stdio.h>

void putstr(char *str, int *len)
{
	int i = 0;
	if(!str)
		str = "(null)";
	while(str[i])
		*len += write(1, &str[i++], 1);
}

void putdigit(long long int num, int base, int *len)
{
	char *number = "0123456789abcdef";

	if(num < 0)
	{
		num *= -1;
		*len += write(1, "-", 1);
	}
	if (num >= base)
		putdigit(num/base, base, len);
	*len += write(1, &number[num % base], 1);
}

int ft_printf(const char *format, ...)
{
	int len = 0;
	va_list ptr;

	va_start(ptr, format);
	while(*format)
	{
		if ((*format) && ((*(format + 1) == 's') || (*(format + 1) == 'd') || (*(format + 1) == 'x')))
		{
			format++;
			if (*format == 's')
				putstr(va_arg(ptr, char *), &len);
			else if(*format == 'd')
				putdigit((long long int)va_arg(ptr, int), 10, &len);
			else if(*format == 'x')
				putdigit((long long int)va_arg(ptr, unsigned int), 16, &len);
		}
		else
			len += write(1, format, 1);
		format++;
	}
	return (len);
}
/*
int main()
{
	ft_printf("%d\n", ft_printf("%s", "caracolisisimo"));
	printf("%d\n", printf("%s", "caracolisisimo"));
	ft_printf("%d\n", ft_printf("%d", 4242));
	printf("%d\n", printf("%d", 4242));
	ft_printf("%d\n", ft_printf("%x", 331));
	printf("%d\n", printf("%x", 331));
}
*/
