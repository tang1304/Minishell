/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_convert_address.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgellon <tgellon@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/25 16:36:20 by rrebois           #+#    #+#             */
/*   Updated: 2023/05/31 11:36:48 by tgellon          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/libft.h"

static void	ft_convert_base_address(size_t i, char *base, unsigned int *ptr)
{
	if (i < 16)
		ft_putchar(base[i], ptr);
	else
	{
		ft_convert_base_address(i / 16, base, ptr);
		ft_convert_base_address(i % 16, base, ptr);
	}
}

void	ft_convert_address(size_t i, unsigned int *ptr)
{
	char	*base_min;

	base_min = "0123456789abcdef";
	ft_putstr("0x", ptr);
	ft_convert_base_address(i, base_min, ptr);
}

static void	ft_dconvert_base_address(int d, size_t i, char *base, \
									unsigned int *ptr)
{
	if (i < 16)
		ft_dputchar(d, base[i], ptr);
	else
	{
		ft_dconvert_base_address(d, i / 16, base, ptr);
		ft_dconvert_base_address(d, i % 16, base, ptr);
	}
}

void	ft_dconvert_address(int d, size_t i, unsigned int *ptr)
{
	char	*base_min;

	base_min = "0123456789abcdef";
	ft_dputstr(d, "0x", ptr);
	ft_dconvert_base_address(d, i, base_min, ptr);
}
