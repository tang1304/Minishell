/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrebois <rrebois@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/09 10:26:10 by rrebois           #+#    #+#             */
/*   Updated: 2023/06/12 14:01:01 by rrebois          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minishell.h"

void	free_substr_strct(t_substr *s)
{
	if (s->before)
		free(s->before);
	if (s->middle)
		free(s->middle);
	if (s->after)
		free(s->after);
	if (s->sub_b)
		free(s->sub_b);
	if (s->sub_m)
		free(s->sub_m);
	if (s->sub_a)
		free(s->sub_a);
	ft_bzero(s, sizeof(t_substr));
}

void	free_substr_strct_hd(t_substr *s)
{
	if (s->s)
		free(s->s);
	if (s->before)
		free(s->before);
	if (s->middle)
		free(s->middle);
	if (s->after)
		free(s->after);
	if (s->sub_b)
		free(s->sub_b);
	if (s->sub_m)
		free(s->sub_m);
	if (s->sub_a)
		free(s->sub_a);
	ft_bzero(s, sizeof(t_substr));
}
