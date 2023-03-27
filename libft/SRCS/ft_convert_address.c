/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_convert_address.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrebois <rrebois@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/25 16:36:20 by rrebois           #+#    #+#             */
/*   Updated: 2023/01/02 11:34:43 by rrebois          ###   ########lyon.fr   */
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
