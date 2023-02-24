/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smessal <smessal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 15:36:37 by zel-kass          #+#    #+#             */
/*   Updated: 2023/02/24 17:48:27 by smessal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	signal_nl(int num)
{
	if (num == SIGINT)
	{
		ft_putstr_fd("\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
		g_status = 130;
	}
}

void	child_signal(int num)
{
	if (num == SIGINT)
		g_status = 130;
	if (num == SIGQUIT)
		g_status = 131;
}

void	hd_sig_child(int num)
{
	(void)num;
	write(2, "\n", 1);
	close(0);
	g_status = 130;
}

void	hd_sig_parent(int num)
{
	(void)num;
	g_status = 130;
}

void	sig_unexpected_eof(void)
{
	ft_putstr_fd("minishell: warning: here-document delimited by ", 2);
	ft_putstr_fd("end-of-file (wanted `%s')\n", 2);
}
