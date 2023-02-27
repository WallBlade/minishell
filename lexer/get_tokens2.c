/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_tokens2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smessal <smessal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/11 21:13:18 by smessal           #+#    #+#             */
/*   Updated: 2023/02/27 17:32:03 by smessal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	conditions_quotes(int *dominant, int *tab, int index)
{
	if (*dominant == 2)
		tab[index] = 0;
	else if (*dominant == 1)
	{
		tab[index] = 1;
		*dominant = 0;
	}
	else
	{
		tab[index] = 1;
		*dominant = 1;
	}
}

void	conditions_dquotes(int *dominant, int *tab, int index)
{
	if (*dominant == 1)
		tab[index] = 0;
	else if (*dominant == 2)
	{
		tab[index] = 1;
		*dominant = 0;
	}
	else
	{
		tab[index] = 1;
		*dominant = 2;
	}
}

void	active_quotes(char *line, t_tks *tks)
{
	int	i;
	int	j;
	int	k;
	int	dominant;

	i = 0;
	j = 0;
	k = 0;
	dominant = 0;
	while (line && line[i])
	{
		if (line[i] == '\'')
			conditions_quotes(&dominant, tks->q_on, j++);
		else if (line[i] == '"')
			conditions_dquotes(&dominant, tks->dq_on, k++);
		i++;
	}
}

void	active_d_tokens(char *line, t_tks *tks, char *dc)
{
	int	i;
	int	j;
	int	k;

	i = -1;
	j = 0;
	k = 0;
	if (!ft_strncmp(dc, ">>", 2))
		k = 1;
	else if (!ft_strncmp(dc, "<<", 2))
		k = 2;
	while (line && line[++i])
	{
		if (!ft_strncmp(&line[i], dc, 2) && (not_quotes(tks, i, '"'))
			&& (not_quotes(tks, i, '\'')))
		{
			fill_tks(&tks, k, 1, j++);
			i++;
		}
		else if (!ft_strncmp(&line[i], dc, 2))
		{
			fill_tks(&tks, k, 0, j++);
			i++;
		}
	}
}
