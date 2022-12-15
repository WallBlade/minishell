/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_tokens2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zel-kass <zel-kass@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/11 21:13:18 by smessal           #+#    #+#             */
/*   Updated: 2022/12/13 22:30:37 by zel-kass         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
		if (!ft_strncmp(&line[i], dc, 2) && (not_quotes(tks, i, '"') && 
			not_quotes(tks, i, '\'')))
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