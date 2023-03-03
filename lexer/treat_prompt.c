/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   treat_prompt.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zel-kass <zel-kass@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/12 23:01:19 by smessal           #+#    #+#             */
/*   Updated: 2023/03/03 19:30:43 by zel-kass         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*fill_2_ouf(char *str, int len, int *k)
{
	int		j;
	char	*ret;

	ret = collect(sizeof(char) * (len + 1));
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
		if ((prompt[i] == '>' || prompt[i] == '<')
			&& (prompt[i + 1] != '<' && prompt[i + 1] != '>'))
		{
			if (!in_quotes(tks, prompt, i))
				if (prompt[i + 1] && prompt[i + 1] != ' '
					&& prompt[i + 1] != '\t')
				len += 2;
		}
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
	clean = collect(sizeof(char) * (compute_new_len(prompt, tks) + 1));
	if (!clean)
		return (NULL);
	while (prompt[i])
	{
		if ((prompt[i] == '<' || prompt[i] == '>')
			&& (prompt[i + 1] != '<' && prompt[i + 1] != '>')
			&& (!in_quotes(tks, prompt, i)))
		{
			if (prompt[i + 1] && prompt[i + 1] != ' ' && prompt[i + 1] != '\t')
			{
				clean[j++] = ' ';
				clean[j++] = prompt[i++];
				clean[j++] = ' ';
			}
		}
		clean[j++] = prompt[i++];
	}
	return (clean[j] = '\0', clean);
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
