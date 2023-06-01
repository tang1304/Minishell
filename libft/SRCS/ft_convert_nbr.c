/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_convert_nbr.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgellon <tgellon@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/23 17:39:39 by rrebois           #+#    #+#             */
/*   Updated: 2023/05/31 11:43:02 by tgellon          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/libft.h"

static void	ft_convert_base_nbr(unsigned int i, char *base, unsigned int *ptr)
{
	if (i < 16)
		ft_putchar(base[i], ptr);
	else
	{
		ft_convert_base_nbr(i / 16, base, ptr);
		ft_convert_base_nbr(i % 16, base, ptr);
	}
}

void	ft_convert_nbr(unsigned int i, char c, unsigned int *ptr)
{
	char	*base_min;
	char	*base_max;

	base_min = "0123456789abcdef";
	base_max = "0123456789ABCDEF";
	if (c == 'u')
		ft_putnbr_unsigned(i, ptr);
	else if (c == 'x')
		ft_convert_base_nbr(i, base_min, ptr);
	else if (c == 'X')
		ft_convert_base_nbr(i, base_max, ptr);
}

static void	ft_dputnbr_unsigned(int d, unsigned int i, unsigned int *ptr)
{
	if (i < 10)
		ft_dputchar(d, i + '0', ptr);
	else
	{
		ft_dputnbr_unsigned(d, i / 10, ptr);
		ft_dputnbr_unsigned(d, i % 10, ptr);
	}
}

static void	ft_dconvert_base_nbr(int d, unsigned int i, char *base, \
								unsigned int *ptr)
{
	if (i < 16)
		ft_dputchar(d, base[i], ptr);
	else
	{
		ft_dconvert_base_nbr(d, i / 16, base, ptr);
		ft_dconvert_base_nbr(d, i % 16, base, ptr);
	}
}

void	ft_dconvert_nbr(int d, unsigned int i, char c, unsigned int *ptr)
{
	char	*base_min;
	char	*base_max;

	base_min = "0123456789abcdef";
	base_max = "0123456789ABCDEF";
	if (c == 'u')
		ft_dputnbr_unsigned(d, i, ptr);
	else if (c == 'x')
		ft_dconvert_base_nbr(d, i, base_min, ptr);
	else if (c == 'X')
		ft_dconvert_base_nbr(d, i, base_max, ptr);
}
