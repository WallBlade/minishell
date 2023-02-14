/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_lexer.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smessal <smessal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 16:42:43 by smessal           #+#    #+#             */
/*   Updated: 2023/02/14 16:42:51 by smessal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_tks(t_tks *tks)
{
	if (tks)
	{
		if (tks->q)
			free(tks->q);
		if (tks->dq)
			free(tks->dq);
		if (tks->q_on)
			free(tks->q_on);
		if (tks->dq_on)
			free(tks->dq_on);
		if (tks->p)
			free(tks->p);
		if (tks->in)
			free(tks->in);
		if (tks->out)
			free(tks->out);
		if (tks->ap)
			free(tks->ap);
		if (tks->d_in)
			free(tks->d_in);
		if (tks->dol)
			free(tks->dol);
		free_tks2(tks);
	}
}

void	free_tks2(t_tks *tks)
{
	if (tks->qst)
		free(tks->qst);
	if (tks->prompt)
		free(tks->prompt);
	free(tks);
}
