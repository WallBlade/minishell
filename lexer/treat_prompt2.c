/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   treat_prompt2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smessal <smessal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 15:37:51 by zel-kass          #+#    #+#             */
/*   Updated: 2023/02/28 15:57:10 by smessal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

void	print_syntax_error(char tok)
{
	ft_putstr_fd("minishell: syntax error near unexpected token ", 2);
	ft_putchar_fd(tok, 2);
	ft_putstr_fd("\n", 2);
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
	sdf = collect(sizeof(char *) * (count_pipes(str, tks) + 1));
	if (!sdf)
		return (NULL);
	while (++i < count_pipes(str, tks) && len && len[i])
		sdf[i] = fill_2_ouf(str, len[i], &k);
	sdf[i] = 0;
	return (sdf);
}

char	**split(char *str)
{
	int		i;
	int		j;
	char	**spl;

	spl = NULL;
	spl = collect(sizeof(char *) * (cwords(str) + 1));
	if (!spl)
		return (NULL);
	i = -1;
	j = 0;
	while (++i < cwords(str))
	{
		while (str[j] == ' ' || str[j] == '\t')
			j++;
		if (str[j] != ' ' && str[j] != '\t')
		{
			spl[i] = fill_wrd(str, &j);
			if (!spl[i])
				return (NULL);
		}
	}
	spl[i] = 0;
	return (spl);
}
