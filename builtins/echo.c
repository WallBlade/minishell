/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zel-kass <zel-kass@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/05 17:18:17 by zel-kass          #+#    #+#             */
/*   Updated: 2023/02/25 22:05:38 by zel-kass         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int    is_there_n(char **cmd)
{
    int	i;
	int	j;

    i = 0;
	while (cmd && cmd[i])
	{
		if (!ft_strncmp(cmd[i], "-n", 2))
		{
			j = 1;
			while (cmd[i][j])
			{
				if (cmd[i][j] != 'n')
					return(i + 1);
				j++;
			}
		}
		else
			return(i + 1);
		i++;
	}
	return (i + 1);
}

int	ft_echo(char *str, int fd)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (write(fd, &str[i], 1) < 0)
		{
			ft_putstr_fd("bash: echo: write error: No space left on device\n", 2);
			return (0);
		}
		i++;
	}
	return (1);
}

void    echo(char **cmd, int fd)
{
    int    i;
    int    flag;

    flag = is_there_n(cmd + 1);
    if (flag == 1)
        i = flag;
    else
        i = flag;
    while (cmd && cmd[i])
    {
		if (!ft_echo(cmd[i], fd))
			break ;
        if (cmd[i + 1])
            ft_putstr_fd(" ", fd);
        i++;
    }
    if (flag == 1)
		write(fd, "\n", 1);
	if (fd > 1)
		close(fd);
}
