/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_error2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zel-kass <zel-kass@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/26 15:54:43 by smessal           #+#    #+#             */
/*   Updated: 2023/02/26 18:03:07 by zel-kass         ###   ########.fr       */
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

int	consecutive_pipes(char *prompt, t_tks *tks)
{
	int		i;
	
	i = 0;	
	while (prompt && prompt[i])
	{
		if (prompt[i] == '|' && !in_quotes(tks, prompt, i))
		{
			i++;
			if (prompt[i] && prompt[i] == '|')
				return (1);
		}
		if (prompt[i])
			i++;
	}
	return (0);
}

int	syntax_error(char *prompt, t_tks *tks)
{
	if (unclosed_quotes(prompt))
	{
		ft_putstr_fd("Unclosed quotes\n", 2);
		return (1);
	}
	else if (unvalid_char(prompt, tks))
	{
		ft_putstr_fd("Unvalid char\n", 2);
		return (1);
	}
	else if (pipe_end(prompt, tks))
	{
		ft_putstr_fd("Pipe not followed by command\n", 2);
		return (1);
	}
	else if (consecutive_pipes(prompt, tks) || consecutive_redir(prompt, tks))
	{
		ft_putstr_fd("Consecutive pipes or redirections\n", 2);
		return (1);
	}
	return (0);
}
// int	redir_null(char *prompt, t_tks *tks)
// {
// 	int	i;
	
// 	i = 0;
// 	while (prompt && prompt[i])
// 	{
// 		if ((prompt[i] == '<' || prompt[i] == '>') && !in_quotes(tks, prompt, i))
// 		{
// 			i++;
// 			while (prompt[i] && prompt[i])
// 		}
// 	}
// }