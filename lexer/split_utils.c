/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smessal <smessal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/15 20:40:46 by zel-kass          #+#    #+#             */
/*   Updated: 2023/02/28 22:17:55 by smessal          ###   ########.fr       */
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
	char	c;

	i = 0;
	count = 0;
	while (str && str[i])
	{
		if (str[i] && (str[i] != ' ' && str[i] != '\t'))
		{
			count++;
			while (str[i] && (str[i] != ' ' && str[i] != '\t'))
			{
				if (str[i] && (str[i] == '"' || str[i] == '\t'))
				{
					c = str[i++];
					while (str[i] && str[i] != c)
						i++;
				}
				i++;
			}
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

char	*fill_wrd(char *s, int *i)
{
	int		j;
	int		k;
	char	c;
	char	*ret;

	j = 0;
	k = *i;
	ret = collect(sizeof(char) * (wdlen(s, k) + 1));
	if (!ret)
		return (NULL);
	while (s[k] && s[k] != ' ' && s[k] != '\t')
	{
		if (s[k] && (s[k] == '"' || s[k] == '\''))
		{
			c = s[k++];
			while (s[k] && s[k] != c)
				ret[j++] = s[k++];
			k++;
		}
		if (s[k] && s[k] != ' ' && s[k] != '\t' && s[k] != '"' && s[k] != '\'')
			ret[j++] = s[k++];
		*i = k;
	}
	ret[j] = '\0';
	return (ret);
}
