/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smessal <smessal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 19:31:06 by smessal           #+#    #+#             */
/*   Updated: 2023/02/17 17:23:55 by smessal          ###   ########.fr       */
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

int is_numeric(char *str)
{
    int     i;
    int     j;
    char    *nums;
    int     count;

    i = 0;
    nums = allocate_str("0123456789");
    count = 0;
    while (str && str[i])
    {
        j = 0;
        while (nums && nums[j])
        {
            if (str[i] == nums[j])
                count++;
            j++;
        }
        i++;
    }
    if (count == ft_strlen(str))
        return (1);
    return (0);
}