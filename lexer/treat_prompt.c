/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   treat_prompt.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zel-kass <zel-kass@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/12 23:01:19 by smessal           #+#    #+#             */
/*   Updated: 2022/12/13 22:03:05 by zel-kass         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	count_pipes(char *str, t_tks *tks)
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

int	*pipe_strlen(char *str, t_tks *tks)
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

int	ft_cwords(char const *s, char c, t_tks *tks)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (s && s[i])
	{
		if (s[i] != c || between_quotes(tks, i, s[i]))
		{
			count++;
			while (s[i] && (s[i] != c))
				i++;
		}
		while (s[i] && s[i] == c && !between_quotes(tks, i, s[i]))
			i++;
	}
	return (count);
}

size_t	ft_wdlen(char const *s, char c, int i, t_tks *tks)
{
	size_t	len;

	len = 0;
	while (s && s[i] && (s[i] != c || between_quotes(tks, i, s[i])))
	{
		i++;
		len++;
	}
	return (len);
}

char	**split(char *s, char c, t_tks *tks)
{
	char	**big;
	int		i;
	int		j;
	int		k;

	big = (char **)malloc(sizeof(char *) * (ft_cwords(s, c, tks) + 1));
	if (!big)
		return (NULL);
	i = 0;
	j = 0;
	while (j < ft_cwords(s, c, tks))
	{
		k = 0;
		while (s[i] && s[i] == c && !between_quotes(tks, i, s[i]))
			i++;
		big[j] = malloc(sizeof(char) * (ft_wdlen(s, c, i, tks) + 1));
		if (!big[j])
			return (NULL);
		while (s[i] && (s[i] != c || between_quotes))
			big[j][k++] = s[i++];
		big[j++][k] = '\0';
	}
	big[j] = 0;
	return (big);
}

// char	**split_cleaner_2000(char **sdf, t_tks *tks)
// {
// 	int		i;
// 	int		len;
// 	char	**clean;

// 	i = 0;
// 	clean = ft_split(sdf[i], ' ');
// }