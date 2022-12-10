/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smessal <smessal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/09 14:54:40 by zel-kass          #+#    #+#             */
/*   Updated: 2022/12/10 01:00:46 by smessal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_tok    *init_tokens(char *str)
{
    t_tok *tks;

    tks = malloc(sizeof(t_tok));
    if (!tks)
        return (NULL);
    tks->q = malloc(sizeof(int) * (count_elem(str, '\'')));
    tks->dq = malloc(sizeof(int) * (count_elem(str, '"')));
    tks->p = malloc(sizeof(int) * (count_elem(str, '|')));
    tks->in = malloc(sizeof(int) * count_elem(str, '<'));
    tks->out = malloc(sizeof(int) * count_elem(str, '>'));
    // Faire fonction pour compter double chev
    // tks->ap = malloc(sizeof(int) * )
    tks->dol = malloc(sizeof(int) * count_elem(str, '$'));
    tks->qst = malloc(sizeof(int) * count_elem(str, '?'));
    return (tks);
}