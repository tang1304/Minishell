/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrebois <rrebois@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/17 13:43:49 by rrebois           #+#    #+#             */
/*   Updated: 2022/12/19 11:31:45 by rrebois          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/libft.h"

void	ft_putnbr_fd(int n, int fd)
{
	char	a;

	if (n < 0)
	{
		write(fd, "-", 1);
		n = (unsigned int)n * -1;
	}
	if ((unsigned int)n < 10)
	{
		a = (unsigned int)n + '0';
		write(fd, &a, 1);
	}
	else
	{
		ft_putnbr_fd((unsigned int)n / 10, fd);
		ft_putnbr_fd((unsigned int)n % 10, fd);
	}
}
