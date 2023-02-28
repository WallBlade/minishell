/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_tokens3.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smessal <smessal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 15:39:15 by zel-kass          #+#    #+#             */
/*   Updated: 2023/02/28 15:42:22 by smessal          ###   ########.fr       */
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

int	in_quotes(t_tks *tks, char *str, int i)
{
	int	q_len;
	int	dq_len;

	q_len = count_elem(str, '\'');
	dq_len = count_elem(str, '"');
	if ((between_squotes(tks->q, q_len, i))
		|| (between_dquotes(tks->dq, dq_len, i)))
		return (1);
	return (0);
}
