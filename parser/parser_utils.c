/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smessal <smessal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/05 12:33:27 by smessal           #+#    #+#             */
/*   Updated: 2023/01/05 16:57:29 by smessal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_cmdtab    *lstnew_par(char *pipe)
{
    t_cmdtab    *tab;
    char        **spl;

    tab = malloc(sizeof(t_cmdtab));
    if (!tab)
        return (NULL);
    tab->in.fd = 0;
    tab->out.fd = 0;
    spl = split(pipe);
    fill_in(&tab, spl);
    fill_out(&tab, spl);
    tab->opt = get_opt(spl);
    tab->cmd = get_abs_path(get_paths(), tab->opt);
    tab->prev = NULL;
    tab->next = NULL;
    return (tab);
}

void    lst_addback_par(t_cmdtab **tab, t_cmdtab *new)
{
    t_cmdtab    *temp;

    temp = *tab;
    if (!new)
        return ;
    if (!temp)
    {
        *tab = new;
        return ;
    }
    while (temp->next)
        temp = temp->next;
    temp->next = new;
}
