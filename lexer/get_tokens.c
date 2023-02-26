/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_tokens.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zel-kass <zel-kass@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/11 21:03:41 by smessal           #+#    #+#             */
/*   Updated: 2023/02/25 20:02:06 by zel-kass         ###   ########.fr       */
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

int	in_quotes(t_tks *tks, char *str, int i)
{
	int	q_len;
	int	dq_len;
	
	q_len = count_elem(str, '\'');
	dq_len = count_elem(str, '"');
	if ((between_squotes(tks->q, q_len, i) || between_dquotes(tks->dq, dq_len, i)))
		return (1);
	return (0);
}

int	between_squotes(int *q, int len, int i)
{
	int	j;

	j = 0;
	while (q && j < len)
	{
		if (i > q[j] && i < q[j + 1])
			return (1);
		j += 2;
	}
	return (0);
}

int	between_dquotes(int *dq, int len, int i)
{
	int	j;

	j = 0;
	while (dq && j < len)
	{
		if (i > dq[j] && i < dq[j + 1])
			return (1);
		j += 2;
	}
	return (0);
}

void	fill_tks(t_tks **tks, char c, int active, int j)
{
	if (c == '|')
		(*tks)->p[j] = active;
	else if (c == '<')
		(*tks)->in[j] = active;
	else if (c == '>')
		(*tks)->out[j] = active;
	else if (c == '$')
		(*tks)->dol[j] = active;
	else if (c == '?')
		(*tks)->qst[j] = active;
	else if (c == 1)
		(*tks)->ap[j] = active;
	else if (c == 2)
		(*tks)->d_in[j] = active;
}

void	active_s_tokens(char *line, t_tks *tks, char c)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (line && line[i])
	{
		if (line[i] == c && (not_quotes(tks, i, '"') && 
			not_quotes(tks, i, '\'')))
		{
			fill_tks(&tks, c, 1, j);
			j++;
		}
		else if (line[i] == c)
		{
			fill_tks(&tks, c, 0, j);
			j++;
		}
		i++;
	}
}
