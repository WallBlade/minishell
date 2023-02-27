/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exec.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smessal <smessal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/06 16:33:24 by smessal           #+#    #+#             */
/*   Updated: 2023/02/27 16:52:33 by smessal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_builtin(t_cmdtab *tab)
{
	if (tab && tab->opt && tab->opt[0])
	{
		if (!ft_strcmp(tab->opt[0], "echo"))
			return (1);
		else if (!ft_strcmp(tab->opt[0], "pwd"))
			return (1);
		else if (!ft_strcmp(tab->opt[0], "cd"))
			return (1);
		else if (!ft_strcmp(tab->opt[0], "export"))
			return (1);
		else if (!ft_strcmp(tab->opt[0], "unset"))
			return (1);
		else if (!ft_strcmp(tab->opt[0], "env"))
			return (1);
		else if (!ft_strcmp(tab->opt[0], "exit"))
			return (1);
		else
			return (0);
	}
	else
		return (0);
}

void	launch_cd(t_cmdtab *tab)
{
	if (tab->opt[1] && tab->opt[2])
	{
		ft_putstr_fd("minishell: cd: too many arguments\n", 2);
		g_status = 1;
	}
	else if (!tab->opt[1] || !ft_strcmp(tab->opt[1], "~"))
		change_dir(getenv("HOME"));
	else if (tab->opt[1])
		change_dir(tab->opt[1]);
}

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
			launch_cd(tab);
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
