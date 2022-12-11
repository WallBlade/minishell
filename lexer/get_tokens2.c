/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_tokens2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smessal <smessal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/11 21:13:18 by smessal           #+#    #+#             */
/*   Updated: 2022/12/11 21:19:34 by smessal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	active_dol_token(char *line, t_tok *tks)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (line && line[i])
	{
		if (line[i] == '$'  && between_quotes(tks, i, '\''))
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

