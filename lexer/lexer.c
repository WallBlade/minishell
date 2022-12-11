/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smessal <smessal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 14:39:34 by smessal           #+#    #+#             */
/*   Updated: 2022/12/11 21:22:17 by smessal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// t_cmd	*epur_str(char **str)
// {
// 	t_cmd	*brut;
// 	t_cmd	*temp;
// 	int		i;

// 	i = 0;
// 	brut = malloc(sizeof(t_cmd));
// 	if (!brut)
// 		return (NULL);
// 	brut = NULL;
// 	while (str && str[i])
// 	{
// 		temp = malloc(sizeof(t_cmd));
// 		if (!temp)
// 			return (NULL);
// 		temp->next = NULL;
// 		temp->brut = ft_split(str[i], ' ');
// 		lstaddback(&brut, temp);
// 		i++;
// 	}
// 	return (brut);	
// }

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
	t_tok	*tok;
	char    *prompt;

	while (1)
	{
		prompt = readline("minishell> ");
		tok = init_tokens(prompt);
		init_active_tokens(&tok, prompt);
		for (int i = 0; i < count_elem(prompt, '$'); i++)
			printf("%d\n", tok->dol[i]);
		add_history(prompt);
	}
	rl_clear_history();
}
