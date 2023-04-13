/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_var.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgellon <tgellon@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 10:50:17 by tgellon           #+#    #+#             */
/*   Updated: 2023/04/12 16:12:15 by tgellon          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minishell.h"

static char	*env_var_search(t_data *data, char *tmp, int j)
{
	char	*var;

	while (*data->envp)
	{
		if (ft_strncmp(*data->envp, tmp, j - 1) == 0)
		{
			var = ft_substr(*data->envp, j, (ft_strlen(*data->envp) - j));
			// if (var == NULL)
			// 	return (NULL);
			break ;
		}
		else
			var = ft_strdup("");
		// if (var == NULL)
		// 	return (NULL);
		data->envp++;
	}
	return (var);
}

static int	dollar_handle(t_data *data, char *str, char **new_word, int i)
{
	int		j;
	char	*tmp;
	char	*var;

	j = 1;
	while (ft_isalnum(str[i + j]) || str[i + j] == '_')
		j++;
	tmp = ft_substr(str, i + 1, j);
	// if (tmp == NULL)
	// 	return (-2);
	var = env_var_search(data, tmp, j);
	// if (var == NULL)
	// 	return (-2);
	free(tmp);
	*new_word = ft_strjoin_gnl(*new_word, var);
	// if (new_word == NULL)
	// 	 return (-2);
	free(var);
	i += j - 1;
	return (i);
}

static int	s_quote_handle(t_lexer *lexer, char **new_word, int i)
{
	size_t	j;
	char	*tmp;

	j = 0;
	while (lexer->word[i + j] && lexer->word[i + 1] != '\'')
		j++;
	tmp = ft_substr(lexer->word, i, j);
	*new_word = ft_strjoin_gnl(*new_word, tmp);
	free(tmp);
	i += j;
	return (i);
}

static char	*var_replacement(t_data *data, t_lexer *tmp)
{
	char	*new_word;
	int		i;

	i = -1;
	new_word = ft_strdup("");
	while (tmp->word[++i])
	{
		if (tmp->word[i] == '\'')
			tmp->s_q = 1;
		if (tmp->word[i] == '"')
			tmp->d_q = 1;
		if (tmp->s_q && !tmp->d_q && tmp->word[i + 1])
			i = s_quote_handle(data->lexer, &new_word, i);
		if (tmp->word[i] == '$' && ft_isalnum(tmp->word[i + 1]) \
			&& (tmp->d_q || (!tmp->d_q && !tmp->s_q)) && tmp->word[i + 1])
			i = dollar_handle(data, tmp->word, &new_word, i);
		// else if (tmp->word[i] == '$' && (tmp->d_q 
				// || (!tmp->d_q && !tmp->s_q)) && tmp->word[i + 1] == '?')
		// 	; handle with signals
		else
			new_word = char_join_to_str(new_word, tmp->word[i]);
		if (!new_word || i == -2)
			return (NULL);
	}
	return (new_word);
}

int	expand(t_data *data)
{
	t_lexer	*tmp;
	char	*new_word;

	tmp = data->lexer;
	while (tmp != NULL)
	{
		tmp->s_q = 0;
		tmp->d_q = 0;
		if (tmp->word == NULL)
		{
			tmp = tmp->next;
			continue ;
		}
		new_word = var_replacement(data, tmp);
		// if (new_word == NULL)
		// 	return (0);
		free(tmp->word);
		tmp->word = ft_strdup(new_word);
		// if (tmp->word == NULL)
		// 	return (0);
		free(new_word);
		printf("expand-> word :%s\n", tmp->word);
		tmp = tmp->next;
	}
	return (1);
}
