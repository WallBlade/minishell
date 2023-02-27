/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exec.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smessal <smessal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/06 16:33:24 by smessal           #+#    #+#             */
/*   Updated: 2023/02/27 18:47:30 by smessal          ###   ########.fr       */
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

char	*get_pwd(char *var, char **env)
{
	int		i;
	char	*pwd;

	i = 0;
	pwd = NULL;
	while (env && env[i])
	{
		if (!ft_strncmp(env[i], var, ft_strlen(var)))
			return (env[i]);
		i++;
	}
	return (pwd);
}

char	**prepare_pwd(char **env)
{
	char	**pwds;
	char	*pwd;

	pwds = collect(sizeof(char *) * 3);
	if (!pwds)
		return (NULL);
	if (env)
	{
		pwd = getcwd(NULL, 0);
		pwds[0] = ft_strjoin("PWD=", pwd);
		pwds[1] = ft_strjoin("OLDPWD", get_pwd("PWD", env));
		pwds[2] = NULL;
		if (pwd)
			free(pwd);
	}
	return (pwds);
}

void	launch_cd(t_cmdtab *tab, t_data *data)
{
	char	**var_exp;

	var_exp = NULL;
	if (tab->opt[1] && tab->opt[2])
	{
		ft_putstr_fd("minishell: cd: too many arguments\n", 2);
		g_status = 1;
	}
	else if (!tab->opt[1] || !ft_strcmp(tab->opt[1], "~"))
	{
		change_dir(getenv("HOME"));
		var_exp = prepare_pwd(data->env);
		if (var_exp && var_exp[1] && var_exp[2])
			data->env = export(data->env, var_exp);
	}
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
