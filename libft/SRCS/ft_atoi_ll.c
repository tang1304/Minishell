/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi_ll.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgellon <tgellon@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 12:04:43 by tgellon           #+#    #+#             */
/*   Updated: 2023/06/01 16:37:40 by tgellon          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

long long	ft_atoi_ll(const char *str, int *err)
{
	size_t			i;
	int				sign;
	long long int	output;

	i = 0;
	output = 0;
	sign = 1;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == ' ')
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign = -sign;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		if (output != ((output * 10 + (sign * (str[i] - '0'))) / 10))
			*err = 1;
		output = output * 10 + ((str[i] - '0') * sign);
		i++;
	}
	return ((long long)output);
}
