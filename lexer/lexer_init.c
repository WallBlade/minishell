/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smessal <smessal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/09 14:54:40 by zel-kass          #+#    #+#             */
/*   Updated: 2022/12/11 21:21:55 by smessal          ###   ########.fr       */
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
    tks->ap = malloc(sizeof(int) * count_d_elem(str, ">>"));
    tks->d_in = malloc(sizeof(int) * count_d_elem(str, "<<"));
    tks->dol = malloc(sizeof(int) * count_elem(str, '$'));
    tks->qst = malloc(sizeof(int) * count_elem(str, '?'));
    return (tks);
}

void	init_active_tokens(t_tok **tks, char *line)
{
	char	*tokens;
	int		i;

	tokens = "<>|?";
	i = 0;
	get_quotes(line, (*tks));
	while (tokens[i])
        active_s_tokens(line, (*tks), tokens[i++]);
    active_dol_token(line, (*tks));
    active_d_tokens(line, (*tks), ">>");
	active_d_tokens(line, (*tks), "<<");
}