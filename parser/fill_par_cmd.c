/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_par_cmd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zel-kass <zel-kass@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/22 17:46:20 by smessal           #+#    #+#             */
/*   Updated: 2023/02/07 16:15:21 by zel-kass         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**get_paths(void)
{
	int		i;
	char	*path_var;
	char	**env_path;

    path_var = getenv("PATH");
	env_path = ft_split(path_var, ':');
	i = -1;
	while (env_path[++i])
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
    opt = malloc(sizeof(char *) * (len_cmd(split) + 1));
    if (!opt)
        return (NULL);
    while (split && split[i])
    {
        if (is_redir(split[i]))
            i += 2;
        if (split[i])
        {
            opt[j] = ft_strdup(split[i]);
            j++;
            i++;
        }
    }
    opt[j] = NULL;
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
		free(abs);
		abs = NULL;
		i++;
    }
    return (abs);
}
