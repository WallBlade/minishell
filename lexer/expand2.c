/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zel-kass <zel-kass@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 12:48:34 by smessal           #+#    #+#             */
/*   Updated: 2023/03/06 20:03:47 by zel-kass         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_varname(char *prompt, int start, int end)
{
	char	*varname;
	int		i;

	i = 0;
	varname = collect(sizeof(char) * (end - start + 1));
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
	if (env_var && var && !ft_strncmp(var, env_var, ft_strlen(var))
		&& ft_strchr(env_var, '=') == ft_strlen(var))
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
	expanded = collect(sizeof(char) * (len + (end - start) + 1));
	if (!expanded)
		return (NULL);
	while (str_status && str_status[j])
		expanded[i++] = str_status[j++];
	while (prompt && prompt[start] && start < end)
		expanded[i++] = prompt[start++];
	expanded[i] = '\0';
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
	return (var);
}
