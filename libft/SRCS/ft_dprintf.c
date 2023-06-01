/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dprintf.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgellon <tgellon@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/22 12:25:06 by rrebois           #+#    #+#             */
/*   Updated: 2023/05/31 11:47:36 by tgellon          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/libft.h"

void	ft_dputchar(int d, char c, unsigned int *ptr)
{
	write(d, &c, 1);
	*ptr = *ptr + 1;
}

void	ft_dputstr(int d, char *s, unsigned int *ptr)
{
	if (s == NULL)
	{
		write(d, "(null)", 6);
		*ptr = *ptr + 6;
		return ;
	}
	write(d, s, ft_strlen(s));
	*ptr = *ptr + ft_strlen(s);
}

static void	ft_dputnbr(int d, int i, unsigned int *ptr)
{
	if (i < 0)
	{
		ft_dputchar(d, '-', ptr);
		i = (unsigned int)i * -1;
	}
	if ((unsigned int)i < 10)
		ft_dputchar(d, i + '0', ptr);
	else
	{
		ft_dputnbr(d, (unsigned int)i / 10, ptr);
		ft_dputnbr(d, (unsigned int)i % 10, ptr);
	}
}

static int	ft_check(int d, char c, va_list ap, unsigned int *ptr)
{
	if (c == 'c' || c == 's' || c == 'p' || c == 'd' || c == 'i' || c == 'u' \
	|| c == 'x' || c == 'X' || c == '%')
	{
		if (c == 'c')
			ft_dputchar(d, (char) va_arg(ap, int), ptr);
		else if (c == 's')
			ft_dputstr(d, va_arg(ap, char *), ptr);
		else if (c == 'p')
			ft_dconvert_address(d, va_arg(ap, size_t), ptr);
		else if (c == 'd' || c == 'i')
			ft_dputnbr(d, va_arg(ap, int), ptr);
		else if (c == 'u')
			ft_dconvert_nbr(d, va_arg(ap, unsigned int), c, ptr);
		else if (c == 'x' || c == 'X')
			ft_dconvert_nbr(d, va_arg(ap, unsigned int), c, ptr);
		else if (c == '%')
			ft_dputchar(d, '%', ptr);
		return (0);
	}
	return (1);
}

int	ft_dprintf(int d, const char *s, ...)
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
			if (ft_check(d, s[i + 1], ap, ptr) == 0)
				i++;
		}
		else if (s[i] != '%')
			ft_dputchar(d, s[i], ptr);
		i++;
	}
	va_end(ap);
	return (count);
}
