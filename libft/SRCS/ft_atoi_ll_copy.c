/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi_ll.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgellon <tgellon@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 08:26:11 by rrebois           #+#    #+#             */
/*   Updated: 2023/06/01 16:02:31 by tgellon          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/libft.h"

static void	ft_check(long long value, long long sign)
{
	if (value * sign > 0 && value * sign > LLONG_MAX)
	{
		return (0);
	}
	else if (value * sign < 0 && value * sign < LLONG_MIN)
	{
		exit (0);
	}
}

long long	ft_atoi_ll(const char *str)
{
	int			i;
	long long	value;
	long long	sign;

	i = 0;
	value = 0;
	sign = 1;
	while (str[i] != '\0')
	{
		while (str[i] == 32 || (str[i] >= 9 && str[i] <= 13))
			i++;
		if (str[i] == 45)
			sign *= -1;
		if (str[i] == 43 || str[i] == 45)
			i++;
		while (str[i] >= 48 && str[i] <= 57)
		{
			value = value * 10 + (str[i] - '0');
			ft_check(value, sign);
			i++;
		}
		return ((long long int)sign * value);
	}
	return (0);
}
