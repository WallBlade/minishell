/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_par_cmd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smessal <smessal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/22 17:46:20 by smessal           #+#    #+#             */
/*   Updated: 2023/02/27 10:09:50 by smessal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char    **get_paths(char **env)
{
    int        i;
    char    *path_var;
    char    **env_path;

    i = 0;
    env_path = NULL;
    while (env && env[i])
    {
        path_var = ft_strnstr(env[i], "PATH=", 6);
        if (path_var)
        {
            env_path = ft_split(path_var, ':');
            break ;
        }
        i++;
    }
    i = -1;
    while (env_path && env_path[++i])
        env_path[i] = ft_strjoin(env_path[i], "/");
    return (env_path);
}

int len_cmd(char **split)
{
    int i;
    int len;

    i = 0;
    len = 0;
    while (split && split[i])
    {
        if (is_redir(split[i]))
            i += 2;
        if (split[i])
        {   
            len++;
            i++;
        }
    }
    return (len);
}

char    **get_opt(char **split)
{
    int     i;
    int     j;
    char    **opt;
    
    i = 0;
    j = 0;
	opt = NULL;
	if (split)
	{
		opt = collect(sizeof(char *) * (len_cmd(split) + 1));
		if (!opt)
			return (NULL);
		while (split && split[i])
		{
			if (is_redir(split[i]))
				i += 2;
			else if (split[i])
			{
				opt[j] = ft_strdup(split[i]);
				j++;
				i++;
			}
		}
		opt[j] = NULL;
	}
    return (opt);
}

char    *get_abs_path(char **paths, char **opt)
{
    int     i;
    char    *abs;

    i = 0;
    abs = NULL;
    while (paths && paths[i] && opt[0])
    {
     	abs = ft_strjoin(ft_strdup(paths[i]), opt[0]);
		if (access(abs, F_OK | X_OK) == 0)
			break ;
		abs = NULL;
		i++;
    }
    return (abs);
}
