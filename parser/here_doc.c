/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zel-kass <zel-kass@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 15:49:53 by zel-kass          #+#    #+#             */
/*   Updated: 2023/02/26 19:44:13 by zel-kass         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	here_doc(char *split, t_file *in)
{
    char    *prompt;
      
	prompt = NULL;
    while (1)
    {
        prompt = readline(">");
		if (g_status == 130)
		{
			close(in->fd);
			unlink(in->file);
			break ;
		}
		else if (!prompt)
		{
			unlink(in->file);
			sig_unexpected_eof(split);
			break ;
		}
		if (!ft_strcmp(prompt, split))
        {
			close(in->fd);
            break ;
        }
        ft_putstr_fd(prompt, in->fd);
		ft_putstr_fd("\n", in->fd);
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
		here_doc(split, in);
		free_gc();
		exit(0);
	}
	waitpid(pid, 0, 0);
	if (g_status != 130)
		in->fd = open(hd_name, O_RDONLY);
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
// void	get_right_fd(t_cmdtab *tab)
// {
	
// }

// void    fill_in(t_cmdtab **par, char **split)
// {
//     int i;
//     int pid;

//     i = -1;
//     while (split && split[++i])
//     {
//         if (split[i] && split[i + 1] && !ft_strcmp(split[i], "<<"))
//         {
//             (*par)->in.file = allocate_str("temp");
//             (*par)->in.operator = allocate_str("<<");
//             pid = fork();
//             if (pid == 0)
//             {
//                 (*par)->in.fd = open("temp", O_WRONLY | O_CREAT, 0777);
//                 here_doc(split[i + 1], (*par)->in.fd);
//                 if ((*par)->in.fd > 0)
//                     close((*par)->in.fd);
//                 exit(0);
//             }
//             waitpid(pid, 0, 0);
//             (*par)->in.fd = open("temp", O_RDONLY, 0777);
//         }
//         else if (split[i] && split[i + 1] && !ft_strcmp(split[i], "<"))
//         {
//             (*par)->in.file = ft_strdup(split[i + 1]);
//             (*par)->in.operator = allocate_str("<");
// 		}
// 	}
// }