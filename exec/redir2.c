/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zel-kass <zel-kass@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/24 15:09:16 by smessal           #+#    #+#             */
/*   Updated: 2023/03/03 15:49:46 by zel-kass         ###   ########.fr       */
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
		while (temp->in && temp->in->fd > 0)
		{
			close(temp->in->fd);
			if (temp->in->op == HERE_DOC && temp->in->file)
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

int	detect_hd_loop(char **spl, t_cmdtab *tab, int *count)
{
	int	j;
	int	c;

	j = 0;
	c = *count;
	while (spl && spl[j])
	{
		if (is_redir(spl[j]) == HERE_DOC && spl[j + 1])
		{
			lst_addback_red(&tab->in, fill_hd(HERE_DOC, spl[j + 1],
					tab, c));
			*count += 1;
			c = *count;
			if (g_status == 130)
				return (0);
		}
		j++;
	}
	return (1);
}
