/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smessal <smessal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/05 17:19:32 by zel-kass          #+#    #+#             */
/*   Updated: 2023/02/15 23:35:57 by smessal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int len_tab(char **tab)
{
    int i;

    i = 0;
    while (tab && tab[i])
        i++;
    return (i);
}

int    existing_var(char **env, char *var_exp)
{
    int i;

    i = 0;
    while (env && env[i])
    {
        if (!ft_strncmp(var_exp, env[i], ft_strchr(env[i], '='))
            && ft_strchr(var_exp, '=') == ft_strchr(env[i], '='))
            return (1);
        i++;
    }
    return (0);
}

char    **export(char **env, char *var_exp)
{
    int     i;
    char    **exported;

    i = 0;
    exported = malloc(sizeof(char *) * (len_tab(env) + 2));
    if (!exported)
        return (NULL);
    if (existing_var(env, var_exp))
        env = unset(env, get_varname(var_exp, 0, ft_strchr(var_exp, '=')));
    while (env && env[i])
    {
        exported[i] = ft_strdup(env[i]);
        free(env[i++]);
    }
    exported[i++] = ft_strdup(var_exp);
    exported[i] = NULL;
	if (env)
		free(env);
    return (exported);
}

char    *ft_strdup_quote(char *env)
{
    int     i;
    int     j;
    char    *quote;
    int     first;

    i = 0;
    j = 0;
    first = 1;
    quote = malloc(sizeof(char) * (ft_strlen(env) + 3));
    if (!quote)
        return (NULL);
    while (env && env[i])
    {
        quote[j] = env[i];
        if (env[i] == '=' && first)
        {
            quote[++j] = '"';
            first = 0;
        }
        i++;
        j++;
    }
    if (!first)
        quote[j++] = '"';
    quote[j] = '\0';
    return(quote);
}

char    **converted_env(char **env)
{
    int     i;
    char    **converted;

    i = 0;
    converted = malloc(sizeof(char *) * (ft_tablen(env) + 1));
    if (!converted)
        return (NULL);
    while (env && env[i])
    {
        converted[i] = ft_strdup_quote(env[i]);
        i++;
    }
    converted[i] = NULL;
    return (converted);
}

void    print_export(t_cmdtab *tab, char **env)
{
    int i;
    char    **env_export;

    i = 0;
    env_export = converted_env(env);
    while (env_export && env_export[i])
    {
        ft_putstr_fd("export ", tab->out.fd);
        ft_putstr_fd(env_export[i], tab->out.fd);
        ft_putstr_fd("\n", tab->out.fd);
        i++;
    }
	if (env_export)
		free_tab(env_export);
}
