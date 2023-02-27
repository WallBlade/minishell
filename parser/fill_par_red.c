/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_par_red.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zel-kass <zel-kass@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/20 22:33:29 by smessal           #+#    #+#             */
/*   Updated: 2023/02/27 12:03:52 by zel-kass         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	fds_ok(t_cmdtab *tab)
{
	t_file	*in;
	t_file	*out;

	in = NULL;
	out = NULL;
	if (tab && tab->in)
		in = tab->in;
	if (tab && tab->out)
		out = tab->out;
	while (in && in->next)
		in = in->next;
	if (in && in->fd && in->fd < 0)
		return (0);
	while (out && out->next)
		out = out->next;
	if (out && out->fd && out->fd < 0)
		return (0);
	return (1);
}

void	init_files(t_cmdtab *tab, char **spl)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (spl[i])
	{
		if (is_redir(spl[i]) == HERE_DOC && spl[i + 1])
			lst_addback_red(&tab->in, fill_hd(HERE_DOC, spl[i + 1], tab, count++));
		else if (fds_ok(tab))
		{
			if (is_redir(spl[i]) == REDIR_IN && spl[i + 1])
				lst_addback_red(&tab->in, fill_in(REDIR_IN, spl[i + 1]));
			else if (is_redir(spl[i]) == REDIR_OUT && spl[i + 1])
				lst_addback_red(&tab->out, fill_out(REDIR_OUT, spl[i + 1]));
			else if (is_redir(spl[i]) == APPEND && spl[i + 1])
				lst_addback_red(&tab->out, fill_out(APPEND, spl[i + 1]));
		}
		i++;
	}
	close_fds(tab);
	throw_error(tab->in);
	throw_error(tab->out);	
}

t_file	*fill_in(int op, char *file)
{
	t_file	*in;
	
	in = collect(sizeof(t_file));
	if (!in)
		return (NULL);
    in->op = op;
    in->fd = 0;
    if (file)
    {
		in->file = ft_strdup(file);
		in->fd = open(in->file, O_RDONLY);
	}
	else
		in->file = NULL;
	in->next = NULL;
	return (in);
}

t_file	*fill_out(int op, char *file)
{
	t_file	*out;
	
	out = collect(sizeof(t_file));
	if (!out)
		return (NULL);
	out->op = op;
	out->fd = 1;
	if (file)
	{
		out->file = ft_strdup(file);
		if (op == REDIR_OUT)
			out->fd = open(out->file, O_RDWR | O_CREAT | O_TRUNC, 0664);
		else if (op == APPEND)
			out->fd = open(out->file, O_RDWR | O_APPEND | O_CREAT, 0664);
	}
	else
		out->file = NULL;
	out->next = NULL;
	return(out);
}

int is_redir(char *arg)
{
    if (!ft_strncmp(arg, "<", ft_strlen(arg)))
        return(REDIR_IN);
    else if (!ft_strncmp(arg, ">", ft_strlen(arg)))
        return (REDIR_OUT);
    else if (!ft_strncmp(arg, ">>", ft_strlen(arg)))
        return (APPEND);
    else if (!ft_strncmp(arg, "<<", ft_strlen(arg)))
        return (HERE_DOC);
    return (0);
}
