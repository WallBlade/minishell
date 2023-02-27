/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zel-kass <zel-kass@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/26 15:54:43 by smessal           #+#    #+#             */
/*   Updated: 2023/02/27 15:16:09 by zel-kass         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	unclosed_quotes(char *prompt)
{
	int	i;
	int	dominant;

	i = -1;
	dominant = 0;
	while (prompt && prompt[++i])
	{
		if (prompt[i] == '"' && dominant != 3)
		{
			if (dominant == 1)
				dominant = 0;
			else
				dominant = 1;
		}
		else if (prompt[i] == '\'' && dominant != 1)
		{
			if (dominant == 3)
				dominant = 0;
			else
				dominant = 3;
		}
	}
	return (dominant);
}

int	is_unvalid(char c)
{
	int		i;
	char	*unvalid;
	int		result;

	unvalid = allocate_str(";\\(){}");
	i = 0;
	result = 0;
	while (unvalid && unvalid[i])
	{
		if (unvalid[i] == c)
			result = 1;
		i++;
	}
	return (result);
}

int	unvalid_char(char *prompt, t_tks *tks)
{
	char	*unvalid;
	int		i;

	i = 0;
	unvalid = allocate_str(";\\(){}&");
	while (prompt && prompt[i])
	{
		if (is_unvalid(prompt[i]) && !in_quotes(tks, prompt, i))
			return (1);
		i++;
	}
	return (0);
}

int	pipe_end(char *prompt, t_tks *tks)
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
			if (!prompt[i])
				return (1);
		}
		if (prompt[i])
			i++;
	}
	return (0);
}

int	consecutive_redir(char *prompt, t_tks *tks)
{
	int		i;
	int		count;
	char	c;

	i = 0;
	while (prompt && prompt[i])
	{
		count = 0;
		if ((prompt[i] == '<' || prompt[i] == '>')
			&& !in_quotes(tks, prompt, i))
		{
			c = prompt[i++];
			count++;
			while (prompt[i] && prompt[i] == c)
			{
				count++;
				i++;
			}
			if (count > 2)
				return (1);
		}
		if (prompt[i])
			i++;
	}
	return (0);
}
