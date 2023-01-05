/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smessal <smessal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/05 17:19:32 by zel-kass          #+#    #+#             */
/*   Updated: 2023/01/05 23:11:54 by smessal          ###   ########.fr       */
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

/*
    Faudra voir ce qu'il faut free
    Copier env dans double char et mettre a jour a chaque export
    Check sur cmdtab:
        Verifier si "export" est dans cmdtab->opt[0]
        Si opt existe: appeler fonction export() sur cmdtab->opt[1]
    Le double char devrait etre mis a jour, il faudra le passer a la fonction expand
*/

char    **export(char **env, char *var_exp)
{
    int i;
    char    **exported;

    i = 0;
    exported = malloc(sizeof(char *) * (len_tab(env) + 2));
    if (!exported)
        return (NULL);
    while (env && env[i])
    {
        exported[i] = ft_strdup(env[i]);
        i++;
    }
    exported[i++] = ft_strdup(var_exp);
    exported[i] = NULL;
    return (exported);
}