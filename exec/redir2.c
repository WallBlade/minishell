/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smessal <smessal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/24 15:09:16 by smessal           #+#    #+#             */
/*   Updated: 2023/02/24 15:10:11 by smessal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	close_final_fd(t_cmdtab *tab)
{
	if (tab->in && tab->in->file && tab->in->fd > 0)
	{
		close(tab->in->fd);
		if (tab->in->op == HERE_DOC)
			unlink(tab->in->file);
	}
	if (tab->out && tab->out->file && tab->out->fd > 1)
		close(tab->out->fd);
}
