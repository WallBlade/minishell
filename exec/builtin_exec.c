/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exec.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smessal <smessal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/06 16:33:24 by smessal           #+#    #+#             */
/*   Updated: 2023/02/14 17:32:26 by smessal          ###   ########.fr       */
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
		else
			return (0);
	}
	else
		return (0);
}

int	launch_builtin(t_cmdtab *tab, t_data *data)
{
	if (tab && tab->opt && tab->opt[0])
	{
		if (!ft_strcmp(tab->opt[0], "echo"))
			echo(tab->opt, tab->out.fd);
		else if (!ft_strcmp(tab->opt[0], "pwd"))
			pwd(tab->out.fd);
		else if (!ft_strcmp(tab->opt[0], "cd"))
		{
			if (!tab->opt[1] || !ft_strcmp(tab->opt[1], "~"))
				change_dir(getenv("HOME"));
			else if (tab->opt[1])
				change_dir(tab->opt[1]);
		}
		else if (!ft_strcmp(tab->opt[0], "export"))
		{
			if (tab->opt[1])
				data->env = export(data->env, tab->opt[1]);
			else
				print_export(tab, data->env);
		}
        else if (!ft_strcmp(tab->opt[0], "env"))
            env_print(data->env, tab->out.fd);
        else if (!ft_strcmp(tab->opt[0], "unset") && tab->opt[1])
            data->env = unset(data->env, tab->opt[1]);
	}
	return (1);
}
