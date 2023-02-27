/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smessal <smessal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/19 11:42:00 by smessal           #+#    #+#             */
/*   Updated: 2023/02/27 10:54:32 by smessal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void    printer(t_cmdtab *tab)
{
    t_cmdtab    *temp;

    temp = tab;
    while (temp)
    {
        if (temp->cmd)
            printf("abs_path: %s\n", temp->cmd);
        if (temp->opt)
        {
            for (int i = 0; temp->opt[i]; i++)
                printf("option_%d %s\n", i, temp->opt[i]);
        }
        temp = temp->next;
    }
}

void	throw_error(t_file *f)
{
	if (f && f->fd < 0)
	{
		ft_putstr_fd("minishell: ", 2);
		if (access(f->file, F_OK | X_OK) == -1)
			perror(f->file);
		g_status = 1;
	}
}

t_cmdtab    *parser(char **lexer)
{
	int			i;
	char		**spl;
	t_cmdtab	*tab;

	i = 0;
	tab = NULL;
	spl = NULL;
	while (lexer && lexer[i])
	{
		spl = NULL;
		spl = split(lexer[i]);
		if (!syntax_err_redir(spl))
			return (NULL);
		lst_addback_cmd(&tab, lstnew_cmd(spl, i));
		i++;
	}
	// if (tab->in->fd && tab->out->fd)
		// printf()
	return (tab);
}
