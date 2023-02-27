/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_print.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smessal <smessal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/17 12:22:12 by smessal           #+#    #+#             */
/*   Updated: 2023/02/27 13:30:10 by smessal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_strdup_quote(char *env)
{
	int		i;
	int		j;
	char	*quote;
	int		first;

	i = -1;
	j = 0;
	first = 1;
	quote = collect(sizeof(char) * (ft_strlen(env) + 3));
	if (!quote)
		return (NULL);
	while (env && env[++i])
	{
		quote[j] = env[i];
		if (env[i] == '=' && first)
		{
			quote[++j] = '"';
			first = 0;
		}
		j++;
	}
	if (!first)
		quote[j++] = '"';
	quote[j] = '\0';
	return (quote);
}

char	**converted_env(char **env)
{
	int		i;
	char	**converted;

	i = 0;
	converted = collect(sizeof(char *) * (len_tab(env) + 1));
	if (!converted)
		return (NULL);
	while (env && env[i])
	{
		converted[i] = ft_strdup_quote(env[i]);
		i++;
	}
	converted[i] = NULL;
	return (converted);
}

void	print_export(t_cmdtab *tab, char **env)
{
	int		i;
	int		fd;
	char	**env_export;

	i = 0;
	fd = 1;
	if (tab->out && tab->out->fd)
		fd = tab->out->fd;
	env_export = converted_env(env);
	while (env_export && env_export[i])
	{
		ft_putstr_fd("export ", fd);
		ft_putstr_fd(env_export[i], fd);
		ft_putstr_fd("\n", fd);
		i++;
	}
	g_status = 0;
	if (fd > 1)
		close(fd);
}
