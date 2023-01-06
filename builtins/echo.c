/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zel-kass <zel-kass@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/05 17:18:17 by zel-kass          #+#    #+#             */
/*   Updated: 2023/01/06 14:51:02 by zel-kass         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int    is_there_n(char **cmd)
{
    int    i;

    i = 0;
    while (cmd && cmd[i])
    {
        if (!ft_strcmp(cmd[i], "echo") && !ft_strcmp(cmd[i + 1], "-n"))
            return (1);
        i++;
    }
    return (0);
}

void    echo(char **cmd, int fd)
{
    int    i;
    int    flag;

    flag = is_there_n(cmd);
    if (flag == 0)
        i = 1;
    else
        i = 2;
    while (cmd && cmd[i])
    {
        ft_putstr_fd(cmd[i], fd);
        i++;
    }
    if (flag == 0)
        write(fd, "\n", 1);
}
