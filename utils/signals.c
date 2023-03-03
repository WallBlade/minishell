/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zel-kass <zel-kass@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 15:36:37 by zel-kass          #+#    #+#             */
/*   Updated: 2023/03/03 19:19:15 by zel-kass         ###   ########.fr       */
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

void	sig_unexpected_eof(char *del, int line)
{
	ft_putstr_fd("minishell: warning: here-document at line ", 2);
	ft_putstr_fd(ft_itoa(line), 2);
	ft_putstr_fd(" delimited by end-of-file (wanted `", 2);
	ft_putstr_fd(del, 2);
	ft_putstr_fd("')\n", 2);
}
