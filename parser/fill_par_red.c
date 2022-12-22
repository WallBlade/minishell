/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_par_red.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smessal <smessal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/20 22:33:29 by smessal           #+#    #+#             */
/*   Updated: 2022/12/22 20:01:29 by smessal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* 
    Il faut gerer le cas ou les chevrons sont colles au filename 
    comme: <infile au lieu de < infile;
*/
char    *here_doc(char **split, int i)
{
    char    *stack;
    char    *prompt;
      
    prompt = NULL;
    stack = NULL;
    while (1)
    {
        prompt = readline(">");
        if (!ft_strncmp(prompt, split[i + 1], ft_strlen(split[i + 1])))
            break;
        /*Reste a check si necessaire de free s2 sur strjoin*/
        stack = ft_strjoin(stack, prompt);
        stack = ft_strjoin(stack, "\n");
    }
    return (stack);
}

void    fill_in(t_parser **par, char **split)
{
    int i;

    i = -1;
    while (split && split[i++])
    {
        if (split[i] && split[i + 1] && !ft_strncmp(split[i], "<<", ft_strlen(split[i])))
        {
            if ((*par)->in.fd > 0)
                close((*par)->in.fd);
            (*par)->in.fd = open("tmp", O_WRONLY | O_CREAT);
            ft_putstr_fd(here_doc(split, i), (*par)->in.fd);
            close((*par)->in.fd);
            (*par)->in.file = "tmp";
            (*par)->in.operator = "<<";
        }
        else if (split[i] && split[i + 1] && !ft_strncmp(split[i], "<", ft_strlen(split[i])))
        {
            (*par)->in.file = split[i + 1];
            (*par)->in.operator = "<";
            if ((*par)->in.fd > 0)
                close((*par)->in.fd);
            (*par)->in.fd = open(split[i + 1], O_RDONLY);
        }
        if ((*par)->in.fd < 0)
            return ;
    }
}

void    fill_out(t_parser *par, char **split)
{
    int i;

    i = -1;
    while (split && split[i++])
    {
        if (split[i] && split[i + 1] && !ft_strncmp(split[i], ">>", ft_strlen(split[i])))
        {
            par->out.file = split[i + 1];
            par->out.operator = ">>";
            if (par->out.fd > 0)
                close(par->out.fd);
            par->out.fd = open(split[i + 1], O_RDWR | O_APPEND | O_CREAT);
        }
        else if (split[i] && split[i + 1] && !ft_strncmp(split[i], ">", ft_strlen(split[i])))
        {
            par->out.file = split[i + 1];
            printf("test\n");
            par->out.operator = ">";
            if (par->out.fd > 0)
                close(par->out.fd > 0);
            par->out.fd = open(split[i + 1], O_RDWR| O_CREAT | O_TRUNC);
        }
        if (par->out.fd < 0)
            return ;
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
