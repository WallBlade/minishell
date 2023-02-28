/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exec2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zel-kass <zel-kass@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 18:48:51 by zel-kass          #+#    #+#             */
/*   Updated: 2023/02/28 15:39:04 by zel-kass         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	launch_export(t_cmdtab *tab, t_data *data)
{
	if (tab->opt[1])
		data->env = export(data->env, tab->opt);
	else
		print_export(tab, data->env);
}

int	launch_builtin(t_cmdtab *tab, t_data *data)
{
	int	fd;

	if (tab->out && tab->out->fd)
		fd = tab->out->fd;
	else
		fd = 1;
	if (tab && tab->opt && tab->opt[0])
	{
		if (!ft_strcmp(tab->opt[0], "echo"))
			echo(tab->opt, fd);
		else if (!ft_strcmp(tab->opt[0], "pwd"))
			pwd(fd);
		else if (!ft_strcmp(tab->opt[0], "cd"))
			launch_cd(tab, data);
		else if (!ft_strcmp(tab->opt[0], "export"))
			launch_export(tab, data);
		else if (!ft_strcmp(tab->opt[0], "env"))
			env_print(data->env, fd);
		else if (!ft_strcmp(tab->opt[0], "unset") && tab->opt[1])
			data->env = unset(data->env, tab->opt[1]);
		else if (!ft_strcmp(tab->opt[0], "exit"))
			exit_bin(tab, data);
	}
	return (1);
}
