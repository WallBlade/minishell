/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zel-kass <zel-kass@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 19:31:06 by smessal           #+#    #+#             */
/*   Updated: 2023/02/26 18:06:55 by zel-kass         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int len_tab(char **tab)
{
    int i;

    i = 0;
    while (tab && tab[i])
        i++;
    return (i);
}

char    **ft_strdup_tab(char **tab)
{
    int     i;
    char    **dupl;

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

char    **ft_tabdup_env(char **tab)
{
    int     i;
    char    **dupl;

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

int	numlen(int num)
{
	int	i;

	i = 0;
	if (num < 0)
	{
		i++;
		num *= -1;
	}
	while (num > 0)
	{
		num /= 10;
		i++;
	}
	return (i);
}

int is_numeric(char *str)
{
	if (numlen(ft_atoi(str)) == ft_strlen(str))
		return (1);
    return (0);
}

char	*ft_strjoin_hd(char *s1, char *s2)
{
	int		i;
	int		j;
	size_t	len;
	char	*dest;

	if (!s1)
		return (ft_strdup(s2));
	len = ft_strlen(s1) + ft_strlen(s2);
	dest = (char *)collect(sizeof(char) * (len + 1));
	if (!dest)
		return (NULL);
	i = -1;
	j = -1;
	while (s1[++i])
		dest[i] = s1[i];
	while (s2[++j])
		dest[i++] = s2[j];
	dest[i] = '\0';
	return (dest);
}