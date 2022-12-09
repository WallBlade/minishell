/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smessal <smessal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 21:21:16 by smessal           #+#    #+#             */
/*   Updated: 2022/12/09 01:44:39 by smessal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// int	*find_single_quotes(char *s)
// {
// 	int	count;
// 	int	j;
// 	int	*positions;

// 	count = 0;
// 	j = 0;
// 	while (s && s[j])
// 	{
// 		if (s[j] == '\'')
// 			count++;
// 		j++;
// 	}
// 	positions = malloc(sizeof(int) * (count + 1));
// 	if (!positions)
// 		return (NULL);
// 	j = 0;
// 	count = 0;
// 	while (s && s[j])
// 	{
// 		if (s[j] == '\'')
// 			positions[count++] = j;
// 		j++;
// 	}
// 	positions[count] = 0;
// 	return (positions);
// }

// int	between_quotes(char *s, int i)
// {
// 	int	j;
// 	int	*positions;

// 	j = 0;
// 	positions = find_single_quotes(s);
// 	if (!positions)
// 		return (0);
// 	while (positions && positions[j] && positions[j + 1])
// 	{
// 		if (i > positions[j] && i < positions[j + 1])
// 			return (free(positions), 1);
// 		j++;
// 	}
// 	return (free(positions), 0);
// }

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

	big = (char **)malloc(sizeof(char *) * (ft_cwords(s, c) + 1));
	if (!big)
		return (NULL);
	i = 0;
	j = 0;
	while (j < ft_cwords(s, c))
	{
		k = 0;
		while (s[i] && s[i] == c)
			i++;
		big[j] = malloc(sizeof(char) * (ft_wdlen(s, c, i) + 1));
		if (!big[j])
			return (NULL);
		while (s[i] && (s[i] != c))
			big[j][k++] = s[i++];
		big[j++][k] = '\0';
	}
	big[j] = 0;
	return (big);
}
