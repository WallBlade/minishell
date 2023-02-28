/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zel-kass <zel-kass@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/24 15:09:16 by smessal           #+#    #+#             */
/*   Updated: 2023/02/28 20:02:33 by zel-kass         ###   ########.fr       */
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
	{
		close(tab->out->fd);
	}
}

void	close_fds_hd(t_cmdtab *tab)
{
	t_cmdtab	*temp;

	temp = tab;
	while (temp)
	{
		while (temp->in)
		{
			close(temp->in->fd);
			if (temp->in->op == HERE_DOC)
				unlink(temp->in->file);
			temp->in = temp->in->next;
		}
		while (temp->out && temp->out->fd > 1)
		{
			close(temp->out->fd);
			temp->out = temp->out->next;
		}
		temp = temp->prev;
	}
}