/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zel-kass <zel-kass@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 21:21:16 by smessal           #+#    #+#             */
/*   Updated: 2023/02/26 17:58:55 by zel-kass         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_cwords(char const *s, char c)
{
	size_t	i;
	size_t	count;

	i = 0;
	count = 0;
	while (s && s[i])
	{
		if (s[i] != c)
		{
			count++;
			while (s[i] && (s[i] != c))
				i++;
		}
		while (s[i] && s[i] == c)
			i++;
	}
	return (count);
}

static size_t	ft_wdlen(char const *s, char c, int i)
{
	size_t	len;

	len = 0;
	while (s && s[i] && (s[i] != c))
	{
		i++;
		len++;
	}
	return (len);
}

char	**ft_split(char *s, char c)
{
	char	**big;
	size_t	i;
	size_t	j;
	size_t	k;

	big = (char **)collect(sizeof(char *) * (ft_cwords(s, c) + 1));
	if (!big)
		return (NULL);
	i = 0;
	j = 0;
	while (j < ft_cwords(s, c))
	{
		k = 0;
		while (s[i] && s[i] == c)
			i++;
		big[j] = collect(sizeof(char) * (ft_wdlen(s, c, i) + 1));
		if (!big[j])
			return (NULL);
		while (s[i] && (s[i] != c))
			big[j][k++] = s[i++];
		big[j++][k] = '\0';
	}
	big[j] = 0;
	return (big);
}
