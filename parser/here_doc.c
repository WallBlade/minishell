/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zel-kass <zel-kass@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 15:49:53 by zel-kass          #+#    #+#             */
/*   Updated: 2023/02/21 18:46:15 by zel-kass         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	here_doc(char *split, int fd)
{
    char    *prompt;
      
    prompt = NULL;
    while (1)
    {
        prompt = readline(">");
		if (!ft_strcmp(prompt, split))
        {
            close(fd);
            exit(0);
        }
        ft_putstr_fd(prompt, fd);
		ft_putstr_fd("\n", fd);
    }
}

// void	init_hd()
// {
	
// }

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