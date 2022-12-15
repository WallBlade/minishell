/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zel-kass <zel-kass@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/09 14:54:40 by zel-kass          #+#    #+#             */
/*   Updated: 2022/12/15 16:17:15 by zel-kass         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_tks	*init_tokens(char *str)
{
	t_tks	*tks;

	tks = malloc(sizeof(t_tks));
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

void	init_active_tokens(t_tks **tks, char *line)
{
	char	*tokens;
	int		i;

	tokens = "<>|?";
	i = 0;
	get_squotes(line, (*tks)->q);
	get_dquotes(line, (*tks)->dq);
	while (tokens[i])
		active_s_tokens(line, (*tks), tokens[i++]);
	active_dol_token(line, (*tks));
	active_d_tokens(line, (*tks), ">>");
	active_d_tokens(line, (*tks), "<<");
}
