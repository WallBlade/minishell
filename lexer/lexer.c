/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smessal <smessal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 14:39:34 by smessal           #+#    #+#             */
/*   Updated: 2023/02/07 20:49:18 by smessal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	count_elem(char *str, char c)
{
	int	i;
	int	len;

	i = 0;
	len = 0;
	while (str && str[i])
	{
		if ((c == '<' || c == '>') && str[i + 1] &&
			str[i] == c && str[i + 1] == c)
			i++;
		else if (str[i] && str[i] == c)
			len++;
		i++;
	}	
	return (len);
}

int	count_d_elem(char *str, char *sub)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (str && str[i] && str[i + 1])
	{
		if (!ft_strncmp(&str[i], sub, 2))
		{
			count++;
			i++;
		}
		i++;
	}
	return (count);
}

int	is_token(char c)
{
	char	*tok;
	int		i;

	i = 0;
	tok = "<>|\"'$";
	while (tok[i])
	{
		if (tok[i] == c)
			return (1);
		i++;
	}
	return (0);
}

char	**lexer(char *prompt, char **env)
{
	t_tks		*tks;
	char		*expanded;
	
	tks = init_tokens(prompt);
	init_active_tokens(&tks, prompt);
	expanded = expand(prompt, env, tks);
	char **sdf = split_2_ouf(clean_2_ouf(expanded, tks), tks);
	return (sdf);
}

