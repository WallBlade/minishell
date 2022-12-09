/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zel-kass <zel-kass@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 14:39:34 by smessal           #+#    #+#             */
/*   Updated: 2022/12/09 14:52:54 by zel-kass         ###   ########.fr       */
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

void	get_dquotes(char *line, t_tokens *tks)
{
	int			i;
	int			j;

	i = 0;
	j = 0;
	while (line[i])
	{
		if (line[i] == '"')
		{
			tks->dq_pos[j] = i;
			j++;
		}
		i++;	
	}
	while (tks->dq_pos[i])
	{
		printf("dq = %d\n", tks->dq_pos[i]);
		i++;
	}
}

int main()
{
	char    *test;
	char	**str;
	// t_cmd	*cmd;
	int		i;

	test = readline("minishell> ");
	str = NULL;
	i = 0;
	// cmd = NULL;
	while (ft_strncmp(test, "exit", 4))
	{
		test = readline("minishell> ");
		str = ft_split(test, '|');
		while (str && str[i])
		{
			printf("%s\n", str[i]);
			i++;
		}
		// cmd = epur_str(str);
		add_history(test);
		free(test);
		free_tab(str);
	}
	rl_clear_history();
}