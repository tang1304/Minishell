/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aviscogl <aviscogl@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/25 13:10:14 by rrebois           #+#    #+#             */
/*   Updated: 2023/01/28 10:49:49 by aviscogl         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/libft.h"

void	ft_putstr(char *s, unsigned int *ptr)
{
	if (s == NULL)
	{
		write(1, "(null)", 6);
		*ptr = *ptr + 6;
		return ;
	}
	write(1, s, ft_strlen(s));
	*ptr = *ptr + ft_strlen(s);
}
