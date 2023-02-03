/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smessal <smessal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 19:31:06 by smessal           #+#    #+#             */
/*   Updated: 2023/02/03 17:10:50 by smessal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int ft_tablen(char **tab)
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
    dupl = malloc(sizeof(char *) * (ft_tablen(tab) + 1));
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
