/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smessal <smessal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/05 12:33:27 by smessal           #+#    #+#             */
/*   Updated: 2023/02/27 10:27:44 by smessal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_cmdtab	*lstnew_cmd(char **spl, int index)
{
	t_cmdtab    *tab;

	tab = collect(sizeof(t_cmdtab));
	if (!tab)
		return (NULL);
	tab->opt = NULL;
	tab->opt = get_opt(spl);
    tab->cmd = NULL;
	tab->in = NULL;
	tab->out = NULL;
	tab->index = index;
	init_files(tab, spl);
    tab->next = NULL;
    return (tab);
}

void	lst_addback_cmd(t_cmdtab **tab, t_cmdtab *new)
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

void	lst_addback_red(t_file **red, t_file *new)
{
    t_file    *tmp;

    tmp = *red;
    if (!new)
        return ;
    if (!tmp)
    {
        *red = new;
        return ;
    }
    while (tmp->next)
        tmp = tmp->next;
    tmp->next = new;
}

int	lstsize(t_cmdtab *lst)
{
	int	i;

	i = 0;
	while (lst)
	{
		lst = lst->next;
		i++;
	}
	return (i);
}