/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smessal <smessal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/05 20:04:13 by smessal           #+#    #+#             */
/*   Updated: 2023/01/05 20:22:58 by smessal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_varname(char *prompt, int start, int end)
{
	char	*var;
	int		i;
	
	i = 0;
	var = malloc(sizeof(char) * (end - start + 1));
	if (!var)
		return (NULL);
	if (end - start == 1)
	{
		var[0] = '$';
		var[1] = NULL;
	}
	else
	{
		while (prompt && prompt[start] && start < end)
		{
			var[i] = prompt[start];
			i++;
			start++;
		}
	}
	return (var);
}

char	*get_var(char *prompt, char **env, int start, int end)
{
	char	*varname;
	char	*var;
	int		i;

	varname = get_varname(prompt, start, end);
	var = NULL;
	i = 0;
	while (env && env[i] && varname)
	{
		if (!ft_strncmp(varname, env[i], ft_strlen(varname)))
			var = ft_strdup(&env[i + ft_strlen(varname) + 1]);
		i++;
	}
	return (var);
}

int	len_expand(char *prompt, t_tks *tks, char **env)
{
	int		i;
	int		j;
	int		len;
	int		start;
	char	*var;

	i = 0;
	j = 0;
	len = 0;
	while (prompt && prompt[i])
	{
		if (prompt[i] == '$' && tks->dol[j++])
		{
			start = i++;
			while (prompt[i] != ' ' && !is_token(prompt[i]))
				i++;
			var = get_var(prompt, env, start, i);
			len += ft_strlen(var);
			free(var);		
		}
		else
		{
			i++;
			len++;
			
		}		
	}
	return (len);
}

char	*expand(char *prompt, char **env, tks *tks)
{
	char    *expanded;
    int     i;
    int     j;
    int     k;
    int     l;

    i = 0;
    j = 0;
    k = 0;
    l = 0;
    expanded = malloc(sizeof(char) * (len_expand(prompt, tks, env) + 1));
    if (!expanded)
        return (NULL);
    while (prompt && prompt[i])
	{
		if (prompt[i] == '$' && tks->dol[l++])
		{
			start = i++;
			while (prompt[i] != ' ' && !is_token(prompt[i]))
				i++;
			var = get_var(prompt, env, start, i);
			while (var[k])
                expanded[j++] = var[k++];
			free(var);		
		}
        expanded[j++] = prompt[i++];
    }
    return (expanded);
}
