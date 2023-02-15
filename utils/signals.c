/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zel-kass <zel-kass@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 15:36:37 by zel-kass          #+#    #+#             */
/*   Updated: 2023/02/15 16:27:33 by zel-kass         ###   ########.fr       */
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
	{
		ft_putstr_fd("\n", 1);
		g_status = 130;
	}
	if (num == SIGQUIT)
	{
		ft_putstr_fd("Quit (core dumped)\n", 1);
		g_status = 131;
	}
}