/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zel-kass <zel-kass@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/19 11:42:00 by smessal           #+#    #+#             */
/*   Updated: 2023/02/27 17:12:24 by zel-kass         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

t_cmdtab	*parser(char **lexer)
{
	int			i;
	char		**spl;
	t_cmdtab	*tab;

	i = 0;
	tab = NULL;
	spl = NULL;
	g_status = 0;
	while (lexer && lexer[i])
	{
		spl = NULL;
		spl = split(lexer[i]);
		if (!syntax_err_redir(spl))
			return (NULL);
		lst_addback_cmd(&tab, lstnew_cmd(spl, i));
		i++;
	}
	if (g_status == 130)
		return (NULL);
	return (tab);
}
