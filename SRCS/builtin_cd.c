/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgellon <tgellon@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 12:36:28 by rrebois           #+#    #+#             */
/*   Updated: 2023/04/28 11:57:39 by tgellon          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minishell.h"

char	*search_env(t_data *data, char *env, char *str)
{
	t_env	*tmp;
	size_t	size;
	int		i;

	tmp = data->env;
	size = ft_list_size(tmp);
	i = 0;
	while (i < size)
	{
		if (ft_strcmp(env, str))
		tmp = tmp->next;
		i++;
	}
}

int	ft_cd(t_data *data, char **cmd)
{
	char	*home;
	t_env	*tmp;
	int		i;

	if (cmd[2])
		return (printf("minishell: cd: too many arguments"), 0);
	tmp = data->env;
	if (cmd[0] && (!cmd[1] || cmd[1][0] == '\0' || cmd[1][0] == '~'))
	{
		while (tmp->next != NULL)
		{
			if (ft_strncmp(tmp->var_name, "HOME", 4))
			{
				home = ft_strdup(tmp->var_value);
				// if (!home)
				// 	;
				chdir(home);
				free (home);
				return (1);
			}
			tmp = tmp->next;
		}
	}
	if (chdir(cmd[1]) == -1)
		return (perror("chdir: "), 0);
	else
	{
		i = 0;
		while (i <)
	}
}
