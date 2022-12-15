/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   treat_prompt.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smessal <smessal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/12 23:01:19 by smessal           #+#    #+#             */
/*   Updated: 2022/12/15 22:14:49 by smessal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*fill_2_ouf(char *str, int len, int *k)
{
	
	int		j;
	char	*ret;
	
	ret = malloc(sizeof(char) * (len + 1));
	if (!ret)
		return (NULL);
	j = 0;
	while (j < len)
		ret[j++] = str[*k++];
	ret[j] = '\0';
	*k = *k + 1;
	return (ret);
}

char	**split_2_ouf(char *str, t_tks *tks)
{
	int		i;
	int		k;
	int		*len;
	char	**sdf;

	i = -1;
	k = 0;
	len = pipe_strlen(str, tks);
	if (!len)
		return (NULL);
	sdf = malloc(sizeof(char *) * (count_pipes(str, tks) + 1));
	if (!sdf)
		return (NULL);
	printf("len: %d\n", len[0]);
	while (++i < count_pipes(str, tks))
		sdf[i] = fill_2_ouf(str, len[i], &k);
	sdf[i] = 0;
	return (sdf);
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