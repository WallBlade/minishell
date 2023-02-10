/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_par_red.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smessal <smessal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/20 22:33:29 by smessal           #+#    #+#             */
/*   Updated: 2023/02/10 17:58:59 by smessal          ###   ########.fr       */
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

void    fill_in(t_cmdtab **par, char **split)
{
    int i;
    int pid;

    i = -1;
    while (split && split[++i])
    {
        if (split[i] && split[i + 1] && !ft_strcmp(split[i], "<<"))
        {
            if ((*par)->in.fd > 0)
                close((*par)->in.fd);
            // (*par)->in.fd = open("tmp", O_RDWR | O_CREAT);
            (*par)->in.file = allocate_str("temp");
            (*par)->in.operator = allocate_str("<<");
            pid = fork();
            if (pid == 0)
            {
                (*par)->in.fd = open("temp", O_WRONLY | O_CREAT, 0777);
                here_doc(split[i + 1], (*par)->in.fd);
                if ((*par)->in.fd > 0)
                    close((*par)->in.fd);
                exit(0);
            }
            waitpid(pid, 0, 0);
            (*par)->in.fd = open("temp", O_RDONLY, 0777);
            
        }
        else if (split[i] && split[i + 1] && !ft_strcmp(split[i], "<"))
        {
            (*par)->in.file = split[i + 1];
            (*par)->in.operator = allocate_str("<");
            // if ((*par)->in.fd > 0)
            //     close((*par)->in.fd);
		}
	}
}

void    fill_out(t_cmdtab **par, char **split)
{
    int i;

    i = -1;
    while (split && split[++i])
    {
        if (split[i] && split[i + 1] && !ft_strncmp(split[i], ">>", 2))
        {
            (*par)->out.file = split[i + 1];
            (*par)->out.operator = allocate_str(">>");
            // if ((*par)->out.fd > 1)
            //     close((*par)->out.fd);
            // (*par)->out.fd = open(split[i + 1], O_RDWR | O_APPEND | O_CREAT);
        }
        else if (split[i] && split[i + 1] && !ft_strncmp(split[i], ">", ft_strlen(split[i])))
        {
            (*par)->out.file = split[i + 1];
            (*par)->out.operator = allocate_str(">");
            // if ((*par)->out.fd > 1)
            //     close((*par)->out.fd);
        }
	}
}

int is_redir(char *arg)
{
    if (!ft_strncmp(arg, ">", ft_strlen(arg)))
        return(1);
    else if (!ft_strncmp(arg, ">>", ft_strlen(arg)))
        return (1);
    else if (!ft_strncmp(arg, "<", ft_strlen(arg)))
        return (1);
    else if (!ft_strncmp(arg, "<<", ft_strlen(arg)))
        return (1);
    return (0);
}
