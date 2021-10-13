/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alabalet <alabalet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/09 21:38:22 by alabalet          #+#    #+#             */
/*   Updated: 2021/10/10 19:03:47 by alabalet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	heredoc(t_token *tkn, int i)
{
	char	*filename;
	char	*tmp;
	char	*line;
	int		fd;

	tmp = ft_itoa(i);
	filename = ft_strjoin(".tmp", tmp);
	free(tmp);
	fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	g_sig.status = 2;
	line = readline("> ");
	while (line && ft_strncmp(line, tkn->str, ft_strlen(tkn->str)))
	{
		write(fd, line, ft_strlen(line));
		write(fd, "\n", 1);
		free(line);
		line = readline("> ");
	}
	free(line);
	g_sig.status = 1;
	close(fd);
	tkn->type = LEFT;
	free(tkn->str);
	tkn->str = filename;
}

int	substract_quotes(char **str, int i_res, int i_str)
{
	char	q;
	char	*result;

	q = 0;
	result = malloc(ft_strlen(*str));
	while ((*str)[++i_str])
	{
		if ((*str)[i_str] == '\'' || (*str)[i_str] == '"')
		{
			if (q && q != (*str)[i_str])
				result[i_res++] = (*str)[i_str];
			q = (*str)[i_str] * (q == 0) + q * (q != (*str)[i_str]);
		}
		else
			result[i_res++] = (*str)[i_str];
		if (q == 0 && (*str)[i_str] == ' ')
		{
			free(result);
			return (1);
		}
	}
	result[i_res] = 0;
	free(*str);
	*str = result;
	return (0);
}

int	parse_redir(t_vars *v)
{
	int	i;
	int	i_hd;

	i = -1;
	i_hd = 0;
	while (v->tkn_tab[++i].type)
	{
		if (v->tkn_tab[i].type == LLEFT)
		{
			substract_quotes(&(v->tkn_tab[i].str), 0, -1);
			heredoc(&(v->tkn_tab[i]), i_hd++);
		}
		else if (LEFT <= v->tkn_tab[i].type && v->tkn_tab[i].type <= RRIGHT)
		{
			expand(&(v->tkn_tab[i].str), v);
			if (substract_quotes(&(v->tkn_tab[i].str), 0, -1))
			{
				print_error("minishell: ambiguous redirect\n", 3);
				return (1);
			}
		}
	}
	return (0);
}

/*
Tranforme la liste de mots en une liste de tokens
Parcours la liste des tokens de redirection :
	Si <, > ou >> :
		expand les variable not single quoted
		soustrait les quotes unquoted et retourne une erreur si ' ' unquoted
			-> ambiguous redirect
	
	Si <<
		ouvre un fichier temporaire
		Remplit le fichier avec des prompts succesifs
		Ferme le fichier
		remplace le token par un token de type LEFT avec filename en argument
		incremente compteur de heredoc
*/
int	tokenize(t_vars *v)
{
	int	i_word;
	int	i_tkn;

	i_tkn = 0;
	i_word = -1;
	while (v->word_tab[++i_word])
		;
	v->tkn_tab = malloc((i_word + 1) * sizeof(t_token));
	i_word = 0;
	while (v->word_tab[i_word])
	{
		v->tkn_tab[i_tkn].type = get_type(v->word_tab[i_word]);
		if (v->tkn_tab[i_tkn].type == PIPE)
			v->tkn_tab[i_tkn].str = 0;
		else if (1 <= v->tkn_tab[i_tkn].type && v->tkn_tab[i_tkn].type <= 4)
			v->tkn_tab[i_tkn].str = ft_strdup(v->word_tab[++i_word]);
		else
			v->tkn_tab[i_tkn].str = ft_strdup(v->word_tab[i_word]);
		i_word++;
		i_tkn++;
	}
	v->tkn_tab[i_tkn].type = END;
	v->tkn_tab[i_tkn].str = 0;
	return (parse_redir(v));
}
