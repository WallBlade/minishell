/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zel-kass <zel-kass@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 12:03:58 by smessal           #+#    #+#             */
/*   Updated: 2023/02/26 14:20:55 by zel-kass         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	cwords_syn(char *str)
{
	int		i;
	int		count;
	char	c;

	i = 0;
	count = 0;
	while (str && str[i])
	{
		if (str[i] && (str[i] == '"' || str[i] == '\''))
		{
			c = str[i++];
			count++;
			while (str[i] && str[i] != c)
				i++;
			i++;
		}
		else if (str[i] && (str[i] != ' ' && str[i] != '\t'))
		{
			count++;
			while (str[i] && (str[i] != ' ' && str[i] != '\t'))
				i++;
		}
		i++;
	}
	return (count);
}

int	wdlen_syn(char *str, int i)
{
	int		len;
	char	c;

	len = 0;
	if (str[i] && (str[i] == '"' || str[i] == '\''))
	{
		c = str[i];
		while (str[i] && str[++i] != c)
			len++;
		return (len + 1);
	}
	while (str[i] && str[i] != ' ' && str[i] != '\t')
	{
		i++;
		len++;
	}
	return (len);
}

char	*fill_wrd_syn(char *str, int *i)
{
	int		j;
	int		k;
	char	c;
	char	*ret;

	j = 0;
	k = *i;
	ret = malloc(sizeof(char) * (wdlen_syn(str, k) + 1));
	if (!ret)
		return (NULL);
	if (str[k] && (str[k] == '"' || str[k] == '\''))
	{
		c = str[k];
		ret[j++] = str[k++];
		while (str[k] && str[k] != c)
			ret[j++] = str[k++];
		ret[j++] = str[k++];
		*i = k;
	}
	else
	{
		while (str[k] && str[k] != ' ' && str[k] != '\t')
			ret[j++] = str[k++];
		*i = k;
	}
	ret[j] = '\0';
	return (ret);
}

char	**split_syn(char *str)
{
	int		i;
	int		j;
	char	**spl;

	spl = malloc(sizeof(char *) * (cwords_syn(str) + 1));
	if (!spl)
		return (NULL);
	i = -1;
	j = 0;
	while (++i < cwords_syn(str))
	{
		while ((str[j] == ' ' || str[i] == '\t')
			&& (str[j] != '"' && str[j] != '\''))
			j++;
		if ((str[j] != ' ' && str[j] != '\t')
			|| (str[j] == '"' || str[j] == '\''))
		{
			spl[i] = fill_wrd_syn(str, &j);
			if (!spl[i])
				return (free_tab(spl), NULL);
		}
	}
	spl[i] = 0;
	return (spl);
}
