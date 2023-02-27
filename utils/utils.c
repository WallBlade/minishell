/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smessal <smessal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 19:31:06 by smessal           #+#    #+#             */
/*   Updated: 2023/02/27 15:38:24 by smessal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	len_tab(char **tab)
{
	int	i;

	i = 0;
	while (tab && tab[i])
		i++;
	return (i);
}

char	**ft_strdup_tab(char **tab)
{
	int		i;
	char	**dupl;

	i = 0;
	dupl = collect(sizeof(char *) * (len_tab(tab) + 1));
	if (!dupl)
		return (NULL);
	while (tab && tab[i])
	{
		dupl[i] = ft_strdup(tab[i]);
		i++;
	}
	dupl[i] = NULL;
	return (dupl);
}

char	*ft_strdup_env(char *src)
{
	int		i;
	char	*dup;

	dup = malloc(sizeof(char) * (ft_strlen(src) + 1));
	if (!dup)
		return (0);
	i = 0;
	while (src[i])
	{
		dup[i] = src[i];
		i++;
	}
	dup[i] = '\0';
	return (dup);
}

char	**ft_tabdup_env(char **tab)
{
	int		i;
	char	**dupl;

	i = 0;
	dupl = malloc(sizeof(char *) * (len_tab(tab) + 1));
	if (!dupl)
		return (NULL);
	while (tab && tab[i])
	{
		dupl[i] = ft_strdup_env(tab[i]);
		i++;
	}
	dupl[i] = NULL;
	return (dupl);
}

char	*allocate_str(char *str)
{
	int		i;
	char	*allocated;

	i = 0;
	allocated = collect(sizeof(char) * (ft_strlen(str) + 1));
	if (!allocated)
		return (NULL);
	while (str && str[i])
	{
		allocated[i] = str[i];
		i++;
	}
	allocated[i] = '\0';
	return (allocated);
}
