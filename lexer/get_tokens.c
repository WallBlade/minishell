/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_tokens.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zel-kass <zel-kass@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/11 21:03:41 by smessal           #+#    #+#             */
/*   Updated: 2022/12/13 22:10:01 by zel-kass         ###   ########.fr       */
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
	return (q);
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

int	between_quotes(t_tks *tks, int i, char c)
{
	int	j;
	int	*positions;

	j = 0;
	if (c == '"')
		positions = tks->dq;
	else
		positions = tks->q;
	while (positions && positions[j] >= 0 && positions[j + 1])
	{
		if (i > positions[j] && i < positions[j + 1])
			return (0);
		j = j + 2;
	}
	return (1);
}

int	between_squotes(int *q, int i)
{
	int	j;

	j = 0;
	while (q && q[j] >= 0 && q[j + 1])
	{
		if (i > q[j] && i < q[j + 1])
			return (0);
		j++;
	}
	return (1);
}

int	between_dquotes(int *dq, int i)
{
	int	j;

	j = 0;
	while (dq && dq[j] >= 0 && dq[j + 1])
	{
		if (i > dq[j] && i < dq[j + 1])
			return (0);
		j++;
	}
	return (1);
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
		if (line[i] == c && (between_quotes(tks, i, '"') && 
			between_quotes(tks, i, '\'')))
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

