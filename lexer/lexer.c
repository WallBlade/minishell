/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smessal <smessal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 14:39:34 by smessal           #+#    #+#             */
/*   Updated: 2022/12/12 23:05:05 by smessal          ###   ########.fr       */
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
		if ((c == '<' || c == '>') && str[i + 1] && str[i] == c && str[i + 1] == c)
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
	tok = "<>|\"'$?";
	while (tok[i])
	{
		if (tok[i] == c)
			return (1);
		i++;
	}
	return (0);
}

int main()
{
	t_tks	*tks;
	char    *prompt;

	while (1)
	{
		prompt = readline("minishell> ");
		tks = init_tokens(prompt);
		init_active_tokens(&tks, prompt);
		printf("pipes = %d\n", count_pipes(prompt, tks));
		pipe_strlen(prompt, tks);
		int *len = pipe_strlen(prompt, tks);
		for (int i = 0; len[i]; i++)
			printf("len[%d] = %d\n", i, len[i]);
		split_2_ouf(prompt, tks);
		// for (int i = 0; sdf[i]; i++)
		// 	printf("sdf[%d] = %s\n", i, sdf[i]);
		add_history(prompt);
	}
	rl_clear_history();
}
