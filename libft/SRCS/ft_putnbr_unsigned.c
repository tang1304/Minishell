/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_unsigned.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrebois <rrebois@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/25 11:05:14 by rrebois           #+#    #+#             */
/*   Updated: 2023/01/02 10:57:40 by rrebois          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/libft.h"

void	ft_putnbr_unsigned(unsigned int i, unsigned int *ptr)
{
	if (i < 10)
		ft_putchar(i + '0', ptr);
	else
	{
		ft_putnbr_unsigned(i / 10, ptr);
		ft_putnbr_unsigned(i % 10, ptr);
	}
}
