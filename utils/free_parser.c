/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_parser.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smessal <smessal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 17:08:27 by smessal           #+#    #+#             */
/*   Updated: 2023/02/14 18:00:59 by smessal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_cmdtab(t_cmdtab *tab)
{
	t_cmdtab	*temp;

	while (tab)
	{
		if (tab->in.file)
			free(tab->in.file);
		if (tab->in.operator)
			free(tab->in.operator);
		if (tab->out.file)
			free(tab->out.file);
		if (tab->out.operator)
			free(tab->out.operator);
		if (tab->opt)
			free_tab(tab->opt);
		if (tab->cmd)
			free(tab->cmd);
		temp = tab;
		tab = tab->next;
		free(temp);
	}
}

void	free_data_struct(t_data *data)
{
	int	i;

	i = 0;
	if (data->fd)
	{
		while (data->fd[i])
		{
			free(data->fd[i]);
			i++;
		}
	}
	if (data->pid)
		free(data->pid);
}