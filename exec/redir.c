/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zel-kass <zel-kass@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/13 16:10:20 by smessal           #+#    #+#             */
/*   Updated: 2023/01/14 14:50:32 by zel-kass         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_pipes(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->p_count)
	{
		if (pipe(data->fd[i]) == -1)
			return ;
		i++;
	}
}

void	close_pipes(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->p_count)
	{
		close(data->fd[i][0]);
		close(data->fd[i][1]);
		i++;
	}
}

void	make_dup(int in, int out)
{
	dup2(in, 0);
	dup2(out, 1);
}

void	redir(t_data *data, t_cmdtab *tab, int index)
{
	if (tab->in.file)
		make_dup(tab->in.fd, 1);
	if (tab->out.file)
        make_dup(0, tab->out.fd);
	if (index == 0 && data->p_count > 1)
		make_dup(0, data->fd[index][1]);
	else if (index > 0 && index < data->p_count - 1)
		make_dup(data->fd[index - 1][0], data->fd[index][1]);
	else if (index != 0 && index == data->p_count - 1)
		make_dup(data->fd[index - 1][0], 1);
}