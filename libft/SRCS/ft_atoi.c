/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aviscogl <aviscogl@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 08:26:11 by rrebois           #+#    #+#             */
/*   Updated: 2023/01/28 14:07:12 by aviscogl         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/libft.h"

static void	ft_check(long value, long sign)
{
	if (value * sign > 0 && value * sign > 2147483647)
	{
		ft_printf("Error\n");
		exit (1);
	}
	else if (value * sign < 0 && value * sign < -2147483648)
	{
		ft_printf("Error\n");
		exit (1);
	}
}

int	ft_atoi(const char *str)
{
	int		i;
	long	value;
	long	sign;

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
		return ((int)sign * value);
	}
	return (0);
}
