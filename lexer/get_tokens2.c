/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_tokens2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zel-kass <zel-kass@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/11 21:13:18 by smessal           #+#    #+#             */
/*   Updated: 2022/12/12 22:51:16 by zel-kass         ###   ########.fr       */
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

int	count_pipes(char *str, t_tok *tks)
{
	int	i;
	int	j;
	int	count;

	i = 0;
	j = 0;
	count = 0;
	while (str && str[i])
	{
		if (str[i] == '|' && tks->p[j++] == 1)
			count++;
		i++;
	}
	return (count + 1);
}

int	*pipe_strlen(char *str, t_tok *tks)
{
	int	i;
	int	j;
	int	count;
	int	*lens;

	i = 0;
	j = 0;
	count = 0;
	lens = malloc(sizeof(int) * (count_pipes(str, tks)));
	if (!lens)
		return (0);
	while (str && str[i])
	{
		if (str[i] == '|' && tks->p && tks->p[j] == 1)
		{
			lens[j] = count;
			count = 0;
			j++;
		}
		i++;
		count++;
	}
	lens[j] = count;
	return (lens);
}

char	**split_2_ouf(char *str, t_tok *tks)
{
	int		i;
	int		j;
	int		k;
	int		*len;
	char	**sdf;
	
	i = -1;
	k = 0;
	len = pipe_strlen(str, tks);
	sdf = malloc(sizeof(char *) * (count_pipes(str, tks) + 1));
	if (!sdf)
		return (NULL);
	while (++i < count_pipes(str, tks))
	{
		sdf[i] = malloc(sizeof(char) * (len[i] + 1));
		if (!sdf[i])
			return (free_tab(sdf), NULL);
		j = 0;
		while (j < len[i] && str[k])
			sdf[i][j++] = str[k++];
		sdf[i][j] = '\0';
		printf("%s\n", sdf[i]);
		k++;
	}
	sdf[i] = 0;
	return (sdf);
}