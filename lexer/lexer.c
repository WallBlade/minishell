/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smessal <smessal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 14:39:34 by smessal           #+#    #+#             */
/*   Updated: 2022/12/08 21:01:39 by smessal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_cmd	**epur_str(char **str)
{
	t_cmd	**full;
	t_cmd	*temp;
	int		i;

	i = 0;
	full = malloc(sizeof(t_cmd *));
	if (!full)
		return (NULL);
	full = NULL;
	while (str && str[i])
	{
		temp = malloc(sizeof(t_cmd));
		if (!temp)
			return (NULL);
		temp->full = ft_split(str[i], ' ');
		lstaddback(full, temp);
		printf("%s\n", temp->full[0]);
		i++;
	}
	return (full);	
}

int main()
{
	char    *test;
	char	**str;
	t_cmd	**cmd;
	int		i;

	test = readline("minishell> ");
	cmd = NULL;
	while (ft_strncmp(test, "exit", 4))
	{
		test = readline("minishell> ");
		if (!ft_strncmp(test, "print", 5))
		{
			printf("test\n");
			while (cmd && (*cmd))
			{
				i = 0;
				while ((*cmd)->full[i])
				{
					printf("%s ", (*cmd)->full[i]);
					i++;
				}
				printf("\n\n");
				*cmd = (*cmd)->next;
			}
		}
		str = ft_split(test, '|');
		cmd = epur_str(str);
		add_history(test);
	}
	rl_clear_history();
}