/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_tokens3.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zel-kass <zel-kass@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 15:39:15 by zel-kass          #+#    #+#             */
/*   Updated: 2023/02/27 15:48:06 by zel-kass         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	get_squotes(char *line, int *q)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (line[i])
	{
		if (line[i] == '\'')
			q[j++] = i;
		i++;
	}
}

void	get_dquotes(char *line, int *dq)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (line[i])
	{
		if (line[i] == '"')
			dq[j++] = i;
		i++;
	}
}

int	not_quotes(t_tks *tks, int i, char c)
{
	int	j;
	int	*positions;

	j = 0;
	if (c == '"')
		positions = tks->dq;
	else
		positions = tks->q;
	while (positions && j < count_elem(tks->prompt, c))
	{
		if (i > positions[j] && i < positions[j + 1])
			return (0);
		j = j + 2;
	}
	return (1);
}

void	active_dol_token(char *line, t_tks *tks)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (line && line[i])
	{
		if (line[i] == '$' && not_quotes(tks, i, '\''))
		{
			fill_tks(&tks, '$', 1, j);
			j++;
		}
		else if (line[i] == '$')
		{
			fill_tks(&tks, '$', 0, j);
			j++;
		}
		i++;
	}
}
