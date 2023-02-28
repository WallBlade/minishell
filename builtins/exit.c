/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smessal <smessal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/17 15:45:23 by smessal           #+#    #+#             */
/*   Updated: 2023/02/27 19:48:48 by smessal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exit_bin(t_cmdtab *tab, t_data *data)
{
	if (data->p_count == 1)
		ft_putstr_fd("exit\n", 1);
	if (tab->opt && tab->opt[1])
	{
		if (is_numeric(tab->opt[1]) && len_tab(tab->opt) > 2)
		{
			g_status = 1;
			ft_putstr_fd("minishell: exit: too many arguments\n", 2);
		}
		else if (!is_numeric(tab->opt[1]) && len_tab(tab->opt) >= 2)
		{
			ft_putstr_fd("minishell: exit: numeric argument required\n", 2);
			free_gc();
			exit(2);
		}
		else if (is_numeric(tab->opt[1]) && len_tab(tab->opt) == 2)
		{
			g_status = ft_atoi(tab->opt[1]) % 256;
			free_gc();
			exit(g_status);
		}
	}
	else
	{
		free_gc();
		exit(g_status);
	}
}
