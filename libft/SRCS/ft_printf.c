/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrebois <rrebois@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/22 12:25:06 by rrebois           #+#    #+#             */
/*   Updated: 2023/01/02 11:35:31 by rrebois          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/libft.h"

static int	ft_check(char c, va_list ap, unsigned int *ptr)
{
	if (c == 'c' || c == 's' || c == 'p' || c == 'd' || c == 'i' || c == 'u' \
	|| c == 'x' || c == 'X' || c == '%')
	{
		if (c == 'c')
			ft_putchar((char) va_arg(ap, int), ptr);
		else if (c == 's')
			ft_putstr(va_arg(ap, char *), ptr);
		else if (c == 'p')
			ft_convert_address(va_arg(ap, size_t), ptr);
		else if (c == 'd' || c == 'i')
			ft_putnbr(va_arg(ap, int), ptr);
		else if (c == 'u')
			ft_convert_nbr(va_arg(ap, unsigned int), c, ptr);
		else if (c == 'x' || c == 'X')
			ft_convert_nbr(va_arg(ap, unsigned int), c, ptr);
		else if (c == '%')
			ft_putchar('%', ptr);
		return (0);
	}
	return (1);
}

int	ft_printf(const char *s, ...)
{
	unsigned int	i;
	unsigned int	count;
	unsigned int	*ptr;
	va_list			ap;

	i = 0;
	count = 0;
	ptr = &count;
	if (write(1, 0, 0) != 0)
		return (-1);
	va_start(ap, s);
	while (s[i] != '\0')
	{
		if (s[i] == '%' && s[i + 1] != '\0')
		{
			if (ft_check(s[i + 1], ap, ptr) == 0)
				i++;
		}
		else if (s[i] != '%')
			ft_putchar(s[i], ptr);
		i++;
	}
	va_end(ap);
	return (count);
}
