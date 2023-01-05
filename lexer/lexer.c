/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smessal <smessal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 14:39:34 by smessal           #+#    #+#             */
/*   Updated: 2023/01/05 18:15:10 by smessal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	count_elem(char *str, char c)
{
	int	i;
	int	len;

	i = 0;
	len = 0;
	while (str && str[i])
	{
		if ((c == '<' || c == '>') && str[i + 1] &&
			str[i] == c && str[i + 1] == c)
			i++;
		else if (str[i] && str[i] == c)
			len++;
		i++;
	}	
	return (len);
}

int	count_d_elem(char *str, char *sub)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (str && str[i] && str[i + 1])
	{
		if (!ft_strncmp(&str[i], sub, 2))
		{
			count++;
			i++;
		}
		i++;
	}
	return (count);
}

int	is_token(char c)
{
	char	*tok;
	int		i;

	i = 0;
	tok = "<>|\"'$?";
	while (tok[i])
	{
		if (tok[i] == c)
			return (1);
		i++;
	}
	return (0);
}

char	*get_var(char *prompt, char **env)
{
	int	
}

int	len_expand(char *prompt, t_tks *tks, char **env)
{
	int	i;
	int	j;
	int	len;

	i = 0;
	j = 0;
	len = 0;
	while (prompt && prompt[i])
	{
		if (prompt[i] == '$' && tks->dol[j++])
		{
			while (prompt[i] != ' ' && !is_token(prompt[i]))
				i++;
			len += 
		}
	}
}

char	*str_expand(char *prompt, char **env)
{
	
}

char	*expand(char *prompt, t_tks *tks, char **env)
{
	int		i;
	int		j;
	char	*expd;
	
	i = 0;
	j = 0;
	while (prompt[i])
	{
		if (prompt[i] == '$' && tks->dol[j++])
		{
			
		}
			
	}
}

char	**lexer(char *prompt)
{
	t_tks		*tks;
	
	tks = init_tokens(prompt);
	init_active_tokens(&tks, prompt);
	char **sdf = split_2_ouf(clean_2_ouf(prompt, tks), tks);
	return (sdf);
}

// int	main()
// {
// 	t_tks		*tks;
// 	t_cmdtab	*par;
// 	char	*prompt;

// 	par = malloc(sizeof(t_cmdtab));
// 	while (1)
// 	{
// 		prompt = readline("minishell> ");
// 		tks = init_tokens(prompt);
// 		init_active_tokens(&tks, prompt);
// 		char **sdf = split_2_ouf(clean_2_ouf(prompt, tks), tks);
// 		for (int i = 0; sdf[i]; i++)
// 		{
// 			char **spl = split(sdf[i]);
// 			par->in.fd = 0;
// 			fill_in(&par, spl);
// 			fill_out(par, spl);
// 			char **paths = get_paths();
// 			par->opt = get_opt(spl);
// 			par->cmd = get_abs_path(paths, par->opt);
// 		}
// 		add_history(prompt);
// 	}
// 	rl_clear_history();
// }
