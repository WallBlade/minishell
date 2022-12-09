/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_list.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smessal <smessal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 20:12:13 by smessal           #+#    #+#             */
/*   Updated: 2022/12/08 23:20:22 by smessal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_cmd   *lstnew(void)
{
    t_cmd   *new;

    new = malloc(sizeof(t_cmd) * 1);
    if (!new)
        return (NULL);
    new->next = NULL;
    return (new);
}

void    lstaddback(t_cmd **list, t_cmd *new)
{
    t_cmd   *temp;

    if (!*list)
    {
        *list = new;
        return ;
    }
    temp = *list;
    while (temp->next)
        temp = temp->next;
    temp->next = new;
}
