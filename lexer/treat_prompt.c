/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   treat_prompt.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zel-kass <zel-kass@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/12 23:01:19 by smessal           #+#    #+#             */
/*   Updated: 2022/12/15 17:18:33 by zel-kass         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// int	count_pipes(char *str, t_tks *tks)
// {
// 	int	i;
// 	int	j;
// 	int	count;

// 	i = 0;
// 	j = 0;
// 	count = 0;
// 	while (str && str[i])
// 	{
// 		if (str[i] == '|' && tks->p[j++] == 1)
// 			count++;
// 		i++;
// 	}
// 	return (count + 1);
// }

// int	*pipe_strlen(char *str, t_tks *tks)
// {
// 	int	i;
// 	int	j;
// 	int	count;
// 	int	*lens;

// 	i = 0;
// 	j = 0;
// 	count = 0;
// 	lens = malloc(sizeof(int) * (count_pipes(str, tks)));
// 	if (!lens)
// 		return (0);
// 	while (str && str[i])
// 	{
// 		if (str[i] == '|' && tks->p && tks->p[j] == 1)
// 		{
// 			lens[j] = count;
// 			count = 0;
// 			j++;
// 		}
// 		i++;
// 		count++;
// 	}
// 	lens[j] = count;
// 	return (lens);
// }

// char	**split_2_ouf(char *str, t_tks *tks)
// {
// 	int		i;
// 	int		j;
// 	int		k;
// 	int		*len;
// 	char	**sdf;

// 	i = -1;
// 	k = 0;
// 	len = pipe_strlen(str, tks);
// 	sdf = malloc(sizeof(char *) * (count_pipes(str, tks) + 1));
// 	if (!sdf)
// 		return (NULL);
// 	while (++i < count_pipes(str, tks))
// 	{
// 		sdf[i] = malloc(sizeof(char) * (len[i] + 1));
// 		if (!sdf[i])
// 			return (free_tab(sdf), NULL);
// 		j = 0;
// 		while (j < len[i] && str[k] != '|')
// 			sdf[i][j++] = str[k++];
// 		sdf[i][j] = '\0';
// 		k++;
// 	}
// 	sdf[i] = 0;
// 	return (free(len), sdf);
// }

int	cwords(char *str)
{
	int		i;
	int		count;
	char	c;
	
	i = 0;
	count = 0;
	while (str && str[i])
	{
		if (str[i] && (str[i] == '"' || str[i] == '\''))
		{
			c = str[i];
			count++;
			i++;
			while (str[i] && str[i] != c)
				i++;
			i++;
		}
		else if (str[i] && (str[i] != ' ' && str[i] != '\t'))
		{
			count++;
			while (str[i] && (str[i] != ' ' && str[i] != '\t'))
				i++;
		}
		while (str[i] && (str[i] == ' ' || str[i] == '\t'))
			i++;
	}
	return (count);
}

// int	ft_wdlen(char *str, int i)
// {
// 	int		len;
// 	char	c;

// 	len = 0;
// 	if (str[i] == '"' || str[i] == '\'')
// 	{
// 		c = str[i];
// 		i++;
// 		while (str[i] != c)
// 		{
// 			i++;
// 			len++;
// 		}
// 		return (len);
// 	}
// 	else
// 	{
// 		while (str[i] )

// }

// char	**split(char *str)
// {
// 	int		*q;
// 	int		*dq;
// 	char	**spl;

// 	q = malloc(sizeof(int) * count_elem(str, '\''));
// 	dq = malloc(sizeof(int) * count_elem(str, '"'));
// 	get_squotes(str, q);
// 	get_dquotes(str, dq);
// 	spl = malloc(sizeof(char *) * (cwords() + 1));
// 	if (!spl)
// 		return (NULL);
// }

// int main(int argc, char **argv)
// {
// 	(void)argc;
// 	printf("%d\n", cwords(argv[1]));
// 	return (0);
// }