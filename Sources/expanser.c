/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expanser.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alabalet <alabalet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/09 23:08:08 by alabalet          #+#    #+#             */
/*   Updated: 2021/10/10 18:38:45 by alabalet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_posix(char c)
{
	return ((ft_isalpha(c) || c == '_' || c == '?'));
}

char	*get_substr(char *str, int *i, t_vars *v)
{
	char	*value;
	char	*key;
	int		i_key;

	key = malloc(ft_strlen(str));
	i_key = 0;
	while (ft_isalnum(str[*i + i_key]) || str[*i + i_key] == '_')
	{
		key[i_key] = str[*i + i_key];
		i_key++;
	}
	key[i_key] = 0;
	*i += i_key - 1;
	value = get_tabenv(v, key);
	free(key);
	return (value);
}

void	str_replace(char **str, char *substr, int i1, int *i)
{
	char	*ret;
	int		i_str;
	int		i_ret;

	i_str = -1;
	i_ret = -1;
	ret = malloc(ft_strlen(*str) + ft_strlen(substr) + 1);
	while (++i_str < i1)
		ret[++i_ret] = (*str)[i_str];
	i_str = -1;
	while (substr[++i_str])
		ret[++i_ret] = substr[i_str];
	i_str = *i;
	*i = i_ret;
	while ((*str)[++i_str])
		ret[++i_ret] = (*str)[i_str];
	ret[i_ret + 1] = 0;
	free(*str);
	*str = ret;
}

/*
Remplace :
	$? par g_sig.exit_code
	$var par sa valeur dans tabenv
		var doit commencer par un caractere alphabetique ou par un _
		si var n'existe pas ou n'a pas de valeur $var -> ""
*/
void	expand(char **str, t_vars *v)
{
	char	*substr;
	int		i;
	int		i1;
	char	q;

	i = -1;
	q = 0;
	while ((*str)[++i])
	{
		if ((*str)[i] == '\'' || (*str)[i] == '"')
			q = (*str)[i] * (q == 0) + q * (q != (*str)[i]);
		if (q != '\'' && (*str)[i] == '$' && is_posix((*str)[i + 1]))
		{
			i1 = i++;
			if ((*str)[i] == '?')
				substr = ft_itoa(g_sig.exit_code);
			else
				substr = get_substr(*str, &i, v);
			str_replace(str, substr, i1, &i);
			free(substr);
			q = 0;
		}
	}
}
