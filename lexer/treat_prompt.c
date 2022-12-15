/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   treat_prompt.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zel-kass <zel-kass@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/12 23:01:19 by smessal           #+#    #+#             */
/*   Updated: 2022/12/15 20:45:06 by zel-kass         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	**split_2_ouf(char *str, t_tks *tks)
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
		while (j < len[i] && str[k] != '|')
			sdf[i][j++] = str[k++];
		sdf[i][j] = '\0';
		k++;
	}
	sdf[i] = 0;
	return (free(len), sdf);
}

char	**split(char *str)
{
	int		i;
	int		j;
	char	**spl;

	spl = malloc(sizeof(char *) * (cwords(str) + 1));
	if (!spl)
		return (NULL);
	i = -1;
	j = 0;
	while (++i < cwords(str))
	{
		while ((str[j] == ' ' || str[i] == '\t')
			&& str[j] != '"' && str[j] != '\'')
			j++;
		if ((str[j] != ' ' && str[j] != '\t') || (str[j] == '"' || str[j] == '\''))
		{
			spl[i] = fill_wrd(str, j);
			if (!spl[i])
				return (free_tab(spl), NULL);
			j = j + ft_strlen(spl[i]);
		}
	}
	spl[i] = 0;
	return (spl);
}