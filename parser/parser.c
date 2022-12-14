/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zel-kass <zel-kass@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/19 11:42:00 by smessal           #+#    #+#             */
/*   Updated: 2023/01/08 13:09:08 by zel-kass         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void    printer(t_cmdtab *tab)
{
    t_cmdtab    *temp;

    temp = tab;
    while (temp)
    {
        if (temp->cmd)
            printf("abs_path: %s\n", temp->cmd);
        if (temp->opt)
        {
            for (int i = 0; temp->opt[i]; i++)
                printf("option_%d %s\n", i, temp->opt[i]);
        }
        if (temp->in.file)
            printf("%s\n", temp->in.file);
        if (temp->in.operator)
            printf("%s\n", temp->in.operator);
        if (temp->out.file)
            printf("%s\n", temp->out.file);
        if (temp->out.operator)
            printf("%s\n", temp->out.operator);
        temp = temp->next;
    }
}

t_cmdtab    *parser(char **lexer)
{
    int         i;
    t_cmdtab    *tab;

    i = 0;
    tab = NULL;
    while (lexer && lexer[i])
    {
        lst_addback_par(&tab, lstnew_par(lexer[i]));
        i++;
    }
    return (tab);
}
