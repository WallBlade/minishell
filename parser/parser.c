/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smessal <smessal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/19 11:42:00 by smessal           #+#    #+#             */
/*   Updated: 2023/01/05 14:14:38 by smessal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_cmdtab    *parser(char **lexer)
{
    int i;
    t_cmdtab    *tab;

    i = 0;
    while (lexer && lexer[i])
    {
        lst_addback_par(&tab, lstnew_par(lexer[i]));
        i++;
    }
    return (tab);
}

int main()
{
    char        *prompt;
    char        **lex;
    t_cmdtab    *tab;

    tab = NULL;
    while (1)
    {
        prompt = readline("minishell> ");
        lex = lexer(prompt);
        tab = parser(lex);
        printf("%s\n", tab->cmd);
        tab = tab->next;
        printf("%s\n", tab->cmd);
    }
}