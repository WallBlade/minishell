/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smessal <smessal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/06 19:05:38 by zel-kass          #+#    #+#             */
/*   Updated: 2023/02/13 20:07:04 by smessal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void file_error(char *file)
{
    if (access(file, F_OK) == -1)
		exit(1);
	else if (access(file, X_OK) == -1)
        exit(126);
}

void cmd_error(char *cmd)
{
    ft_putstr_fd("minishell: ", 2);
    ft_putstr_fd(cmd, 2);
    ft_putstr_fd(": command not found\n", 2);
}

void check_status(char *cmd, char *file)
{
    if (status == 127)
        cmd_error(cmd);
    if (status == 126 && access(cmd, F_OK) == 0 && access(cmd, X_OK) == -1)
    {
        ft_putstr_fd("minishell: ", 2);
        ft_putstr_fd(cmd, 2);
        ft_putstr_fd(": permission denied\n", 2);
    }
    else if (status == 1)
    {
        ft_putstr_fd("minishell: ", 2);
        ft_putstr_fd(file, 2);
        ft_putstr_fd(": No such file or directory\n", 2);
    }
    else if (status == 1 && open(file, O_RDWR) == -1)
    {
        ft_putstr_fd("minishell: ", 2);
        ft_putstr_fd(file, 2);
        ft_putstr_fd(": permission denied\n", 2);
    }
}

int	check_access(t_data *data, t_cmdtab *tab)
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
    if (!get_paths(data->env) && !tab->cmd && tab->opt[0])
        file_error(tab->opt[0]);
    if (access(tab->opt[0], F_OK) == 0
		&& access(tab->opt[0], X_OK) == -1)
		exit(126);
	if (!tab->cmd && tab->opt[0]) /*Source problemes pipes consecutifs*/
		exit(127);
	return (0);
}