/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smessal <smessal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 14:39:34 by smessal           #+#    #+#             */
/*   Updated: 2022/12/10 01:25:44 by smessal          ###   ########.fr       */
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

void	get_tokens(char *line, t_tok *tks)
{
	int	i;
	int	j;
	int	k;

	i = 0;
	j = 0;
	k = 0;
	while (line[i])
	{
		if (line[i] == '"')
		{
			tks->dq[j++] = i;
			// printf("l = %d\n", tks);
		}
		else if (line[i] == '\'')
			tks->q[k++] = i;
		i++;
	}
}

int main()
{
	t_tok	*tok;
	char    *prompt;

	while (1)
	{
		prompt = readline("minishell> ");
		tok = init_tokens(prompt);
		get_tokens(prompt, tok);
		for (int i = 0; i < count_elem(prompt, '\''); i++)
			printf("%d\n", tok->q[i]);
		add_history(prompt);
	}
	rl_clear_history();
}