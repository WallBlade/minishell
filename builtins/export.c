/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smessal <smessal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/05 17:19:32 by zel-kass          #+#    #+#             */
/*   Updated: 2023/02/27 13:31:27 by smessal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	existing_var(char **env, char *var_exp)
{
	int	i;

	i = 0;
	while (env && env[i])
	{
		if (!ft_strncmp(var_exp, env[i], ft_strchr(env[i], '='))
			&& ft_strchr(var_exp, '=') == ft_strchr(env[i], '='))
			return (1);
		i++;
	}
	i = 0;
	while (env && env[i])
	{
		if (!ft_strchr(var_exp, '=') || !ft_strchr(env[i], '='))
		{
			if (!ft_strchr(env[i], '=')
				&& !ft_strncmp(env[i], var_exp, ft_strlen(env[i])))
				return (1);
			else if (ft_strchr(env[i], '=')
				&& !ft_strncmp(env[i], var_exp, ft_strchr(env[i], '=')))
				return (2);
		}
		i++;
	}
	return (0);
}

char	**multi_export(char **env, char *var_exp)
{
	int		i;
	char	**exported;

	i = 0;
	if (!existing_var(env, var_exp))
		exported = collect(sizeof(char *) * (len_tab(env) + 2));
	else
		exported = collect(sizeof(char *) * (len_tab(env) + 1));
	if (!exported)
		return (NULL);
	if (existing_var(env, var_exp) == 1)
		env = unset(env, get_varname(var_exp, 0, ft_strchr(var_exp, '=')));
	while (env && env[i])
	{
		exported[i] = ft_strdup(env[i]);
		i++;
	}
	if (existing_var(env, var_exp) != 2)
		exported[i++] = ft_strdup(var_exp);
	exported[i] = NULL;
	return (exported);
}

char	**export(char **env, char **var_exp)
{
	int		j;
	char	**exported;

	j = 1;
	exported = collect(sizeof(char *) * (len_tab(env) + len_tab(var_exp) + 1));
	if (!exported)
		return (NULL);
	while (env && var_exp && var_exp[j])
	{
		if (!error_export(var_exp[j]))
		{
			exported = multi_export(env, var_exp[j]);
			g_status = 0;
			env = ft_strdup_tab(exported);
		}
		else
		{
			error_export_print(var_exp[j]);
			exported = ft_strdup_tab(env);
		}
		j++;
	}
	return (exported);
}
