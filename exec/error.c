/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zel-kass <zel-kass@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/06 19:05:38 by zel-kass          #+#    #+#             */
/*   Updated: 2023/02/26 18:45:58 by zel-kass         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void check_status(char *cmd)
{
    if (g_status == 127)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(cmd, 2);
		ft_putstr_fd(": command not found\n", 2);
	}
	else if (g_status == 126 && access(cmd, F_OK) == 0 && access(cmd, X_OK) == -1)
    {
        ft_putstr_fd("minishell: ", 2);
        ft_putstr_fd(cmd, 2);
        ft_putstr_fd(": permission denied\n", 2);
    }
}

int	check_access(t_data *data, t_cmdtab *tab)
{
	if (!is_builtin(tab) && tab->opt && tab->opt[0])
	{
		tab->cmd = get_abs_path(get_paths(data->env), tab->opt);
		if (!data->env || !tab->cmd)
		{
			if (access(tab->opt[0], X_OK) == 0)
			{
				tab->cmd = tab->opt[0];
				data->is_abs = 1;
			}
		}
		if (access(tab->opt[0], F_OK) == 0
			&& access(tab->opt[0], X_OK) == -1)
			exit(126);
		if (!tab->cmd && tab->opt[0])
		{
			close_final_fd(tab);
			close_pipes(data);
			free_gc();
			exit(127);
		}
	}
	return (0);
}

int	check_redir(t_cmdtab *tab)
{
	if (tab->in && tab->in->fd < 0)
		return (0);
	if (tab->out && tab->out->fd < 0)
		return (0);
	return (1);
}