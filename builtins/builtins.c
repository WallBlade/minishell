/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smessal <smessal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/05 17:18:57 by zel-kass          #+#    #+#             */
/*   Updated: 2023/02/27 12:07:02 by smessal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	pwd(int fd)
{
	char	*pwd;

	pwd = getcwd(NULL, 0);
	ft_putstr_fd(pwd, fd);
 	ft_putstr_fd("\n", fd);
	if (pwd)
		free (pwd);
	if (fd > 1)
		close(fd);
	g_status = 0;
}

int    change_dir(char *path)
{
    int success;

    success = chdir(path);
	if (success == -1)
	{
		g_status = 1;
		ft_putstr_fd("minishell: cd: ", 2);
		ft_putstr_fd(path, 2);
		ft_putstr_fd(": No such file or directory\n", 2);
	}
	else
		g_status = 0;
	return(success);
}

void    env_print(char **env, int fd)
{
    int i;

    i = 0;
    while (env && env[i])
    {
      if (ft_strnstr(env[i], "=", ft_strlen(env[i])))
      {
        ft_putstr_fd(env[i], fd);
		write(fd, "\n", 1);
      }
      i++;
    }
	if (fd > 1)
		close(fd);
	g_status = 0;
}
