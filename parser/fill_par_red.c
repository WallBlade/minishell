/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_par_red.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smessal <smessal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/20 22:33:29 by smessal           #+#    #+#             */
/*   Updated: 2022/12/22 17:46:36 by smessal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int check_active(int *token)
{
    int i;
    
    i = 0;
    while (token && token[i] >= 0)
    {
        if (token[i] == 1)
            return (1);
        i++;
    }
    return (0);
}
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

void    fill_in(t_parser *par, char **split, t_tks *tks_pipe)
{
    int i;

    i = -1;
    if (check_active(tks_pipe->d_in))
    {
        while (split && split[i++])
        {
            if (split[i] && split[i + 1] && !ft_strncmp(split[i], "<<", 2))
            {
                par->in.file = here_doc(split, i);
                par->in.operator = "<<";
            }
        }
    }
    else if (check_active(tks_pipe->in))
    {
        while (split && split[i++])
        {
            if (split[i][0] == '<' && split[i + 1])
            {
                par->in.file = split[i + 1];
                par->in.operator = "<";
            }
        }
    }
}

void    fill_out(t_parser *par, char **split, t_tks *tks_pipe)
{
    int i;

    i = -1;
    if (check_active(tks_pipe->ap))
    {
        while (split && split[i++])
        {
            if (split[i] && split[i + 1] && !ft_strncmp(split[i], ">>", 2))
            {
                par->out.file = split[i + 1];
                par->out.operator = ">>";
            }
        }
    }
    else if (check_active(tks_pipe->out))
    {
        while (split && split[i++])
        {
            if (split[i][0] == '>' && split[i + 1])
            {
                par->out.file = split[i + 1];
                par->out.operator = ">";
            }
        }
    }
}

int is_redir(char *arg)
{
    if (!ft_strnmcp(arg, ">", ft_strlen(arg)))
        return(1);
    else if (!ft_strnmcp(arg, ">>", ft_strlen(arg)))
        return (1);
    else if (!ft_strnmcp(arg, "<", ft_strlen(arg)))
        return (1);
    else if (!ft_strnmcp(arg, "<<", ft_strlen(arg)))
        return (1);
    return (0);
}
