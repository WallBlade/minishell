/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zel-kass <zel-kass@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 15:36:37 by zel-kass          #+#    #+#             */
/*   Updated: 2023/02/16 22:28:22 by zel-kass         ###   ########.fr       */
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

// static void	handle_signal_hd(int signal, siginfo_t *info, void *context)
// {
// 	int	fd;

// 	(void)info;
// 	(void)context;
// 	if (signal == SIGINT)
// 	{
// 		fd = open("/dev/null", O_RDONLY);
// 		dup2(fd, STDIN_FILENO);
// 		close(fd);
// 		ft_putstr_fd("\n", 1);
// 		g_status = 777;
// 	}
// 	if (signal == SIGQUIT)
// 		ft_putstr_fd("\b\b  \b\b", 0);
// }

// void	here_doc_signal()
// {
// 	struct sigaction	s_sig;

// 	s_sig.sa_sigaction = handle_signal_hd;
// 	s_sig.sa_flags = SA_SIGINFO;
// 	sigemptyset(&s_sig.sa_mask);
// 	sigaction(SIGINT, &s_sig, 0);
// 	sigaction(SIGQUIT, &s_sig, 0);
// }