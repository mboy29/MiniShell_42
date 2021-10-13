/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alabalet <alabalet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/09 17:58:02 by alabalet          #+#    #+#             */
/*   Updated: 2021/10/11 19:13:59 by alabalet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_symbol(char c)
{
	return (c == '<' || c == '>' || c == '|' || c == ' ');
}

int	word_count(char *str)
{
	int		i;
	int		wc;
	char	q;

	wc = 0;
	i = 0;
	q = 0;
	while (str[i])
	{
		while (str[i] == ' ')
			i++;
		wc++;
		if (is_symbol(str[i]))
			i += 1 + (str[i] != '|' && str[i] == str[i + 1]);
		else
		{
			while (str[i] && (q != 0 || !is_symbol(str[i])))
			{
				if (str[i] == '"' || str[i] == '\'')
					q = str[i] * (q == 0) + q * (q != str[i]);
				i++;
			}
		}
	}
	return (wc);
}

char	*parse_symbol(char *str, int *i)
{
	char	*word;

	word = malloc(3);
	if (str[*i] != '|' && str[*i + 1] == str[*i])
	{
		word[0] = str[*i];
		word[1] = str[*i + 1];
		word[2] = 0;
		*i += 2;
	}
	else
	{
		word[0] = str[*i];
		word[1] = 0;
		*i += 1;
	}
	return (word);
}

char	*parse_word(char *str, int *i)
{
	char	*word;
	char	q;
	int		i_word;

	word = malloc(ft_strlen(str));
	i_word = 0;
	q = 0;
	while (str[*i] && (q != 0 || !is_symbol(str[*i])))
	{
		if (str[*i] == '"' || str[*i] == '\'')
			q = str[*i] * (q == 0) + q * (q != str[*i]);
		word[i_word++] = str[*i];
		(*i)++;
	}
	word[i_word] = 0;
	return (word);
}

/*
Alloue et remplit un tableau de string dans v
en separant line selon les ' ' unquoted et les
caracteres speciaux : "<, >, <<, >>, |"
Conserve les quotes
Verifie la syntaxe
*/
int	lexer(t_vars *v, char *line)
{
	int	wc;
	int	i_tab;
	int	i_str;

	wc = word_count(line);
	v->word_tab = malloc((wc + 1) * sizeof(char *));
	i_tab = -1;
	i_str = 0;
	while (++i_tab < wc)
	{
		while (line[i_str] == ' ')
			i_str++;
		if (is_symbol(line[i_str]))
			v->word_tab[i_tab] = parse_symbol(line, &i_str);
		else
			v->word_tab[i_tab] = parse_word(line, &i_str);
	}
	v->word_tab[i_tab] = 0;
	return (check_syntax(v->word_tab));
}
