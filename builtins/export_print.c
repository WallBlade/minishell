/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_print.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smessal <smessal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/17 12:22:12 by smessal           #+#    #+#             */
/*   Updated: 2023/02/17 17:19:14 by smessal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
    converted = malloc(sizeof(char *) * (len_tab(env) + 1));
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
