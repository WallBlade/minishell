/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zel-kass <zel-kass@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/05 20:04:13 by smessal           #+#    #+#             */
/*   Updated: 2023/02/15 16:41:41 by zel-kass         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_varname(char *prompt, int start, int end)
{
	char	*varname;
	int		i;

	i = 0;
	varname = malloc(sizeof(char) * (end - start + 1));
	if (!varname)
		return (NULL);
	while (prompt && prompt[start] && start < end)
	{
		varname[i] = prompt[start];
		i++;
		start++;
	}
	varname[i] = '\0';
	return (varname);
}

int	find_varname_env(char *var, char *env_var)
{
	if (env_var && var && env_var[ft_strlen(var)]
		&& env_var[ft_strlen(var)] == '='
		&& !ft_strncmp(var, env_var, ft_strlen(var)))
		return (1);
	else
		return (0);
}

char	*expand_err_code(char *prompt, int start, int end)
{
	int		i;
	int		j;
	int		len;
	char	*expanded;
	char	*str_status;

	i = 0;
	j = 0;
	str_status = ft_itoa(g_status);
	len = ft_strlen(str_status);
	start++;
	expanded = malloc(sizeof(char) * (len + (end - start) + 1));
	if (!expanded)
		return (NULL);
	while (str_status && str_status[j])
		expanded[i++] = str_status[j++];
	while (prompt && prompt[start] && start < end)
		expanded[i++] = prompt[start++];
	expanded[i] = '\0';
	if (str_status)
		free(str_status);
	return (expanded);
}

char	*get_var(char *prompt, char **env, int start, int end)
{
	char	*varname;
	char	*var;
	int		i;

	varname = get_varname(prompt, start, end);
	var = NULL;
	if (prompt[start] == '?')
		var = expand_err_code(prompt, start, end);
	else if (!varname[0] && start == end)
		var = allocate_str("$");
	else if (!varname[0])
		var = allocate_str("\n");
	i = 0;
	while (env && env[i] && varname && varname[0])
	{
		if (find_varname_env(varname, env[i]))
			var = ft_strdup(&env[i][ft_strlen(varname) + 1]);
		i++;
	}
	if (varname)
		free(varname);
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
			start = ++i;
			while (prompt[i] && prompt[i] != ' ' && !is_token(prompt[i]))
				i++;
			var = get_var(prompt, env, start, i);
			len += ft_strlen(var);
			if (var)
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

t_expand	*init_expand(char **env)
{
	t_expand	*exp;

	exp = malloc(sizeof(t_expand));
	if (!exp)
		return (NULL);
	exp->env = env;
	exp->i = 0;
	exp->j = 0;
	exp->k = 0;
	exp->l = 0;
	return (exp);
}

char	*expand(char *prompt, char **env, t_tks *tks)
{
	char	*expanded;
	int		i;
	int		j;
	int		k;
	int		l;
	int		start;
	char	*var;

	i = 0;
	j = 0;
	k = 0;
	l = 0;
	start = 0;
	expanded = malloc(sizeof(char) * (len_expand(prompt, tks, env) + 1));
	if (!expanded)
		return (NULL);
	while (prompt && prompt[i])
	{
		k = 0;
		if (prompt[i] == '$' && tks->dol[l++])
		{
			start = ++i;
			while (prompt[i] && prompt[i] != ' ' && !is_token(prompt[i]))
				i++;
			var = get_var(prompt, env, start, i);
			while (var && var[k])
				expanded[j++] = var[k++];
			if (var)
				free(var);
		}
		else
			expanded[j++] = prompt[i++];
	}
	expanded[j] = '\0';
	return (expanded);
}
