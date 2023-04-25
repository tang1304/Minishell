/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_var.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrebois <rrebois@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 10:50:17 by tgellon           #+#    #+#             */
/*   Updated: 2023/04/25 16:33:03 by rrebois          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minishell.h"

// char	*expand_dollar(t_data *data, char *s, size_t *i) //func too long
// {
// 	char	*bef;
// 	char	*exp;
// 	char	*aft;

// 	bef = NULL;
// 	exp = NULL;
// 	aft = NULL;
// 	while (s[*i] != '\0')
// 	{
// 		if (*i > 0)
// 			bef = ft_substr(s, 0, *i);
// // if (bef != NULL)
// 	// printf("\n\n\nbef = %s c = %d\n", bef, bef[ft_strlen(bef) - 1]);
// 		while (ft_isalnum(s[*i] == 1))
// 			*i = *i + 1;//ou fonc si 0 alors ++ sinon break et chercher aussi $
// 				// if (s[j] == '$' && s[j - 1] && s[j - 1] != '$')
// 				// 	break ;




// // printf("char stopped: %c\n", s[j]);
// 		aft = ft_substr(s, *i, ft_strlen(s));
// // printf("aft = %s c = %d\n", aft, aft[ft_strlen(aft) - 1]);
// 		exp = ft_substr(s, ft_strlen(bef) + 1, *i - ft_strlen(bef) - 1);
// // printf("exp = %s c = %d\n\n\n", exp, exp[ft_strlen(exp) - 1]);
// 			// s = get_var()
// 		exp = get_var(data, exp);
// 		*i = ft_strlen(bef) + ft_strlen(exp);
// 	}
// 	return (join_all(s, bef, exp, aft));
// }

char	*get_var(t_data *data, char *s)
{printf("WORD PASSED: %s\n", s);
	char	*var;
	size_t	i;
	size_t	k;

	k = 0;
	var = ft_strdup("");
	// if (var == NULL)
	// 	return (NULL);
	while (data->envp[k])
	{
		i = 0;
		while (data->envp[k][i] != '=')
			i++;
//
		if (ft_strncmp(data->envp[k], s, i - 1) == 0 && ft_strlen(s) == i)
		{
			free(var);
			var = ft_substr(data->envp[k], i + 1, (ft_strlen(*data->envp)));
			// if (var == NULL)
			// 	return (NULL);
			break ;
		}
		k++;
	}
	return (var);
}

char	*join_all(char *s, char *b, char *e, char *a)
{
	free(s);
	s = NULL;
	if (b != NULL && e != NULL)
		s = ft_strjoin_free(b, e);
	else if (b == NULL && e != NULL)
		s = e;
	else if (b != NULL && e == NULL)
		s = b;
	if (a != NULL)
		s = ft_strjoin_free(s, a);
	return (s);
}
