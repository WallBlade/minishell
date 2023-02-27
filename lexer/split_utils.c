/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zel-kass <zel-kass@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/15 20:40:46 by zel-kass          #+#    #+#             */
/*   Updated: 2023/02/27 16:50:46 by zel-kass         ###   ########.fr       */
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
	int	k;
	int	count;
	int	*lens;

	i = 0;
	j = 0;
	k = 0;
	count = 0;
	lens = collect(sizeof(int) * (count_pipes(str, tks)));
	if (!lens)
		return (0);
	while (str && str[i])
	{
		if (str[i] == '|' && tks->p[j++] == 1)
		{
			lens[k++] = count;
			count = -1;
		}
		i++;
		count++;
	}
	lens[k] = count;
	return (lens);
}

int	cwords(char *str)
{
	int		i;
	int		count;

	i = 0;
	count = 0;
	while (str && str[i])
	{
		if (str[i] && (str[i] != ' ' && str[i] != '\t'))
		{
			count++;
			while (str[i] && (str[i] != ' ' && str[i] != '\t'))
				i++;
		}
		while (str[i] && (str[i] == ' ' || str[i] == '\t'))
			i++;
	}
	return (count);
}

int	wdlen(char *str, int i)
{
	int		len;
	char	c;

	len = 0;
	while (str[i] && (str[i] != ' ' && str[i] != '\t'))
	{
		if (str[i] == ' ' || str[i] == '\t')
			i++;
		if (str[i] && (str[i] == '"' || str[i] == '\''))
		{
			if (str[i + 1])
				c = str[i++];
			while (str[i] && str[i++] != c)
				len++;
		}
		if (i >= ft_strlen(str) || str[i] == ' ' || str[i] == '\t')
			break ;
		i++;
		len++;
	}
	return (len);
}

char	*fill_wrd(char *str, int *i)
{
	int		j;
	int		k;
	char	c;
	char	*ret;

	j = 0;
	k = *i;
	ret = collect(sizeof(char) * (wdlen(str, k) + 1));
	if (!ret)
		return (NULL);
	while (str[k] && str[k] != ' ' && str[k] != '\t')
	{
		if (str[k] && (str[k] == '"' || str[k] == '\''))
		{
			c = str[k++];
			while (str[k] && str[k] != c)
				ret[j++] = str[k++];
			k++;
		}
		if (str[k] && str[k] != ' ' && str[k] != '\t' && str[k] != '"' && str[k] != '\'')
			ret[j++] = str[k++];
		*i = k;
	}
	ret[j] = '\0';
	return (ret);
}
