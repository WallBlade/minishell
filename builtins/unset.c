/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smessal <smessal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/05 23:17:28 by smessal           #+#    #+#             */
/*   Updated: 2023/02/26 14:32:44 by smessal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char    **unset(char **env, char *varname)
{
    int     i;
    int     j;
    char    **unseted;

    i = 0;
    j = 0;
	if (existing_var(env, varname))
    	unseted = malloc(sizeof(char *) * (len_tab(env)));
	else
		unseted = malloc(sizeof(char *) * (len_tab(env) + 1));
    if (!unseted)
        return (NULL);
    while (env && env[i])
    {
        if (!ft_strncmp(varname, env[i], ft_strchr(env[i], '='))
            && ft_strlen(varname) == ft_strchr(env[i], '='))
            free(env[i++]);
		else if (!ft_strchr(env[i], '=') && ft_strlen(varname) == ft_strlen(env[i]))
			free(env[i++]);
        if (env[i])
        {
            unseted[j++] = ft_strdup(env[i]);
            free(env[i++]);
        }
    }
    unseted[j] = NULL;
	if (env)
		free(env);
    return (unseted);
}
