/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smessal <smessal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/05 23:17:28 by smessal           #+#    #+#             */
/*   Updated: 2023/02/15 23:28:03 by smessal          ###   ########.fr       */
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
    unseted = malloc(sizeof(char *) * (len_tab(env)));
    if (!unseted)
        return (NULL);
    while (env && env[i])
    {
        if (!ft_strncmp(varname, env[i], ft_strchr(env[i], '='))
            && ft_strlen(varname) == ft_strchr(env[i], '='))
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
