/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_tokens.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smessal <smessal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/11 21:03:41 by smessal           #+#    #+#             */
/*   Updated: 2022/12/12 23:06:29 by smessal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	get_quotes(char *line, t_tks *tks)
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
			tks->dq[j++] = i;
		else if (line[i] == '\'')
			tks->q[k++] = i;
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

void	active_d_tokens(char *line, t_tks *tks, char *dc)
{
	int	i;
	int	j;
	int	k;

	i = 0;
	j = 0;
	k = 0;
	if (!ft_strncmp(dc, ">>", 2))
		k = 1;
	else if (!ft_strncmp(dc, "<<", 2))
		k = 2;
	while (line && line[i])
	{
		if (!ft_strncmp(&line[i], dc, 2) && (between_quotes(tks, i, '"') && 
			between_quotes(tks, i, '\'')))
		{
			fill_tks(&tks, k, 1, j);
			j++;
		}
		else if (!ft_strncmp(&line[i], dc, 2))
		{
			fill_tks(&tks, k, 0, j);
			j++;
		}
		i++;
	}
}
