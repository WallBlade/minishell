/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smessal <smessal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/05 17:18:57 by zel-kass          #+#    #+#             */
/*   Updated: 2023/02/06 14:28:02 by smessal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	pwd(int fd)
{
	char	*pwd;

	pwd = getcwd(NULL, 0);
	ft_putstr_fd(pwd, fd);
  ft_putstr_fd("\n", fd);
	if (pwd)
		free (pwd);
}

int    change_dir(char *path)
{
    int success;

    success = chdir(path);
    return(success);
}

void    env_print(char **env, int fd)
{
    int i;
    int j;

    i = 0;
    j = 0;
    while (env && env[i])
    {
		j = 0;
		while (env[i][j])
			write(fd, &env[i][j++], 1);
		write(fd, "\n", 1);
		i++;
    }
}
