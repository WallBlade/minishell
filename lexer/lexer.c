/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zel-kass <zel-kass@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 14:39:34 by smessal           #+#    #+#             */
/*   Updated: 2023/03/06 20:06:26 by zel-kass         ###   ########.fr       */
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
		if ((c == '<' || c == '>') && str[i + 1]
			&& str[i] == c && str[i + 1] == c)
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
	tok = "<>|\"'$.+[]@#:%";
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
	t_tks	*tks;
	char	*expanded;
	char	**sdf;
	char	*cdo;

	tks = init_tokens(prompt);
	init_active_tokens(&tks, prompt);
	expanded = expand(prompt, env, tks);
	if (syntax_error(prompt, tks) == 1)
	{
		g_status = 2;
		ft_putstr_fd("minishell: syntax error near unexpected token\n", 2);
		return (NULL);
	}
	if (syntax_error(prompt, tks) == 2)
	{
		g_status = 127;
		ft_putstr_fd("minishell: Command not found\n", 2);
		return (NULL);
	}
	cdo = final_treat(prompt_2_ouf(clean_2_ouf(expanded, tks), tks), tks);
	sdf = split_2_ouf(cdo, tks);
	return (sdf);
}
