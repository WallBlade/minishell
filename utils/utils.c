/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smessal <smessal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 19:31:06 by smessal           #+#    #+#             */
/*   Updated: 2023/02/23 19:27:18 by smessal          ###   ########.fr       */
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
    dupl = malloc(sizeof(char *) * (len_tab(tab) + 1));
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

char	*allocate_str(char *str)
{
	int		i;
	char	*allocated;
	
	i = 0;
	allocated = malloc(sizeof(char) * (ft_strlen(str) + 1));
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
