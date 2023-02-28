/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smessal <smessal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/24 15:09:16 by smessal           #+#    #+#             */
/*   Updated: 2023/02/28 18:48:49 by smessal          ###   ########.fr       */
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

void	close_fds_hd(t_cmdtab *tab)
{
	// printf("opt = %s\n", tab->opt[0]);
	t_cmdtab	*temp;

	temp = tab;
	printf("opt: %p\n", tab->prev);
	while (temp)
	{
		printf("g_status: %d\n", g_status);
		while (temp->in)
		{
			close(temp->in->fd);
			printf("closed_in\n");
			if (temp->in->op == HERE_DOC && g_status != 130)
				unlink(temp->in->file);
			temp->in = temp->in->next;
		}
		while (temp->out && temp->out->fd > 1)
		{
			close(temp->out->fd);
			printf("closed_out\n");
			temp->out = temp->out->next;
		}
		temp = temp->prev;
	}
}