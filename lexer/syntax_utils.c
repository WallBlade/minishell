/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smessal <smessal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 15:15:47 by zel-kass          #+#    #+#             */
/*   Updated: 2023/02/27 17:13:43 by smessal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	consecutive_pipes(char *prompt, t_tks *tks)
{
	int	i;

	i = 0;
	while (prompt && prompt[i])
	{
		if (prompt[i] == '|' && !in_quotes(tks, prompt, i))
		{
			i++;
			while (prompt[i] && (prompt[i] == ' ' || prompt[i] == '\t'))
				i++;
			if (prompt[i] && prompt[i] == '|')
				return (1);
		}
		if (prompt[i])
			i++;
	}
	return (0);
}

int	empty_string(char *expanded)
{
	int	i;

	i = 0;
	while (expanded && expanded[i])
	{
		if (expanded[i] != '"' && expanded[i] != '\'')
			return (0);
		i++;
	}
	if (ft_strlen(expanded) > 1)
		return (1);
	else
		return (0);
}

int	syntax_error(char *prompt, t_tks *tks)
{
	if (unclosed_quotes(prompt))
		return (1);
	else if (unvalid_char(prompt, tks))
		return (1);
	else if (pipe_end(prompt, tks))
		return (1);
	else if (consecutive_pipes(prompt, tks) || consecutive_redir(prompt, tks))
		return (1);
	else if (empty_string(prompt))
		return (2);
	return (0);
}

int	syntax_err_redir(char **split)
{
	int	i;

	i = 0;
	while (split && split[i])
	{
		if (is_redir(split[i]))
		{
			if (!split[i + 1] || is_redir(split[i + 1]))
			{
				g_status = 2;
				ft_putstr_fd("minishell: syntax error ", 2);
				ft_putstr_fd("near unexpected token ", 2);
				ft_putstr_fd(split[i], 2);
				ft_putstr_fd("\n", 2);
				return (0);
			}
		}
		i++;
	}
	return (1);
}
