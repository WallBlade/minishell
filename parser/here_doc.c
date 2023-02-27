/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zel-kass <zel-kass@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 15:49:53 by zel-kass          #+#    #+#             */
/*   Updated: 2023/02/27 19:46:23 by zel-kass         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	here_doc(char *split, int fd)
{
	char	*prompt;

	prompt = NULL;
	g_status = 0;
	while (1)
	{
		prompt = readline(">");
		if (!prompt)
		{
			close(fd);
			sig_unexpected_eof(split);
			break ;
		}
		else if (g_status == 130 || !ft_strcmp(prompt, split))
		{
			close(fd);
			break ;
		}
		ft_putstr_fd(prompt, fd);
		ft_putstr_fd("\n", fd);
	}
}

void	init_hd(char *split, char *hd_name, t_file *in)
{
	int		pid;

	pid = fork();
	signal(SIGINT, hd_sig_parent);
	if (pid == 0)
	{
		signal(SIGINT, hd_sig_child);
		in->fd = open(hd_name, O_WRONLY | O_CREAT, 0777);
		here_doc(split, in->fd);
		free_gc();
		exit(0);
	}
	waitpid(pid, 0, 0);
	if (g_status != 130)
		in->fd = open(hd_name, O_RDONLY);
	else
		unlink(hd_name);
}

t_file	*fill_hd(int op, char *eof, t_cmdtab *tab, int count)
{
	t_file	*in;
	char	*hd_name;

	hd_name = ft_strjoin_hd(ft_itoa(tab->index), allocate_str("_hd_"));
	hd_name = ft_strjoin(hd_name, ft_itoa(count));
	in = collect(sizeof(t_file));
	if (!in)
		return (NULL);
	in->op = op;
	in->fd = 0;
	if (eof)
	{
		in->file = ft_strdup(hd_name);
		init_hd(eof, hd_name, in);
	}
	else
		in->file = NULL;
	in->next = NULL;
	return (in);
}
