/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smessal <smessal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/19 11:42:00 by smessal           #+#    #+#             */
/*   Updated: 2022/12/19 20:41:05 by smessal          ###   ########.fr       */
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

char    *here_doc(t_parser *par, char **split, t_tks *tks_pipe)
{
    char    *stack;
    char    *prompt;
    int     i;

    i = 0;
    while (split && split[i])
    {
        if (split[i] && split[i + 1] && !ft_strncmp(split[i], "<<", 2))
            break;
        i++;
    }        
    prompt = NULL;
    stack = NULL;
    while (1)
    {
        prompt = readline(">");
        if (!ft_strncmp(prompt, split[i + 1], ft_strlen(split[i + 1])))
            break;
        stack = ft_strjoin(stack, prompt);
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
                par->in.file = split[i + 1];
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

t_parser    *init_par_index(int len)
{
    t_parser    *par;
    t_parser    *temp;
    t_parser    *temp2;
    int         i;

    i = 0;
    par = malloc(sizeof(t_parser));
    if (!par)
        return (NULL);
    par->index = i++;
    par->len_pip = len;
    par->prev = NULL;
    temp2 = par;
    while (i < len)
    {
        temp = malloc(sizeof(t_parser));
        temp->index = i++;
        temp->len_pip = len;
        temp2->next = temp;
        temp2 = temp2->next;
        temp2->prev = temp;
    }
    temp2->next = NULL;
    return (par);
}

void    init_parser(t_parser *par, char *pip)
{
    char    **splited;
    char    *tks_pipe;

    splited = split(pip);
    tks_pipe = init_tokens(pip);
    init_active_tokens(&tks_pipe, pip);
    
}
