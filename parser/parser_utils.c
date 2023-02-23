/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zel-kass <zel-kass@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/05 12:33:27 by smessal           #+#    #+#             */
/*   Updated: 2023/02/23 16:44:51 by zel-kass         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_cmdtab	*lstnew_cmd(char **spl)
{
    t_cmdtab    *tab;

    tab = malloc(sizeof(t_cmdtab));
    if (!tab)
        return (NULL);
    tab->opt = get_opt(spl);
    tab->cmd = NULL;
	tab->in = NULL;
	tab->out = NULL;
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