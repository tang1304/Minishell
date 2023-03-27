/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_convert_nbr.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrebois <rrebois@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/23 17:39:39 by rrebois           #+#    #+#             */
/*   Updated: 2023/01/02 10:57:50 by rrebois          ###   ########lyon.fr   */
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
