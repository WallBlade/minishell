/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   treat_prompt.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smessal <smessal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/12 23:01:19 by smessal           #+#    #+#             */
/*   Updated: 2023/02/14 16:54:47 by smessal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*fill_2_ouf(char *str, int len, int *k)
{
	int		j;
	char	*ret;

	ret = malloc(sizeof(char) * (len + 1));
	if (!ret)
		return (NULL);
	j = 0;
	while (j < len)
	{
		ret[j++] = str[*k];
		*k += 1;
	}
	ret[j] = '\0';
	*k = *k + 1;
	return (ret);
}

int	compute_new_len(char *prompt, t_tks *tks)
{
	int	i;
	int	len;

	i = 0;
	len = 0;
	while (prompt && prompt[i])
	{
		if ((prompt[i] == '>' || prompt[i] == '<') && (prompt[i + 1] != '<' && prompt[i + 1] != '>')
			&& (!in_quotes(tks->q, tks->dq, i)))
			if (prompt[i + 1] && prompt[i + 1] != ' ' && prompt[i + 1] != '\t')
				len++;
		i++;
		len++;
	}
	return (len);
}

char	*clean_2_ouf(char *prompt, t_tks *tks)
{
	int		i;
	int		j;
	char	*clean;

	i = 0;
	j = 0;
	clean = malloc(sizeof(char) * (compute_new_len(prompt, tks) + 1));
	if (!clean)
		return (NULL);
	while (prompt[i])
	{
		if ((prompt[i] == '<' || prompt[i] == '>') && (prompt[i + 1] != '<' && prompt[i + 1] != '>')
			&& (!in_quotes(tks->q, tks->dq, i)))
		{
			if (prompt[i + 1] && prompt[i + 1] != ' ' && prompt[i + 1] != '\t')
			{
				clean[j++] = prompt[i++];
				clean[j++] = ' ';
			}
		}
		clean[j++] = prompt[i++];
	}
	clean[j] = '\0';
	return (clean);
}

int	rep_tok(char *str)
{
	int		i;
	int		j;
	int		len;
	char	*tok;

	i = 0;
	len = 0;
	tok = "<>()\\;";
	while (tok && tok[i])
	{
		j = 0;
		while (str && str[j])
		{
			if (tok[i] == str[j])
				len++;
			if (str[j] == ';' || str[j] == '\\')
				return (5);
			j++;
		}
		i++;
	}
	return (len);
}

int	is_syntax_tok(char *str)
{
	int		i;
	int		j;
	char	*tok;

	i = 0;
	j = 0;
	tok = "<>|()\\;";
	if (str && str[i] && (str[i] == '"' || str[i] == '\''))
		return (0);
	while (str && str[i])
	{	
		j = 0;
		while (tok[j])
		{
			if (str[i] == tok[j])
				return (1);
			j++;
		}
		i++;
	}
	return (0);
}

void	print_syntax_error(char *tok)
{
	ft_putstr_fd("minishell: syntax error near unexpected token ", 2);
	ft_putstr_fd(tok, 2);
	ft_putstr_fd("\n", 2);
}

int	scan_2_ouf(char **sdf)
{
	int	i;

	i = 0;
	while (sdf && sdf[i])
	{
		if (sdf[i][0] && sdf[i][0] != '"' && sdf[i][0] != '\'')
		{
			if (sdf[i + 1] && is_syntax_tok(sdf[i]) && is_syntax_tok(sdf[i + 1]))
			{
				status = 2;
				print_syntax_error(sdf[i + 1]);
				return(free_tab(sdf), 0);
			}
			else if ((is_syntax_tok(sdf[i]) && !sdf[i + 1]) || (rep_tok(sdf[i]) > 2))
			{
				status = 2;
				print_syntax_error(sdf[i]);
				return(free_tab(sdf), 0);
			}
		}
		else if ((sdf[i][0] == '"' || sdf[i][0] == '\'')
			&& (sdf[i][ft_strlen(sdf[i]) - 1] != '"' && sdf[i][ft_strlen(sdf[i]) - 1] != '\''))
		{
			status = 2;
			ft_putstr_fd("minishell: syntax error, quotes not closed\n", 2);
			return (free_tab(sdf), 0);
		}
		i++;
	}
	if (sdf)
		free_tab(sdf);
	return (1);
}

char	**split_2_ouf(char *str, t_tks *tks)
{
	int		i;
	int		k;
	int		*len;
	char	**sdf;

	i = -1;
	k = 0;
	len = pipe_strlen(str, tks);
	if (!len)
		return (NULL);
	sdf = malloc(sizeof(char *) * (count_pipes(str, tks) + 1));
	if (!sdf)
		return (NULL);
	while (++i < count_pipes(str, tks) && len && len[i])
		sdf[i] = fill_2_ouf(str, len[i], &k);
	sdf[i] = 0;
	if (len)
		free(len);
	return (sdf);
}

char	**split(char *str)
{
	int		i;
	int		j;
	char	**spl;

	spl = malloc(sizeof(char *) * (cwords(str) + 1));
	if (!spl)
		return (NULL);
	i = -1;
	j = 0;
	while (++i < cwords(str))
	{
		while ((str[j] == ' ' || str[i] == '\t')
			&& (str[j] != '"' && str[j] != '\''))
			j++;
		if ((str[j] != ' ' && str[j] != '\t')
			|| (str[j] == '"' || str[j] == '\''))
		{
			spl[i] = fill_wrd(str, &j);
			if (!spl[i])
				return (free_tab(spl), NULL);
		}
	}
	spl[i] = 0;
	return (spl);
}
