/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zel-kass <zel-kass@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/05 17:18:57 by zel-kass          #+#    #+#             */
/*   Updated: 2023/03/02 18:25:14 by zel-kass         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	pwd(int fd)
{
	char	*pwd;

	pwd = getcwd(NULL, 0);
    if (!pwd)
    {
        ft_putstr_fd("pwd: error retrieving current directory: ", 2);
        ft_putstr_fd("getcwd: cannot access parent directories: ", 2);
        ft_putstr_fd("No such file or directory\n", 2);
        g_status = 1;
        return ;
    }
	ft_putstr_fd(pwd, fd);
	ft_putstr_fd("\n", fd);
	if (pwd)
		free(pwd);
	if (fd > 1)
		if (close(fd) == -1)
			perror("");
	g_status = 0;
}

int	change_dir(char *path)
{
	int	success;

	success = chdir(path);
	if (success == -1)
	{
		ft_putstr_fd("minishell: cd: ", 2);
		ft_putstr_fd(path, 2);
		ft_putstr_fd(": No such file or directory\n", 2);
		g_status = 1;
	}
	else
		g_status = 0;
	return (success);
}

void	env_print(char **env, int fd)
{
	int	i;

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
