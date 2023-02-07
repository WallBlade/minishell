/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zel-kass <zel-kass@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/06 19:05:38 by zel-kass          #+#    #+#             */
/*   Updated: 2023/02/07 12:24:24 by zel-kass         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void file_error(char *file)
{
    if (access(file, F_OK) == -1)
    {
        free(file);
        status = 1;
    }
    else if (access(file, X_OK) == -1)
    {
        free(file);
        status = 126;
    }
}

void cmd_error(char *cmd)
{
    ft_putstr_fd("bash: ", 2);
    ft_putstr_fd(cmd, 2);
    ft_putstr_fd(": command not found\n", 2);
}

void check_status(int stat, char *cmd, char *file)
{
	printf("status = %d\n", status);
	printf("stat = %d\n", stat);
    if (stat == 127)
        cmd_error(cmd);
    if (stat == 126 && access(cmd, F_OK) == 0 && access(cmd, X_OK) == -1)
    {
        ft_putstr_fd("bash: ", 2);
        ft_putstr_fd(cmd, 2);
        ft_putstr_fd(": permission denied\n", 2);
    }
    else if (stat == 1)
    {
        ft_putstr_fd("bash: ", 2);
        ft_putstr_fd(file, 2);
        ft_putstr_fd(": No such file or directory\n", 2);
    }
    else if (stat == 1 && open(file, O_RDWR) == -1)
    {
        ft_putstr_fd("bash: ", 2);
        ft_putstr_fd(file, 2);
        ft_putstr_fd(": permission denied\n", 2);
    }
}