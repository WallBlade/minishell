/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smessal <smessal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/13 18:08:26 by smessal           #+#    #+#             */
/*   Updated: 2023/01/13 18:37:40 by smessal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void    redir_cmd(t_data *data, t_cmdtab *tab, int index)
{
    (void)index;
    (void)data;
    if (tab->in.file)
        make_dup(tab->in.fd, 1);
    if (tab->out.file)
        make_dup(0, tab->out.fd);
}